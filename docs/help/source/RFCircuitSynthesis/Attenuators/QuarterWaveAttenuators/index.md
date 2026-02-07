# Quarter-Wave Attenuators

## Overview

Narrowband matched attenuators using a quarter-wavelength (λ/4) transmission line section combined with resistive elements. Provides attenuation at a specific frequency with excellent match.

## Quarter-Wave Series Attenuator

### Topology (Distributed)

```
Input ──┬──[λ/4 TL]──┬── Output
        │    Z₀      │
       [R]          [R]
        │            │
       GND          GND
         └──[Z₀]──┘
             │
            GND
```

Series resistor R in parallel with λ/4 shunt line.

### Topology (Lumped Equivalent)

```
Input ──┬──[L]──┬── Output
        │       │
       [C]     [R]
        │   │   │
       GND [R] GND
            │
        [Z₀][C]
         │   │
        GND GND
```

### Design Equations

```
R = Zin / (10^(0.05 × Attenuation) - 1)

l_λ/4 = c / (4 × f)

Zout = R + Zin × (R + Zin) / (2R + Zin)
```

**For lumped implementation (low frequency):**
```
ω₀ = 2πf
L = Zin / ω₀
C = 1 / (Zin × ω₀)
```

### Power Dissipation

```
K = (R + Zin)²

Pdiss_R1 = Pin × Zin × R / K    (shunt at input)
Pdiss_R2 = Pin × R² / K         (series path)
Pdiss_R3 = Pin × Zin × R / K    (shunt via λ/4)
```

## Quarter-Wave Shunt Attenuator

### Topology (Distributed)

```
Input ──[R]──┬── Output
             │
         [λ/4 TL]
             Z₀
          │  │  │
        [Z₀][R][Z₀]
          │  │  │
         GND GND GND
```

Shunt resistors with λ/4 line providing transformation.

### Design Equations

```
R = Zin × (10^(0.05 × Attenuation) - 1)

l_λ/4 = c / (4 × f)

Zout = R + Zin × (R + Zin) / (2R + Zin)
```

**For lumped implementation:**
```
L = Zin / ω₀
C = 1 / (Zin × ω₀)
```

### Power Dissipation

```
K = (R + Zin)²

Pdiss_R1 = Pin × Zin × R / K
Pdiss_R2 = Pin × Zin² / K
Pdiss_R3 = Pin × Zin × R / K
```

## Example: 10 dB at 2 GHz, Z₀ = 50 Ω

### Quarter-Wave Series

```
R = 50 / (10^(0.05 × 10) - 1)
  = 50 / (10^0.5 - 1)
  = 50 / 2.162
  ≈ 23.1 Ω

λ/4 = (3×10⁸) / (4 × 2×10⁹)
    = 37.5 mm

Zout ≈ 35.8 Ω
```

**Resistor values:**
- R1 (input shunt): 23.1 Ω
- R2 (series): 23.1 Ω  
- R3 (λ/4 shunt): 23.1 Ω
- λ/4 line: Z₀=50Ω, l=37.5mm

### Quarter-Wave Shunt

```
R = 50 × (10^0.5 - 1)
  ≈ 108.1 Ω

λ/4 = 37.5 mm

Zout ≈ 141.0 Ω
```

**Resistor values:**
- R1 (first shunt): 108.1 Ω
- R2 (λ/4 bottom, Z₀): 50 Ω
- R3 (second shunt): 108.1 Ω
- λ/4 line: Z₀=50Ω, l=37.5mm

## Limitations

- **Narrowband** (typically 20-30% fractional BW)
- Physical size large at lower frequencies


## References

[1] Doherty, W. E., & Joos, R. D. (1998). *The PIN Diode Circuit Designer's Handbook*, Chapter 5: Reflection Attenuators. Microsemi Corp.

## See Also

```{toctree}
:maxdepth: 1
/RFCircuitSynthesis/index
/RFCircuitSynthesis/Attenuators/index
```