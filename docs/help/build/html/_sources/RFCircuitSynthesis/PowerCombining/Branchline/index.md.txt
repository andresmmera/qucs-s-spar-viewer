
# Branch-Line Coupler (Quadrature Hybrid)

## Overview

The branch-line coupler is a four-port network that provides **90° phase difference** (quadrature) between output ports. Also called a quadrature hybrid or 3 dB coupler, it's essential for applications requiring phase quadrature.

## Topology

```
Port 1 ─────────[ZA]──────── Port 2
(Input)    │           |    (Through, 0°)
           │           │
         [ZB]        [ZB]
           │           │
           │           │
Port 4 ─────────[ZA]──────── Port 3
    (Isolated)            (Coupled, -90°)
```

## Design Equations

### Power Split Ratio

K = P₂/P₃

### Transmission Line Impedances

```
ZA = Z₀ / √2 ≈ 0.707 × Z₀
ZB = Z₀
R = Z₀
```

**For Z₀ = 50 Ω:**
```
ZA = 35.4 Ω
ZB = 50 Ω
R = 50 Ω
```

## Advantages

1. **Quadrature outputs**
2. **Broader BW:** with respect to the single box Branch-Line coupler

## Limitations

1. **Narrowband:** 10-20% fractional BW (single octave max)
2. **Large size:** Four λ/4 lines (larger than Wilkinson)
3. **Low ZA for large K:** ZA → 0 as K → ∞ (hard to fabricate)

## Comparison with Wilkinson

| Feature | Branch-Line | Wilkinson |
|---------|-------------|-----------|
| **Phase** | 90° (quadrature) | 0° (in-phase) |
| **Outputs** | 2 | 2 |
| **Bandwidth** | 10-20% | 20-40% |
| **Size** | Larger (4 lines) | Smaller (2 lines) |
| **Isolation** | 15-25 dB | 20-30 dB |
| **Application** | IQ, mixers | General power split |

## References

[1] Pozar, D. M. (2012). *Microwave Engineering* (4th ed.), Section 7.5, pp. 347-352. Wiley.