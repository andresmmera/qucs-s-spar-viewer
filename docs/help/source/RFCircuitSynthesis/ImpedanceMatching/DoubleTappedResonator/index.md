# Double-Tapped Resonator Matching

## Description

The double-tapped resonator uses a shunt-series-shunt arrangement of two
inductors and two capacitors to achieve impedance matching at a target
frequency. A user-specified series inductor L2 (Ltap) forms part of a
resonant tank with C1, giving an extra degree of freedom over the Tapped-C
and Tapped-L networks. The loaded Q controls the bandwidth.

## When to Use

* RF frequencies.
* Narrow bandwidth.
* An fixed inductive feature that must be embedded into the matching network.

## Design Equations

### Auxiliary Q Factor
```{math}
Q_2 = \sqrt{\frac{R_L}{R_S}(Q^2 + 1) - 1}
```

### Component Values
```{math}
L_1 = \frac{R_S}{\omega_0\, Q}
```
```{math}
L_{eq} = \frac{L_1\, Q^2}{1 + Q^2} + L_2
```
```{math}
C_{eq} = \frac{1}{\omega_0^2\, L_{eq}}
```
```{math}
C_2 = \frac{Q_2}{\omega_0\, R_L}
```
```{math}
C_2' = \frac{C_2\,(1 + Q_2^2)}{Q_2^2}
```
```{math}
C_1 = \frac{C_{eq}\, C_2'}{C_2' - C_{eq}}
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
| **Ltap** | User-specified series inductor L2 (nH) |

## Limitations

* Narrowband.
* Only real-to-real matching.
* The value of Ltap directly affects C1 through the resonator equations;
  very large Ltap values may push C1 to impractical or negative values.

## See Also
```{toctree}
:maxdepth: 1

/RFCircuitSynthesis/index
/RFCircuitSynthesis/ImpedanceMatching/index
/RFCircuitSynthesis/ImpedanceMatching/TappedC/index
/RFCircuitSynthesis/ImpedanceMatching/TappedL/index
```
