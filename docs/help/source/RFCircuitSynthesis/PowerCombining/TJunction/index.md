# T-Junction Power Divider

## Overview

The **simplest** RF power divider using only transmission line impedance transformations. Provides matched input port but **no isolation** between outputs. Ideal for applications where isolation is not required and high power handling is needed.

## Topology

```
                    ┌──[Z₂, λ/4]── Port 2
                    │
Input ──[Z₀, λ/4]───┤
     (Port 1)       │
                    └──[Z₃, λ/4]── Port 3
```

**Basic structure:**
- Input λ/4 line at Z₀
- Two output λ/4 branches at Z₂, Z₃
- Physical T-junction connection point

**For unequal split, additional matching:**
```
                    ┌──[Z₂, λ/4]──[Z₂ₘ, λ/4]── Port 2
                    │
Input ──[Z₀, λ/4]───┤
                    │
                    └──[Z₃, λ/4]──[Z₃ₘ, λ/4]── Port 3
```

## Design Equations

### Power Split Ratio

K = P₂/P₃ = (Port 2 power / Port 3 power)

### Branch Impedances (First Stage)

```
Z₂ = Z₀ × (K + 1)          (to higher power port)
Z₃ = Z₀ × (K + 1) / K      (to lower power port)
```

### Matching Sections (Unequal Split Only)

For K ≠ 1, add λ/4 matching transformers:

```
Z₂ₘ = √(2 × Z₀² × (K + 1))
Z₃ₘ = √(2 × Z₀² × (K + 1) / K)
```

### Equal Split (K = 1)

```
Z₂ = Z₃ = 2 × Z₀

No additional matching needed
```

**For Z₀ = 50 Ω:**
```
Z₂ = Z₃ = 100 Ω
```

## S-Parameters (Ideal, Equal Split)

At design frequency f₀:

```
|S₁₁| < -30 dB  (good input match)
|S₂₁| = -3 dB   (half power to Port 2)
|S₃₁| = -3 dB   (half power to Port 3)

|S₂₃| ≈ 0 dB    (NO ISOLATION - outputs connected!)
```

**Critical:** Ports 2 and 3 are directly connected through the junction, so there's no isolation between them.

## Advantages

1. **Simplest design:** Only transmission lines, no resistors
2. **Low insertion loss:** Only conductor/dielectric losses
3. **Small size:** Compact layout (equal split)
4. **Low cost:** No isolation resistors to specify/purchase

## Limitations

1. **No isolation:** S₂₃ ≈ 0 dB
   - Signals at Port 2 leak directly to Port 3
   - Impedance at one output affects the other
2. **Impedance mismatch**

## Comparison with Wilkinson

| Feature | T-Junction | Wilkinson |
|---------|------------|-----------|
| **Isolation** | None (~0 dB) | Excellent (>20 dB) |
| **Components** | TL only | TL + Resistor |
| **Power handling** | Very high | Limited by R |
| **Insertion loss** | Very low | Low  |
| **Complexity** | Simplest | Simple |
| **Bandwidth** | Narrow (10-15%) | Medium (20-40%) |
| **Combining** | Cannot combine | Can combine |
| **Cost** | Lowest | Low |

## References

[1] Pozar, D. M. (2012). *Microwave Engineering* (4th ed.), Section 7.3. Wiley.