## Context

The `Device` module currently exposes `screenResolution` and `videoResolution` as readonly properties. There is no refresh rate API. Apps that need to match frame timing to display cadence (24p film, 60 Hz UI, 120 Hz gaming) have no platform-agnostic way to get this value.

The new `displayRefreshRate` property follows the exact pattern of the existing readonly properties: no parameters, returns a scalar numeric value, and has an `on<Name>Changed` event companion.

## Goals / Non-Goals

**Goals:**
- Add `displayRefreshRate` (Hz, float) as a readonly property on `Device`
- Add `onDisplayRefreshRateChanged` event for apps to react to rate changes
- Expose through the C++ SDK generated from the updated OpenRPC spec

**Non-Goals:**
- Setting the refresh rate (controlled by the platform, not apps)
- Negotiating refresh rate (e.g., adaptive sync — future change)
- Localization module changes (kept in `.modules` for future extension; no spec changes in this iteration)

## Decisions

**Float Hz value, not an enum** — Refresh rates like 23.976, 29.97, 59.94 are common in broadcast contexts. A `number` schema allows exact values without requiring a new string enum that would need updating for every new display type.

**Property:readonly tag** — Matches `screenResolution`/`videoResolution` pattern. The OpenRPC generator picks this up to emit a getter with no setter and an `onChanged` companion event.

## Risks / Trade-offs

[Risk: Platform may not expose refresh rate via the transport layer] → Mitigation: implementation returns a best-effort value (e.g. from EDID or OS API); documented in summary description.

[Risk: Sub-Hz precision (23.976)] → Mitigation: `number` type (float64) covers this without API changes.
