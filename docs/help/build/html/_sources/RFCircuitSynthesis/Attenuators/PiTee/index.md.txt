# Pi and Tee Attenuators

## Overview

Pi and Tee are the two most common bilateral matched attenuator topologies. Both provide perfect impedance match when Zin = Zout = Z₀.

## Pi Attenuator

### Topology

```
Input ──┬──[R2]──┬── Output
        │        │
       [R1]     [R3]
        │        │
       GND      GND
```

Two shunt resistors (R1, R3) with one series resistor (R2).

### Design Equations

```
L = 10^(Attenuation/10)

R₂ = 0.5 × (L - 1) × √(Zin × Zout / L)

R₁ = 1 / (((L + 1) / (Zin × (L - 1))) - (1 / R₂))

R₃ = 1 / (((L + 1) / (Zout × (L - 1))) - (1 / R₂))
```

For **matched** case (Zin = Zout = Z₀):
```
R₁ = R₃ = Z₀ × (L + 1) / (L - 1)
R₂ = Z₀ × (L² - 1) / (2L)
```

### Power Dissipation

```
Pdiss_R1 = Pin × Zin / R₁

Pdiss_R2 = Pin × R₂ × (R₁ - Zin)² / (R₁² × Zin)

K = R₁ × R₂ - Zin × (R₁ + R₂)
Pdiss_R3 = Pin × K² / (R₁² × R₃ × Zin)
```

## Tee Attenuator

### Topology

```
Input ──[R1]──┬──[R3]── Output
              │
             [R2]
              │
             GND
```

Two series resistors (R1, R3) with one shunt resistor (R2).

### Design Equations

```
L = 10^(Attenuation/10)

R₂ = (2 × √(Zin × Zout × L)) / (L - 1)

R₁ = Zin × ((L + 1) / (L - 1)) - R₂

R₃ = Zout × ((L + 1) / (L - 1)) - R₂
```

For **matched** case (Zin = Zout = Z₀):
```
R₁ = R₃ = Z₀ × (L - 1) / (L + 1)
R₂ = 2 × Z₀ × L / (L² - 1)
```

### Power Dissipation

```
Pdiss_R1 = Pin × R₁ / Zin

Pdiss_R2 = Pin × (R₁ - Zin)² / (R₂ × Zin)

Pdiss_R3 = Pin × R₃ × (R₁ + R₂ - Zin)² / (Zin × R₂²)
```

## Example: 10 dB Matched Attenuator (Z₀ = 50 Ω)

**Given:**
- Attenuation = 10 dB
- Z₀ = 50 Ω
- Pin = 30 dBm (1 W)

**Calculation:**
```
L = 10^(10/10) = 10
```

**Pi Attenuator:**
```
R₁ = R₃ = 50 × (10 + 1) / (10 - 1) = 61.1 Ω
R₂ = 50 × (10² - 1) / (2 × 10) = 247.5 Ω

Pdiss_R1 ≈ 0.082 W
Pdiss_R2 ≈ 0.018 W
Pdiss_R3 ≈ 0.82 W
```

**Tee Attenuator:**
```
R₁ = R₃ = 50 × (10 - 1) / (10 + 1) = 40.9 Ω
R₂ = 2 × 50 × 10 / (10² - 1) = 10.1 Ω

Pdiss_R1 ≈ 0.818 W
Pdiss_R2 ≈ 0.082 W
Pdiss_R3 ≈ 0.001 W
```

## Pi vs. Tee Comparison

| Characteristic | Pi | Tee |
|----------------|----|----|
| **Series resistor value** | Higher | Lower |
| **Shunt resistor value** | Lower | Higher |
| **High attenuation** | Series R₂ becomes very large | Shunt R₂ becomes very small |
| **Low attenuation** | Shunt R₁,R₃ become very large | Series R₁,R₃ become very small |
| **Preferred for high Z₀** | Tee (smaller shunt R) | — |
| **Preferred for low Z₀** | Pi (larger shunt R) | — |

## Advantages

- Matched at both ports
- Broadband
- Easy to implement with chip resistors

## References

Vizmuller, P. (1995). *RF Design Guide: Systems, Circuits, and Equations*, Chapter 3. Artech House.