# RF Circuit Synthesis Tools

## Introduction

<ul style="margin-top: 0; line-height: 0.5;">
  <li>Filters</li>
  <li>Matching networks</li>
  <li>Power combining/splitting circuits</li>
  <li>Attenuators</li>
</ul>

```{figure} /Data-management-panel/images/tools-filter-tab.png
---
class: with-border
---

RF synthesis tools widget
```

## Design Tools

### [Filter Design](/RFCircuitSynthesis/Filters/index)

The following RF and MW filters can be synthesized:

```{eval-rst}
.. list-table::
   :header-rows: 1
   :class: sphinx-datatable

   * - Topology
     - Response type
     - Notes
   * - `Lumped LC filters - Canonical <../RFCircuitSynthesis/Filters/LC_Canonical/index>`_
     - LPF / HPF / BPF / BSF
     -
   * - `Lumped LC filters - Elliptic <../RFCircuitSynthesis/Filters/LC_Canonical/index>`_
     - LPF / HPF / BPF / BSF
     -
   * - `Lumped LC filters - Direct-coupled (BPF) <../RFCircuitSynthesis/Filters/LC_Canonical/index>`_
     - BPF
     -
   * - `Stepped-Z <../RFCircuitSynthesis/Filters/SteppedZ/index>`_
     - LPF
     -
   * - `Quarter-wavelength <../RFCircuitSynthesis/Filters/QuarterWave/index>`_
     - BPF / BSF
     -
   * - `Capacitively-coupled shunt resonators <../RFCircuitSynthesis/Filters/CapCoupledShuntResonators/index>`_
     - BPF
     -
   * - Side-coupled
     - BPF
     -
   * - `End-coupled <../RFCircuitSynthesis/Filters/EndCoupled/index>`_
     - BPF
     -
   * - Semilumped
     - LPF / HPF
     -
```

[Learn more](/RFCircuitSynthesis/Filters/index)

### Matching Networks

Single-port and two-port matching networks can be synthesized. The load can be entered manually or loaded from a Touchstone file. The following topologies are available:

```{eval-rst}
.. list-table::
   :header-rows: 1
   :class: sphinx-datatable

   * - Topology
     - Elements
     - Bandwidth
     - Complex Loads
     - Adjustable
   * - `L-section <../RFCircuitSynthesis/ImpedanceMatching/LSection/index>`_
     - 2 lumped
     - Narrow (5-10%)
     - Yes
     - No
   * - `Single-stub <../RFCircuitSynthesis/ImpedanceMatching/SingleStub/index>`_
     - 1 TL + stub
     - Moderate (10-20%)
     - Yes
     - No
   * - `Double-stub <../RFCircuitSynthesis/ImpedanceMatching/DoubleStub/index>`_
     - 1 TL + 2 stubs
     - Moderate (10-20%)
     - Yes
     - Yes
   * - `Multisection λ/4 <../RFCircuitSynthesis/ImpedanceMatching/MultisectionLambda4/index>`_
     - N×λ/4 TL
     - Broad (40-80%)
     - Real only
     - No
   * - `Cascaded LC <../RFCircuitSynthesis/ImpedanceMatching/CascadedLC/index>`_
     - 2N lumped
     - Moderate (20-40%)
     - Real only
     - No
   * - `λ/8 + λ/4 <../RFCircuitSynthesis/ImpedanceMatching/Lambda8Lambda4/index>`_
     - 2 TL sections
     - Moderate (10-20%)
     - Yes
     - No
```

### Power combining

This tool allows to synthesize a number of power splitters/combiners and couplers

