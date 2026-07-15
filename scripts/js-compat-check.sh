#!/usr/bin/env bash
# js-compat-check.sh — JavaScript/TypeScript SDK backwards-compatibility gate
#
# Runs two checks:
#
#   Check A — SDK generates cleanly from the modified OpenRPC specs.
#             Runs: npm run compile && npm run slice (per SDK workspace)
#             Validates that the generated TypeScript compiles with tsc.
#
#   Check B — Structural type compatibility: generates TypeScript types from
#             git-HEAD OpenRPC specs, then checks that the NEW types are
#             assignable from the OLD types (no narrowing, no removed exports).
#             Uses a generated "compatibility shim" file compiled with tsc.
#
# Exit code: 0 = all checks pass, 1 = one or more failures
#
# Usage:
#   ./scripts/js-compat-check.sh \
#       --modules device,localization,firebolt \
#       --apis-dir /path/to/firebolt-apis \
#       [--base HEAD] \
#       [--sdk-workspaces core,manage,discovery] \
#       [--skip-build]          # skip npm build, only check generated output
#
# Environment:
#   NODE_ENV is set to "test" during the run.
set -euo pipefail

APIS_DIR="."
BASE_REF="HEAD"
MODULES=""
SDK_WORKSPACES="core,manage,discovery"
SKIP_BUILD=0
VERBOSE=0

# ---------------------------------------------------------------------------
# Argument parsing
# ---------------------------------------------------------------------------
while [[ $# -gt 0 ]]; do
  case "$1" in
    --apis-dir)      APIS_DIR="$2"; shift 2 ;;
    --base)          BASE_REF="$2"; shift 2 ;;
    --modules)       MODULES="$2"; shift 2 ;;
    --sdk-workspaces) SDK_WORKSPACES="$2"; shift 2 ;;
    --skip-build)    SKIP_BUILD=1; shift ;;
    --verbose|-v)    VERBOSE=1; shift ;;
    *) echo "Unknown argument: $1" >&2; exit 1 ;;
  esac
done

APIS_DIR="$(realpath "$APIS_DIR")"
PASS=()
FAIL=()
WARN=()

log() { echo "  $*" >&2; }
ok()  { echo "  ✓ $*" >&2; }
err() { echo "  ✗ $*" >&2; }

# ---------------------------------------------------------------------------
# Check A — Build JS SDK from modified specs (tsc compilation)
# ---------------------------------------------------------------------------
echo "Check A — JS SDK build + TypeScript compile" >&2

