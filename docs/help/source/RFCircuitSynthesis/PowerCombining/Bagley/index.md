# Bagley Power Divider

## Overview

**N-way** planar power divider suitable for splitting power to any odd number of outputs (>=3).

## Topology

```
                                  Input
                                    │
                     ───────────────────────────────
                    │                               │  
                  [λ/4]                           [λ/4] 
                    │                               │  
                    │─────[λ/2]─────|─────[λ/2]─────│
                  Out #1          Out #2          Out #N     (odd)
```

**Structure:**
- **Input branches:** Two λ/4 sections at Zbr connect to input
- **First output:** Taken from left branch
- **Interconnections:** λ/2 sections at Zbr connect remaining outputs
- **All lines:** At impedance Zbr

## Design Equations

### For N Outputs (Equal Split)

**Branch impedance:**
```
Zbr = (2 × Z₀) / √N
```

**All transmission lines:**
- Impedance: Zbr
- Input vertical branches: λ/4 length
- Horizontal interconnects: λ/2 length


## Example

### 3-Way Divider, Z₀ = 50 Ω, f₀ = 2 GHz

**Design:**
```
N = 3
Zbr = (2 × 50) / √3 = 100 / 1.732 ≈ 57.7 Ω

λ₀ = 150 mm
λ/4 = 37.5 mm (vertical branches)
λ/2 = 75 mm (horizontal sections)

Insertion loss = 10 × log₁₀(3) ≈ 4.77 dB per output
```

## Physical Size

**Total length (horizontal):**
```
L_total ≈ (N - 1) × λ/2

N = 3: ~1.0λ
N = 4: ~1.5λ
N = 8: ~3.5λ
```

## References

[1] Pozar, D. M. (2012). *Microwave Engineering* (4th ed.). Wiley.

