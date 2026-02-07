# Capacitively-Coupled Shunt Resonators Filter

## Overview

Bandpass filter topology using λ/4 short-circuit stub resonators coupled through series capacitors. Each stub acts as a shunt resonator, and the coupling capacitors provide the inter-resonator and external coupling.

## Principle

The filter consists of N short-circuited λ/4 stubs connected in shunt to the main transmission line. Series capacitors between each resonator and at the input/output ports provide coupling. The capacitor values and stub lengths are derived from the normalized lowpass prototype using admittance inverter transformations.

## Design Equations

### Admittance Inverters (J)

The coupling between resonators is realized through **J-inverters**, approximated by series capacitors.

**First section (input coupling, k=0):**
```{math}
J₀ = √(π × δ / (4 × g₁)) / Z₀
C₀ = J₀ / (ω₀ × √(1 - Z₀² × J₀²))
```

**Internal sections (inter-resonator coupling, k=1 to N-1):**
```{math}
Jₖ = (π × δ / 4) / (√(gₖ × gₖ₊₁) × Z₀)
Cₖ = Jₖ / ω₀
```

**Last section (output coupling, k=N):**
```{math}
Jₙ = √(π × δ / (4 × gₙ × gₙ₊₁)) / Z₀
Cₙ = Jₙ / (ω₀ × √(1 - Z₀² × Jₙ²))
```

### Stub Lengths with Capacitive Loading Compensation

The shunt stubs are nominally λ₀/4 long, but must be adjusted to compensate for the loading effect of the coupling capacitors.

**Capacitive loading:**
```{math}
ΔCₖ = -Cₖ₋₁ - Cₖ
```

**Adjusted stub length:**
```{math}
lₖ = λ₀/4 + (Z₀ × ω₀ × ΔCₖ / (2π)) × λ₀
```

If lₖ < 0, add λ₀/4 to bring it into the physical range.

Where:
| Parameter | Description |
|-----------|-------|
|**bw = BW / fc**|fractional bandwidth|
|**ω₀ = 2πfc**|Center angular frequency|
|**λ₀ = c / fc**|Free-space wavelength at center frequency|
|**gₖ**| Normalized lowpass prototype coefficients|
|**Z₀**| System impedance|

## Input Parameters

| Parameter | Range | Default | Description |
|-----------|-------|---------|-------------|
| Center freq (fc) | — | 2 GHz | Bandpass center frequency |
| Bandwidth (BW) | — | 400 MHz | 3 dB bandwidth |
| Order (N) | 2 – 10 | 3 | Number of resonators |
| Z₀ | — | 50 Ω | System impedance |

## Topology

```
         C₀        C₁        C₂              Cₙ
Input ──[═]──┬──[═]──┬──[═]──┬── ... ──┬──[═]── Output
             │       │       │         │
           stub₁   stub₂   stub₃     stubₙ
            l₁      l₂      l₃        lₙ
             │       │       │         │
            GND     GND     GND       GND
```

All stubs have characteristic impedance Z₀ = ZS (typically 50 Ω).


## Advantages

- Compact, planar layout
- All stubs have the same impedance.
- Series capacitors easy to realize (chip caps or gap caps)

## Limitations

- Narrowband (typically 5–20% fractional BW)
- Requires precise coupling values
- Spurious passbands at odd harmonics (3fc, 5fc, ...)
- Via inductance can affect performance at high frequencies

## References

[1] Pozar, D. M. (2012). *Microwave Engineering* (4th ed.), Section 8.7, pp. 443–448. Wiley.

## See Also

```{toctree}
:maxdepth: 1
/RFCircuitSynthesis/index
/RFCircuitSynthesis/Filters/index
```