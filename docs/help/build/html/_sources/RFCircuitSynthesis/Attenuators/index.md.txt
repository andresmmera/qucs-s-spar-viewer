# RF Attenuator Design Tool

## Overview

The RF Attenuator Design Tool provides synthesis of resistive attenuators in various topologies. All designs include automatic power dissipation calculations for proper component selection.

## Attenuator Topologies

The tool supports 10 different attenuator topologies, categorized by matching characteristics and structure:

| Topology | Notes|
|-----------|-------|
|[Pi](/RFCircuitSynthesis/Attenuators/PiTee/index)|Matched|
|[Tee](/RFCircuitSynthesis/Attenuators/PiTee/index)|Matched|
|[Bridged-Tee](/RFCircuitSynthesis/Attenuators/BridgedTee/index)|Matched|
|[Reflection attenuator](/RFCircuitSynthesis/Attenuators/ReflectionAttenuator/index)|Matched|
|[Quarter-wavelength series](/RFCircuitSynthesis/Attenuators/QuarterWaveAttenuators/index)|Frequency-dependent. Output port unmatched|
|[Quarter-wavelength shunt](/RFCircuitSynthesis/Attenuators/QuarterWaveAttenuators/index)|Frequency-dependent. Output port unmatched|
|[L-pad 1st series](/RFCircuitSynthesis/Attenuators/Lpad1stSeries/index)|Very broadband matching|
|[L-pad 1st shunt](/RFCircuitSynthesis/Attenuators/Lpad1stShunt/index)|Very broadband matching|
|[Series resistor](/RFCircuitSynthesis/Attenuators/Rseries/index)|Two ports unmatched|
|[Shunt resistor](/RFCircuitSynthesis/Attenuators/Rshunt/index)|Two ports unmatched|


See individual topology documentation for detailed design equations and schematics.

## Design Flow

1. **Select topology** based on matching requirements and bandwidth
2. **Set attenuation** (dB)
3. **Define impedances** (Zin, Zout)
4. **Enter input power** for dissipation calculation
5. For quarter-wave: **specify frequency** and **TL implementation**
6. **Generate schematic** → Tool outputs resistor values and power dissipation

## Topology Selection Guide

| Requirement | Recommended Topology |
|-------------|----------------------|
| Broadband match, simple | **Pi** or **Tee** |
| Widest bandwidth | **Reflection** (DC to multi-GHz) |
| Narrowband, low insertion loss | **Quarter-Wave** |
| Impedance transformation + attenuation | **L-pad** |
| Simplest (no matching) | **R-series** or **R-shunt** |

## References

[1] Vizmuller, P. (1995). *RF Design Guide: Systems, Circuits, and Equations*. Artech House.

[2] Doherty, W. E., & Joos, R. D. (1998). *The PIN Diode Circuit Designer's Handbook*. Microsemi Corp.

```{toctree}
:maxdepth: 1
/RFCircuitSynthesis/index
```