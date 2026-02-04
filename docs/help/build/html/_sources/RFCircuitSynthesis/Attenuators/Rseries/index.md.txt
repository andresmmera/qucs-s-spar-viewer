# Series Resistor Attenuator

## Overview

The simplest attenuator configurations using a **single resistor**. Used as a lossy matching network or when impedance matching is not required.

---

### Topology

```
Input ──[R]── Output
```

Single series resistor between source and load.

### Design Equation

Given:
- Source impedance: ZS
- Load impedance: ZL  
- Desired power attenuation: α (linear power ratio, α < 1)

The series resistor value is:

```
R = (-1) × ((ZL + ZS) × α - 2√(ZL × ZS × α)) / α
```

**Simplified for ZS = ZL = Z₀:**

```
R = 2 × Z₀ × (1/√α - 1)
```

### Impedances Seen

**Input impedance (looking into attenuator from source):**
```
Zin = R + ZL
```

**Output impedance (looking back from load):**
```
Zout = R + ZS
```

### Power Dissipation

```
Pdiss = Pin × (1 - α)
```

All dissipated power goes into the single resistor.

### Example: 10 dB, ZS = ZL = 50 Ω, Pin = 1 W

```
α = 10^(-10/10) = 0.1
√α ≈ 0.316

R = 2 × 50 × (1/0.316 - 1)
  = 2 × 50 × (3.162 - 1)
  = 216.2 Ω

Zin = 216.2 + 50 = 266.2 Ω
Zout = 216.2 + 50 = 266.2 Ω

Pdiss = 1 × (1 - 0.1) = 0.9 W
```

### VSWR at Input

When ZS ≠ Zin:

```
VSWR_in = (Zin/ZS)    if Zin > ZS
        = (ZS/Zin)    if ZS > Zin
```

For the example above:
```
VSWR_in = 266.2 / 50 = 5.32:1  (poor match)
```