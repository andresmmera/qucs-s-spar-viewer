# Recombinant 3-Way Wilkinson

## Overview

Alternative **3-way equal-split** power divider using a **recombinant topology** with crossed branches. Features two-stage design with unique impedance distribution providing excellent isolation and balanced power split. Optimized coefficients provide good bandwidth with predictable performance.

## Topology

```
                                       ┌─[Z2, λ/4]──────[Z2, λ/4]── Output #1
                                       |            |
                     ┌─[Z2, λ/4]───────|           [R2]
                     │            |    |            |
                     │            |    |            |
Input ─[Z1, λ/4]─────┤           [R1]  └─[Z3, λ/4]──|     
                     │            |                 |
                     │            |    ┌─[Z3, λ/4]──────[Z2, λ/4]── Output #2
                     │            |    |            |  
                     └─[Z2, λ/4]────────           [R2]
                                       |            |
                                       └─[Z2, λ/4]──|───[Z2, λ/4]── Output #3
   
               
```

**Key features:**
- Input branch Z₁ splits into two paths
- Upper and lower branches cross in recombinant structure
- Two isolation resistors (R1, R2)
- Three stages per complete path
- Equal power to three outputs

## Design Equations (Equal Split)

### Impedances

```
Z₁ = 0.72 × Z₀    (input section)
Z₂ = 0.80 × Z₀    (first split sections)
Z₃ = 0.80 × Z₀    (upper recombinant)
Z₄ = 1.60 × Z₀    (middle path)
Z₅ = 0.80 × Z₀    (output matching)
Z₆ = 1.60 × Z₀    (lower recombinant)

R₁ = Z₀           (first isolation)
R₂ = 2 × Z₀       (second isolation)
```

**For Z₀ = 50 Ω:**

| Parameter | Value | 
|-----------|-------|
|**Z₁**|36 Ω|
|**Z₂ = Z₃ = Z₅**|40 Ω|
|**Z₄ = Z₆**|80 Ω|




**All transmission lines:** λ/4 at f₀

## References

[1] "A recombinant in-phase power divider", IEEE Trans. Microwave Theory Tech., vol. MTT-39, Aug. 1991, pp. 1438-1440

[2] "Power combiners, impedance transformers and directional couplers: part II". Andrei Grebennikov. High Frequency Electronics. 2008

## See Also

```{toctree}
:maxdepth: 1
/RFCircuitSynthesis/index
/RFCircuitSynthesis/PowerCombining/index
```