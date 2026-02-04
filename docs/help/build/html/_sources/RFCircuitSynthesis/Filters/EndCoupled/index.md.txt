# End-Coupled Bandpass Filter

## Overview

Bandpass filter using λ/4 or λ/2 resonators coupled through small gaps at their ends. The coupling is capacitive, realized by the fringing fields between adjacent resonator ends.

## Principle

Each resonator is approximately λ/2 long at the center frequency. Adjacent resonators are physically separated by a small gap, creating capacitive coupling. The gap capacitance acts as a series coupling element between resonators.

## Design Equations

### J-Inverter Parameters

The required coupling between resonators is expressed as **J-inverters**:

**First section (external coupling):**
```
J₀ = √(0.5 × π × bw / (g₀ × g₁))
```

**Last section (external coupling):**
```
Jₙ = √(0.5 × π × bw / (gₙ × gₙ₊₁))
```

**Internal sections (inter-resonator coupling):**
```
Jₖ = (0.5 × π × bw) / √(gₖ × gₖ₊₁)
```

### Susceptance and Capacitance

Each J-inverter is approximated by a series capacitor:

```
B = J / (1 - J²)
C = B / ω₀
```

### Resonator Lengths

The resonator electrical length accounts for the phase shift introduced by the coupling capacitors:

```
θₖ = π - 0.5 × (arctan(2Bₖ₋₁) + arctan(2Bₖ))
lₖ = θₖ × λ_g0 / (2π)
```

Where:
- `bw = BW / fc` = fractional bandwidth
- `ω₀ = 2πfc` = center angular frequency
- `λ_g0 = c / fc` = wavelength at center frequency
- `gₖ` = normalized lowpass prototype coefficients
- `Bₖ` = susceptance of coupling capacitor k

## Input Parameters

| Parameter | Range | Default | Description |
|-----------|-------|---------|-------------|
| Center freq (fc) | — | 2 GHz | Bandpass center frequency |
| Bandwidth (BW) | — | 400 MHz | 3 dB bandwidth |
| Order (N) | 2 – 10 | 3 | Number of resonators |
| Z₀ | — | 50 Ω | System impedance |

## Topology

```
Input ──[C₀]──[TL₁]──[C₁]──[TL₂]──[C₂]──[TLₙ]──[Cₙ]── Output
        gap     λ₁     gap    λ₂     gap    λₙ     gap
```

Each `[TL]` section represents a resonator with adjusted length `θₖ < π`.

## Example

**Specification:**
- 3rd-order Butterworth bandpass
- fc = 2 GHz, BW = 400 MHz
- Z₀ = 50 Ω

**Normalized prototype (Butterworth N=3):**
```
g₀ = 1.0000
g₁ = 1.0000
g₂ = 2.0000
g₃ = 1.0000
g₄ = 1.0000
```

**Fractional bandwidth:**
```
bw = BW / fc = 400 / 2000 = 0.2
ω₀ = 2π × 2×10⁹ = 1.257×10¹⁰ rad/s
λ_g0 = 3×10⁸ / 2×10⁹ = 0.15 m
```

**External coupling (k=0):**
```
J₀ = √(0.5 × π × 0.2 / (1.0 × 1.0)) ≈ 0.628
B₀ = 0.628 / (1 - 0.628²) ≈ 1.01
C₀ = 1.01 / (50 × 1.257×10¹⁰) ≈ 1.61 pF
```

**Internal coupling (k=1):**
```
J₁ = (0.5 × π × 0.2) / √(1.0 × 2.0) ≈ 0.222
B₁ = 0.222 / (1 - 0.222²) ≈ 0.233
C₁ = 0.233 / (50 × 1.257×10¹⁰) ≈ 0.370 pF
```

**Resonator length (k=1):**
```
θ₁ = π - 0.5 × (arctan(2 × 1.01) + arctan(2 × 0.233))
   ≈ π - 0.5 × (1.122 + 0.431)
   ≈ 2.365 rad
l₁ = 2.365 × 0.15 / (2π) ≈ 56.5 mm
```

## Advantages

- Planar, single-layer layout
- Easy to fabricate in microstrip

## Limitations

- Narrowband (5–10%)
- Gap capacitances may be difficult to control precisely

## References

[1] David M. Pozar (2012). *Microwave Engineering*, pp. 441–442. Wiley.


## See Also

```{toctree}
:maxdepth: 1

../Filters/index
```