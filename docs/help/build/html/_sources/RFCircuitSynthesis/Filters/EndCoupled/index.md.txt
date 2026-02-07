# End-Coupled Bandpass Filter

## Overview

Bandpass filter using λ/4 or λ/2 resonators coupled through small gaps at their ends. The coupling is capacitive, realized by the fringing fields between adjacent resonator ends.

## Principle

Each resonator is approximately λ/2 long at the center frequency. Adjacent resonators are physically separated by a small gap, creating capacitive coupling. The gap capacitance acts as a series coupling element between resonators.

## Design Equations

### J-Inverter Parameters

The required coupling between resonators is expressed as **J-inverters**:

**First section (external coupling):**
```{math}
J₀ = √(0.5 × π × bw / (g₀ × g₁))
```

**Last section (external coupling):**
```{math}
Jₙ = √(0.5 × π × bw / (gₙ × gₙ₊₁))
```

**Internal sections (inter-resonator coupling):**
```{math}
Jₖ = (0.5 × π × bw) / √(gₖ × gₖ₊₁)
```

### Susceptance and Capacitance

Each J-inverter is approximated by a series capacitor:

```{math}
B = J / (1 - J²)
C = B / ω₀
```

### Resonator Lengths

The resonator electrical length accounts for the phase shift introduced by the coupling capacitors:

```{math}
θₖ = π - 0.5 × (arctan(2Bₖ₋₁) + arctan(2Bₖ))
lₖ = θₖ × λ_g0 / (2π)
```

Where:

| Parameter | Description | 
|-----------|-------|
|**bw = BW / fc**|Fractional bandwidth|
|**ω₀ = 2πfc**|Center angular frequency|
|**λ_g0 = c / fc**|Wavelength at center frequency|
|**gₖ**|Normalized lowpass prototype coefficients|
|**Bₖ**|Susceptance of coupling capacitor k|

## Input Parameters

| Parameter | Range | Default | Description |
|-----------|-------|---------|-------------|
| Center freq (fc) | — | 2 GHz | Bandpass center frequency |
| Bandwidth (BW) | — | 400 MHz | 3 dB bandwidth |
| Order (N) | 2 – 10 | 3 | Number of resonators |
| Z₀ | — | 50 Ω | System impedance |

## Topology

```
Input ──[C₀]──[TL₁]──[C₁]──[TL₂]──[C₂]──[TLₙ]──[Cₙ]── Output
        gap     λ₁     gap    λ₂     gap    λₙ     gap
```


## Limitations

- Narrowband (5–10%)
- Gap capacitances may be difficult to control precisely

## References

[1] David M. Pozar (2012). *Microwave Engineering*, pp. 441–442. Wiley.


## See Also

```{toctree}
:maxdepth: 1
/RFCircuitSynthesis/index
/RFCircuitSynthesis/Filters/index
```