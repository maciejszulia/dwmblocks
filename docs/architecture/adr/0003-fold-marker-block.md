# ADR 0003: A block without a command is the fold marker

## Status

Accepted.

## Context

The bar holds more blocks than fit on screen. The companion dwm fork shows
the text before the byte `0x1f` only while the pointer is over the status.
dwmblocks needs a way to place that byte at a fixed position in the block list.

## Decision

A block whose command is `NULL` makes `getcmd()` return the single byte
`0x1f` and start no process. [blocks.h](../../../blocks.h) places
`{"", NULL, 0, 0}` between the hover-only blocks and the always-visible blocks.

## Consequences

- The fold position is set in the configuration, not in code.
- `CMDLENGTH` grew from 50 to 128 in the same change, because the weather and
  limit lines no longer fit (commit message of `2d67ef9`).

## Evidence

- Commit `2d67ef9` ("feat: bar fold marker, wider blocks, weather rotation block").
- `getcmd()` in [dwmblocks.c](../../../dwmblocks.c); the fold entry in [blocks.h](../../../blocks.h).
