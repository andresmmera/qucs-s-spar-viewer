# Capacitively-Coupled Shunt Resonators Filter

## Overview

Bandpass filter topology using λ/4 short-circuit stub resonators coupled through series capacitors. Each stub acts as a shunt resonator, and the coupling capacitors provide the inter-resonator and external coupling.

## Principle

The filter consists of N short-circuited λ/4 stubs connected in shunt to the main transmission line. Series capacitors between each resonator and at the input/output ports provide coupling. The capacitor values and stub lengths are derived from the normalized lowpass prototype using admittance inverter transformations.

## Design Equations

### Admittance Inverters (J)

The coupling between resonators is realized through **J-inverters**, approximated by series capacitors.

**First section (input coupling, k=0):**
```
J₀ = √(π × δ / (4 × g₁)) / Z₀
C₀ = J₀ / (ω₀ × √(1 - Z₀² × J₀²))
```

**Internal sections (inter-resonator coupling, k=1 to N-1):**
```
Jₖ = (π × δ / 4) / (√(gₖ × gₖ₊₁) × Z₀)
Cₖ = Jₖ / ω₀
```

**Last section (output coupling, k=N):**
```
Jₙ = √(π × δ / (4 × gₙ × gₙ₊₁)) / Z₀
Cₙ = Jₙ / (ω₀ × √(1 - Z₀² × Jₙ²))
```

### Stub Lengths with Capacitive Loading Compensation

The shunt stubs are nominally λ₀/4 long, but must be adjusted to compensate for the loading effect of the coupling capacitors.

**Capacitive loading:**
```
ΔCₖ = -Cₖ₋₁ - Cₖ
```

**Adjusted stub length:**
```
lₖ = λ₀/4 + (Z₀ × ω₀ × ΔCₖ / (2π)) × λ₀
```

If lₖ < 0, add λ₀/4 to bring it into the physical range.

Where:
- `δ = BW / fc` = fractional bandwidth
- `ω₀ = 2πfc` = center angular frequency
- `λ₀ = c / fc` = free-space wavelength at center frequency
- `gₖ` = normalized lowpass prototype coefficients
- `Z₀` = system impedance (also stub characteristic impedance)

## Input Parameters

| Parameter | Range | Default | Description |
|-----------|-------|---------|-------------|
| Center freq (fc) | — | 2 GHz | Bandpass center frequency |
| Bandwidth (BW) | — | 400 MHz | 3 dB bandwidth |
| Order (N) | 2 – 10 | 3 | Number of resonators |
| Z₀ | — | 50 Ω | System impedance |

## Topology

```
         C₀        C₁        C₂              Cₙ
Input ──[═]──┬──[═]──┬──[═]──┬── ... ──┬──[═]── Output
             │       │       │         │
           stub₁   stub₂   stub₃     stubₙ
            l₁      l₂      l₃        lₙ
             │       │       │         │
            GND     GND     GND       GND
```

All stubs have characteristic impedance Z₀ = ZS (typically 50 Ω).

## Microstrip Implementation

When microstrip is selected:
- Short-circuit stubs are realized as **microstrip lines (MLIN)** with **vias to ground**
- Stub width is synthesized from Z₀ and substrate parameters
- Stub length accounts for both resonance and capacitive loading
- **Via parameters:**
  - Diameter: 0.5 mm
  - Number of vias per stub: 4
  - Via model accounts for parasitic inductance

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
δ = BW / fc = 400 / 2000 = 0.2
ω₀ = 2π × 2×10⁹ = 1.257×10¹⁰ rad/s
λ₀ = 3×10⁸ / 2×10⁹ = 0.150 m = 150 mm
```

**Input coupling (k=0):**
```
J₀ = √(π × 0.2 / (4 × 1.0)) / 50
   = √(0.1571) / 50
   ≈ 0.00794
C₀ = 0.00794 / (1.257×10¹⁰ × √(1 - 50² × 0.00794²))
   ≈ 0.632 pF
```

**Inter-resonator coupling (k=1):**
```
J₁ = (π × 0.2 / 4) / (√(1.0 × 2.0) × 50)
   = 0.1571 / (1.414 × 50)
   ≈ 0.00222
C₁ = 0.00222 / (1.257×10¹⁰)
   ≈ 0.177 pF
```

**Stub 1 length (compensated):**

First, note that there's no stub before C₀, so:
```
ΔC₀ = -C₀ - C₁ = -0.632 - 0.177 = -0.809 pF
l₀ = 150/4 + (50 × 1.257×10¹⁰ × (-0.809×10⁻¹²) / (2π)) × 150
   = 37.5 + (-0.967)
   = 36.53 mm
```

**Inter-resonator coupling (k=2):**
```
J₂ = (π × 0.2 / 4) / (√(2.0 × 1.0) × 50)
   ≈ 0.00222
C₂ = 0.177 pF
```

**Stub 2 length:**
```
ΔC₁ = -C₁ - C₂ = -0.177 - 0.177 = -0.354 pF
l₁ = 150/4 + (50 × 1.257×10¹⁰ × (-0.354×10⁻¹²) / (2π)) × 150
   = 37.5 - 0.423
   = 37.08 mm
```

**Output coupling (k=3):**
```
J₃ = √(π × 0.2 / (4 × 1.0 × 1.0)) / 50
   ≈ 0.00794
C₃ = 0.632 pF
```

**Stub 3 length:**
```
ΔC₂ = -C₂ - C₃ = -0.177 - 0.632 = -0.809 pF
l₂ = 150/4 + (50 × 1.257×10¹⁰ × (-0.809×10⁻¹²) / (2π)) × 150
   = 36.53 mm
```

## Summary of Components

| Component | Value | Notes |
|-----------|-------|-------|
| C₀ (input) | 0.632 pF | External coupling |
| Stub 1 | Z₀=50Ω, l=36.53 mm | Shunt resonator |
| C₁ | 0.177 pF | Inter-resonator |
| Stub 2 | Z₀=50Ω, l=37.08 mm | Shunt resonator |
| C₂ | 0.177 pF | Inter-resonator |
| Stub 3 | Z₀=50Ω, l=36.53 mm | Shunt resonator |
| C₃ (output) | 0.632 pF | External coupling |

## Advantages

- Compact, planar layout
- All stubs have the same impedance¡
- Series capacitors easy to realize (chip caps or gap caps)

## Limitations

- Narrowband (typically 5–20% fractional BW)
- Requires precise coupling values
- Spurious passbands at odd harmonics (3fc, 5fc, ...)
- Via inductance can affect performance at high frequencies

## References

[1] Pozar, D. M. (2012). *Microwave Engineering* (4th ed.), Section 8.7, pp. 443–448. Wiley.