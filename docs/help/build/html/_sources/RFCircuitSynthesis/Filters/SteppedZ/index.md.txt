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

| Parameter | Description |
|-----------|-------------|
| **gₖ** | normalized lowpass prototype coefficient |
| **β = 2πfc / c**  | propagation constant at cutoff frequency |
| **Z₀**|System impedance|
| **c**|speed of light|

## Input Parameters

| Parameter | Range | Default | Description |
|-----------|-------|---------|-------------|
| Minimum Z | 1 – 40 Ω | 10 Ω | Low-impedance line (Z_{low}) |
| Maximum Z | 50 – 400 Ω | 200 Ω | High-impedance line (Z_{high}) |
| Cutoff freq (fc) | — | 1 GHz | Lowpass cutoff |
| Order (N) | 2 – 10 | 3 | Number of sections |


## References

Pozar, D. M. (2012). *Microwave Engineering* (4th ed.), Section 8.5, pp. 424–426. Wiley.

## See Also

```{toctree}
:maxdepth: 1
/RFCircuitSynthesis/index
/RFCircuitSynthesis/Filters/index
```