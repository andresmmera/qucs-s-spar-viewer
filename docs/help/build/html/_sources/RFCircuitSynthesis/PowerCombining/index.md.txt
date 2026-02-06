# RF Power Combining/Dividing Design Tool

## Overview

The Power Combining/Dividing Design Tool provides synthesis of various RF power splitter and combiner topologies. All designs support both **power division** (1→N) and **power combining** (N→1) by reciprocity.

## Supported Topologies

The tool supports 10 different power divider/combiner topologies:

| Topology | Outputs | Power Split | Isolation | Bandwidth | Notes |
|----------|---------|-------------|-----------|-----------|-------------|
| [Wilkinson](/RFCircuitSynthesis/PowerCombining/Wilkinson/index) | 2 | Equal/Unequal | Excellent | Medium | Most common, simple |
| [Multistage Wilkinson](/RFCircuitSynthesis/PowerCombining/MultistageWilkinson/index) | 2ⁿ | Equal | Excellent | Wide | Cascaded 2-way stages |
| [T-Junction](/RFCircuitSynthesis/PowerCombining/TJunction/index) | 2 | Equal/Unequal | None | Narrowband | Simplest, reactive |
| [Branch-Line](/RFCircuitSynthesis/PowerCombining/Branchline/index) | 2 | Equal/Unequal | Good | Medium | 90° phase, quadrature hybrid |
| [Double-box Branch-Line](/RFCircuitSynthesis/PowerCombining/DoubleBoxBranchLine/index) | 2 | Equal/Unequal | Better | Medium | Improved branch-line |
| [Bagley](/RFCircuitSynthesis/PowerCombining/Bagley/index) | N | Equal | Good | Narrowband | Multi-way, planar |
| [Gysel](/RFCircuitSynthesis/PowerCombining/Gysel/index) | 2 | Equal | Excellent | Medium | High power, grounded resistors |
| [Lim-Eom](/RFCircuitSynthesis/PowerCombining/LimEom/index) | 2 | Equal | Excellent | Wide | Wideband improvement |
| [3-way Improved Isolation](/RFCircuitSynthesis/PowerCombining/ThreeWayWilkinsonImprovedIsolation/index) | 3 | Equal | Excellent | Medium | Enhanced 3-port isolation |
| [Recombinant 3-way Wilkinson](/RFCircuitSynthesis/PowerCombining/Recombinant3Way/index)| 3 | Equal | Excellent | Medium | Alternative 3-port design |

## Common Parameters

### Electrical Specifications

| Parameter | Range | Default | Description |
|-----------|-------|---------|-------------|
| Z₀ | 1 – 1000 Ω | 50 Ω | System impedance |
| Frequency | 1 Hz – 1 MHz | 1 GHz | Design frequency |
| Output Power Ratio | -20 to +20 dB | 0 dB | Power split ratio (where applicable) |
| Number of Outputs | 2, 3, 4, 8, 16 | 2 | For multi-way topologies |

### Implementation Options

1. **Ideal TL:** Lossless transmission lines (schematic simulation)
2. **Microstrip:** Physical microstrip layout (requires substrate parameters)
3. **Lumped:** LC equivalent circuits (low frequency, Wilkinson only)

## Key Concepts

### Reciprocity

All power dividers are **reciprocal**:
- **Divider mode:** 1 input → N outputs (signal split)
- **Combiner mode:** N inputs → 1 output (signal combining)

Performance (insertion loss, isolation, match) is identical in both directions.

### Power Split Ratio

For 2-way dividers, the **power split ratio** K determines how power divides between outputs:

```
K = P₂/P₃ = 10^(K_dB/10)

where K_dB is the ratio in dB
```

**Equal split:** K = 1 (K_dB = 0 dB) → P₂ = P₃ = Pin/2
**Unequal split:** K ≠ 1 → P₂ = K×P₃

### Isolation

**Isolation** is the signal attenuation between output ports (Port 2 ↔ Port 3):

```
Isolation (dB) = -20 × log₁₀(|S₂₃|)
```

**High isolation** (>20 dB) is critical for:
- Combining independent amplifiers (prevents interaction)
- Antenna systems (reduces coupling)
- Measurement systems (prevents crosstalk)

### Insertion Loss

**Insertion Loss** is the power loss from input to each output:

```
IL (dB) = -10 × log₁₀(Pout/Pin)
```

