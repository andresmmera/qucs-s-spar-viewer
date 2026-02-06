# 3-Way Wilkinson with Improved Isolation

## Overview

Enhanced **3-way equal-split** power divider with **two-stage design** providing high isolation between all output ports compared to standard single-stage 3-way Wilkinson.

## Topology

```

       ┌──────[Z₁, λ/4]────────────[Z₂, λ/4]─────── Port 2
       │                     │                   │
       │                     │                   │
       │                   [R1]                [R2]   
       │                     │                   │
Input──┤                     │                   │
       │                     │                   │ 
       ├──────[Z₁, λ/4]─────────────[Z₂, λ/4]─────── Port 3
       │                     │                   │
       │                     │                   │
       │                    [R1]                [R2]
       │                     │                   │
       │                     │                   │
       └──────[Z₁, λ/4]─────────────[Z₂, λ/4]─────── Port 4

```

**Structure:**
- **Stage 1:** Three Z₁ branches with R1 isolation resistors
- **Stage 2:** Three Z₂ branches with R2 isolation resistors  
- Two-stage cascade for improved bandwidth and isolation

## Design Equations (Equal Split)

### Optimized Impedances

```
Z₁ = 2.28 × Z₀    (first stage)
Z₂ = 1.316 × Z₀   (second stage)

R₁ = 1.319 × Z₀   (first stage isolation)
R₂ = 4 × Z₀       (second stage isolation)
```

**For Z₀ = 50 Ω:**
```
Z₁ = 114 Ω
Z₂ = 65.8 Ω

R₁ = 66 Ω
R₂ = 200 Ω
```

**All transmission lines:** λ/4 at f₀

## References

[1] Goldfarb, M.E. ‘A recombinant, In-phase power divider’, IEEE Trans. Microw. Theory Tech., 1991, 39, (8), pp. 1438–1440
[2] Andrei Grebennikov. "Power combiners, impedance transformers and directional couplers: part II". High Frequency Electronics. 2008