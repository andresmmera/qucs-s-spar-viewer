# S-Parameter Viewer & RF Synthesis Tools

## Introduction

This is a comprehensive toolkit for RF and microwave circuit design. It combines S-parameter visualization capabilities with synthesis tools for filters, matching networks, attenuators, and power combiners. Additionally, a number of simple RF engineering calculators are available in the menu bar at the top of the window.

## Features

### Display Features

The tool can display S-parameter data in various formats, including polar plots and Smith charts. Data markers are supported in each display widget. Additionally, the magnitude display supports limit lines.

### Data Capabilities

This tool can read data from Touchstone files and Qucs-S datasets. Users can easily manage files and traces using the data tabs to add and remove data. Sessions can be saved into a file for later use.

### Design Tools

The tool includes built-in design tools such as:

- [RF circuit synthesis tools](/RFCircuitSynthesis/index)
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
- And more...

[View all calculators](/Calculators/index)

## See Also

```{toctree}
:maxdepth: 1

Data-display-panel/index
Data-management-panel/index
Calculators/index
RFCircuitSynthesis/index
```