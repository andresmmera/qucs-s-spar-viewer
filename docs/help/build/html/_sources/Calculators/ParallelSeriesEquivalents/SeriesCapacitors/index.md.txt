# Series Capacitors Calculator

## Overview

Calculates the equivalent capacitance of any number of capacitors connected in series.

## Formula

```
C_eq = 1 / (1/C₁ + 1/C₂ + ... + 1/Cₙ)
```

Series capacitance follows the same reciprocal-sum structure as parallel resistances and parallel inductances. The equivalent capacitance is always less than the smallest individual capacitor.

## Input Parameters

| Parameter | Default | Description |
|-----------|---------|-------------|
| C₁…Cₙ | 1pF | Capacitance values |

## Capacitance Parsing

Values are entered as strings using standard shorthand notation, where the prefix letter replaces the decimal point. A trailing `F` is optional and ignored.

| Input | Parsed Value |
|-------|--------------|
| `100` | 100 F |
| `1pF` | 1 pF |
| `4n7` | 4.7 nF |
| `0p5F` | 0.5 pF |
| `22uF` | 22 μF |
| `10n` | 10 nF |

Supported prefixes: `p` (10⁻¹²), `n` (10⁻⁹), `u` (10⁻⁶), `m` (10⁻³). Output formatting also covers `fF` (10⁻¹⁵).

## Output

- **C_{eq}**: Equivalent capacitance of the series network

## Example

**Input:**
- C₁ = 1pF, C₂ = 2p2, C₃ = 4n7

**Calculation:**
```
C_eq = 1 / (1/1e-12 + 1/2.2e-12 + 1/4.7e-9)
     = 1 / (1e12 + 4.545e11 + 2.128e8)
     ≈ 1 / (1.4549e12)
     ≈ 0.6873 pF
```

**Output:**

| Parameter | Value |
|-----------|-------|
| C_{eq} | 0.6873 pF |

In this case C₁ and C₂ dominate because they are orders of magnitude smaller than C₃ — the series result is pulled toward the smallest capacitor.
