# Lowpass Prototype Coefficients

## Overview

All filter implementations begin with normalized lowpass prototype coefficients `gₖ`. These dimensionless values represent a normalized lowpass filter with:
- Source and load impedance = 1 Ω
- Cutoff frequency = 1 rad/s

The prototype is then scaled and transformed to produce the desired filter response.

## Coefficient Calculation

### Butterworth

Maximally flat magnitude response.

**Formula:**
```
gₖ = 2 × sin(π(2k-1)/(2N))    for k = 1 to N
g₀ = 1 (source)
gₙ₊₁ = 1 (load)
```

**Example (N=3):**
```
g₁ = 2 × sin(π/6) = 1.0000
g₂ = 2 × sin(π/2) = 2.0000
g₃ = 2 × sin(5π/6) = 1.0000
```

### Chebyshev

Equal-ripple in passband, steeper rolloff than Butterworth.

**Formula:**
```
β = ln(1 / tanh(Ripple_dB / 17.37))
γ = sinh(β / (2N))

aₖ = sin(π(2k-1)/(2N))
bₖ = γ² + sin²(kπ/N)

g₁ = 2a₁ / γ
gₖ = (4aₖ₋₁aₖ) / (bₖ₋₁gₖ₋₁)   for k = 2 to N

g₀ = 1 (source)
gₙ₊₁ = 1/tanh²(β/4)   if N is even
gₙ₊₁ = 1              if N is odd
```

**Example (N=3, Ripple=0.1 dB):**
```
g₁ ≈ 1.0316
g₂ ≈ 1.1474
g₃ ≈ 1.0316
g₄ = 1.0000
```

### Bessel

Maximally flat group delay (linear phase). Coefficients are **pre-calculated** from Zverev tables.

**Example (N=3):**
```
g₁ = 0.3374
g₂ = 0.9705
g₃ = 2.2034
```

### Gaussian

Gaussian-shaped impulse response. Coefficients are **pre-calculated** from Zverev tables.

**Example (N=3):**
```
g₁ = 0.2624
g₂ = 0.8167
g₃ = 2.2262
```

### Legendre

Steepest monotonic rolloff (no passband ripple). Coefficients are **pre-calculated** from Zverev tables.

**Example (N=3):**
```
g₁ = 1.1737
g₂ = 1.3538
g₃ = 2.1801
```

## Coefficient Tables (N = 2 to 10)

Pre-calculated coefficients for Bessel, Gaussian, and Legendre responses are stored in lookup tables for orders 2 through 10. For orders outside this range or for Butterworth/Chebyshev responses, coefficients are computed analytically.

## Transformation to Physical Filters

The normalized prototype `gₖ` values are transformed based on the desired filter type:

| Filter Type | Transformation |
|-------------|----------------|
| **Lowpass** | Scale by fc and Z₀ |
| **Highpass** | Swap L↔C, invert gₖ, scale by fc and Z₀ |
| **Bandpass** | Replace each element with resonator, scale by fc, BW, Z₀ |
| **Bandstop** | Replace with dual resonator, scale by fc, BW, Z₀ |

See individual filter documentation for specific transformation equations.

## Zverev Tables vs. Computed Coefficients

The tool supports two coefficient sources:

### Standard (Computed)
- Butterworth and Chebyshev computed from formulas
- Bessel, Gaussian, Legendre from pre-calculated tables
- **Load impedance:** g₀ = gₙ₊₁ = 1 Ω

### Zverev Tables
- All responses use pre-calculated values
- **Load impedance:** May differ from source (gₙ₊₁ ≠ 1)
- Historically used for hand calculations

The "Use Zverev Tables" option affects load impedance handling in the final design.

## Ripple Correction (Chebyshev Only)

For Chebyshev filters, the cutoff frequency can be adjusted so that fc corresponds to the -3 dB point rather than the ripple edge:

**Lowpass/Highpass correction:**
```
ε = √(10^(Ripple_dB/10) - 1)
fc_corrected = fc × cosh(acosh(1/ε) / N)
```

This is automatically applied when "Use Zverev Tables" is disabled.

## References

[1] Matthaei, G. L., Young, L., & Jones, E. M. T. (1964). *Microwave Filters, Impedance-Matching Networks, and Coupling Structures*. Artech House.

[2] Zverev, A. I. (1967). *Handbook of Filter Synthesis*. Wiley.