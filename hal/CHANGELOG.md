v0.x
---
- Fixes to serial header.
1. Minor documentation fixes, init struct takes a pointer.
- Updates to serial header.
1. Change return type of `tx`/`rx` callbacks.
2. Add `tx` buffer length/pointer to `init` struct.
3. Remove buffer param from `rx` non-blocking function.

v0.3
---
- Updates to GPIO header.
1. Remove alternate function callback, replace with singular value.
- Addition of serial header.
2. Add functions to set-up/teardown, transmit and receive, callback.

v0.2
---
- Updates to GPIO HAL header.
1. Change name of init/teardown functions from peripheral basis to pin basis.
2. Documentation updates.
3. Parameter updates to use pointers rather than pass-by-value.
4. Pull-up/pull-down enum added.
5. Pin mode, trigger, speed now in pin struct rather than overall peripheral init.

v0.1
---
- Initial alpha release, includes:
1. GPIO header.
2. I2C header (host only).
3. HAL Result header.
4. Core clock setup.
5. Core interrupt control.
