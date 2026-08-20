# Order — Clickable blocks: BUTTON handling and per-block actions

Repository: /home/ms/src/dwmblocks (this worktree, current branch). The dwm side
(statuscmd click resolution) is delivered by a separate order in /home/ms/src/dwm —
read that repo read-only for the contract, do not modify it.
Work MUST NOT: restart the live dwmblocks process, install binaries, or modify
~/.local/bin scripts in place (new helper scripts go into this repo under scripts/).
Second brain: /home/ms/.local/share/silverbullet/space — read index.md, operating-model.md,
briefings/2026-08-12-omx-stack.md before starting (path only; do not paste their contents).

## Problem

blocks.h defines 13 blocks (CLD, CDX, CPU, RAM, GPU, PNG, DSK, BRI, separator, BAT,
VOL, weather, clock); three have realtime signals (VOL=10, BRI=11, weather=12). The
binary has no click support: no BUTTON env, no per-block actions (dwmblocks.c handles
only SIGRT updates). dwm is being extended with the statuscmd contract (signal +
button number) by the companion order.

## Required outcome

1. dwmblocks.c handles the statuscmd contract: on a click signal it re-runs the
   clicked block's command with BUTTON set (standard statuscmd-for-dwmblocks
   behaviour), consistent with the dwm-side design in
   /home/ms/src/dwm/docs/orders/2026-08-20-statuscmd-per-block-clicks.md.
2. Proposed default actions, implemented in the block commands (inline in blocks.h or
   as small scripts in scripts/ within this repo):
   - VOL: Button1 toggle mute, scroll up/down ±5% (reuse the conventions of
     /home/ms/.local/bin/volume — read-only).
   - BRI: scroll up/down brightness step (reuse /home/ms/.local/bin/brightness).
   - BAT: Button1 → notify-send with status/capacity/power draw details.
   - weather: Button1 keeps today's ack behaviour (contract moved from dwm's global
     weatherack binding), Button3 → notify-send full forecast (reuse
     /home/ms/.local/bin/weather output).
   - CLD/CDX: Button1 → notify-send with the full usage details behind the number.
   - CPU/RAM/PNG/DSK/clock: propose in the report only; implement nothing yet.
3. Blocks gaining click actions get signal numbers where required by the mechanism;
   keep existing numbers 10/11/12 unchanged.
4. Clean `make`. blocks.def.h kept in sync with blocks.h.
5. OMX-REPORT.md at the worktree root with a block→action table (implemented vs
   proposed-only) for owner sign-off, plus gate exit codes.

## Verification (record exit codes in OMX-REPORT.md)

1. make clean && make → exit 0
2. Static check: every block command referencing BUTTON is guarded for BUTTON unset
   (normal periodic runs must behave exactly as today).
3. If any helper script is added under scripts/: bash -n each; shellcheck if
   available on the host, otherwise note it.

## Constraints

No new dependencies (notify-send/dunst already on the host — verify with command -v
and report, do not install). Diff surface: dwmblocks.c, blocks.h, blocks.def.h,
scripts/, docs/orders/ (this file), OMX-REPORT.md. English commits, no
Co-Authored-By. Ponytail style.

## Definition of done

Branch with clickable support and the listed actions committed, clean build, report
with the sign-off table. Stop there: no process restart, no install, no push, no dwm
changes.
