# LC Canonical (Ladder) Filters

## Overview

Classical lumped-element filter topology using inductors and capacitors arranged in a ladder network. Supports all four filter classes: lowpass, highpass, bandpass, and bandstop.

## Principle

Normalized lowpass prototype coefficients are transformed into actual component values based on the desired filter type. The network can begin with either a shunt or series element, yielding first-series or first shunt topologies.

## Topology Options

### CLC (1st shunt)
Begins with a shunt capacitor (to ground).

**Lowpass:**
```
Input ──┬──[L]──┬──[L]──┬── Output
        │       │       │
       [C]     [C]     [C]
        │       │       │
       GND     GND     GND
```

### LCL (1st series)
Begins with a series inductor.

**Lowpass:**
```
Input ──[L]──┬──[L]──┬──[L]── Output
             │       │
            [C]     [C]
             │       │
            GND     GND
```

## Design Equations

### Lowpass

Element values are scaled from the normalized prototype:

**Shunt capacitor:**
```{math}
C = gₖ / (2π × fc × Z₀)
```

**Series inductor:**
```{math}
L = gₖ × Z₀ / (2π × fc)
```

### Highpass

Inductors and capacitors swap roles (dual network):

**Shunt inductor:**
```{math}
L = Z₀ / (2π × fc × gₖ)
```

**Series capacitor:**
```{math}
C = 1 / (2π × fc × gₖ × Z₀)
```

### Bandpass

Each lowpass element is replaced by a series or parallel resonant circuit:

**Series inductor →** series LC resonator:
```{math}
Lₛ = gₖ × Z₀ / (2π × BW)
Cₛ = BW / (gₖ × Z₀ × (2π × fc)²)
```

**Shunt capacitor →** parallel LC resonator:
```{math}
Cₚ = gₖ / (2π × BW × Z₀)
Lₚ = BW × Z₀ / (gₖ × (2π × fc)²)
```

### Bandstop

Each lowpass element is replaced by its dual resonator:

**Series inductor →** parallel LC resonator (series arm):
```{math}
Lₚ = gₖ × Z₀ × BW / ((2π × fc)²)
Cₚ = 1 / (gₖ × Z₀ × 2π × BW)
```

**Shunt capacitor →** series LC resonator (shunt arm):
```{math}
Lₛ = Z₀ / (gₖ × 2π × BW)
Cₛ = gₖ × BW / (Z₀ × (2π × fc)²)
```

Where:

| Parameter | Description |
|-----------|-------------|
|**fc**|Cutoff frequency (LP/HP) or center frequency (BP/BS)|
|**BW**|Bandwidth (BP/BS)|
|**Z₀**|System impedance|
|**gₖ**|Normalized lowpass prototype coefficients|

## Input Parameters

| Parameter | Range | Default | Description |
|-----------|-------|---------|-------------|
| Cutoff freq (fc) | — | 1 GHz | LP/HP cutoff |
| Center freq (fc) | — | 2 GHz | BP/BS center |
| Bandwidth (BW) | — | 400 MHz | BP/BS bandwidth |
| Order (N) | 2 – 10 | 3 | Number of elements |
| Topology | CLC / LCL | CLC | Shunt-first or series-first |

## Semilumped Option

For lowpass and highpass filters, shunt capacitors and/or series inductors can be replaced by transmission line sections to create a hybrid lumped/distributed implementation.

**Shunt capacitor replacement:**
```{math}
l_C = (λ₀ / 2π) × arcsin(2π × fc × Z_min × C)
```

**Series inductor replacement:**
```{math}
l_L = (λ₀ / 2π) × arcsin(2π × fc × L / Z_max)
```

Where:

| Parameter | Description |
|-----------|-------------|
|**Z_min**|Minimum realizable impedance (e.g., 10 Ω)|
|**Z_max**|Maximum realizable impedance (e.g., 120 Ω)|


## References

[1] "Handbook of Filter Synthesis", Anatol I. Zverev. John Wiley and Sons Inc. 1967

## See Also

```{toctree}
:maxdepth: 1
/RFCircuitSynthesis/index
/RFCircuitSynthesis/Filters/index
```
