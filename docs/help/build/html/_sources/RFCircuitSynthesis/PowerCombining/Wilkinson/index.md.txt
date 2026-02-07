# Wilkinson Power Divider

## Overview

The Wilkinson power divider is the most widely used RF power splitter topology. It provides **matched ports**, **high isolation** between outputs, and can be designed for **equal** or **unequal** power split ratios.

## Topology

```
           ┌───[Zbr, λ/4]──── Output #1
           │               |
Input  ────┤              [R]
           │               |
           └───[Zbr, λ/4]──── Output #2

```

**Key components:**
- Two λ/4 transmission line branches
- One isolation resistor (R) between outputs. If the balance is perfect, no current flows through it.

## Design Equations

### Equal Power Split (K = 1, 0 dB ratio)

```{math}
Z₂ = Z₃ = √2 × Z₀ ≈ 70.7 Ω  (for Z₀ = 50Ω)
R = 2 × Z₀ = 100 Ω
```

**Power division:**
```{math}
P₂ = P₃ = Pin / 2  (3 dB to each output)
```

### Unequal Power Split (K ≠ 1)

Power ratio: K = P₂/P₃ (linear), or K_dB = 10 × log₁₀(K)

**Branch impedances:**
```{math}
Z₂ = Z₀ × √(2 × (1 + K) / K)
Z₃ = Z₀ × √(2 × (1 + K))
```

**Isolation resistor:**
```{math}
R₂ = Z₀ × K        (series with Port 2)
R₃ = Z₀ / K        (series with Port 3)
R = R₂ + R₃ = Z₀ × (K + 1/K)
```

**Power division:**
```{math}
P₂ = Pin × K/(K + 1)
P₃ = Pin × 1/(K + 1)
```

## Example: Equal Split, Z₀ = 50 Ω, f₀ = 2 GHz

**Design:**
```{math}
Z₂ = Z₃ = 50 × √2 = 70.7 Ω
R = 2 × 50 = 100 Ω
λ/4 = (3×10⁸) / (4 × 2×10⁹) = 37.5 mm
```

## Advantages

1. **Matched ports:** All ports matched to Z₀
2. **Good isolation:** Typically 20–30 dB between outputs
3. **Good bandwidth:** 20–40% fractional
4. **Scalable:** Can cascade for N-way division (N = 2ⁿ)
5. **Well-established:** Mature design, extensive literature

## Limitations

1. **Resistor loss:** Isolation resistor may dissipate power if the circuit is not perfectly balanced
2. **Physical size:** λ/4 lines large at low frequency
4. **Unequal split limitations:**
   - Wide Z₂/Z₃ ratios → fabrication challenges
   - Large K → very high/low impedances
   
**Rule of thumb:** Keep 30Ω < Z₂, Z₃ < 150Ω for practical fabrication


## References

[1] Wilkinson, E. J. (1960). "An N-Way Hybrid Power Divider." *IRE Trans. Microwave Theory Tech.*, MTT-8, pp. 116-118.

[2] Pozar, D. M. (2012). *Microwave Engineering* (4th ed.), Section 7.3, pp. 336-340. Wiley.

## See Also

```{toctree}
:maxdepth: 1
/RFCircuitSynthesis/index
/RFCircuitSynthesis/PowerCombining/index
```