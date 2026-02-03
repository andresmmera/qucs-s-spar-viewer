# Parallel Resistors Calculator

## Overview

Calculates the equivalent resistance of any number of parallel resistors, along with the current and power dissipation through each one. Flags resistors that exceed a user-defined maximum power rating.

## Formulas

### Equivalent Resistance
```
R_eq = 1 / (1/R₁ + 1/R₂ + ... + 1/Rₙ)
```

### Per-Resistor Current (shared voltage ΔV)
```
Iₙ = ΔV / Rₙ
```

### Per-Resistor Power Dissipation
```
Pₙ = Iₙ² × Rₙ = ΔV² / Rₙ
```

## Input Parameters

| Parameter | Range | Default | Description |
|-----------|-------|---------|-------------|
| ΔV | 0 – 1000 V | 5 V | Voltage across the parallel network |
| P_max | 0 – 10000 mW | 50 mW | Per-resistor power threshold for warnings |
| R₁…Rₙ | dynamic | 1k | Resistor values (minimum 1) |

## Resistance Parsing

Resistor values are entered as strings and support standard shorthand notation. The prefix letter replaces the decimal point:

| Input | Parsed Value |
|-------|--------------|
| `470` | 470 Ω |
| `2k2` | 2200 Ω |
| `0k5` | 500 Ω |
| `22k` | 22 kΩ |
| `4.7meg` | 4.7 MΩ |
| `100m` | 100 mΩ |
| `1g` | 1 GΩ |

Supported prefixes: `m` (10⁻³), `k` (10³), `meg` (10⁶), `g` (10⁹).

## Output

- **R_{eq}**: Equivalent resistance of the full parallel network
- **Per-resistor table**: Current and power for each resistor, plus a total row
- **Power warning**: Any resistor whose dissipation exceeds P_max is highlighted

## Example

**Input:**
- ΔV: 5 V
- P_max: 50 mW
- R₁ = 1k, R₂ = 2k2, R₃ = 470

**Calculation:**
```
R_eq = 1 / (1/1000 + 1/2200 + 1/470)
     = 1 / (0.001 + 0.000454 + 0.002128)
     = 1 / 0.003583
     ≈ 279.1 Ω

I₁ = 5 / 1000   = 5 mA       →  P₁ = 5² × 1000    = 25 mW
I₂ = 5 / 2200   ≈ 2.27 mA    →  P₂ = 2.27² × 2200 ≈ 11.36 mW
I₃ = 5 / 470    ≈ 10.64 mA   →  P₃ = 10.64² × 470 ≈ 53.19 mW  ⚠️
```

**Output:**

| Resistor | Current | Power Dissipation |
|----------|---------|-------------------|
| R1 | 5 mA | 25 mW |
| R2 | 2.273 mA | 11.36 mW |
| R3 | 10.64 mA | **53.19 mW ⚠️** |
| **Total** | **17.91 mA** | **89.55 mW** |

R₃ exceeds the maximum dissipation power threshold (50 mW).