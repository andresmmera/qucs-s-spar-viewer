# Side-Coupled (Parallel-Coupled) Bandpass Filter

## Overview

Bandpass filter using λ/4 coupled transmission line sections placed side-by-side. The electromagnetic coupling between parallel resonators realizes the filter response. Also known as parallel-coupled line filter or edge-coupled filter.

## Principle

The filter consists of N λ/4 coupled-line sections arranged in cascade. Each section acts as a resonator at the center frequency, and the coupling between adjacent sections is controlled by their physical spacing (gap). The coupling is primarily magnetic at the design frequency.

## Design Equations

### Admittance Inverters (J)

The required coupling between resonators is first calculated as **J-inverters**:

**First section (input coupling, k=0):**
```
J₀ = √(π × δ / (2 × g₁)) / Z₀
```

**Internal sections (inter-resonator coupling, k=1 to N-1):**
```
Jₖ = (π × δ / 2) / (√(gₖ × gₖ₊₁) × Z₀)
```

**Last section (output coupling, k=N):**
```
Jₙ = √(π × δ / (2 × gₙ × gₙ₊₁)) / Z₀
```

### Even and Odd Mode Impedances

Each coupled-line section is characterized by its even-mode (Z₀e) and odd-mode (Z₀o) impedances, which are derived from the J-inverter parameter:

```
Z₀e = Z₀ × (1 + J × Z₀ + (J × Z₀)²)
Z₀o = Z₀ × (1 - J × Z₀ + (J × Z₀)²)
```

These impedances determine the required coupling strength. Tighter coupling (larger J) produces larger Z₀e and smaller Z₀o.

### Physical Length

All coupled-line sections are exactly λ/4 at the center frequency:

```
l = λ₀ / 4 = c / (4 × fc)
```

Where:
- `δ = BW / fc` = fractional bandwidth
- `fc` = center frequency
- `Z₀` = system impedance (typically 50 Ω)
- `gₖ` = normalized lowpass prototype coefficients
- `c` = speed of light

## Input Parameters

| Parameter | Range | Default | Description |
|-----------|-------|---------|-------------|
| Center freq (fc) | — | 2 GHz | Bandpass center frequency |
| Bandwidth (BW) | — | 400 MHz | 3 dB bandwidth |
| Order (N) | 2 – 10 | 3 | Number of resonators |
| Z₀ | — | 50 Ω | System impedance |

## Topology

```
Input ──╪═══╪──╪═══╪──╪═══╪──╪═══╪── Output
        ║   ║  ║   ║  ║   ║  ║   ║
        ╪═══╪  ╪═══╪  ╪═══╪  ╪═══╪
       Section Section Section Section
          1      2      3      N
```

Each `╪═══╪` represents a λ/4 coupled-line section with two parallel traces.

## Microstrip Implementation

When microstrip is selected, each coupled-line section is synthesized to physical dimensions:

**MSCOUP (Microstrip Coupled Lines):**
- **W**: Line width (both traces have equal width)
- **L**: Physical length (includes effective εᵣ)
- **S**: Gap spacing between traces

The synthesis routine `synthesizeCoupledMicrostrip(Z₀e, Z₀o, l, fc)` determines W and S such that the structure exhibits the required Z₀e and Z₀o at the design frequency.

**Typical dimensions at 2 GHz on FR4 (εᵣ=4.5, h=1.6mm):**
- Line width W: 1–3 mm
- Gap spacing S: 0.1–1 mm (tighter for stronger coupling)
- Physical length L: ~15–20 mm (shorter than λ₀/4 due to εᵣ)

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
```

**Physical length:**
```
λ₀ / 4 = (3×10⁸) / (4 × 2×10⁹) = 37.5 mm
```

**Section 1 (input coupling, k=0):**
```
J₀ = √(π × 0.2 / (2 × 1.0)) / 50
   = √(0.314) / 50
   ≈ 0.0112

Z₀e = 50 × (1 + 0.0112 × 50 + (0.0112 × 50)²)
    = 50 × (1 + 0.56 + 0.314)
    ≈ 93.7 Ω

Z₀o = 50 × (1 - 0.0112 × 50 + (0.0112 × 50)²)
    = 50 × (1 - 0.56 + 0.314)
    ≈ 37.7 Ω
```

**Section 2 (inter-resonator, k=1):**
```
J₁ = (π × 0.2 / 2) / (√(1.0 × 2.0) × 50)
   = 0.314 / (1.414 × 50)
   ≈ 0.00444

Z₀e = 50 × (1 + 0.00444 × 50 + (0.00444 × 50)²)
    = 50 × (1 + 0.222 + 0.049)
    ≈ 63.6 Ω

Z₀o = 50 × (1 - 0.00444 × 50 + (0.00444 × 50)²)
    = 50 × (1 - 0.222 + 0.049)
    ≈ 41.4 Ω
```

**Section 3 (inter-resonator, k=2):**
```
J₂ = (π × 0.2 / 2) / (√(2.0 × 1.0) × 50)
   ≈ 0.00444

Z₀e ≈ 63.6 Ω
Z₀o ≈ 41.4 Ω
```

**Section 4 (output coupling, k=3):**
```
J₃ = √(π × 0.2 / (2 × 1.0 × 1.0)) / 50
   ≈ 0.0112

Z₀e ≈ 93.7 Ω
Z₀o ≈ 37.7 Ω
```

## Summary of Coupled Sections

| Section | Z₀e | Z₀o | Length | Coupling Strength |
|---------|-----|-----|--------|-------------------|
| 1 (input) | 93.7 Ω | 37.7 Ω | λ/4 | Strong (external) |
| 2 | 63.6 Ω | 41.4 Ω | λ/4 | Weak (internal) |
| 3 | 63.6 Ω | 41.4 Ω | λ/4 | Weak (internal) |
| 4 (output) | 93.7 Ω | 37.7 Ω | λ/4 | Strong (external) |

Note the symmetry: external coupling is stronger than internal coupling.

## Design Guidelines

**Coupling strength vs. impedance ratio:**
- Tighter coupling (larger J) → larger Z₀e/Z₀o ratio
- Weaker coupling (smaller J) → Z₀e ≈ Z₀o ≈ Z₀

**Fractional bandwidth limits:**
- Practical range: 5–30%
- Wider BW requires tighter coupling (smaller gaps, harder to fabricate)
- Narrower BW requires weaker coupling (may be limited by substrate height)

**Fabrication constraints:**
- Minimum gap spacing: ~0.1 mm (typical PCB)
- Maximum Z₀e: ~120 Ω (avoids excessively narrow lines)
- Minimum Z₀o: ~30 Ω (avoids excessively wide lines)

## Advantages

- Fully planar, single-layer layout
- No vias or chip components required
- Well-established design methodology
- Good power handling
- Scalable to higher orders (N > 5)

## Limitations

- Fractional bandwidth limited by fabrication (typically 5–30%)
- Spurious passband at 3fc due to λ/4 resonance
- Requires accurate EM modeling of coupled lines
- Physical size can be large at lower frequencies
- Substrate thickness affects achievable coupling range

## References

[1] David M. Pozar (2012). *Microwave Engineering*, pp. 430–437. Wiley.

## See Also

```{toctree}
:maxdepth: 1

../Filters/index
```