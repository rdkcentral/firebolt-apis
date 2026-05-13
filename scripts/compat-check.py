#!/usr/bin/env python3
"""
compat-check.py — OpenRPC backwards-compatibility differ

Compares git HEAD versions of Firebolt OpenRPC JSON modules against the working
tree and reports any changes that would break C++ platform implementors or
JavaScript/TypeScript API consumers.

Exit code: 0 = compat (additive or unchanged), 1 = breaking changes detected
Output: JSON report on stdout

Usage:
  python3 scripts/compat-check.py \
      --base HEAD \
      --modules device,localization,firebolt \
      --apis-dir /path/to/firebolt-apis

  --base       git ref to compare against (default: HEAD)
  --modules    comma-separated list of module names (no .json extension)
  --apis-dir   root of the firebolt-apis repo (default: .)
  --json       always output JSON, even on clean result (default: only on breaks)
  --quiet      suppress non-JSON output
"""
import argparse
import json
import subprocess
import sys
import tempfile
import os

# ---------------------------------------------------------------------------
# Helpers
# ---------------------------------------------------------------------------

def git_show(ref: str, path: str) -> dict | None:
    """Return parsed JSON for <ref>:<path>, or None if not found at that ref."""
    try:
        result = subprocess.run(
            ["git", "show", f"{ref}:{path}"],
            capture_output=True, text=True, check=True
        )
        return json.loads(result.stdout)
    except subprocess.CalledProcessError:
        return None  # file didn't exist at that ref
    except json.JSONDecodeError as e:
        raise RuntimeError(f"JSON parse error in {ref}:{path}: {e}") from e


def read_json(path: str) -> dict | None:
    try:
        with open(path, encoding="utf-8") as f:
            return json.load(f)
    except FileNotFoundError:
        return None


def method_index(spec: dict) -> dict[str, dict]:
    """Return {methodName: method_object} from an OpenRPC spec."""
    return {m["name"]: m for m in spec.get("methods", [])}


def schema_index(spec: dict) -> dict[str, dict]:
    """Return {schemaName: schema_object} from components.schemas."""
    return spec.get("components", {}).get("schemas", {})


# ---------------------------------------------------------------------------
# Breaking-change detectors
# ---------------------------------------------------------------------------

def result_type_key(method: dict) -> str:
    """Stable string representation of a method's result schema for diffing."""
    result = method.get("result", {})
    schema = result.get("schema", {})
    return json.dumps(schema, sort_keys=True)


def params_key(method: dict) -> list[dict]:
    return method.get("params", [])


def required_params(method: dict) -> list[str]:
    return [p["name"] for p in params_key(method) if p.get("required", False)]


def check_method_compat(name: str, old: dict, new: dict) -> list[dict]:
    """Compare one method old→new and return list of breaking issues."""
    issues = []

    # 1. Return type changed
    if result_type_key(old) != result_type_key(new):
        issues.append({
            "kind": "type-changed",
            "surface": "both",
            "method": name,
            "was": result_type_key(old),
            "now": result_type_key(new),
            "severity": "breaking",
        })

    # 2. Required param added
    old_req = set(required_params(old))
    new_req = set(required_params(new))
    for added in new_req - old_req:
        issues.append({
            "kind": "param-added",
            "surface": "both",
            "method": name,
            "param": added,
            "severity": "breaking",
        })

    # 3. Required param removed (not breaking for callers, but breaking for
    #    any codegen that requires all params — flag as warning only)
    for removed in old_req - new_req:
        issues.append({
            "kind": "param-removed",
            "surface": "both",
            "method": name,
            "param": removed,
            "severity": "warning",
        })

    # 4. Optional param added — fine for existing callers, but worth noting
    old_params = {p["name"] for p in params_key(old)}
    new_params = {p["name"] for p in params_key(new)}
    for added in new_params - old_params:
        if added not in new_req:
            issues.append({
                "kind": "optional-param-added",
                "surface": "both",
                "method": name,
                "param": added,
                "severity": "additive",
            })

    return issues


def check_enum_compat(name: str, old_schema: dict, new_schema: dict) -> list[dict]:
    """Detect removed enum values (breaking for both C++ switch statements and TS exhaustive checks)."""
    issues = []
    old_vals = set(old_schema.get("enum", []))
    new_vals = set(new_schema.get("enum", []))
    for removed in old_vals - new_vals:
        issues.append({
            "kind": "enum-value-removed",
            "surface": "both",
            "schema": name,
            "value": removed,
            "severity": "breaking",
        })
    for added in new_vals - old_vals:
        issues.append({
            "kind": "enum-value-added",
            "surface": "both",
            "schema": name,
            "value": added,
            "severity": "additive",
        })
    return issues


def check_object_compat(name: str, old_schema: dict, new_schema: dict) -> list[dict]:
    """Detect removed required fields or required-field additions in object schemas."""
    issues = []
    old_required = set(old_schema.get("required", []))
    new_required = set(new_schema.get("required", []))
    old_props = set(old_schema.get("properties", {}).keys())
    new_props = set(new_schema.get("properties", {}).keys())

    # Required field removed from result struct — callers that destructure it will break
    for removed in old_props - new_props:
        if removed in old_required:
            issues.append({
                "kind": "field-removed",
                "surface": "both",
                "schema": name,
                "field": removed,
                "severity": "breaking",
            })
        else:
            issues.append({
                "kind": "optional-field-removed",
                "surface": "both",
                "schema": name,
                "field": removed,
                "severity": "warning",
            })

    # Field became required when it was previously optional
    for field in old_props & new_props:
        if field in new_required and field not in old_required:
            issues.append({
                "kind": "field-became-required",
                "surface": "both",
                "schema": name,
                "field": field,
                "severity": "breaking",
            })

    # New required fields added — breaks serialization code that builds the struct
    for added in new_required - old_required:
        if added not in old_props:
            issues.append({
                "kind": "required-field-added",
                "surface": "both",
                "schema": name,
                "field": added,
                "severity": "breaking",
            })

    return issues


