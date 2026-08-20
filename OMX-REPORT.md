# OMX Report — Clickable blocks

## Result

- Added `SA_SIGINFO` handling for configured realtime signals. A queued non-zero button value is exported as `BUTTON` only while the clicked block command runs; ordinary update signals and periodic runs leave `BUTTON` unset.
- Wrapped each signalled block's rendered text in its signal byte so the companion `dwm` status resolver can open and close the exact clickable region.
- Preserved signals VOL `10`, BRI `11`, and weather `12`; assigned CLD `6`, CDX `7`, and BAT `8`.
- Reused the existing volume, brightness, weather, Claude-usage, and Codex-usage helpers read-only. Added no dependency or helper script.
- Made `blocks.def.h` identical to `blocks.h`.

## Block action sign-off table

| Block | Signal | Status | Button action |
| --- | ---: | --- | --- |
| CLD | 6 | Implemented | Button1: show the full current Claude usage output with `notify-send`. |
| CDX | 7 | Implemented | Button1: show the full current Codex usage output with `notify-send`. |
| CPU | 0 | Proposed only | Button1: show the highest CPU-consuming processes. |
| RAM | 0 | Proposed only | Button1: show memory totals and the highest memory-consuming processes. |
| GPU | 0 | Unchanged | No action requested. |
| PNG | 0 | Proposed only | Button1: show current latency, packet loss, and route details. |
| DSK | 0 | Proposed only | Button1: show filesystem type, free space, and inode usage for `/`. |
| BRI | 11 | Implemented | Button4/Button5: raise/lower brightness by the helper's existing 5% step. |
| Separator | 0 | Unchanged | Structural fold marker; no action. |
| BAT | 8 | Implemented | Button1: show status, capacity, and power draw with `notify-send`. |
| VOL | 10 | Implemented | Button1: toggle mute; Button4/Button5: raise/lower volume by 5%. |
| Weather | 12 | Implemented | Button1: acknowledge today's warning; Button3: show the full forecast with `notify-send`. |
| Clock | 0 | Proposed only | Button1: show a compact monthly calendar. |

## Ponytail choices

- Kept actions inline where the existing helper already owns the behaviour; no wrapper or dispatcher was added.
- The lazier partial alternative was signal forwarding without CLD, CDX, and BAT actions. It was not used because the order requires those actions now.

## Verification

- `make clean && make` -> exit `0` (`returnStatus` retains its pre-existing unused-variable warning; no build failure).
- Guard check over every `blocks.h` command containing `BUTTON` -> exit `0`; all four commands begin with `case ${BUTTON:-} in`, so unset `BUTTON` performs no action.
- Syntax-check all 12 non-null block commands with `/bin/sh -n -c` -> exit `0`.
- Isolated `NO_X` statuscmd harness: queued Button3 rendered `BUTTON=3`, then a normal realtime update rendered `BUTTON` unset, with matching signal bytes around each result -> exit `0`.
- `cmp -s blocks.h blocks.def.h` -> exit `0`.
- `command -v notify-send` -> exit `0` (`/usr/bin/notify-send`).
- `git diff --check` -> exit `0`.
- Helper-script checks: not applicable; no file was added under `scripts/`.

No live process restart, install, local helper mutation, `dwm` change, push, or deployment was performed.
