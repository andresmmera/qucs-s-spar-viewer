# Free Space Path Loss Calculator

## Overview

The Free Space Path Loss (FSPL) calculator computes signal attenuation in free space based on frequency, distance, and antenna gains.

## Formula

The FSPL is calculated using:

```
FSPL (dB) = 20×log₁₀(4π/c) + 20×log₁₀(f) + 20×log₁₀(d) - G_TX - G_RX
```

Where:
- `f` = frequency in Hz
- `d` = distance in meters
- `c` = speed of light (299,792,458 m/s)
- `G_TX` = transmitter antenna gain in dBi
- `G_RX` = receiver antenna gain in dBi
- `20×log₁₀(4π/c)` ≈ -147.55 dB (constant term)

## Input Parameters

| Parameter | Range | Units Available |
|-----------|-------|-----------------|
| Frequency | 0 to 10¹⁵ | Hz, kHz, MHz, GHz, THz |
| Distance | 0 to 10¹⁵ | m, km, cm, mm, ft, mi, nmi |
| G_TX | -50 to 100 dB | dBi |
| G_RX | -50 to 100 dB | dBi |

## Output

The calculator displays path loss for five distance points:
- d/4 (quarter distance)
- d/2 (half distance)
- d (specified distance, highlighted)
- 2×d (double distance)
- 4×d (quadruple distance)

## Example

**Input:**
- Frequency: 1000 MHz (1 GHz)
- Distance: 1 km
- G_TX: 0 dBi
- G_RX: 0 dBi

**Calculation:**
```
f = 1×10⁹ Hz
d = 1000 m
FSPL = -147.55 + 20×log₁₀(10⁹) + 20×log₁₀(1000) - 0 - 0
     = -147.55 + 180 + 60
     = 92.45 dB
```

**Output Table:**

| Distance | Path Loss |
|----------|-----------|
| 250 m (d/4) | 80.43 dB |
| 500 m (d/2) | 86.44 dB |
| **1 km (d)** | **92.45 dB** |
| 2 km (2×d) | 98.47 dB |
| 4 km (4×d) | 104.48 dB |

## Notes

- Distance doubling increases path loss by approximately 6 dB
- Higher frequencies result in greater path loss
- Antenna gains reduce overall path loss
- Invalid inputs (frequency or distance ≤ 0) display "Error"