# Double-Box Branch-Line Coupler

## Overview

Enhanced **quadrature hybrid** using two cascaded branch-line sections providing **wider bandwidth** and **better impedance transformation** than single-box design. Maintains 90° phase difference while achieving 50-75% wider bandwidth through dual-box structure.

## Topology

```
Port 1 ─────────[ZB]────────[ZB]───────  Port 2
(Input)    │           |            |  (Through, 0°)
           │           │            │
          [ZA]        [ZB]         [ZA]
           │           │            │
           │           │            │
Port 4 ─────────[ZB]────────[ZB]───────  Port 3
(Isolated)                           (Coupled, -90°)
```

## Design Equations

**For equal split (K = 1):**

Let $t = \sqrt{2}$, $r = 1$. The shunt and series arm impedances are:

```{math}
Z_A = Z_D = \frac{Z_0}{\sqrt{2} - 1} = Z_0\,(\sqrt{2} + 1) \approx 2.414 \times Z_0
```

```{math}
Z_B = \frac{Z_0}{\sqrt{2}} \approx 0.707 \times Z_0
```

```{math}
R = Z_0 \quad \text{(isolation resistor)}
```

**For Z₀ = 50 Ω:**

| Parameter | Value |
|-----------|-------|
| **Z_A = Z_D** | 120.7 Ω |
| **Z_B** | 35.4 Ω |
| **R** | 50 Ω |

## Advantages Over Single-Box

1. **Wider bandwidth:** 25–35% vs. 15–20% (50–75% improvement)

## Limitations

1. **Larger size:** 7 lines vs. 4 — approximately 2× the area of a single-box design
2. **More complex layout**
3. **Higher impedance (Z_A, Z_D):** 120.7 Ω results in narrow lines, challenging on thin substrates where fabrication tolerance is critical
4. **Still narrowband** relative to other broadband coupler topologies

## See Also

```{toctree}
:maxdepth: 1
/RFCircuitSynthesis/index
/RFCircuitSynthesis/PowerCombining/index
```
