v0.x
---   
- Fixes to serial header.
> Minor documentation fixes, init struct takes a pointer.

v0.3
---
- Updates to GPIO header.
> Remove alternate function callback, replace with singular value.
- Addition of serial header.
> Add functions to set-up/teardown, transmit and receive, callback.

v0.2
---
- Updates to GPIO HAL header.
> Change name of init/teardown functions from peripheral basis to pin basis.
> Documentation updates.
> Parameter updates to use pointers rather than pass-by-value.
> Pull-up/pull-down enum added.
> Pin mode, trigger, speed now in pin struct rather than overall peripheral init.

v0.1
---
- Initial alpha release, includes:
> GPIO header.
> I2C header (host only).
> HAL Result header.
> Core clock setup.
> Core interrupt control.
