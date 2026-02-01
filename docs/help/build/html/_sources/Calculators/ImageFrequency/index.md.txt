# Image Frequency Calculator

In a superheterodyne receiver, the **image frequency** is an unwanted frequency that,
when mixed with the local oscillator (LO), produces the same intermediate frequency (IF) as the
desired RF signal.

```{note}
**Problem:** Consequently, if it is not properly filtered out *before* the mixer,
any signal present in the image band will appear at the IF output along with the wanted signal, causing interference.
```

## How Mixers Work

A mixer produces sum and difference frequencies:

```{math}
f_{out} = |f_{RF} \pm f_{LO}|
```

For downconversion purposes:

```{math}
f_{IF} = |f_{RF} - f_{LO}|
```

## Injection Modes

### Low-Side Injection

The LO frequency is **below** the RF frequency:

```{math}
f_{IF} = f_{RF} - f_{LO}
```

Then:

```{math}
f_{LO} = f_{RF} - f_{IF}
```

The image frequency is taken from the negative side of the spectrum:

```{math}
f_{IF} = -f_{IM} + f_{LO}
```

```{math}
\mathbf{f_{IM} = f_{LO} - f_{IF} = f_{RF} - 2 \times f_{IF}}
```

### High-Side Injection

The LO frequency is **above** the RF frequency:

```{math}
f_{IF} = f_{LO} - f_{RF}
```

Then:

```{math}
f_{LO} = f_{RF} + f_{IF}
```

The image frequency in high-side injection comes from the positive side of the spectrum and fall in the IF frequency but in the negative side of the spectrum:

```{math}
-f_{IF} = f_{IM} - f_{LO}
```

```{math}
\mathbf{f_{IM} = f_{RF} + 2 \times f_{IF}}
```

*Why?* Because $f_{LO} - f_{IM} = f_{IF}$

## Example Calculation

| Parameter | Value |
|-----------|-------|
| RF Frequency | 1000 MHz |
| IF Frequency | 200 MHz |

### Low-Side Injection

* $f_{LO} = 1000 - 200 = \mathbf{800\ MHz}$
* $f_{IM} = 1000 - 2 \times 200 = \mathbf{600\ MHz}$

Verification: 800 - 600 = 200 MHz ✓

### High-Side Injection

* $f_{LO} = 1000 + 200 = \mathbf{1200\ MHz}$
* $f_{IM} = 1000 + 2 \times 200 = \mathbf{1400\ MHz}$

Verification: 1400 - 1200 = 200 MHz ✓

## Choosing the IF Frequency: The Trade-Off

### High IF

| Pros | Cons |
|------|------|
| • Large separation ($2 \times f_{IF}$) between signal and image<br>• RF preselector can easily reject the image<br>• Simpler, cheaper RF filters required | • Harder to build very narrow, high-Q channel filters at high frequency<br>• Poor adjacent-channel selectivity<br>• More expensive components |

### Low IF

| Pros | Cons |
|------|------|
| • Easy to build very narrow, high-quality filters<br>• Excellent adjacent-channel selectivity<br>• Better performance and lower cost | • Small separation between signal and image<br>• Image frequency is close to wanted signal<br>• May require sharp, expensive RF preselection |