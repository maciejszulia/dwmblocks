# ADR 0004: Mask real-time signals during the rebuild

## Status

Accepted.

## Context

A wheel tick on the bar queues a real-time signal. With `sleep(1)`, the
signal cut the sleep short, and the loop ran `getcmds(i++)` at once. Because
`i` counts seconds, a burst of ticks ran interval blocks out of turn. The
signal handler also writes the same buffers as the loop, so a signal during
`getstatus()` could duplicate text or write past `STATUSLENGTH`.

## Decision

- `setupsignals()` collects all real-time signals in `rtmask` and uses it as
  the handler's `sa_mask`.
- `statusloop()` blocks `rtmask` with `sigprocmask()` while it runs
  `getcmds()` and `writestatus()`.
- The loop sleeps with `nanosleep()` and resumes the remaining time after
  `EINTR`.

## Consequences

- Clicks are handled between ticks and do not change the tick schedule.
- A click waits until the current rebuild ends.
- The commit message reports a drop from 86k to 29k minor faults above idle
  over a 20-tick burst.

## Evidence

- Commit `4b3dcb0` ("fix(status): keep clicks from replaying the whole tick schedule").
- `setupsignals()` and `statusloop()` in [dwmblocks.c](../../../dwmblocks.c).
