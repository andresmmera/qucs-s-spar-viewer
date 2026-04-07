# Tapped-C Transformer Matching

## Description

The Tapped-C transformer uses a shunt-series-shunt arrangement of one inductor
and two capacitors to achieve impedance matching at a target frequency. The
loaded Q controls the bandwidth. Unlike the Tee and Pi networks there is no
LP/HP mask — the component placement is fixed by the impedance ratio alone.

## When to Use

* RF frequencies.
* Narrow bandwidth.
* Small area to be implemented.
* Typically used in some RF oscillators.

## Design Equations

When RL > RS the roles of the two ports are internally swapped before
computing component values, and L and C2 are placed on opposite sides of
the network (see Topology section).

### Auxiliary Q Factor
```{math}
Q_2 = \sqrt{\frac{R_L}{R_S}(Q^2 + 1) - 1}
```

### Component Values
```{math}
L = \frac{R_S}{\omega_0\, Q}
```
```{math}
C_2 = \frac{Q_2}{R_L\, \omega_0}
```
```{math}
C_1 = \frac{C_2\,(Q_2^2 + 1)}{Q\,Q_2 - Q_2^2}
```

### Minimum Q Constraint
```{math}
Q > Q_{\min} = \sqrt{\frac{\max(R_S, R_L)}{\min(R_S, R_L)} - 1}
```

Values of Q below Qmin make Q2 imaginary and the design is invalid.

## Parameters

| Parameter | Description |
|-----------|-------------|
| **Z0** | Source impedance RS (Ω) |
| **ZL** | Load impedance (Ω) |
| **Frequency** | Matching frequency (Hz) |
| **Q** | Loaded Q factor (Q > Qmin) |


## Tapped-C vs Tapped-L

The Tapped-C and Tapped-L are duals of each other. Both use a
shunt-series-shunt Pi arrangement with one reactive element type forming
the series arm and the other split across the two shunt arms:

| | Tapped-C | Tapped-L |
|-|----------|----------|
| Series element | C1 (capacitor) | L1 (inductor) |
| Shunt elements | L and C2 | C and L2 |
| Preferred use | Tank circuits, oscillators |  |


## Limitations

* Q constraint must be given -> Narrowband.
* Only real-to-real matching.

## See Also
```{toctree}
:maxdepth: 1

/RFCircuitSynthesis/index
/RFCircuitSynthesis/ImpedanceMatching/index
/RFCircuitSynthesis/ImpedanceMatching/TappedL/index
/RFCircuitSynthesis/ImpedanceMatching/DoubleTappedResonator/index
```
