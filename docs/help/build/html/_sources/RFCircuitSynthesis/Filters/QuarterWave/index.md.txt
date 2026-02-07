# Quarter-Wave Filters

## Overview

Bandpass and bandstop filters constructed from quarter-wavelength transmission line sections with alternating short-circuit or open-circuit stubs. Simple topology with predictable performance.

## Principle

A cascade of λ/4 transmission lines with shunt stubs realizes a bandpass or bandstop response. The stub impedances are derived from the normalized lowpass prototype coefficients through a lowpass-to-bandpass transformation.

## Design Equations

### Quarter-Wave Transmission Line
```{math}
λ/4 = c / (4 × fc)
```

All connecting lines are exactly λ/4 at the center frequency.

### Stub Impedances

**Bandpass filter (short-circuit stubs):**
```{math}
Z_stub = (π × Z₀ × bw) / (4 × gₖ)
```

**Bandstop filter (open-circuit stubs):**
```{math}
Z_stub = (4 × Z₀) / (π × bw × gₖ)
```

Where:

| Parameter | Range |
|-----------|-------|
|**fc**|Center frequency|
|**bw = BW / fc**|Fractional bandwidth|
|**gₖ**|Normalized lowpass prototype coefficient|
|**Z₀**|System impedance|

## Input Parameters

| Parameter | Range | Default | Description |
|-----------|-------|---------|-------------|
| Center freq (fc) | — | 2 GHz | Filter center frequency |
| Bandwidth (BW) | — | 400 MHz | 3 dB bandwidth |
| Order (N) | 2 – 10 | 3 | Number of resonators |
| Filter type | BP / BS | BP | Bandpass or Bandstop |

## Topology

### Bandpass

```
Input ──[λ/4]──┬──[λ/4]──┬──[λ/4]──┬──[λ/4]── Output
               │         │         │
              SC        SC        SC
             stub₁     stub₂     stub₃
               │         │         │
              GND       GND       GND
```

Each stub is **short-circuited** (grounded) at its far end.

### Bandstop

```
Input ──[λ/4]──┬──[λ/4]──┬──[λ/4]──┬──[λ/4]── Output
               │         │         │
              OC        OC        OC
             stub₁     stub₂     stub₃
               │         │         │
             OPEN      OPEN      OPEN
```

Each stub is **open-circuited** at its far end.


## Advantages

- Simple, symmetric layout
- Well-established design procedure

## Limitations

- Spurious passbands at odd harmonics (3fc, 5fc, ...)
- Requires low stub impedances for wideband BP (difficult in microstrip)
- Large physical size at lower frequencies

## References

[1] David M. Pozar (2012). *Microwave Engineering*, pp. 437–440. Wiley.

## See Also

```{toctree}
:maxdepth: 1
/RFCircuitSynthesis/index
/RFCircuitSynthesis/Filters/index
```
