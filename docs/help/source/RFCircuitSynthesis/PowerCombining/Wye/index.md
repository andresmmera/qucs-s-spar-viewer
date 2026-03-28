# Wye Resistive Splitter

## Overview

This is perhaps the simpler combiner/splitter. The Wye splitter provides a N-way equal power split.
Since the impedance of the resistor is constant over frequency, this arrangement is very broadband, yet lossy.
Care must be taken with high-RF power as the network is dissipative.

## Topology

```
                                  ┌─[R]── Port 1
                                  │
Port_in ──[R]── Node ─────────────┼─[R]── Port 2
                                  │
                                  ├─[R]── Port 3
                                  │
                                  ⋮
                                  │
                                  └─[R]── Port N
```

**Key features:**
- Single input resistor followed by a central star node
- N identical output resistors, one per output port
- All ports simultaneously matched to Z₀
- Inherently lossy: (N−1)/N of the input power is dissipated in the resistors
- Very broadband, extremely compact

## Design Equations (Equal Split)

### Resistor Value

```
R = Z₀ × (N − 1) / (N + 1)
```

**For Z₀ = 50 Ω:**

| N (outputs) | R (Ω) | Insertion Loss (dB) |
|:-----------:|:-----:|:-------------------:|
| **2**       | 16.7  | 6.0                 |
| **3**       | 25.0  | 9.5                 |
| **4**       | 30.0  | 12.0                |
| **8**       | 38.9  | 18.1                |

> Insertion loss = −10 log₁₀(1/N²) relative to the matched-load case.



## References

[1] "Resistive power splitters", Microwaves101.  
    https://www.microwaves101.com/encyclopedias/resistive-power-splitters

## See Also

```{toctree}
:maxdepth: 1
/RFCircuitSynthesis/index
/RFCircuitSynthesis/PowerCombining/index
```
