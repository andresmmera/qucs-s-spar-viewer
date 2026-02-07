# Shunt Resistor Attenuator

## Overview

The simplest attenuator configurations using a **single resistor**. Used as a lossy matching network or when impedance matching is not required.

---

### Topology

```
Input ──┬── Output
        │
       [R]
        │
       GND
```

Single shunt resistor to ground.

### Design Equation

Given:
- Source impedance: ZS
- Load impedance: ZL
- Desired power attenuation: α (linear power ratio, α < 1)

The shunt resistor value is:

```
R = (2√(ZL × ZS × α) × ZL × ZS + (ZL² × ZS + ZL × ZS²) × α) / 
    (4 × ZL × ZS - (ZL² + 2×ZL×ZS + ZS²) × α)
```

**Simplified for ZS = ZL = Z₀:**

```
R = Z₀ × (1 + √α) / (1 - √α)
```

### Impedances Seen

**Input impedance:**
```
Zin = R ∥ ZL = (R × ZL) / (R + ZL)
```

**Output impedance:**
```
Zout = R ∥ ZS = (R × ZS) / (R + ZS)
```

### Power Dissipation

```
Pdiss = Pin × (1 - α)
```

### Example: 10 dB, ZS = ZL = 50 Ω, Pin = 1 W

```
α = 0.1
√α ≈ 0.316

R = 50 × (1 + 0.316) / (1 - 0.316)
  = 50 × 1.316 / 0.684
  ≈ 96.2 Ω

Zin = (96.2 × 50) / (96.2 + 50) ≈ 32.9 Ω
Zout = (96.2 × 50) / (96.2 + 50) ≈ 32.9 Ω

Pdiss = 1 × (1 - 0.1) = 0.9 W
```

### VSWR at Input

```
VSWR_in = 50 / 32.9 ≈ 1.52:1  (better than series, but still mismatched)
```

---

## Comparison: R-Series vs. R-Shunt

### 10 dB Example (ZS = ZL = 50 Ω)

| Parameter | R-Series | R-Shunt |
|-----------|----------|---------|
| **R value** | 216.2 Ω | 96.2 Ω |
| **Zin** | 266.2 Ω | 32.9 Ω |
| **Zout** | 266.2 Ω | 32.9 Ω |
| **VSWR (50Ω system)** | 5.32:1 | 1.52:1 |
| **Power dissipation** | 0.9 W | 0.9 W |

**Key observations:**
- **R-series:** Increases impedance (poor match)
- **R-shunt:** Decreases impedance (better match, but still poor)
- **Both:** Same power dissipation
- **Shunt has better VSWR** for same attenuation

### Attenuation Range

| Attenuation (dB) | R-Series (Ω) | R-Shunt (Ω) | VSWR_in (Series) | VSWR_in (Shunt) |
|------------------|--------------|-------------|------------------|-----------------|
| 3 | 70.7 | 183.3 | 2.41:1 | 1.37:1 |
| 6 | 100.0 | 125.0 | 3.00:1 | 1.60:1 |
| 10 | 216.2 | 96.2 | 5.32:1 | 1.52:1 |
| 20 | 495.0 | 55.3 | 10.9:1 | 1.11:1 |

**Trend:**
- **R-series:** VSWR worsens dramatically with attenuation
- **R-shunt:** VSWR improves slightly with attenuation (but output impedance drops)

---

## Advantages

1. **Extremely simple**
2. **Low cost:**
3. **Broadband:** Resistive, works DC to GHz (limited by parasitics)
4. **Small size:** Smallest footprint
5. **Predictable:** No resonances or complex behavior

## Limitations

1. **Poor impedance match:** High VSWR at both ports
2. **Attenuation depends on source/load impedances:** Not constant like matched designs
3. **Reflections:** Standing waves in transmission line systems
4. **Bidirectional mismatch:** Both input and output are affected
5. **Not suitable for RF:** Mismatch causes measurement errors, signal integrity issues


## See Also

```{toctree}
:maxdepth: 1
/RFCircuitSynthesis/index
/RFCircuitSynthesis/Attenuators/index
```