# Single-Stub Matching

## Description

Single-stub matching uses one transmission line section followed by a shunt stub (open or short-circuited) to achieve impedance matching. This distributed-element approach is suitable for microwave frequencies.

## When to Use

* Microwave frequencies (> 1 GHz)
* Distributed element implementation required
* Moderate bandwidth needed (10-20%)

## Design Equations

### Transmission Line Distance

```{math}
t = \frac{X_L + \sqrt{(R_L/Z_0)|Z_0^2 - R_L^2 + X_L^2|}}{R_L - Z_0}
```

```{math}
d = \frac{\lambda}{2\pi}\arctan(t)
```

### Stub Susceptance

```{math}
B = \frac{R_L^2 t - (Z_0 - X_L t)(Z_0 t + X_L)}{Z_0(R_L^2 + (Z_0 t + X_L)^2)}
```

### Stub Length

For open-circuit stub:

```{math}
l_{stub} = -\frac{\lambda}{2\pi}\arctan(BZ_0)
```

For short-circuit stub:

```{math}
l_{stub} = \frac{\lambda}{2\pi}\arctan\left(\frac{1}{BZ_0}\right)
```

where λ is the wavelength at the matching frequency.

## Parameters

| Parameter | Description |
|-----------|-------------|
| **Z0** | Characteristic impedance (Ω) |
| **ZL** | Load impedance (Ω) |
| **Frequency** | Matching frequency (Hz) |
| **Stub Type** | Open or short-circuit termination |
| **Implementation** | Ideal TL or microstrip |

## Stub Termination

**Open-Circuit Stub**
* Easier to fabricate in microstrip (no vias nor shunt caps (1 nF or so) required)
* End effect requires compensation
* Avoid DC paths to ground

**Short-Circuit Stub**
* Requires via to ground plane
* No end-effect compensation needed
* Better for narrowband matching

## Limitations

* Frequency-dependent (narrow to moderate bandwidth)
* Requires adequate space for transmission line
* Stub length can become impractical at low frequencies
* Sensitive to fabrication tolerances

## Example

**Match 75Ω to 50Ω at 1 GHz**

**Input data**
| Parameter | Value |
|-----------|-------------|
|Z0|50Ω|
|ZL|75Ω|
|frequency|1 GHz|
|Configuration |Open-circuit stub|

**Results**
| Parameter | Value |
|-----------|-------------|
|Line distance (d)|42.3 mm|
|Stub length (l)|131 mm|

Circuit topology:

```
Port ── TLIN(d) ──┬── Load (75Ω)
                  │
                STUB(l)
                  │
                 O/C
```

## Reference

Pozar, D. M. "Microwave Engineering", 4th Edition, Wiley, 2011, pp. 234-241

## See Also

```{toctree}
:maxdepth: 1

/RFCircuitSynthesis/index
/RFCircuitSynthesis/ImpedanceMatching/index
```