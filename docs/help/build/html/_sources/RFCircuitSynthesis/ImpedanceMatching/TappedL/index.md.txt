# Tapped-L Transformer Matching

## Description

The Tapped-L transformer uses a shunt-series-shunt arrangement of two
inductors and one capacitor to achieve impedance matching at a target
frequency. It is the dual of the Tapped-C: the series element is always an
inductor (L1), and the single capacitor C is split across the two shunt arms
together with a second inductor L2. The loaded Q controls the bandwidth.

## When to Use

* RF frequencies.
* Narrow bandwidth.
* Small area to be implemented.

## Design Equations

When RL > RS the roles of the two ports are internally swapped before
computing component values, and C and L2 are placed on opposite sides of
the network (see Topology section).

### Auxiliary Q Factor
```{math}
Q_2 = \sqrt{\frac{R_L}{R_S}(Q^2 + 1) - 1}
```

### Component Values
```{math}
C = \frac{Q}{\omega_0\, R_S}
```
```{math}
L_2 = \frac{R_L}{Q_2\, \omega_0}
```
```{math}
L_1 = \frac{L_2\,(Q\,Q_2 - Q_2^2)}{Q_2^2 + 1}
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
/RFCircuitSynthesis/ImpedanceMatching/TappedC/index
/RFCircuitSynthesis/ImpedanceMatching/DoubleTappedResonator/index
```
