# Parallel Inductors Calculator

## Overview

Calculates the equivalent inductance of any number of inductors connected in parallel.

## Formula

```
L_eq = 1 / (1/L₁ + 1/L₂ + ... + 1/Lₙ)
```

This is analogous to the parallel resistance formula — the equivalent inductance is always less than the smallest individual inductor.

## Input Parameters

| Parameter | Default | Description |
|-----------|---------|-------------|
| L₁…Lₙ | 10nH | Inductance values |

## Inductance Parsing

Values are entered as strings using standard shorthand notation, where the prefix letter replaces the decimal point. A trailing `H` is optional and ignored.

| Input | Parsed Value |
|-------|--------------|
| `470` | 470 H |
| `10nH` | 10 nH |
| `2u2` | 2.2 μH |
| `0u5H` | 500 nH |
| `4m7` | 4.7 mH |
| `22uH` | 22 μH |

Supported prefixes: `n` (10⁻⁹), `u` (10⁻⁶), `m` (10⁻³), `meg` (10⁶).

## Output

- **L_{eq}**: Equivalent inductance of the parallel network

## Example

**Input:**
- L₁ = 10nH, L₂ = 22nH, L₃ = 4n7

**Calculation:**
```
L_eq = 1 / (1/10e-9 + 1/22e-9 + 1/4.7e-9)
     = 1 / (1e8 + 4.545e7 + 2.128e8)
     = 1 / (3.583e8)
     ≈ 2.792 nH
```

**Output:**

| Parameter | Value |
|-----------|-------|
| L_eq | 2.792 nH |
