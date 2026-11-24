# ADR 0002: Pass the mouse button in a queued signal

## Status

Accepted.

## Context

dwm needs to tell dwmblocks which block was clicked and with which mouse
button. Upstream dwmblocks only re-runs a block on `SIGRTMIN + n` and
receives no button.

## Decision

- `getcmd()` writes the block's signal number as a byte before and after the
  block text, so dwm can find the block under the cursor.
- `setupsignals()` installs `sighandler()` with `SA_SIGINFO`.
- `sighandler()` reads `si->si_value.sival_int` (sent by dwm with
  `sigqueue()`), exports it as `BUTTON`, runs every block with that signal,
  removes `BUTTON` and writes the status.

## Consequences

- A block command reacts to buttons with `case ${BUTTON:-} in ...`
  ([blocks.h](../../../blocks.h)).
- dwm and dwmblocks must agree on the byte encoding and the signal offset.
- A block with signal 0 gets no signal byte and receives no clicks.

## Evidence

- Commit `4a623d6` ("feat(status): add per-block click actions").
- [docs/orders/2026-08-20-clickable-blocks.md](../../orders/2026-08-20-clickable-blocks.md),
  [docs/reports/2026-08-20-clickable.md](../../reports/2026-08-20-clickable.md).
- `getcmd()`, `setupsignals()` and `sighandler()` in [dwmblocks.c](../../../dwmblocks.c).
