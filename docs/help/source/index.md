# S-Parameter Viewer & RF Synthesis Tools

## Introduction

This is a comprehensive toolkit for RF and microwave circuit design. It combines S-parameter visualization capabilities with synthesis tools for filters, matching networks, attenuators, and power combiners. Additionally, a number of simple RF engineering calculators are available in the menu bar at the top of the window.

## Features

### Data Display

The tool can display S-parameter data in various formats, including polar plots and Smith charts. Data markers are supported in each display widget. Additionally, the magnitude display supports limit lines.

### Data Management

This tool can read data from Touchstone files and Qucs-S datasets. Users can easily manage files and traces using the data tabs to add and remove data. Sessions can be saved into a file for later use.

### Design Tools

The tool includes built-in design tools such as:

- [RF Circuit Synthesis Tools](/RFCircuitSynthesis/index)
- [RF Engineering Calculators](/Calculators/index)

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

<ul style="margin-top: 0; line-height: 0.5;">
  <li>Marker display</li>
  <li>Limit management</li>
  <li>Synthesis tools</li>
  <li>Note-taking widget</li>
</ul>

[Learn more](/Data-management-panel/index)

### Menu Bar Calculators

A collection of engineering calculators organized by category:

**General Electronics:**

<ul style="margin-top: 0; line-height: 0.5;">
  <li>Voltage dividers</li>
  <li>Equivalent series capacitors</li>
  <li>Parallel resistances</li>
  <li>and more...</li>
</ul>


**RF Electronics:**
<ul style="margin-top: 0; line-height: 0.5;">
    <li>Free Space Loss</li>
    <li> RF power unit converter</li>
    <li> Reflection coefficient unit converters</li>
    <li>And more...</li>
</ul>

[View all calculators](/Calculators/index)

## See Also

```{toctree}
:maxdepth: 1

Data-display-panel/index
Data-management-panel/index
Calculators/index
RFCircuitSynthesis/index
```
