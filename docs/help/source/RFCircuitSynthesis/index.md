# RF Circuit Synthesis Tools

## Introduction

The data management panel contains a tab with tools for synthesizing RF some passive RF circuits:
- Filters
- Matching networks
- Power combining/splitting circuits
- Attenuators

```{figure} /Data-management-panel/images/tools-filter-tab.png
---
class: with-border
---

RF synthesis tools widget
```

## Design Tools

### [Filter Design](/RFCircuitSynthesis/Filters/index)

The following RF and MW filters can be synthesized:

| Topology | Respose type | Notes|
|-----------|-------|-------|
| [Lumped LC filters](/RFCircuitSynthesis/Filters/LC_Canonical/index)  | ||
|    - Canonical filters |  LPF / HPF / BPF / BSF ||
|    - Elliptic | LPF / HPF / BPF / BSF ||
|    - Direct-coupled (BPF) | BPF ||
| [Stepped-Z](/RFCircuitSynthesis/Filters/SteppedZ/index) | LPF ||
|[Quarter-wavelength](/RFCircuitSynthesis/Filters/QuarterWave/index)| BPF / BSF||
|[Capacitively-coupled shunt resonators](/RFCircuitSynthesis/Filters/CapCoupledShuntResonators/index)|BPF||
|Side-coupled|BPF||
|[End-coupled](/RFCircuitSynthesis/Filters/EndCoupled/index)|BPF||
|Semilumped|LPF/HPF||

[Learn more](/RFCircuitSynthesis/Filters/index)

### Matching Networks

Single-port and two-port matching networks can be synthesized. The load can be entered manually or loaded from a Touchstone file.The following topologies are available:

| Topology | Elements | Bandwidth | Complex Loads | Adjustable |
|----------|----------|-----------|---------------|------------|
| [L-section](/RFCircuitSynthesis/ImpedanceMatching/LSection/index) | 2 lumped | Narrow (5-10%) | Yes | No |
| [Single-stub](/RFCircuitSynthesis/ImpedanceMatching/SingleStub/index) | 1 TL + stub | Moderate (10-20%) | Yes | No |
| [Double-stub](/RFCircuitSynthesis/ImpedanceMatching/DoubleStub/index) | 1 TL + 2 stubs | Moderate (10-20%) | Yes | Yes |
| [Multisection λ/4](/RFCircuitSynthesis/ImpedanceMatching/MultisectionLambda4/index) | N×λ/4 TL | Broad (40-80%) | Real only | No |
| [Cascaded LC](/RFCircuitSynthesis/ImpedanceMatching/CascadedLC/index) | 2N lumped | Moderate (20-40%) | Real only | No |
| [λ/8 + λ/4](/RFCircuitSynthesis/ImpedanceMatching/Lambda8Lambda4/index) | 2 TL sections | Moderate (10-20%) | Yes | No |



### [Power combining](/RFCircuitSynthesis/PowerCombining/index)

This tool allows to synthesize a number of power splitters/combiners and couplers

| Topology | Outputs | Power Split | Isolation | Bandwidth | Notes |
|----------|---------|-------------|-----------|-----------|-------------|
| [Wilkinson](/RFCircuitSynthesis/PowerCombining/Wilkinson/index) | 2 | Equal/Unequal | Excellent | Medium | Most common, simple |
| [Multistage Wilkinson](/RFCircuitSynthesis/PowerCombining/MultistageWilkinson/index) | 2ⁿ | Equal | Excellent | Wide | Cascaded 2-way stages |
| [T-Junction](/RFCircuitSynthesis/PowerCombining/TJunction/index) | 2 | Equal/Unequal | None | Narrowband | Simplest, reactive |
| [Branch-line](/RFCircuitSynthesis/PowerCombining/Branchline/index) | 2 | Equal/Unequal | Good | Medium | 90° phase, quadrature hybrid |
| [Double-box Branchline](/RFCircuitSynthesis/PowerCombining/DoubleBoxBranchLine/index) | 2 | Equal/Unequal | Better | Medium | Improved branch-line |
| [Bagley](/RFCircuitSynthesis/PowerCombining/Bagley/index) | N | Equal | Good | Narrowband | Multi-way, planar |
| [Gysel](/RFCircuitSynthesis/PowerCombining/Gysel/index) | 2 | Equal | Excellent | Medium | High power, grounded resistors |
| [Lim-Eom](/RFCircuitSynthesis/PowerCombining/LimEom/index) | 2 | Equal | Excellent | Wide | Wideband improvement |
| [3-way Improved Isolation](/RFCircuitSynthesis/PowerCombining/ThreeWayWilkinsonImprovedIsolation/index) | 3 | Equal | Excellent | Medium | Enhanced 3-port isolation |
| [Recombinant 3-way Wilkinson](/RFCircuitSynthesis/PowerCombining/Recombinant3Way/index)| 3 | Equal | Excellent | Medium | Alternative 3-port design |

### [Attenuator design](/RFCircuitSynthesis/Attenuators/index)

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

### [Matching Network Design](/RFCircuitSynthesis/ImpedanceMatching/index)

| Topology | Elements | Bandwidth | Complex Loads | Adjustable |
|----------|----------|-----------|---------------|------------|
| [L-section](/RFCircuitSynthesis/ImpedanceMatching/LSection/index) | 2 lumped | Narrow (5-10%) | Yes* | No |
| [Single-stub](/RFCircuitSynthesis/ImpedanceMatching/SingleStub/index) | 1 TL + stub | Moderate (10-20%) | Yes | No |
| [Double-stub](/RFCircuitSynthesis/ImpedanceMatching/DoubleStub/index) | 1 TL + 2 stubs | Moderate (10-20%) | Yes | Yes |
| [Multisection λ/4](/RFCircuitSynthesis/ImpedanceMatching/MultisectionLambda4/index) | N×λ/4 TL | Broad (40-80%) | Real only | No |
| [Cascaded LC](/RFCircuitSynthesis/ImpedanceMatching/CascadedLC/index) | 2N lumped | Moderate (20-40%) | Real only | No |
| [λ/8 + λ/4](/RFCircuitSynthesis/ImpedanceMatching/Lambda8Lambda4/index) | 2 TL sections | Moderate (10-20%) | Yes | No |

## See Also

```{toctree}
:maxdepth: 1

../Calculators/index
```