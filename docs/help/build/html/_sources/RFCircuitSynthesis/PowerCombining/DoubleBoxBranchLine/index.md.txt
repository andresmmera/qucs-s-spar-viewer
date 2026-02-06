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

### Optimization Parameter

```
r = 1  (typical optimization value)
t = √((1 + K) × r)

where K = P₂/P₃ (power split ratio)
```

### Impedance Calculations

**For equal split (K = 1):**
```
t = √(2 × 1) = √2

ZA = Z₀ × √(r × (t² - r)) / (t - r)
   = Z₀ × √(1 × (2 - 1)) / (√2 - 1)
   = Z₀ / (√2 - 1)
   = Z₀ × (√2 + 1)
   ≈ 2.414 × Z₀

ZD = Z₀ × √(r × (t² - r)) / (t - 1)
   = Z₀ × √(1 × 1) / (√2 - 1)
   = Z₀ / (√2 - 1)
   ≈ 2.414 × Z₀

ZB = Z₀ × √(r - r²/t²)
   = Z₀ × √(1 - 1/2)
   = Z₀ / √2
   ≈ 0.707 × Z₀

R = Z₀  (isolation resistor)
```

**For Z₀ = 50 Ω:**
```
ZA = ZD ≈ 120.7 Ω
ZB ≈ 35.4 Ω
R = 50 Ω
```

## Advantages Over Single-Box

1. **Wider bandwidth:** 25-35% vs. 15-20%
   - 50-75% improvement
   - Better match across band

## Limitations

1. **Larger size:** 7 lines vs. 4
   - More PCB area
   - Approximately 2× size of single-box

2. **More complex layout**

3. **Higher impedance (ZA, ZD):** 120.7 Ω
   - Narrow lines
   - Challenging on thin substrates
   - Fabrication tolerance critical

4. **Still narrowband**
