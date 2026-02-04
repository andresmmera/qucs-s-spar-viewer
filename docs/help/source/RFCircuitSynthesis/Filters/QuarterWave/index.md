# Quarter-Wave Filters

## Overview

Bandpass and bandstop filters constructed from quarter-wavelength transmission line sections with alternating short-circuit or open-circuit stubs. Simple topology with predictable performance.

## Principle

A cascade of λ/4 transmission lines with shunt stubs realizes a bandpass or bandstop response. The stub impedances are derived from the normalized lowpass prototype coefficients through a lowpass-to-bandpass transformation.

## Design Equations

### Quarter-Wave Transmission Line
```
λ/4 = c / (4 × fc)
```

All connecting lines are exactly λ/4 at the center frequency.

### Stub Impedances

**Bandpass filter (short-circuit stubs):**
```
Z_stub = (π × Z₀ × bw) / (4 × gₖ)
```

**Bandstop filter (open-circuit stubs):**
```
Z_stub = (4 × Z₀) / (π × bw × gₖ)
```

Where:
- `fc` = center frequency
- `bw = BW / fc` = fractional bandwidth
- `gₖ` = normalized lowpass prototype coefficient
- `Z₀` = source impedance

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

## Microstrip Implementation

When microstrip is selected:

**Bandpass:**
- Short-circuit stubs require **vias** or **shunt capacitors** (100 pF, 1 nF) to ground
- Via diameter typically 0.5 mm, 4 vias per stub

**Bandstop:**
- Open-circuit stubs need to account for fringing capacitance at the open end

## Example

**Specification:**
- 3rd-order Butterworth bandpass
- fc = 2 GHz, BW = 400 MHz
- Z₀ = 50 Ω

**Normalized prototype (Butterworth N=3):**
```
g₁ = 1.0000
g₂ = 2.0000
g₃ = 1.0000
```

**Fractional bandwidth:**
```
bw = BW / fc = 400 / 2000 = 0.2
```

**λ/4 line length:**
```
λ/4 = (3×10⁸) / (4 × 2×10⁹) = 37.5 mm
```

**Stub impedances:**
```
Z_stub1 = (π × 50 × 0.2) / (4 × 1.0) = 7.85 Ω
Z_stub2 = (π × 50 × 0.2) / (4 × 2.0) = 3.93 Ω
Z_stub3 = (π × 50 × 0.2) / (4 × 1.0) = 7.85 Ω
```

All connecting lines: **Z₀ = 50 Ω, length = 37.5 mm**

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

../Filters/index
```