**Ideal 2-way equal split:** IL = 3.01 dB (50% power loss is fundamental)
**Real dividers:** IL = 3.01 dB + losses (resistor, conductor, dielectric)

## Topology Selection Guide

| Requirement | Recommended Topology |
|-------------|----------------------|
| **General-purpose 2-way** | **Wilkinson** |
| **High power handling** | **Gysel** (grounded resistors) |
| **Wideband (multi-octave)** | **Multistage Wilkinson** or **Lim-Eom** |
| **Narrowband, simple** | **T-Junction** |
| **90° phase quadrature** | **Branch-line** |
| **Multi-way (N > 2)** | **Bagley** or cascade Wilkinsons |
| **3-way optimized** | **3-Way Wilkinson (Improved)** |
| **No isolation needed** | **T-Junction** (simplest) |

## Design Flow

1. **Select topology** based on requirements (power, bandwidth, isolation, outputs)
2. **Set system impedance** Z₀ (typically 50Ω)
3. **Specify frequency** (center frequency for narrowband designs)
4. **Choose power split ratio** (for 2-way unequal dividers)
5. **Select implementation** (Ideal TL / Microstrip / Lumped)
6. For microstrip: **define substrate** parameters
7. **Generate schematic** → Tool outputs component values and layout

## Implementation Comparison

### Ideal TL (Schematic)
- **Use for:** Circuit simulation, proof-of-concept
- **Pros:** Lossless, frequency-independent impedance
- **Cons:** Not physically realizable

### Microstrip (Layout)
- **Use for:** PCB fabrication, physical prototype
- **Pros:** Manufacturable, accurate EM behavior
- **Cons:** Requires substrate parameters, frequency-dependent
- **Substrate needed:** εᵣ, height, tan δ, conductor σ, thickness

### Lumped LC (Low Frequency)
- **Use for:** Low frequency (<100 MHz), compact size
- **Pros:** Smallest footprint, no TEM mode required
- **Cons:** Limited to Wilkinson, component Q limits performance

## Key Performance Metrics

### Return Loss

Impedance match at each port:

```
RL (dB) = -20 × log₁₀(|Γ|) = -20 × log₁₀(|Sᵢᵢ|)
```

**Good match:** RL > 20 dB (VSWR < 1.22:1)

### Amplitude Balance

Difference in output power levels (equal split):

```
Balance (dB) = |IL₁ - IL₂|
```

**Good balance:** < 0.5 dB

### Phase Balance

Phase difference between outputs:

```
Phase Balance (°) = |∠S₂₁ - ∠S₃₁|
```

**Wilkinson:** 0° (in-phase)
**Branch-line:** 90° (quadrature)

## Bandwidth Considerations

### Narrowband Topologies (10-20% FBW)
- T-Junction
- Bagley
- Single-stage Wilkinson

### Medium Bandwidth (20-50% FBW)
- Branch-line
- Gysel
- 3-Way Wilkinson variants

### Wideband (>50% FBW, multi-octave)
- Multistage Wilkinson
- Lim-Eom

## Power Handling

### Resistive Topologies
Wilkinson, Gysel, Lim-Eom: Power limited by **isolation resistors**

**Average power rating:**
```
P_max ≈ (Isolation_dB - 10) × P_resistor
```

Example: 20 dB isolation, 2W resistors → ~20W max

### Grounded Resistors (Gysel)
- Better thermal management
- Easier heat sinking
- Higher power capability

### Reactive Topologies
T-Junction, Branch-line: No resistors → **very high power** (limited by TL breakdown)

## Multi-Way Combining

For N-way power combining:

1. **Tree topology:** Cascade 2-way dividers
   - N = 2, 4, 8, 16, ... (powers of 2)
   - Simple, modular design
   
2. **Bagley:** Direct N-way planar design
   - Any N
   - More compact than tree
   - Narrower bandwidth

3. **Corporate feed:** Multistage Wilkinson
   - Wideband
   - Good isolation
   - Larger size

## References

[1] Pozar, D. M. (2012). *Microwave Engineering* (4th ed.), Chapter 7. Wiley.

[2] Wilkinson, E. J. (1960). *An N-Way Hybrid Power Divider*. IRE Trans. Microwave Theory Tech., MTT-8, 116-118.

[3] Gysel, U. H. (1975). *A New N-Way Power Divider/Combiner Suitable for High-Power Applications*. IEEE MTT-S Int. Microwave Symp. Digest, 116-118.
