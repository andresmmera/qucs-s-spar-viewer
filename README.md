# Qucs-S S-Parameter Viewer & RF Synthesis Tools

GUI toolkit for RF and MW circuit design that combines S-parameter visualization with synthesis tools for filters, matching networks, attenuators, and power combiners. 
This is part of the [Qucs-S project](https://ra3xdh.github.io/).

**[Documentation](https://andresmmera.github.io/qucs-s-spar-viewer/help/build/html/index.html)**
**[Releases](https://github.com/andresmmera/qucs-s-spar-viewer/releases)**

---

## Features

### S-Parameter Visualization

Display S-parameter data in multiple formats:

- Magnitude and phase (Cartesian)
- Smith chart
- Polar plot
- Port impedance
- VSWR
- Group delay

### Data Management

- Read data from **Touchstone files** and **Qucs-S datasets**
- Add files by drag-and-drop or via the Add File button
- Manage traces, markers, and limit lines from the data management panel
- Save and restore sessions to a file
- Built-in note-taking widget for annotations

### RF Circuit Synthesis

Synthesize schematics for a range of RF building blocks directly inside the tool. Simulation runs internally, no external simulator backend needed. The schematics can be exported to Qucs-S for further analysis.

#### Filters

| Topology | Response |
|---|---|
| Lumped LC — Canonical | LPF / HPF / BPF / BSF |
| Lumped LC — Elliptic | LPF / HPF / BPF / BSF |
| Lumped LC — Direct-coupled | BPF |
| Stepped-Z | LPF |
| Quarter-wavelength | BPF / BSF |
| Capacitively-coupled shunt resonators | BPF |
| Side-coupled | BPF |
| End-coupled | BPF |
| Semilumped | LPF / HPF |

#### Matching Networks

Supports single-port and two-port networks. Complex loads can be entered manually or loaded from a Touchstone file.

| Topology | Elements | Bandwidth | Complex Loads |
|---|---|---|---|
| L-section | 2 lumped | Narrow | Yes |
| Single-stub | 1 TL + stub | Moderate | Yes |
| Double-stub | 1 TL + 2 stubs | Moderate | Yes |
| Multisection λ/4 | N×λ/4 TL | Broad | Real only |
| Cascaded LC | 2N lumped | Moderate | Real only |
| λ/8 + λ/4 | 2 TL sections | Moderate | Yes |
| Tee | 3 lumped | Narrow | Yes |
| Pi | 3 lumped | Narrow | Yes |
| Tapped-C / Tapped-L | 3 lumped | Narrow | No |
| Double Tapped Resonator | 4 lumped | Narrow | No |

#### Power Combiners / Splitters

Wilkinson, Multistage Wilkinson, T-Junction, Branch-line, Double-box Branch-line, Bagley, Gysel, Lim-Eom, 3-way Improved Isolation, Recombinant 3-way Wilkinson, Wye/Delta/Adams resistive combiners.

#### Attenuators

Pi, Tee, Bridged-Tee, Reflection, Quarter-wavelength (series/shunt), L-pad (series/shunt), Series resistor, Shunt resistor.

### Engineering Calculators

A collection of calculators available from the menu bar:

**RF Electronics:** reflection coefficient conversions (Γ ↔ Z ↔ VSWR ↔ S11), octaves/decades from bandwidth, frequency-to-wavelength converter, RF power unit converter, free space path loss, image frequency, secondary image frequency.

**General Electronics:** voltage divider, parallel resistors, parallel inductors, series capacitors.

---

## Building from Source

### Dependencies

- Qt 5 or Qt 6
- CMake ≥ 3.x

### Build

```bash
git clone https://github.com/andresmmera/qucs-s-spar-viewer.git
cd qucs-s-spar-viewer
mkdir build && cd build
cmake ..
make -j$(nproc)
```


---

## License

GPL-3.0-or-later. See [LICENSE](LICENSE) for details.

---
