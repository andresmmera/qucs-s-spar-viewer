# S-Parameter Viewer & RF Synthesis Tools

## Introduction

This is a comprehensive toolkit for RF and microwave circuit design. It combines S-parameter visualization capabilities with synthesis tools for filters, matching networks, attenuators, and power combiners. Additionally, a number of simple RF engineering calculators are available in the menu bar at the top of the window.

## Features

### Display Features

- Rectangular plot, Smith Chart, and polar plot display
- Marker display
- Limit lines (for magnitude and phase plots)

### Data Capabilities

- Reads Touchstone files and Qucs-S datasets
- Trace management
- Session management (save, load, and recent files listing)

### Design Tools

- RF circuit synthesis tools
- [RF engineering calculators](/Calculators/index)

## Interface Overview

```{figure} /images/SPViewer-UI-layout-overview.png
---
class: with-border
---
Overview of the user interface.
```

The tool interface consists of three main components:

### Data Display Panel

Contains the display widgets for visualizing the data. [Learn more](/Data-display-panel/index)

### Data Management Panel

Provides widgets for managing and analyzing data:

- Marker display
- Limit management
- Synthesis tools
- Note-taking widget

[Learn more](/Data-management-panel/index)

### Menu Bar Calculators

A collection of engineering calculators organized by category:

**General Electronics:**
- Voltage dividers
- Equivalent series capacitors
- Parallel resistances
- And more...

**RF Electronics:**
- Free Space Loss
- RF power unit converter
- Reflection coefficient unit converters
- And more

[View all calculators](/Calculators/index)

## See Also

```{toctree}
:maxdepth: 2

Data-display-panel/index
Data-management-panel/index
Calculators/index
```