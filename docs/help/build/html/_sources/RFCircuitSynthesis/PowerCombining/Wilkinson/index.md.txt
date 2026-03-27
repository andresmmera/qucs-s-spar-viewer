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

Branch impedance and isolation resistor:

```{math}
Z_2 = Z_3 = \sqrt{2} \times Z_0 \approx 70.7 \ \Omega \quad (Z_0 = 50 \ \Omega)
```

```{math}
R = 2 \times Z_0 = 100 \ \Omega
```

Power division (3 dB to each output):

```{math}
P_2 = P_3 = \frac{P_{in}}{2}
```

### Unequal Power Split (K ≠ 1)

Power ratio K = P₂/P₃ (linear), or K_dB = 10 × log₁₀(K).

Branch impedances:

```{math}
Z_2 = Z_0 \sqrt{\frac{2\,(1 + K)}{K}}
```

```{math}
Z_3 = Z_0 \sqrt{2\,(1 + K)}
```

Isolation resistor (sum of two series sections):

```{math}
R_2 = Z_0 \times K \qquad R_3 = \frac{Z_0}{K} \qquad R = R_2 + R_3 = Z_0 \left(K + \frac{1}{K}\right)
```

Power division:

```{math}
P_2 = P_{in} \times \frac{K}{K + 1} \qquad P_3 = P_{in} \times \frac{1}{K + 1}
```

## Example: Equal Split, Z₀ = 50 Ω, f₀ = 2 GHz

```{math}
Z_2 = Z_3 = 50\sqrt{2} \approx 70.7 \ \Omega
```

```{math}
R = 2 \times 50 = 100 \ \Omega
```

```{math}
\frac{\lambda}{4} = \frac{3 \times 10^8}{4 \times 2 \times 10^9} = 37.5 \ \text{mm}
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
3. **Unequal split limitations:**
   - Wide Z₂/Z₃ ratios → fabrication challenges
   - Large K → very high/low impedances

**Rule of thumb:** Keep 30 Ω < Z₂, Z₃ < 150 Ω for practical fabrication.

## References

[1] Wilkinson, E. J. (1960). "An N-Way Hybrid Power Divider." *IRE Trans. Microwave Theory Tech.*, MTT-8, pp. 116-118.

[2] Pozar, D. M. (2012). *Microwave Engineering* (4th ed.), Section 7.3, pp. 336-340. Wiley.

## See Also

```{toctree}
:maxdepth: 1
/RFCircuitSynthesis/index
/RFCircuitSynthesis/PowerCombining/index
```
