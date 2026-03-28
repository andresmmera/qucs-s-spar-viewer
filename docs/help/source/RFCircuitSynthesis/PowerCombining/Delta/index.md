# 2-Way Delta Resistive Splitter

## Overview

Simple **2-way equal-split** resistive power divider using a **Delta topology**. Features
three equal resistors arranged in a triangle: two series arms connecting the input node to each
output port, and one shunt isolation resistor bridging the two output nodes. All resistors are
equal to Z₀, providing simultaneous port matching and a 6 dB insertion loss.

Care must be taken with high-RF power as the network is dissipative.

## Topology

```
                    ┌──[R]──────────────── Port 2
                    │              │
Port_in ── Node ───┤             [R]
                    │              │
                    └──[R]──────────────── Port 3
```

**Key features:**
- Two series arm resistors (R = Z₀) from input node to each output
- One isolation resistor (R = Z₀) shunting between the two output nodes
- All three resistors share the same value Z₀
- All ports simultaneously matched to Z₀
- Fixed 2-output topology — Delta mesh does not scale gracefully to N > 2
- Very broadband.

## Design Equations (Equal Split, 2-Way)

### Resistor Value

All three resistors share a single value:

```
R = Z₀
```

**For Z₀ = 50 Ω:**

| Parameter | Value |
|-----------|-------|
| **R₁** (series, top arm) | 50 Ω |
| **R₂** (series, bottom arm) | 50 Ω |
| **R₃** (isolation, output shunt) | 50 Ω |
| **Insertion loss** | 6.0 dB |


### Comparison with Wye Splitter (2-Way)

| | Delta | Wye |
|-|-------|-----|
| **Resistor value** | Z₀ | Z₀/3 |
| **Insertion loss** | 6 dB | 6 dB |
| **Scalable to N > 2** | No (mesh) | Yes |

Both topologies yield identical insertion loss for the 2-way case, but the Delta adds an
isolation resistor between outputs, improving output-to-output isolation.

## References

[1] "Resistive power splitters", Microwaves101.  
    https://www.microwaves101.com/encyclopedias/resistive-power-splitters

## See Also

```{toctree}
:maxdepth: 1
/RFCircuitSynthesis/index
/RFCircuitSynthesis/PowerCombining/index
```
