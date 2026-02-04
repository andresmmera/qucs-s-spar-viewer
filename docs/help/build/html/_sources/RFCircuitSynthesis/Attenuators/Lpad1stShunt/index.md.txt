# L-Pad (1st Shunt) Attenuator

## Overview

L-pad attenuators are essentially broadband L-section matching networks. They are used mainly for impedance transformation (e.g. in network analyzers 50 Ohm to 75 Ohm).

### Topology

```
Input ──┬──[R2]── Output
        │         Zout ≠ Zin
       [R1]
        │
       GND
```

Shunt resistor R1 followed by series resistor R2.

### Design Equations

```
α = 10^(-Attenuation/10)    (power ratio, α < 1)

R₁ = Zin / (1 - √α)         (shunt)

R₂ = Zin × (1 - √α) / √α    (series)

Zout = -Zin × (α - 2√α + 2) / (α - 2√α)
```

### Power Dissipation

```
Pdiss_R1 = Pin × √α × (1 - 2√α + α) / (1 - √α)

Pdiss_R2 = Pin × (1 - √α)
```

### Example: 10 dB, Zin = 50 Ω, Pin = 1 W

```
α = 0.1
√α ≈ 0.316

R₁ = 50 / (1 - 0.316)
   ≈ 73.1 Ω

R₂ = 50 × (1 - 0.316) / 0.316
   ≈ 108.2 Ω

Zout = -50 × (0.1 - 2×0.316 + 2) / (0.1 - 2×0.316)
     = -50 × 1.468 / (-0.532)
     ≈ 138.0 Ω
```

**Power dissipation:**
```
Pdiss_R1 = 1 × 0.316 × (1 - 0.632 + 0.1) / (1 - 0.316) ≈ 0.216 W
Pdiss_R2 = 1 × (1 - 0.316) ≈ 0.684 W

Pout = 1 - 0.216 - 0.684 = 0.1 W  ✓
```

---

## Comparison: First Series vs. First Shunt

### 10 dB Example (Zin = 50 Ω)

| Parameter | First Series | First Shunt |
|-----------|--------------|-------------|
| **R₁ value** | 34.2 Ω | 73.1 Ω |
| **R₂ value** | 23.1 Ω | 108.2 Ω |
| **Zout** | 20.0 Ω | 138.0 Ω |
| **Power in R1** | 68.4% | 21.6% |
| **Power in R2** | 21.6% | 68.4% |

**Key observations:**
- **First series:** Zout < Zin (impedance step-down)
- **First shunt:** Zout > Zin (impedance step-up)
- Power distribution is **reversed** between topologies

### Output Impedance vs Topology

| Attenuation (dB) | First Series Zout | First Shunt Zout |
|------------------|-------------------|------------------|
| 3 | 35.4 Ω | 70.7 Ω |
| 6 | 25.0 Ω | 100.0 Ω |
| 10 | 20.0 Ω | 138.0 Ω |
| 20 | 16.7 Ω | 500.0 Ω |

- **First series:** Zout decreases with attenuation
- **First shunt:** Zout increases with attenuation