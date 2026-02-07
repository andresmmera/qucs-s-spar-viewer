# Gysel Power Divider

## Overview

High-power divider topology with **grounded isolation resistors** for superior thermal management. Maintains Wilkinson-like performance (matched ports, high isolation) while enabling significantly higher power handling through direct heat-sinking of resistors to ground plane.

## Topology

```
Output1 ──────┬──────[Z0, λ/4]──────┬─── R0
              │                     │
           [Z1, λ/4]                │
              │                     │
Input ────────|                 [Z4, λ/2]
              |                     │
           [Z1, λ/4]                │
              │                     │
Output2 ──────┴──────[Z0, λ/4]──────┴─── R0


```

**Key features:**
- Two λ/4 input branches at Z₁
- One λ/2 center line at Z₄
- Two λ/4 output lines at Z₀
- Two **grounded** isolation resistors R

## Design Equations

```
Z₁ = √2 × Z₀ ≈ 1.414 × Z₀    (input quarter-wave arms)
Z₄ = Z₀ / √2 ≈ 0.707 × Z₀    (center half-wave line)
R = Z₀                         (grounded resistors)
```

**For Z₀ = 50 Ω:**

| Parameter | Value | 
|-----------|-------|
|**Z₁**|70.7 Ω|
|**Z₄**|35.4 Ω|
|**R**|50 Ω|

## Advantages Over Wilkinson

1. **Grounded resistors:**
    - Direct thermal path to ground plane
    - Easy heat-sinking (metal slug, thermal vias)

## Limitations

1. **Larger size:** λ/2 center section makes it bigger
   - Gysel: ~1.5× area of Wilkinson

2. **More complex:** Five transmission lines vs. two
3. **Unequal split difficult** 

4. **Cost:** Slightly more expensive (more PCB area, complexity)

## Comparison with Wilkinson

| Feature | Gysel | Wilkinson |
|---------|-------|-----------|
| **Power handling** | Very high | Moderate  |
| **Resistors** | Grounded (2) | Floating (1) |
| **Thermal management** | Excellent | Poor |
| **Size** | Larger (λ/2 section) | Smaller |
| **Complexity** | More complex (5 TL) | Simple (2 TL) |
| **Isolation** | 20-30 dB | 20-30 dB |
| **Bandwidth** | 20-30% | 20-40% |
| **Match** | Excellent | Excellent |
| **Cost** | Higher | Lower |
| **Unequal split** | Difficult | Easy |
| **Best for** | High power | General use |


## References

[1] Gysel, U. H. (1975). "A New N-Way Power Divider/Combiner Suitable for High-Power Applications." *IEEE MTT-S Int. Microwave Symp. Digest*, pp. 116-118.

## See Also

```{toctree}
:maxdepth: 1
/RFCircuitSynthesis/index
/RFCircuitSynthesis/PowerCombining/index
```