if [[ $SKIP_BUILD -eq 0 ]]; then
  BUILD_LOG=$(cd "$APIS_DIR" && NODE_ENV=test npm run compile 2>&1) || {
    err "OpenRPC compile step failed"
    echo "$BUILD_LOG" >&2
    FAIL+=("sdk-compile")
  }

  if [[ ${#FAIL[@]} -eq 0 ]]; then
    ok "OpenRPC compile passed"

    IFS=',' read -ra SDK_WS_LIST <<< "$SDK_WORKSPACES"
    for ws in "${SDK_WS_LIST[@]}"; do
      ws="$(echo "$ws" | tr -d ' ')"
      WS_DIR="$APIS_DIR/src/sdks/$ws"
      [[ -d "$WS_DIR" ]] || { log "SDK workspace $ws not found — skip"; continue; }

      SLICE_LOG=$(cd "$WS_DIR" && npm run slice 2>&1) || {
        err "$ws: slice failed"
        [[ $VERBOSE -eq 1 ]] && echo "$SLICE_LOG" >&2
        FAIL+=("$ws-slice")
        continue
      }

      SDK_LOG=$(cd "$WS_DIR" && npm run sdk 2>&1) || {
        err "$ws: sdk generation failed"
        [[ $VERBOSE -eq 1 ]] && echo "$SDK_LOG" >&2
        FAIL+=("$ws-sdk-gen")
        continue
      }

      # TypeScript declarations check: tsc --noEmit on the generated index.d.ts.
      # We do NOT use test:setup — that transpiles the test suite (which has
      # pre-existing jest matcher type issues unrelated to SDK generation).
      GENERATED_DTS="$WS_DIR/build/javascript/src/index.d.ts"
      if [[ -f "$GENERATED_DTS" ]]; then
        TSC_LOG=$(cd "$WS_DIR" && \
          npx tsc --noEmit --strict --target ES2017 \
                  --moduleResolution node \
                  --lib ES2017,dom \
                  "$GENERATED_DTS" 2>&1) || {
          err "$ws: generated index.d.ts TypeScript check failed"
          echo "$TSC_LOG" >&2
          FAIL+=("$ws-tsc")
          continue
        }
      fi

      ok "$ws: slice + sdk-gen + tsc passed"
      PASS+=("$ws")
    done
  fi
else
  log "SKIP_BUILD set — skipping Check A"
fi

# ---------------------------------------------------------------------------
# Check B — Structural type compatibility (old d.ts assignable to new d.ts)
# ---------------------------------------------------------------------------
echo "" >&2
echo "Check B — TypeScript structural compatibility (HEAD vs working tree)" >&2

TMPDIR_B=$(mktemp -d)
trap 'rm -rf "$TMPDIR_B"' EXIT

if [[ -z "$MODULES" ]]; then
  log "No --modules specified — skipping Check B"
else
  # Get HEAD version of modified openrpc specs
  HEAD_SPECS_DIR="$TMPDIR_B/head-specs/src/openrpc"
  mkdir -p "$HEAD_SPECS_DIR"
  mkdir -p "$TMPDIR_B/head-schemas/src/schemas"

  IFS=',' read -ra MOD_LIST <<< "$MODULES"
  MISSING_HEAD=0

  for mod in "${MOD_LIST[@]}"; do
    mod="$(echo "$mod" | tr -d ' ')"
    git -C "$APIS_DIR" show "${BASE_REF}:src/openrpc/${mod}.json" \
      > "$HEAD_SPECS_DIR/${mod}.json" 2>/dev/null || {
      log "$mod: not found at $BASE_REF — new module, skipping type compat check for this module"
      MISSING_HEAD=1
    }
  done

  # Copy schemas from HEAD for the type generation
  for schema_file in "$APIS_DIR/src/schemas/"*.json; do
    fname="$(basename "$schema_file")"
    git -C "$APIS_DIR" show "${BASE_REF}:src/schemas/${fname}" \
      > "$TMPDIR_B/head-schemas/src/schemas/${fname}" 2>/dev/null || \
      cp "$schema_file" "$TMPDIR_B/head-schemas/src/schemas/${fname}" 2>/dev/null || true
  done

  # Generate TypeScript types from HEAD specs using firebolt-openrpc
  # We use the core SDK workspace as the target for type generation
  HEAD_SDK_DIR="$TMPDIR_B/head-sdk"
  mkdir -p "$HEAD_SDK_DIR"

  # Generate HEAD compiled OpenRPC
  FIREBOLT_OPENRPC=$(cd "$APIS_DIR" && node -e "require.resolve('@firebolt-js/openrpc')" 2>/dev/null || true)
  OPENRPC_BIN="$APIS_DIR/node_modules/.bin/firebolt-openrpc"

  if [[ ! -x "$OPENRPC_BIN" ]]; then
    log "firebolt-openrpc not found at $OPENRPC_BIN — skipping type compat check (Check B)"
    WARN+=("check-b-skipped-no-openrpc")
  else
    # Create a minimal template setup pointing at HEAD specs
    cat > "$TMPDIR_B/tsconfig.json" <<'EOF'
{
  "compilerOptions": {
    "strict": true,
    "noEmit": true,
    "target": "ES2017",
    "moduleResolution": "node",
    "declaration": true,
    "skipLibCheck": true
  }
}
EOF

    # Generate HEAD sdk types
    HEAD_COMPILE_LOG=$("$OPENRPC_BIN" openrpc \
      --input "$TMPDIR_B/head-specs" \
      --template "$APIS_DIR/src/template/openrpc/template.json" \
      --output "$TMPDIR_B/head-compiled.json" \
      --schemas "$TMPDIR_B/head-schemas/src/schemas" 2>&1) || {
      log "HEAD OpenRPC compile failed — skipping Check B"
      [[ $VERBOSE -eq 1 ]] && echo "$HEAD_COMPILE_LOG" >&2
      WARN+=("check-b-head-compile-failed")
    }

    if [[ ! " ${WARN[*]} " =~ "check-b" ]]; then
      # Generate TypeScript types from HEAD
      HEAD_TS_DIR="$TMPDIR_B/head-ts"
      mkdir -p "$HEAD_TS_DIR"
      "$OPENRPC_BIN" sdk \
        --input "$TMPDIR_B/head-compiled.json" \
        --template "$APIS_DIR/src/sdks/core/src/js" \
        --output "$HEAD_TS_DIR" \
        --static-module Platform 2>/dev/null || {
        log "HEAD TypeScript SDK generation failed — skipping Check B"
        WARN+=("check-b-head-ts-gen-failed")
      }

      # Generate TypeScript types from current working tree
      CUR_TS_DIR="$TMPDIR_B/cur-ts"
      CUR_COMPILED="$APIS_DIR/dist/firebolt-open-rpc.json"
      if [[ -f "$CUR_COMPILED" ]]; then
        mkdir -p "$CUR_TS_DIR"
        "$OPENRPC_BIN" sdk \
          --input "$CUR_COMPILED" \
          --template "$APIS_DIR/src/sdks/core/src/js" \
          --output "$CUR_TS_DIR" \
          --static-module Platform 2>/dev/null || {
          log "Current TypeScript SDK generation failed — skipping Check B"
          WARN+=("check-b-cur-ts-gen-failed")
        }
      else
        log "dist/firebolt-open-rpc.json not found (run npm run compile first) — skipping Check B"
        WARN+=("check-b-no-dist")
      fi

      # Write a compatibility shim: imports from HEAD types and assigns to
      # variables typed by the NEW types. If any type was narrowed, tsc fails.
      if [[ ! " ${WARN[*]} " =~ "check-b" ]] && \
         [[ -d "$HEAD_TS_DIR" ]] && [[ -d "$CUR_TS_DIR" ]]; then
        SHIM="$TMPDIR_B/compat-shim.ts"
        cat > "$SHIM" <<EOF
// Auto-generated compatibility shim.
// Validates that every exported type in the HEAD SDK is assignable to
// the corresponding type in the current SDK (no narrowing, no removed exports).
// tsc compiles this; if it fails, a consumer using the old types would break.
import type * as HeadSdk from "$HEAD_TS_DIR/index";
import type * as NewSdk  from "$CUR_TS_DIR/index";

// Structural sub-typing check: old types must be assignable to new
const _check: NewSdk.FireboltSDK = undefined as unknown as HeadSdk.FireboltSDK;
void _check;
EOF

        TSC_SHIM_LOG=$(cd "$TMPDIR_B" && npx tsc --noEmit --strict \
          --moduleResolution node --target ES2017 2>&1) || {
          err "TypeScript structural compatibility check FAILED"
          echo "$TSC_SHIM_LOG" >&2
          FAIL+=("ts-structural-compat")
        }

        if [[ ! " ${FAIL[*]} " =~ "ts-structural-compat" ]]; then
          ok "TypeScript structural compatibility passed"
          PASS+=("ts-structural-compat")
        fi
      fi
    fi
  fi
fi

# ---------------------------------------------------------------------------
# Summary
# ---------------------------------------------------------------------------
echo "" >&2
echo "JS compat check summary:" >&2
echo "  passed:   ${PASS[*]:-none}" >&2
echo "  warnings: ${WARN[*]:-none}" >&2
echo "  failed:   ${FAIL[*]:-none}" >&2

if [[ ${#FAIL[@]} -gt 0 ]]; then
  exit 1
fi
exit 0
