# ADR 0001: Track blocks.h in git

## Status

Accepted.

## Context

Upstream dwmblocks ignores `blocks.h` in git and builds it from
`blocks.def.h`. The [Makefile](../../../Makefile) copies `blocks.def.h` only
when `blocks.h` is absent. This fork keeps the workstation block list, which
depends on the companion dwm fork and on the bar scripts.

## Decision

Track `blocks.h` in git, although [.gitignore](../../../.gitignore) still lists it.
Keep `blocks.def.h` as a separate template.

## Consequences

- A fresh clone builds the workstation configuration.
- `blocks.h` contains host-specific commands and paths; another machine must
  review it before running `./dwmblocks` ([README.md](../../../README.md)).
- `blocks.def.h` and `blocks.h` have different layouts and drift apart.

## Evidence

- Commit `021a531` ("chore: track blocks.h with ping block (artixlinux.org, 10-sample avg)").
- Commit `9b94f54` ("docs: describe the tracked bar configuration and host dependencies").
- [blocks.h](../../../blocks.h), [Makefile](../../../Makefile), [.gitignore](../../../.gitignore).
