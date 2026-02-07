# Matching Network Design Tool

## Overview

The Matching Network Design Tool synthesizes RF/MW impedance matching networks to match a (complex) load impedance to a characteristic impedance (typically 50 Ω). The tool supports both one-port and two-port matching configurations.

## Features

* **Multiple topologies**: L-section, single-stub, double-stub, multisection λ/4, cascaded L-sections, λ/8+λ/4
* **Transmission line implementations**: Ideal transmission lines or physical microstrip
* **Two-port matching**: Design simultaneous input and output matching networks

## Basic Usage

1. Select the matching topology
2. Specify the source impedance (Z0)
3. Define the load impedance (ZL) or reflection coefficient
4. Set the matching frequency
5. Configure topology-specific parameters
6. Generate the matching network schematic

## One-Port vs Two-Port Matching

**One-Port Matching**
: Match a single load impedance to the source impedance. Used for antenna matching, filter terminations, etc.

**Two-Port Matching**
: Design input and output matching networks for active devices (amplifiers, mixers). S-parameters may be entered using the tool widgets or a Touchstone file.

## Topologies

| Topology | Elements | Bandwidth | Complex Loads | Adjustable |
|----------|----------|-----------|---------------|------------|
| [L-section](/RFCircuitSynthesis/ImpedanceMatching/LSection/index) | 2 lumped | Narrow (5-10%) | Yes | No |
| [Single-stub](/RFCircuitSynthesis/ImpedanceMatching/SingleStub/index) | 1 TL + stub | Moderate (10-20%) | Yes | No |
| [Double-stub](/RFCircuitSynthesis/ImpedanceMatching/DoubleStub/index) | 1 TL + 2 stubs | Moderate (10-20%) | Yes | Yes |
| [Multisection λ/4](/RFCircuitSynthesis/ImpedanceMatching/MultisectionLambda4/index) | N×λ/4 TL | Broad (40-80%) | Real only | No |
| [Cascaded LC](/RFCircuitSynthesis/ImpedanceMatching/CascadedLC/index) | 2N lumped | Moderate (20-40%) | Real only | No |
| [λ/8 + λ/4](/RFCircuitSynthesis/ImpedanceMatching/Lambda8Lambda4/index) | 2 TL sections | Moderate (10-20%) | Yes | No |

## See Also

```{toctree}
:maxdepth: 1
/RFCircuitSynthesis/index
```