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

| Topology | Load type | Notes|
|-----------|-------|-------|
| L-section  | {Real, Complex}| Narrowband|
| Single-stub| {Real, Complex}| Narrowband|
| Double-stub| {Real, Complex}| Narrowband|
|Multisection transformers| Real| Broadband|
| Cascaded L-sections| Real| Broadband|
|\lambda/8 + \lambda/4| {Real, Complex}| Narrowband|



### Power combining

This tool allows to synthesize a number of power splitters/combiners and couplers

| Topology | # ways| Notes|
|-----------|-------|-------|
|Wilkinson|2|Narrowband, Matched|
|Multistage Wilkinson|2|Broadband, Matched|
|T-Junction|2|Unmatched|
|Branchline|2|Narrowband, Matched|
|Double-box Branchline|2|Broadband, Matched|
|Bagley|odd {3,5,7,...}||
|Gysel|3|2|
|Lim-Eom|3||
|Wilkinson 3 way|3| High isolation|
|Recombinant 3 way|3||

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

## See Also

```{toctree}
:maxdepth: 1

../Calculators/index
```