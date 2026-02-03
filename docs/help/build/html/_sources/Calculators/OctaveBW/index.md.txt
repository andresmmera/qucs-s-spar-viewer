# Octave Bandwidth Calculator

## Overview

Given a low and high corner frequency, computes the bandwidth, number of octaves and decades, center frequencies, and quality factor of the band.

## Formulas

### Center Frequencies
```
f_c (arithmetic) = (f_high - f_low) / 2
f_c (geometric)  = √(f_low × f_high)
```

### Bandwidth
```
BW = f_high - f_low
```

### Octaves and Decades
```
Octaves = log₂(f_high / f_low)
Decades = log₁₀(f_high / f_low)
```

### Quality Factor
```
Q = f_c (arithmetic) / BW
```

## Input Parameters

| Parameter | Range | Default | Description |
|-----------|-------|---------|-------------|
| f_low | 1 – 10¹² | 1000 | Lower corner frequency |
| f_high | 1 – 10¹² | 2000 | Upper corner frequency |

Both frequencies must share the same unit (Hz, kHz, MHz, etc.). The calculator does not perform unit conversion — the outputs inherit whatever unit the inputs use.

## Output

| Parameter | Description |
|-----------|-------------|
| Central freq (Arithmetic mean) | Midpoint of the band |
| Central freq (Geometric mean) | Log-scale midpoint; preferred for RF |
| BW | Linear bandwidth |
| # Octaves | Number of frequency doublings in the band |
| # Decades | Number of frequency ×10 steps in the band |
| Q | Quality factor of the band |

An error is displayed if f_high ≤ f_low. Q is shown as ∞ when BW is effectively zero.

## Example

**Input:**
- f_low: 1000 MHz
- f_high: 4000 MHz

**Calculation:**
```
f_c (arithmetic) = (4000 - 1000) / 2        = 1500 MHz
f_c (geometric)  = √(1000 × 4000)           = 2000 MHz
BW               = 4000 - 1000              = 3000 MHz
Octaves          = log₂(4000 / 1000)        = log₂(4) = 2.0
Decades          = log₁₀(4000 / 1000)       = log₁₀(4) ≈ 0.6
Q                = 1500 / 3000              = 0.5
```

**Output:**

| Parameter | Value |
|-----------|-------|
| Central freq (Arithmetic mean) | 1500.0 |
| Central freq (Geometric mean) | 2000.0 |
| BW | 3000.0 |
| # Octaves | 2.0 |
| # Decades | 0.6 |
| Q | 0.5 |

## Notes

- Exactly 1 octave corresponds to a 2:1 frequency ratio; 1 decade to a 10:1 ratio