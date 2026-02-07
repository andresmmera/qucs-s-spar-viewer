# Double-Stub Matching

## Description

Double-stub matching uses two shunt stubs separated by a fixed transmission line length (typically λ/8). This configuration allows matching without requiring a variable-length main line, making it practical for tunable matching networks.

## Design Equations

### Load Admittance Transformation

```{math}
G_L = \frac{R_L}{R_L^2 + X_L^2}, \quad B_L = -\frac{X_L}{R_L^2 + X_L^2}
```

### Matchability Condition

The load can be matched if:

```{math}
G_L \leq \frac{Y_0(1 + t^2)}{2t^2}
```

where $t = \tan(\beta d)$ and d = λ/8 (giving t = 1).

### Stub Susceptances

```{math}
B_1 = -B_L + \frac{Y_0 + \sqrt{(1+t^2)G_L Y_0 - G_L^2 t^2}}{t}
```

```{math}
B_2 = \frac{Y_0\sqrt{(1+t^2)G_L Y_0 - G_L^2 t^2} + G_L Y_0}{G_L t}
```

### Stub Lengths

For open-circuit stubs:

```{math}
l_1 = \frac{\lambda}{2\pi}\arctan(B_1 Z_0), \quad l_2 = \frac{\lambda}{2\pi}\arctan(B_2 Z_0)
```

For short-circuit stubs:

```{math}
l_1 = -\frac{\lambda}{2\pi}\arctan\left(\frac{1}{B_1 Z_0}\right), \quad l_2 = -\frac{\lambda}{2\pi}\arctan\left(\frac{1}{B_2 Z_0}\right)
```

## Parameters

| Parameter | Description |
|-----------|-------------|
| **Z0** | Characteristic impedance (Ω) |
| **ZL** | Load impedance (Ω) |
| **Frequency** | Matching frequency (Hz) |
| **Spacing** | Fixed at λ/8 |
| **Stub Type** | Open or short-circuit |
| **Implementation** | Ideal TL or microstrip |

## Advantages

* **Adjustable matching**: Both stubs can be tuned
* **Fixed spacing**: No need to adjust main line length  
* **Laboratory-friendly**: Easy to implement with adjustable stubs
* **Broadband capability**: Can be tuned across frequencies

## Limitations

### Forbidden Region

Loads with high conductance (low resistance) relative to Y0 cannot be matched:

```{math}
G_L > \frac{Y_0(1 + t^2)}{2t^2}
```

For λ/8 spacing (t = 1), this becomes $G_L > Y_0$.


## Stub Terminations

**Open-Circuit Stubs**
* Common in microstrip
* End-effect compensation needed
* Avoid DC paths to ground

**Short-Circuit Stubs**
* Require vias in microstrip
* More predictable at lower frequencies
* Better for high-power applications

## Example

**Match 100 + j50Ω to 50Ω at 3 GHz**

**Input data**
| Parameter | Value |
|-----------|-------------|
|Z0|50Ω|
|ZL|100 + j50Ω|
|frequency|1 GHz|
|Configuration |Open-circuit stubs|


**Results**
| Parameter | Value |
|-----------|-------------|
|Stub 1 length| 59.6 mm|
|Line length| 37.5 mm|
|Stub 2 length| 52.8 mm|

Circuit topology:

```
Port ── STUB1 ── TLIN(λ/8) ── STUB2 ── Load
        │                     │
       O/C                   O/C
```


## Reference

Pozar, D. M. "Microwave Engineering", 4th Edition, Wiley, 2011, pp. 241-245