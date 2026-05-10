# RF Power Converter

## Overview

Converts RF power values between linear and logarithmic units, supporting both 50 Ω and 75 Ω system impedances for dBμV and dBmV, and an arbitrary reference impedance for voltage (V) units.

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
| dBpW | Logarithmic | 1 pW |
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
| V (Z₀) | P_W = V² / Z₀ |
| dBμV (50 Ω) | P_W = 10^((P - 136.99) / 10) |
| dBmV (50 Ω) | P_W = 10^((P - 76.99) / 10) |
| dBpW | P_W = 10^((P - 120) / 10) |

### From Watts

| Unit | Formula |
|------|---------|
| W | P = P_W |
| mW | P = P_W × 10³ |
| dBm | P = 10 × log₁₀(P_W) + 30 |
| dBμV (75 Ω) | P = 10 × log₁₀(P_W) + 138.75 |
| dBmV (75 Ω) | P = 10 × log₁₀(P_W) + 78.75 |
| V (Z₀) | P = √(P_W × Z₀) |
| dBμV (50 Ω) | P = 10 × log₁₀(P_W) + 136.99 |
| dBmV (50 Ω) | P = 10 × log₁₀(P_W) + 76.99 |
| dBpW | P = 10 × log₁₀(P_W) + 120 |

## Direct Conversion Summary

| from \ to | W | dBm | dBμV (75 Ω) | dBmV (75 Ω) | dBμV (50 Ω) | dBmV (50 Ω) | dBpW |
|-----------|---|-----|-------------|-------------|-------------|-------------|------|
| **W** | — | 10·log₁₀(P) + 30 | 10·log₁₀(P) + 138.75 | 10·log₁₀(P) + 78.75 | 10·log₁₀(P) + 136.99 | 10·log₁₀(P) + 76.99 | 10·log₁₀(P) + 120 |
| **dBm** | 10^(0.1·P − 30) | — | P + 108.75 | P + 48.75 | P + 106.99 | P + 46.99 | P + 90 |
| **dBμV (75 Ω)** | 10^(0.1·P − 138.75) | P − 108.75 | — | P − 60 | P − 1.76 | P − 61.76 | P − 18.75 |
| **dBmV (75 Ω)** | 10^(0.1·P − 78.75) | P − 48.75 | P + 60 | — | P + 58.35 | P − 1.76 | P + 41.25 |
| **dBμV (50 Ω)** | 10^(0.1·P − 136.99) | P − 106.99 | P + 1.76 | P − 58.35 | — | P − 60 | P − 16.99 |
| **dBmV (50 Ω)** | 10^(0.1·P − 76.99) | P − 46.99 | P + 61.76 | P + 1.76 | P + 60 | — | P + 43.01 |
| **dBpW** | 10^(0.1·P − 120) | P − 90 | P + 18.75 | P − 41.25 | P + 16.99 | P − 43.01 | — |
