# L-Section Matching

## Description

The L-section is the simplest lumped-element matching network, consisting of one series and one shunt reactive element (inductor or capacitor). It provides narrowband matching at a single frequency.

## When to Use

* Narrowband applications
* Simple, low-cost solution needed
* Load has moderate Q factor

## Design Equations

### Case 1: Z0 > RL (Shunt-Series Configuration)

```{math}
X = \pm\sqrt{R_L(Z_0 - R_L)} - X_L
```

```{math}
B = \pm\frac{\sqrt{(Z_0 - R_L)/R_L}}{Z_0}
```

### Case 2: Z0 < RL (Series-Shunt Configuration)

```{math}
B = \frac{X_L \pm \sqrt{R_L/Z_0}\sqrt{R_L^2 + X_L^2 - Z_0 R_L}}{R_L^2 + X_L^2}
```

```{math}
X = \frac{1}{B} + \frac{X_L Z_0}{R_L} - \frac{Z_0}{B R_L}
```

where:
| Parameter | Description |
|-----------|-------------|
|X|Series reactance|
|B|Shunt susceptance|
|RL|Load resistance|
|XL|Load reactance|
|Z0|System impedance|

### Component Values

For series element:
* If X < 0: Capacitor, {math}`C = -1/(\omega X)`
* If X > 0: Inductor, {math}`L = X/\omega$`

For shunt element:
* If B > 0: Capacitor, {math}`C = B/\omega`
* If B < 0: Inductor, {math}`L = -1/(\omega B)`

## Parameters

| Parameter | Description |
|-----------|-------------|
| **Z0** | Source impedance (Ω) |
| **ZL** | Load impedance (R + jX) (Ω) |
| **Frequency** | Matching frequency (Hz) |
| **Solution** | Solution 1 or 2 (determines high/low-pass characteristic) |

## Solutions

Each L-section match has two solutions:

* **Solution 1**: Typically provides low-pass response
* **Solution 2**: Typically provides high-pass response

Select based on desired filtering characteristics or to avoid DC short/open conditions.

## Limitations

* Narrowband (typically < 10% fractional bandwidth)
* No control over Q factor
* Cannot match purely reactive loads (RL = 0)
* Limited rejection outside passband

## Example

**Match 25Ω to 50Ω at 1 GHz**


**Input data**
| Parameter | Value |
|-----------|-------------|
|Z0|50Ω|
|ZL|25Ω|
|frequency|1 GHz|

**Results**

Solution 1 (Z0 > RL, shunt-series):

| Parameter | Value |
|-----------|-------------|
|Shunt capacitor|3.18 pF|
|Series inductor|3.98 nH|

Circuit topology:

```
Port ──┬── L (3.98 nH) ── Load (25Ω)
       │
       C (3.18 pF)
       │
      GND
```

## Reference

Vizmuller, P. "RF Design Guide: Systems, Circuits, and Equations", Artech House, 1995

## See Also

```{toctree}
:maxdepth: 1
/RFCircuitSynthesis/index
/RFCircuitSynthesis/ImpedanceMatching/index
```