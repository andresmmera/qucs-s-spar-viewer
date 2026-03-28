# Adams Unequal Resistive Splitter

## Overview

**2-way unequal-split** resistive power divider based on the **Adams topology**. Unlike the
symmetric Wye and Delta splitters, this network distributes power unevenly between two output
ports while simultaneously matching all ports to Z₀. The split ratio is a free design parameter.
Four resistors are used: two series arms on the high-power path, one shunt isolation resistor
between the two output nodes, and one shunt resistor to ground on the low-power output.

## Topology

```
Port_in ──[Rs]──── N1 ────[Rs]──── Port 1  (higher power)
                    │
                   [Rt]
                    │
                   N2 ──────────── Port 2  (lower power)
                    │
                   [Ru]
                    │
                   GND
```

**Key features:**
- Two equal series resistors (Rs) on the high-power branch
- One inter-node shunt resistor (Rt) providing isolation between outputs
- One grounded shunt resistor (Ru) on the low-power output node
- All ports matched to Z₀ for any split ratio
- Very broadband. Extremely compact.

## Design Equations (Unequal Split)

Let α be the voltage split ratio, defined from the desired power ratio P₁/P₂:

```
α = 1 / OutputRatio    (where OutputRatio = 10^(dB_split/20))
```

The four resistor values are then (normalised to Z₀, before scaling):

```
Rs  = Z₀ × (1 − α) / (1 + α)

Rp  = Z₀ × (1 − Rs²) / (2 × Rs)        [intermediate]

Ru  = Z₀ × sqrt(1 / (1 − 4 / (2×Rp + Rs + 1)))

Rt  = Z₀ × (Rp − Ru / (Ru + 1))
```

## References

[1] Greg Adams, "Designing Resistive Unequal Power Dividers", *High Frequency Electronics*, 2007.

[2] "Resistive power splitters", Microwaves101.  
    https://www.microwaves101.com/encyclopedias/resistive-power-splitters

## See Also

```{toctree}
:maxdepth: 1
/RFCircuitSynthesis/index
/RFCircuitSynthesis/PowerCombining/index
```
