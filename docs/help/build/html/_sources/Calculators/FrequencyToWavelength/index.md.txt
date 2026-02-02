# Frequency ↔ Wavelength Converter

## Overview

The Frequency-Wavelength converter provides bidirectional conversion between frequency and wavelength, accounting for the medium's relative permittivity.

## Formulas

### Frequency to Wavelength
```
λ = c / (f × √εᵣ)
```

### Wavelength to Frequency
```
f = c / (λ × √εᵣ)
```

Where:
- `λ` = wavelength in meters
- `f` = frequency in Hz
- `c` = speed of light (299,792,458 m/s)
- `εᵣ` = relative permittivity of the medium

## Conversion Modes

The calculator supports two modes:
1. **Frequency → Wavelength**: Input frequency, calculate wavelength
2. **Wavelength → Frequency**: Input wavelength, calculate frequency

## Output

The calculator displays:
- **Frequency (f)**: Operating frequency
- **λ**: Wavelength
- **λ/2**: Half wavelength
- **λ/4**: Quarter wavelength

## Example 1: Frequency to Wavelength

**Input:**
- Mode: Frequency → Wavelength
- Frequency: 1000 MHz
- εᵣ: 4.7 (FR4)

**Calculation:**
```
f = 1×10⁹ Hz
√εᵣ = √4.7 ≈ 2.168
λ = 299,792,458 / (10⁹ × 2.168)
  = 13.8 cm
```
## Example 2: Wavelength to Frequency

**Input:**
- Mode: Wavelength → Frequency
- Wavelength: 30 cm
- εᵣ: 1.0 (vacuum/air)

**Calculation:**
```
λ = 0.30 m
√εᵣ = √1.0 = 1.0
f = 299,792,458 / (0.30 × 1.0)
  = 999.3 MHz
```


## Common Material Permittivities

| Material | εᵣ (Typical) |
|----------|--------------|
| Vacuum/Air | 1.0 |
| RO4003C  | 3.55 |
| FR4 | 4.3 - 4.7 |
| Alumina | 9.8 |

## Notes

- The wavelength is shorter in materials with higher permittivity
- Permittivity must be ≥ 1