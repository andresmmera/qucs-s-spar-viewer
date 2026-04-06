# Pi Matching

## Description

Pi matching uses a shunt-series-shunt lumped-element arrangement to achieve
impedance matching at a target frequency. Like the Tee network, the loaded Q
can be freely chosen, giving direct control over bandwidth. Four LP/HP topology
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
R_v = \frac{\max(R_S,\, R_L)}{Q^2 + 1}
```

Rv is always smaller than both RS and RL.

### Source-side L-section (RS → Rv)

Low-pass solution:
```{math}
X_{1a} = \sqrt{R_v (R_S - R_v)}
```
```{math}
B_1 = \frac{\sqrt{(R_S - R_v)/R_v}}{R_S}
```

High-pass solution: negate both X₁ₐ and B₁.

### Load-side L-section (Rv → ZL)

Low-pass solution:
```{math}
B_2 = \frac{X_L + \sqrt{R_L/R_v}\,\sqrt{R_L^2 + X_L^2 - R_v R_L}}{R_L^2 + X_L^2}
```
```{math}
X_{1b} = \frac{1}{B_2} + \frac{X_L R_v}{R_L} - \frac{R_v}{B_2 R_L}
```

High-pass solution: negate the square-root term in B₂, then recompute X₁ᵦ.

### Combined Series Reactance
```{math}
X_1 = X_{1a} + X_{1b}
```

### Component Values

| Condition | Element | Formula |
|-----------|---------|---------|
| X > 0 | Inductor | L = X / ω₀ |
| X < 0 | Capacitor | C = −1 / (ω₀ X) |
| B > 0 | Capacitor | C = B / ω₀ |
| B < 0 | Inductor | L = −1 / (ω₀ B) |

### Minimum Q Constraint
```{math}
Q > Q_{\min} = \sqrt{\frac{\max(R_S, R_L)}{\min(R_S, R_L)} - 1}
```

Values of Q below Qmin make Rv larger than the smaller termination and the
design is invalid.

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
| LP-LP | Low-pass | Low-pass | Shunt caps, series inductor |
| LP-HP | Low-pass | High-pass | Mixed |
| HP-LP | High-pass | Low-pass | Mixed |
| HP-HP | High-pass | High-pass | Shunt inductors, series cap |

## Tee and Pi matching

The Tee and Pi networks are duals of each other and share the same Q-based
design procedure, but with opposite roles for Rv:

| | Tee | Pi |
|-|-----|----|
| Rv relative to terminations | Rv > RS and RL | Rv < RS and RL |
| Topology | Series-shunt-series | Shunt-series-shunt |
| Favours | Low-impedance terminations | High-impedance terminations |


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
/RFCircuitSynthesis/ImpedanceMatching/TeeMatching/index
```
