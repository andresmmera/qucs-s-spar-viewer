# Resistive Voltage Divider

## Overview

The resistive voltage divider reduces an input voltage into a smaller output voltage using two resistors: one series and one shunt.

This calculator helps you design voltage dividers with power dissipation analysis, supporting parallel resistor combinations for both upper and lower branches.

## Basic Circuit Configuration

- **Upper resistor(s):** Connected between {math}`V_{DC}` and {math}`V_{out}`
- **Lower resistor(s):** Connected between {math}`V_{out}` and ground

The output voltage is taken from the node between the two resistors.

## Voltage Divider Formula

For a basic two-resistor divider, the output voltage is calculated using:

```{math}
V_{out} = V_{DC} \times \frac{R_{lower}}{R_{upper} + R_{lower}}
```

Where:
- {math}`V_{DC}` is the input voltage
- {math}`R_{upper}` is the resistance of the upper branch
- {math}`R_{lower}` is the resistance of the lower branch
- {math}`V_{out}` is the output voltage

## Parallel Resistor Combinations

This calculator supports multiple resistors in parallel for both the upper and lower branches. When multiple resistors are connected in parallel, the equivalent resistance is calculated using:

```{math}
\frac{1}{R_{eq}} = \frac{1}{R_1} + \frac{1}{R_2} + \frac{1}{R_3} + \ldots + \frac{1}{R_n}
```

This allows to
- Distribute the current (i.e. power dissipation) across multiple components
- Add degrees of freedom to fine-tune the output voltage

## Current and Power Calculations

### Current Through Each Resistor

**Upper Branch:**
For each resistor in the upper branch, the current is:

```{math}
I_{upper} = \frac{V_{DC} - V_{out}}{R_{upper}}
```

**Lower Branch:**
For each resistor in the lower branch, the current is:

```{math}
I_{lower} = \frac{V_{out}}{R_{lower}}
```

### Power Dissipation

The power dissipated by each resistor is given by:

```{math}
P = I^2 \times R
```

```{warning}
Real-world resistors come with a power dissipation rating (e.g. 50 mW, 250 mW, etc.). It's critical to keep the power dissipation with enough margin (typically 50-75% derating).
```

## Example Calculation

Consider a voltage divider with the following parameters:

| Parameter | Value |
|-----------|-------|
| Input Voltage ({math}`V_{DC}`) | 5.0 V |
| Upper Resistor | 1 kΩ |
| Lower Resistor | 1 kΩ |
| Max Power per Resistor | 50 mW |

**Output Voltage:**

```{math}
V_{out} = 5.0 \times \frac{1000}{1000 + 1000} = 2.5 \text{ V}
```

**Current Through Each Resistor:**

```{math}
I = \frac{V_{DC}}{R_{upper} + R_{lower}} = \frac{5.0}{2000} = 2.5 \text{ mA}
```

**Power Dissipation:**

```{math}
P_{each} = I^2 \times R = (0.0025)^2 \times 1000 = 6.25 \text{ mW}
```

```{math}
P_{total} = 2 \times 6.25 = 12.5 \text{ mW}
```

Since 6.25 mW < 50 mW, standard 1/8 W (125 mW) resistors would be more than adequate.
