# Bridged-Tee Attenuator

## Overview

The Bridged-Tee attenuator is a bilateral matched attenuator topology that offers improved VSWR characteristics and unique resistor value distributions compared to standard Pi and Tee configurations.

## Topology

```
Input ──┬──[R1]──┬── Output
        │        │
      [R2]      [R3]  (both equal to Z₀)
        │        │
        └──[R4]──┘
             │
            GND
```

**Key characteristic:** R2 and R3 are **always equal to Z₀**, regardless of attenuation level.

## Design Equations

**Note:** Bridged-Tee uses **0.05 × Attenuation** (not 0.1 like Pi/Tee).

```
L = 10^(0.05 × Attenuation)

R₁ = Z₀ × (L - 1)

R₄ = Z₀ / (L - 1)

R₂ = R₃ = Z₀
```

**Constraint:** Requires **Zin = Zout** (bilateral matched design).

## Power Dissipation

Let:
```
K = (R₁ × R₄ + Z₀ × (2×R₄ + Z₀))²
```

Then:

**R1 (series resistor):**
```
Pdiss_R1 / Pin = (4 × R₁ × R₄² × Z₀) / K
```

**R2 (first shunt to bridge):**
```
Pdiss_R2 / Pin = (R₁ × R₄ + Z₀²)² / K
```

**R3 (second shunt to bridge):**
```
Pdiss_R3 / Pin = 0   (carries no current at DC/low frequencies)
```

**R4 (bridge to ground):**
```
Pdiss_R4 / Pin = (4 × R₄ × Z₀²) / K
```

## Example: 10 dB, Z₀ = 50 Ω, Pin = 1 W

```
L = 10^(0.05 × 10) = 10^0.5 ≈ 3.162

R₁ = 50 × (3.162 - 1) = 108.1 Ω
R₄ = 50 / (3.162 - 1) = 23.1 Ω
R₂ = R₃ = 50 Ω
```

**Power dissipation:**
```
K = (108.1 × 23.1 + 50 × (2×23.1 + 50))²
  = (2497.1 + 4810)²
  ≈ 5.34×10⁷

Pdiss_R1 ≈ (4 × 108.1 × 23.1² × 50) / K ≈ 0.022 W
Pdiss_R2 ≈ (2497.1 + 2500)² / K ≈ 0.468 W
Pdiss_R3 = 0 W
Pdiss_R4 ≈ (4 × 23.1 × 2500) / K ≈ 0.004 W

Pout = 1 - 0.022 - 0.468 - 0.004 ≈ 0.506 W  (≈ 0.1 W for 10 dB attenuation)
```

Note: Most power is dissipated in **R2**, which is always equal to Z₀.

## Power Distribution Analysis

| Attenuation (dB) | R₁ (Ω) | R₂ (Ω) | R₃ (Ω) | R₄ (Ω) | Power in R2 (%) |
|------------------|--------|--------|--------|--------|-----------------|
| 3 | 20.5 | 50 | 50 | 121.9 | ~35% |
| 6 | 49.9 | 50 | 50 | 50.1 | ~45% |
| 10 | 108.1 | 50 | 50 | 23.1 | ~50% |
| 20 | 495 | 50 | 50 | 5.05 | ~90% |

**Note:** Most power is dissipated in R2, whose value is **constant** and equal to Z₀.

## Advantages

1. **Constant R2, R3 values**
2. **Low power in R1, R4:** Good for PIN diode-based variable attenuators
   - R1 and R4 can be PIN diodes (controlled by bias current)
   - R2, R3 are fixed SMD resistors

## Limitations

1. **Zin = Zout:** It cannot be used for impedance transformation
2. **R2 power dissipation:** At high attenuation, R2 handles most of the power

## References

[1] Vizmuller, P. (1995). *RF Design Guide: Systems, Circuits, and Equations*, Chapter 3. Artech House.

[2] Doherty, W. E., & Joos, R. D. (1998). *The PIN Diode Circuit Designer's Handbook*, Chapter 4. Microsemi Corp.