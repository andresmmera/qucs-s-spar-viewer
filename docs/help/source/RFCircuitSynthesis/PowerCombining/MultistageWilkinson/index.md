# Multistage Wilkinson Power Divider

## Overview

**Wideband** power divider created by cascading multiple 2-way Wilkinson sections with progressively optimized impedances and resistor values.

## Topology
```
           ┌───[Z1, λ/4]───────[Z2, λ/4]── * * * ───[ZN, λ/4]──── Output #1
           │               |              |                   |
Input  ────┤              [R1]           [R2]                [RN]
           │               |              |                   |
           └───[Z1, λ/4]───────[Z2, λ/4]── * * * ───[ZN, λ/4]──── Output #2
```

## Advantages

1. **Wideband**

3. **High isolation** 
   - Maintained across BW

## Limitations

1. **Larger size**

2. **Design complexity** 

3. **Higher loss** 
   - More TL sections, higher loss

4. **Cost** 
   - Larger PCB area

   ## See Also

```{toctree}
:maxdepth: 1
/RFCircuitSynthesis/index
/RFCircuitSynthesis/PowerCombining/index
```