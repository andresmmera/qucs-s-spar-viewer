# Reflection Attenuator

## Overview

Wideband matched attenuator using a **3 dB 90° hybrid coupler** with resistive terminations on the isolated ports. Provides excellent impedance match.

## Topology

```
        Port 1 ┌──────────────┐ Port 3
   Input ──────┤              ├────── Output
               │   3dB 90°    │
               │    Hybrid    │
        Port 2 │   Coupler    │ Port 4
            ┌──┤              ├──┐
            │  └──────────────┘  │
           [Ri]                 [Ri]
            │                    │
           GND                  GND
```

**Hybrid coupler:**
- Coupling factor: -3 dB (k = 0.7071 = 1/√2)
- Phase shift: 90° between coupled ports
- Ports 1-3 and 2-4 are isolated

**Both termination resistors:** Ri (equal value)

## Principle of Operation

1. Input signal enters Port 1
2. Hybrid splits power equally between Ports 2 and 4 (with 90° phase difference)
3. Resistors Ri reflect a portion of the power based on mismatch
4. Reflected signals recombine at Port 3 with controlled attenuation
5. Remaining power is absorbed in the resistors

## Design Equations

```
L = 10^(-0.05 × Attenuation)

Ri = Z₀ × (1 - L) / (1 + L)
```

**Constraint:** Requires **Zin = Zout = Z₀** (bilateral matched design).

### Derivation

The S-parameter from Port 1 to Port 3 is:

```
S₂₁ = (1/√2) × e^(jπ/2) × Γ₂ + (1/√2) × e^(jπ/2) × Γ₄

where Γ = (Z₀ - Ri) / (Z₀ + Ri)
```

For equal resistors (Ri at Ports 2 and 4):

```
S₂₁ = (Z₀ - Ri) / (Z₀ + Ri) × e^(jπ/2)

|S₂₁| = |Z₀ - Ri| / (Z₀ + Ri)
```

Attenuation:

```
α = -20 × log₁₀(|S₂₁|) = -20 × log₁₀(|Z₀ - Ri| / (Z₀ + Ri))
```

Solving for Ri when Ri < Z₀:

```
10^(-0.05×α) = (Z₀ - Ri) / (Z₀ + Ri)

Ri = Z₀ × (1 - 10^(-0.05×α)) / (1 + 10^(-0.05×α))
```

## Power Dissipation

Each resistor dissipates **half** of the total dissipated power:

```
Pdiss_total = Pin × (1 - 10^(-0.1 × Attenuation))

Pdiss_Ri = 0.5 × Pin × (1 - 10^(-0.1 × Attenuation))
```

Both resistors dissipate **equal power**.

## Example: 10 dB, Z₀ = 50 Ω, Pin = 1 W

```
L = 10^(-0.05 × 10) = 10^(-0.5) ≈ 0.316

Ri = 50 × (1 - 0.316) / (1 + 0.316)
   = 50 × 0.684 / 1.316
   ≈ 26.0 Ω
```

**Power dissipation:**
```
Pdiss_total = 1 × (1 - 10^(-0.1 × 10))
            = 1 × (1 - 0.1)
            = 0.9 W

Pdiss_R1 = Pdiss_R2 = 0.45 W each
```

## Resistor Values vs. Attenuation

| Attenuation (dB) | Ri (Ω, Z₀=50Ω) | Pdiss per resistor (Pin=1W) |
|------------------|----------------|------------------------------|
| 3 | 39.4 | 0.25 W |
| 6 | 31.2 | 0.37 W |
| 10 | 26.0 | 0.45 W |
| 20 | 20.5 | 0.50 W |
| 30 | 18.9 | 0.50 W |

**Observation:** As attenuation increases, Ri approaches Z₀/2 ≈ 25Ω, and power dissipation approaches 50% in each resistor.

## Advantages

1. **Very wideband:** DC to >20 GHz (limited only by hybrid coupler)
2. **Excellent impedance match:** Return loss >20 dB at all frequencies
3. **Less sensitive to tolerances:** Slight resistor value errors cause minimal performance degradation
4. **High power handling:** Limited by hybrid coupler, not resistors

## Limitations

1. **Requires hybrid coupler:** 
   - Bulky at low frequencies (<100 MHz)
   - More expensive than resistor-only designs
   - Adds extra insertion loss
2. **Higher cost:** Hybrid coupler more expensive than three resistors
3. **Matched at both:** Cannot provide impedance transformation

## References

[1] Doherty, W. E., & Joos, R. D. (1998). *The PIN Diode Circuit Designer's Handbook*, Chapter 5: Reflection Attenuators. Microsemi Corp.

## See Also

```{toctree}
:maxdepth: 1
/RFCircuitSynthesis/index
/RFCircuitSynthesis/Attenuators/index
```