```{eval-rst}
.. list-table::
   :header-rows: 1
   :class: sphinx-datatable

   * - Topology
     - Outputs
     - Power Split
     - Isolation
     - Bandwidth
     - Notes
   * - `Wilkinson <../RFCircuitSynthesis/PowerCombining/Wilkinson/index>`_
     - 2
     - Equal/Unequal
     - Excellent
     - Medium
     - Most common, simple
   * - `Multistage Wilkinson <../RFCircuitSynthesis/PowerCombining/MultistageWilkinson/index>`_
     - 2ⁿ
     - Equal
     - Excellent
     - Wide
     - Cascaded 2-way stages
   * - `T-Junction <../RFCircuitSynthesis/PowerCombining/TJunction/index>`_
     - 2
     - Equal/Unequal
     - None
     - Narrowband
     - Simplest, reactive
   * - `Branch-line <../RFCircuitSynthesis/PowerCombining/Branchline/index>`_
     - 2
     - Equal/Unequal
     - Good
     - Medium
     - 90° phase, quadrature hybrid
   * - `Double-box Branchline <../RFCircuitSynthesis/PowerCombining/DoubleBoxBranchLine/index>`_
     - 2
     - Equal/Unequal
     - Better
     - Medium
     - Improved branch-line
   * - `Bagley <../RFCircuitSynthesis/PowerCombining/Bagley/index>`_
     - N
     - Equal
     - Good
     - Narrowband
     - Multi-way, planar
   * - `Gysel <../RFCircuitSynthesis/PowerCombining/Gysel/index>`_
     - 2
     - Equal
     - Excellent
     - Medium
     - High power, grounded resistors
   * - `Lim-Eom <../RFCircuitSynthesis/PowerCombining/LimEom/index>`_
     - 2
     - Equal
     - Excellent
     - Wide
     - Wideband improvement
   * - `3-way Improved Isolation <../RFCircuitSynthesis/PowerCombining/ThreeWayWilkinsonImprovedIsolation/index>`_
     - 3
     - Equal
     - Excellent
     - Medium
     - Enhanced 3-port isolation
   * - `Recombinant 3-way Wilkinson <../RFCircuitSynthesis/PowerCombining/Recombinant3Way/index>`_
     - 3
     - Equal
     - Excellent
     - Medium
     - Alternative 3-port design
   * - `Wye Resistive Combiner <../RFCircuitSynthesis/PowerCombining/Wye/index>`_
     - N
     - Equal
     - Depends on # outputs
     - Very broadband
     - Lossy
   * - `Delta Resistive Combiner <../RFCircuitSynthesis/PowerCombining/Delta/index>`_
     - 2
     - Equal
     - 6 dB
     - Very broadband
     - Lossy
   * - `Adams Resistive Combiner <../RFCircuitSynthesis/PowerCombining/Adams/index>`_
     - 2
     - Unequal
     - Very poor
     - Very broadband
     - Lossy
```

### Attenuator design

```{eval-rst}
.. list-table::
   :header-rows: 1
   :class: sphinx-datatable

   * - Topology
     - Notes
   * - `Pi <../RFCircuitSynthesis/Attenuators/PiTee/index>`_
     - Matched
   * - `Tee <../RFCircuitSynthesis/Attenuators/PiTee/index>`_
     - Matched
   * - `Bridged-Tee <../RFCircuitSynthesis/Attenuators/BridgedTee/index>`_
     - Matched
   * - `Reflection attenuator <../RFCircuitSynthesis/Attenuators/ReflectionAttenuator/index>`_
     - Matched
   * - `Quarter-wavelength series <../RFCircuitSynthesis/Attenuators/QuarterWaveAttenuators/index>`_
     - Frequency-dependent. Output port unmatched
   * - `Quarter-wavelength shunt <../RFCircuitSynthesis/Attenuators/QuarterWaveAttenuators/index>`_
     - Frequency-dependent. Output port unmatched
   * - `L-pad 1st series <../RFCircuitSynthesis/Attenuators/Lpad1stSeries/index>`_
     - Very broadband matching
   * - `L-pad 1st shunt <../RFCircuitSynthesis/Attenuators/Lpad1stShunt/index>`_
     - Very broadband matching
   * - `Series resistor <../RFCircuitSynthesis/Attenuators/Rseries/index>`_
     - Two ports unmatched
   * - `Shunt resistor <../RFCircuitSynthesis/Attenuators/Rshunt/index>`_
     - Two ports unmatched
```

## See Also

```{toctree}
:maxdepth: 1

../Calculators/index
```
