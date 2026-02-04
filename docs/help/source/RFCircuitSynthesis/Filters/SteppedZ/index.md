# Stepped Impedance Filter

## Overview

Lowpass filter topology using alternating high and low impedance transmission line sections to emulate series inductors and shunt capacitors. Compact implementation suitable for microstrip realization.

## Principle

Series inductors are replaced by high-impedance (narrow) TL sections, and shunt capacitors are replaced by low-impedance (wide) TL sections. The electrical lengths are chosen such that the TL sections approximate lumped elements at the design frequency.

## Design Equations

### Impedance Assignment

For a CLC topology (shunt-first):
- **Shunt capacitor** → Low-impedance line
- **Series inductor** → High-impedance line

For an LCL topology (series-first):
- **Series inductor** → High-impedance line
- **Shunt capacitor** → Low-impedance line

### Line Length Calculation

**For low-impedance sections (capacitor replacement):**
```
l = (gₖ × Z_{low}) / (β × Z₀)
```

**For high-impedance sections (inductor replacement):**
```
l = (gₖ × Z₀) / (β × Z_{high})
```

Where:
- `gₖ` = normalized lowpass prototype coefficient
- `β = 2πfc / c` = propagation constant at cutoff frequency
- `Z₀` = source impedance
- `c` = speed of light

## Input Parameters

| Parameter | Range | Default | Description |
|-----------|-------|---------|-------------|
| Minimum Z | 1 – 40 Ω | 10 Ω | Low-impedance line (Z_{low}) |
| Maximum Z | 50 – 400 Ω | 200 Ω | High-impedance line (Z_{high}) |
| Cutoff freq (fc) | — | 1 GHz | Lowpass cutoff |
| Order (N) | 2 – 10 | 3 | Number of sections |

## Microstrip Implementation

When microstrip is selected, each TL section is synthesized to physical dimensions:

**Low-impedance (wide) lines:**
- Wider traces (larger W)
- Shorter physical lengths due to higher effective εᵣ

**High-impedance (narrow) lines:**
- Narrower traces (smaller W)
- Longer physical lengths

**Step transitions (MSTEP)** are automatically inserted between sections with different widths to account for discontinuity effects.

## Design Constraints

- **Impedance ratio** Z_{high}/Z_{low} should typically be 5:1 to 20:1 for good approximation
- Minimum line width limited by fabrication (usually ≥ 0.1 mm)
- Maximum line width limited by substrate height to avoid higher-order modes
- Valid only near the design frequency — wideband performance degrades

## Example

**Specification:**
- 3rd-order Butterworth lowpass
- fc = 2 GHz
- Z₀ = 50 Ω
- Zₗₒw = 20 Ω, Zₕᵢgₕ = 120 Ω

**Lowpass prototype (Butterworth N=3):**
```
g₀ = 1 (source)
g₁ = 1.0000
g₂ = 2.0000
g₃ = 1.0000
g₄ = 1 (load)
```

**Assuming CLC topology (1st shunt):**

β = 2π × 2×10⁹ / 3×10⁸ ≈ 41.89 rad/m

**Section 1 (shunt C → low Z):**
```
l₁ = (g₁ × Zₗₒw) / (β × Z₀)
   = (1.0 × 20) / (41.89 × 50)
   ≈ 9.55 mm
Z₁ = 20 Ω
```

**Section 2 (series L → high Z):**
```
l₂ = (g₂ × Z₀) / (β × Z_{high})
   = (2.0 × 50) / (41.89 × 120)
   ≈ 19.9 mm
Z₂ = 120 Ω
```

**Section 3 (shunt C → low Z):**
```
l₃ = (g₃ × Z_{low}) / (β × Z₀)
   = (1.0 × 20) / (41.89 × 50)
   ≈ 9.55 mm
Z₃ = 20 Ω
```

## Advantages

- Compact layout
- Easy microstrip fabrication
- No lumped components required

## Limitations

- Performance degrades away from fc: It can't reject spurious.

## References

Pozar, D. M. (2012). *Microwave Engineering* (4th ed.), Section 8.5, pp. 424–426. Wiley.

## See Also

```{toctree}
:maxdepth: 1

../Filters/index
```