# Secondary Image Calculator

## Overview

The problem of the second image frequency arises in superheterodyne receivers with two
downconversion steps since the second downconverter also has an image frequency which needs to be filtered
at the RF frontend.

This calculator determines the local oscillator (LO) frequencies and image frequencies
for both stages of a dual-conversion superheterodyne receiver using **low-side injection**.

In a downconversion mixer, two frequencies lie in the same intermediate frequency:

- **The intended intermediate frequency:** {math}`f_{IF} = f_{RF} - f_{LO}`
- **The image frequency** (from the negative side of the spectrum): {math}`-f_{IM} + f_{LO} = f_{IF}`

## Dual-Conversion Receiver Architecture

A dual-conversion receiver performs frequency conversion in two stages:

1. **First Stage:** RF signal → 1st IF
2. **Second Stage:** 1st IF → 2nd IF

## General Formula (Low-Side Injection)

In mixers with low-side injection, the following equation applies:

```{math}
f_{IF} = f_{RF} - f_{LO}
```

## First Conversion Stage (RF → 1st IF)

**LO1 Frequency:**

```{math}
f_{LO1} = f_{RF} - f_{IF1}
```

The image frequency comes from the negative side of the spectrum and falls in the IF band:

```{math}
f_{IF1} = -f_{IM1} + f_{LO1}
```

Therefore:

**First Image Frequency:**

```{math}
f_{IM1} = f_{LO1} - f_{IF1}
```

## Second Conversion Stage (1st IF → 2nd IF)

**LO2 Frequency:**

```{math}
f_{LO2} = f_{IF1} - f_{IF2}
```

Similarly, the second image frequency is:

**Second Image Frequency:**

```{math}
f_{IM2} = f_{LO2} - f_{IF2}
```

## Example Calculation

| Parameter          | Value   |
|-------------------|---------|
| RF Frequency      | 800 MHz |
| 1st IF Frequency  | 200 MHz |
| 2nd IF Frequency  | 10 MHz  |

**First Stage Results:**

- {math}`f_{LO1}` = 800 - 200 = **600 MHz**
- {math}`f_{IM1}` = 600 - 200 = **400 MHz**

**Second Stage Results:**

- {math}`f_{LO2}` = 200 - 10 = **190 MHz**
- {math}`f_{IM2}` = 190 - 10 = **180 MHz**

## Why Not Just One IF?

Choosing an IF frequency is a trade-off between image rejection and selectivity:

### High IF

| Pros | Cons |
|------|------|
| Large separation between desired signal and image: The image can be rejected with a simple filter | Narrow, high-Q filters are still needed at the IF, and they are difficult to build at high frequencies |

### Low IF

| Pros | Cons |
|------|------|
| Easier to build high rejection filters | Image frequency is close to the wanted signal, so image rejection at RF becomes difficult |

```{note}
**Solution:** Dual conversion uses a **high first IF** and then a **low second IF**
```

## Role of the Second IF

Once the signal is at the first IF:

- The **first IF filter** is relatively wide and mainly cleans up mixer products and distant interferers
- The **second mixer** converts this first-IF signal down to a much lower second IF

At the second IF, high selectivity filters are needed, but they are cheaper to build than at higher frequencies.