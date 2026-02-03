# RF Power Converter

## Overview

Converts RF power values between linear and logarithmic units, supporting both 50 Ω and 75 Ω system impedances. All conversions route through watts as an intermediate unit.

## Conversion Pipeline

```
Input (any unit) → Watts → Output (any unit)
```

## Supported Units

| Unit | Type | Reference |
|------|------|-----------|
| W | Linear | — |
| mW | Linear | — |
| dBm | Logarithmic | 1 mW |
| dBμV | Logarithmic | 1 μV |
| dBmV | Logarithmic | 1 mV |
| V | Linear | Z₀ |

Each of dBμV, dBmV, and V is available in both 50 Ω and 75 Ω variants.

## Formulas

### To Watts

| Unit | Formula |
|------|---------|
| W | P_W = P |
| mW | P_W = P × 10⁻³ |
| dBm | P_W = 10^((P - 30) / 10) |
| dBμV (75 Ω) | P_W = 10^((P - 138.75) / 10) |
| dBmV (75 Ω) | P_W = 10^((P - 78.75) / 10) |
| V (75 Ω) | P_W = V² / 75 |
| dBμV (50 Ω) | P_W = 10^((P - 136.99) / 10) |
| dBmV (50 Ω) | P_W = 10^((P - 76.99) / 10) |
| V (50 Ω) | P_W = V² / 50 |

### From Watts

Each formula above is simply inverted. For example:
```
dBm  = 10 × log₁₀(P_W) + 30
V    = √(P_W × Z₀)
```

## Input Parameters

- Power
- Input unit
- Output unit

## Example

**Input:**
- Power: 0 dBm
- Output unit: dBμV (Z₀ = 75 Ω)

**Calculation:**
```
To watts:
  P_W = 10^((0 - 30) / 10) = 10^(-3) = 0.001 W

From watts to dBμV (75 Ω):
  dBμV = 10 × log₁₀(0.001) + 138.75
       = -30 + 138.75
       = 108.75 dBμV
```

**Output:** `108.75 dBμV (Z₀ = 75 Ω)`