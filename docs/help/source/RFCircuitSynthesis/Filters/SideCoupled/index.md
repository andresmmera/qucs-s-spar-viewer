# Side-Coupled (Parallel-Coupled) Bandpass Filter

## Overview

Bandpass filter using λ/4 coupled transmission line sections placed side-by-side. The electromagnetic coupling between parallel resonators realizes the filter response. Also known as parallel-coupled line filter or edge-coupled filter.

## Principle

The filter consists of N λ/4 coupled-line sections arranged in cascade. Each section acts as a resonator at the center frequency, and the coupling between adjacent sections is controlled by their physical spacing (gap). The coupling is primarily magnetic at the design frequency.

## Design Equations

### Admittance Inverters (J)

The required coupling between resonators is first calculated as **J-inverters**:

**First section (input coupling, k=0):**
```{math}
J₀ = √(π × δ / (2 × g₁)) / Z₀
```

**Internal sections (inter-resonator coupling, k=1 to N-1):**
```{math}
Jₖ = (π × δ / 2) / (√(gₖ × gₖ₊₁) × Z₀)
```

**Last section (output coupling, k=N):**
```{math}
Jₙ = √(π × δ / (2 × gₙ × gₙ₊₁)) / Z₀
```

### Even and Odd Mode Impedances

Each coupled-line section is characterized by its even-mode (Z₀e) and odd-mode (Z₀o) impedances, which are derived from the J-inverter parameter:

```{math}
Z₀e = Z₀ × (1 + J × Z₀ + (J × Z₀)²)
Z₀o = Z₀ × (1 - J × Z₀ + (J × Z₀)²)
```

These impedances determine the required coupling strength. Tighter coupling (larger J) produces larger Z₀e and smaller Z₀o.

### Physical Length

All coupled-line sections are exactly λ/4 at the center frequency:

```{math}
l = λ₀ / 4 = c / (4 × fc)
```

Where:

| Parameter | Description |
|-----------|-------|
|**bw= BW / fc**|Fractional bandwidth|
|**fc**|Center frequency|
|**Z₀**|System impedance|
|**gₖ**|Normalized lowpass prototype coefficients|
|**c**|Speed of light|

## Input Parameters

| Parameter | Range | Default | Description |
|-----------|-------|---------|-------------|
| Center freq (fc) | — | 2 GHz | Bandpass center frequency |
| Bandwidth (BW) | — | 400 MHz | 3 dB bandwidth |
| Order (N) | 2 – 10 | 3 | Number of resonators |
| Z₀ | — | 50 Ω | System impedance |

## Topology

```
Input ──╪═══╪──╪═══╪──╪═══╪──╪═══╪── Output
        ║   ║  ║   ║  ║   ║  ║   ║
        ╪═══╪  ╪═══╪  ╪═══╪  ╪═══╪
       Section Section Section Section
          1      2      3      N
```

Each `╪═══╪` represents a λ/4 coupled-line section with two parallel traces.



## Advantages

- Fully planar, single-layer layout
- No vias or chip components required

## Limitations

- Fractional bandwidth limited by fabrication (typically 5–30%)
- Spurious passband at 3fc due to λ/4 resonance
- Large at lower frequencies

## References

[1] David M. Pozar (2012). *Microwave Engineering*, pp. 430–437. Wiley.

## See Also

```{toctree}
:maxdepth: 1
/RFCircuitSynthesis/index
/RFCircuitSynthesis/Filters/index
```