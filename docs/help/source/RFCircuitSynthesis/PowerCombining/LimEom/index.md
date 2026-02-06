# Lim-Eom Power Divider

## Overview

**Wideband** 4-port power divider with **unequal power split** capability and excellent bandwidth performance. Developed by Lim and Eom, this topology provides multi-octave operation while maintaining arbitrary power ratios between three output ports.

## Topology

```
                           Output #1
                              |
                              |
Input     ────────[Z2, λ/4]────────[Z1, λ/4]──────── [R0]
           |                                  |
           |                                  |
      [Z1, λ/4]                          [Z2, λ/4]
           |                                  |
           |                                  |
           |─────────────[Z0, λ/2]────────────|
           |                                  |
           |                                  |
      [Z4, λ/4]                           [Z5, λ/4]
           |                                  |
           |                                  |
Output #2 ────────[Z5, λ/4]────────[Z4, λ/4]────────  Output #3
                              |
                             [R0]


```

**Key features:**
- Four ports: 1 input, 3 outputs
- Two grounded isolation resistors (R1, R2)
- Center λ/2 section (Z3) connects upper and lower halves
- Arbitrary power ratios M:N:K at outputs

## Design Equations

### Power Split Ratios

Define output power ratios:
```
M = P₂/P_total    (Port 2 power ratio)
N = P₃/P_total    (Port 3 power ratio)
K = P₄/P_total    (Port 4 power ratio)

where M + N + K = 1
```

### Impedance Calculations

```
d₁ = M + N + K = 1
d₂ = N + K

Z₁ = Z₀ × √(d₁/d₂) = Z₀ × √(1/(N + K))
Z₂ = Z₀ × √(d₁/M) = Z₀ × √(1/M)
Z₃ = Z₀
Z₄ = Z₀ × √(d₂/N) = Z₀ × √((N + K)/N)
Z₅ = Z₀ × √(d₂/K) = Z₀ × √((N + K)/K)

R₁ = R₂ = Z₀
```

### Line Lengths

```
Z₁, Z₂, Z₄, Z₅: λ/4 at f₀
Z₃: λ/2 at f₀ (impedance repeater)
```

## Example 1: Equal 3-Way Split (M = N = K = 1/3)

**Design:**
```
M = N = K = 1/3
d₂ = 2/3

Z₁ = 50 × √(1/(2/3)) = 50 × √1.5 ≈ 61.2 Ω
Z₂ = 50 × √(1/(1/3)) = 50 × √3 ≈ 86.6 Ω
Z₃ = 50 Ω
Z₄ = 50 × √((2/3)/(1/3)) = 50 × √2 ≈ 70.7 Ω
Z₅ = 50 × √((2/3)/(1/3)) = 50 × √2 ≈ 70.7 Ω

R₁ = R₂ = 50 Ω
```

## Example 2: Unequal Split (M = 1/2, N = 1/3, K = 1/6)

**Power distribution:**
```
Port 2: 50% (3 dB)
Port 3: 33% (4.8 dB)
Port 4: 17% (7.8 dB)
```

**Design:**
```
M = 0.5, N = 0.333, K = 0.167
d₂ = 0.5

Z₁ = 50 × √(1/0.5) = 50 × √2 ≈ 70.7 Ω
Z₂ = 50 × √(1/0.5) = 50 × √2 ≈ 70.7 Ω
Z₃ = 50 Ω
Z₄ = 50 × √(0.5/0.333) ≈ 61.2 Ω
Z₅ = 50 × √(0.5/0.167) ≈ 86.6 Ω

R₁ = R₂ = 50 Ω
```

## Advantages

1. **Wideband operation:**
   - Wider than standard Wilkinson

2. **Arbitrary power split:** Any M:N:K ratio
   - Full design flexibility

3. **High isolation:** >20 dB between all outputs
   - Good for amplifier combining
   - Three-way isolation maintained

4. **Grounded resistors:** 
   - Direct heat-sinking possible
   - Similar to Gysel topology -> Better thermal management
   - Higher power capability

5. **All ports matched:** Good return loss
   - Input and all outputs matched to Z₀
   - Low VSWR

## Limitations

1. **Complexity:** More complex than standard Wilkinson
   - Five different impedances
   - λ/2 section adds length

2. **Size:**
   - λ/2 center section
   - More PCB area required

3. **Limited to 3 outputs:** Fixed 4-port design
   - Cannot extend to N-way easily
   - For N≠3, use tree or other topology

## Comparison with Other 3-Way Dividers

| Feature | Lim-Eom | 3-Way Wilkinson | Tree (2× Wilkinson) |
|---------|---------|-----------------|---------------------|
| **Outputs** | 3 | 3 | 3 |
| **Bandwidth** | 100-150% | 20-40% | 20-40% |
| **Unequal split** | Arbitrary | Difficult | Limited |
| **Size** | Medium | Small | Large (2 stages) |
| **Complexity** | High | Medium | Medium |
| **Isolation** | >20 dB | >20 dB | >20 dB |
| **Resistors** | 2 (grounded) | 3 (floating) | 2 (floating) |
| **Power handling** | High | Moderate | Moderate |


## References

[1] J.-S. Lim and S.-Y. Eom."A New 3-Way Power Divider with Various Output Power Ratios," 1996 IEEE MTT-S Int. Microwave Symp. Dig., pp. 785-788.

[2] Andrei Grebennikov. "Power combiners, impedance transformers and directional couplers: part II". High Frequency Electronics. 2008