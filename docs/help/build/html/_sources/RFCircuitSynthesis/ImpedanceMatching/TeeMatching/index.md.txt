# Tee Matching

## Description

Tee matching uses a series-shunt-series lumped-element arrangement to achieve
impedance matching at a target frequency. The loaded Q can be freely chosen,
giving the designer direct control over bandwidth. Four LP/HP topology
combinations are available for each Q value.

## When to Use

* RF frequencies.
* Narrow bandwidth.
* Small area to be implemented.
* A specific filtering characteristic (low-pass or high-pass) is desired.

## Design Equations

The network is decomposed into two back-to-back L-sections meeting at a real
virtual resistance Rv.

### Virtual Intermediate Resistance
```{math}
R_v = (Q^2 + 1)\,\min(R_S,\, R_L)
```

Rv is always greater than both RS and RL.

### Source-side L-section (RS → Rv)

Low-pass solution:
```{math}
B_{1a} = \frac{\sqrt{R_v/R_S}\,\sqrt{R_v^2 - R_S R_v}}{R_v^2}
```
```{math}
X_1 = \frac{1}{B_{1a}} + \frac{R_S}{R_v} - \frac{R_S}{B_{1a} R_v}
```

High-pass solution: negate both B₁ₐ and X₁.

### Load-side L-section (Rv → ZL)

Low-pass solution:
```{math}
X_2 = \sqrt{R_L(R_v - R_L)} - X_L
```
```{math}
B_{1b} = \frac{\sqrt{(R_v - R_L)/R_L}}{R_v}
```

High-pass solution: negate both B₁ᵦ and X₂, and subtract XL with the
opposite sign.

### Combined Centre Susceptance
```{math}
B_1 = B_{1a} + B_{1b}
```

### Minimum Q Constraint
```{math}
Q > Q_{\min} = \sqrt{\frac{\max(R_S, R_L)}{\min(R_S, R_L)} - 1}
```

Values of Q below Qmin make Rv imaginary and the design is invalid.

## Parameters

| Parameter | Description |
|-----------|-------------|
| **Z0** | Source impedance RS (Ω) |
| **ZL** | Load impedance (Ω), may be complex |
| **Frequency** | Matching frequency (Hz) |
| **Q** | Loaded Q factor (Q > Qmin) |
| **Network type** | LP-LP, LP-HP, HP-LP, or HP-HP |

## Network Type (LP/HP Mask)

Each of the two L-section halves can independently be low-pass or high-pass,
giving four topologies for any given Q:

| Mask | Source side | Load side | Characteristic |
|------|-------------|-----------|----------------|
| LP-LP | Low-pass | Low-pass | All shunt caps, series inductors |
| LP-HP | Low-pass | High-pass | Mixed |
| HP-LP | High-pass | Low-pass | Mixed |
| HP-HP | High-pass | High-pass | All shunt inductors, series caps |

## Limitations

* Q constraint must be given -> Narrowband.

## Reference

Vizmuller, P. "RF Design Guide: Systems, Circuits and Equations."
Artech House, 1995.

## See Also
```{toctree}
:maxdepth: 1

/RFCircuitSynthesis/index
/RFCircuitSynthesis/ImpedanceMatching/index
/RFCircuitSynthesis/ImpedanceMatching/PiMatching/index
```
