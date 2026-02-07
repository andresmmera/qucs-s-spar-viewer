# Reflection Coefficient Calculators

## Overview

Three calculators for the conversion between reflection coefficient and impedance units. They share the same core set of relationships between reflection coefficient (Γ), impedance (Z), VSWR, and S11, but each takes a different quantity as input.

| Calculator | Input | Outputs |
|------------|-------|---------|
| Γ Calculator | \|Γ\|, ∠Γ, Z₀ | Re{Z}, Im{Z}, VSWR, S11 |
| Impedance Calculator | Re{Z}, Im{Z}, Z₀ | Γ (polar), VSWR, S11 |
| VSWR ↔ S11 ↔ \|Γ\| | VSWR **or** S11 **or** \|Γ\| | The other two |

## Core Formulas

### Reflection Coefficient ↔ Impedance
```
Γ = (Z - Z₀) / (Z + Z₀)          (complex)
Z = Z₀ × (1 + Γ) / (1 - Γ)       (complex)
```

### VSWR
```
VSWR = (1 + |Γ|) / (1 - |Γ|)     valid for |Γ| < 1
|Γ|  = (VSWR - 1) / (VSWR + 1)
```

### S11
```
S11 (dB) = 20 × log₁₀(|Γ|)
|Γ|      = 10^(S11 / 20)
```

## Γ Calculator

Converts a reflection coefficient given in polar form to load impedance and match quality metrics.

**Inputs:**

| Parameter | Range | Default |
|-----------|-------|---------|
| \|Γ\| | 0 – 10 | 0.2 |
| ∠Γ | -360° – 360° | 0° |
| Z₀ | 0.1 – 10⁶ Ω | 50 Ω |

Γ is reconstructed in rectangular form before the impedance calculation:
```
Γ = |Γ| × cos(∠Γ) + j × |Γ| × sin(∠Γ)
```

VSWR is shown as ∞ when \|Γ\| ≥ 1. S11 is shown as −∞ when \|Γ\| = 0.

## Impedance Calculator

The inverse of the Γ calculator — takes a complex load impedance and produces Γ in polar form.

**Inputs:**

| Parameter | Range | Default |
|-----------|-------|---------|
| Re{Z} | -10⁶ – 10⁶ Ω | 75 Ω |
| Im{Z} | -10⁶ – 10⁶ Ω | 0 Ω |
| Z₀ | 0.1 – 10⁶ Ω | 50 Ω |

Γ is displayed in polar notation: `|Γ| ∠ angle°`.

## VSWR ↔ S11 ↔ |Γ| Calculator

A three-mode converter that takes any one of the three scalar match metrics and computes the other two. No impedance or phase information is involved — only magnitudes.

**Modes and valid input ranges:**

| Mode | Input | Range |
|------|-------|-------|
| VSWR → \|Γ\|, S11 | VSWR | 1.0 – 1000 |
| S11 → \|Γ\|, VSWR | S11 (dB) | -100 – 0 |
| \|Γ\| → S11, VSWR | \|Γ\| | 0 – 1 |

## Example

**Scenario:** A load of Z = 75 + j10 Ω on a 50 Ω line.

**Impedance Calculator path:**
```
Γ = (75 + j10 - 50) / (75 + j10 + 50)
  = (25 + j10) / (125 + j10)
  |Γ| ≈ 0.205,  ∠Γ ≈ 19.9°

VSWR = (1 + 0.205) / (1 - 0.205) ≈ 1.52
S11  = 20 × log₁₀(0.205) ≈ -13.8 dB
```

**Verify with VSWR ↔ S11 ↔ |Γ| calculator (mode: |Γ| → S11, VSWR):**
```
Input:  |Γ| = 0.205
Output: S11 ≈ -13.8 dB,  VSWR ≈ 1.52   ✓
```

**Verify with Γ calculator (reverse):**
```
Input:  |Γ| = 0.205,  ∠Γ = 19.9°,  Z₀ = 50 Ω
Output: Re{Z} ≈ 75.0 Ω,  Im{Z} ≈ 10.0 Ω   ✓
```

## Edge Cases

| Condition | Γ Calc | Z Calc | SWR/S11 Calc |
|-----------|--------|--------|--------------|
| Perfect match (Z = Z₀) | S11 = −∞ | Γ = 0 ∠ 0° | S11 = −∞ |
| Total reflection (\|Γ\| = 1) | VSWR = ∞ | VSWR = ∞ | VSWR = ∞ |
| Z + Z₀ = 0 | — | Γ = Undefined | — |

## Notes

- VSWR is only meaningful for \|Γ\| < 1; values ≥ 1 indicate total or over-unity reflection
- The Γ calculator accepts \|Γ\| up to 10 to allow exploration of active/amplifying loads, but VSWR will be flagged as ∞ for \|Γ\| ≥ 1
- All three calculators are consistent — output from any one can be fed as input to another