# ---------------------------------------------------------------------------
# Per-module diff
# ---------------------------------------------------------------------------

def diff_module(module: str, base_spec: dict, head_spec: dict) -> dict:
    """Diff two OpenRPC specs for one module; return a report dict."""
    issues = []

    base_methods = method_index(base_spec)
    head_methods = method_index(head_spec)

    # Removed methods
    for name in set(base_methods) - set(head_methods):
        issues.append({
            "kind": "removed",
            "surface": "both",
            "method": name,
            "severity": "breaking",
        })

    # Added methods — additive, but record for the report
    for name in set(head_methods) - set(base_methods):
        issues.append({
            "kind": "added",
            "surface": "both",
            "method": name,
            "severity": "additive",
        })

    # Changed methods
    for name in set(base_methods) & set(head_methods):
        issues.extend(check_method_compat(name, base_methods[name], head_methods[name]))

    # Schema-level checks
    base_schemas = schema_index(base_spec)
    head_schemas = schema_index(head_spec)

    for sname, old_s in base_schemas.items():
        new_s = head_schemas.get(sname)
        if new_s is None:
            issues.append({
                "kind": "schema-removed",
                "surface": "both",
                "schema": sname,
                "severity": "breaking",
            })
            continue
        if old_s.get("type") == "string" and "enum" in old_s:
            issues.extend(check_enum_compat(sname, old_s, new_s))
        elif old_s.get("type") == "object":
            issues.extend(check_object_compat(sname, old_s, new_s))

    breaking = [i for i in issues if i["severity"] == "breaking"]
    warnings = [i for i in issues if i["severity"] == "warning"]
    additive = [i for i in issues if i["severity"] == "additive"]

    return {
        "module": module,
        "result": "breaking" if breaking else ("warning" if warnings else "additive"),
        "breaking": breaking,
        "warnings": warnings,
        "additive": additive,
    }


# ---------------------------------------------------------------------------
# CLI
# ---------------------------------------------------------------------------

def main():
    parser = argparse.ArgumentParser(description="OpenRPC backwards-compatibility differ")
    parser.add_argument("--base", default="HEAD", help="git ref to compare against (default: HEAD)")
    parser.add_argument("--modules", required=True, help="comma-separated module names")
    parser.add_argument("--apis-dir", default=".", help="root of firebolt-apis repo")
    parser.add_argument("--json", action="store_true", dest="force_json",
                        help="always output JSON even on clean result")
    parser.add_argument("--quiet", action="store_true", help="suppress non-JSON stderr")
    args = parser.parse_args()

    modules = [m.strip() for m in args.modules.split(",") if m.strip()]
    apis_dir = os.path.abspath(args.apis_dir)
    openrpc_dir = os.path.join(apis_dir, "src", "openrpc")

    if not args.quiet:
        print(f"Comparing {len(modules)} module(s) against {args.base}...", file=sys.stderr)

    # Change to apis_dir so git commands resolve correctly
    orig_cwd = os.getcwd()
    os.chdir(apis_dir)

    try:
        report = {"modules": [], "overall": "additive"}
        any_breaking = False

        for mod in modules:
            rel_path = f"src/openrpc/{mod}.json"
            abs_path = os.path.join(apis_dir, rel_path)

            base_spec = git_show(args.base, rel_path)
            head_spec = read_json(abs_path)

            if base_spec is None and head_spec is None:
                if not args.quiet:
                    print(f"  {mod}: not found at {args.base} or on disk — skip", file=sys.stderr)
                continue

            if base_spec is None:
                # Brand new module — all additive
                report["modules"].append({
                    "module": mod,
                    "result": "new",
                    "breaking": [],
                    "warnings": [],
                    "additive": [{"kind": "new-module", "severity": "additive"}],
                })
                continue

            if head_spec is None:
                # Module deleted — everything breaking
                report["modules"].append({
                    "module": mod,
                    "result": "breaking",
                    "breaking": [{"kind": "module-deleted", "severity": "breaking"}],
                    "warnings": [],
                    "additive": [],
                })
                any_breaking = True
                continue

            mod_report = diff_module(mod, base_spec, head_spec)
            report["modules"].append(mod_report)
            if mod_report["result"] == "breaking":
                any_breaking = True

            if not args.quiet:
                result = mod_report["result"]
                b = len(mod_report["breaking"])
                w = len(mod_report["warnings"])
                a = len(mod_report["additive"])
                status = "✗ BREAKING" if result == "breaking" else \
                         "⚠ warning" if result == "warning" else \
                         "✓ additive"
                print(f"  {mod}: {status}  (breaking={b}, warnings={w}, additive={a})", file=sys.stderr)
                for issue in mod_report["breaking"]:
                    method_or_schema = issue.get("method") or issue.get("schema") or ""
                    print(f"    ✗ {issue['kind']} — {method_or_schema}", file=sys.stderr)

        report["overall"] = "breaking" if any_breaking else "additive"

        if args.force_json or any_breaking:
            print(json.dumps(report, indent=2))

        sys.exit(1 if any_breaking else 0)

    finally:
        os.chdir(orig_cwd)


if __name__ == "__main__":
    main()
