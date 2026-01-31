/// @file SecondaryImageDocs.cpp
/// @brief Documentation for the secondary image frequency calculator
/// @author Andrés Martínez Mera - andresmmera@protonmail.com
/// @date Jan 31, 2026
/// @copyright Copyright (C) 2026 Andrés Martínez Mera
/// @license GPL-3.0-or-later


#include "SecondaryImageCalculatorDialog.h"
#include <QTextBrowser>

void SecondaryImageCalculatorDialog::showDocumentation()
{
    QDialog* docDialog = new QDialog(this);
    docDialog->setWindowTitle("Secondary Image Calculator - Documentation");
    docDialog->setMinimumWidth(600);
    docDialog->setMinimumHeight(400);

    QVBoxLayout* layout = new QVBoxLayout(docDialog);

    QTextBrowser* browser = new QTextBrowser();
    browser->setOpenExternalLinks(true);

    QString htmlContent = R"(
<!DOCTYPE html>
<html>
<head>
    <style>
        body {
            font-family: Arial, sans-serif;
            margin: 20px;
            line-height: 1.6;
        }
        h1 {
            color: #2c3e50;
            border-bottom: 2px solid #3498db;
            padding-bottom: 10px;
        }
        h2 {
            color: #34495e;
            margin-top: 25px;
        }
        h3 {
            color: #546e7a;
            margin-top: 15px;
            margin-bottom: 10px;
        }
        .equation {
            background-color: #f8f9fa;
            border-left: 4px solid #3498db;
            padding: 15px;
            margin: 15px 0;
            font-family: 'Courier New', monospace;
        }
        .note {
            background-color: #fff3cd;
            border-left: 4px solid #ffc107;
            padding: 10px;
            margin: 15px 0;
        }
        table {
            border-collapse: collapse;
            width: 100%;
            margin: 15px 0;
        }
        th, td {
            border: 1px solid #ddd;
            padding: 8px;
            text-align: left;
        }
        th {
            background-color: #3498db;
            color: white;
        }
        tr:nth-child(even) {
            background-color: #f2f2f2;
        }
    </style>
</head>
<body>
    <h1>Secondary Image Calculator</h1>

    <h2>Overview</h2>
    <p>This calculator determines the local oscillator (LO) frequencies and image frequencies
    for both stages of a dual-conversion superheterodyne receiver using <strong>low-side injection</strong>.</p>

    <p>In a downconversion mixer, two frequencies lie in the same intermediate frequency:</p>
    <ul>
        <li><strong>The intended intermediate frequency:</strong> f<sub>IF</sub> = f<sub>RF</sub> - f<sub>LO</sub></li>
        <li><strong>The image frequency</strong> (from the negative side of the spectrum): -f<sub>IM</sub> + f<sub>LO</sub> = f<sub>IF</sub></li>
    </ul>

    <div class="note">
        The problem of the second image frequency arises in superheterodyne receivers with two
        downconversion steps since the second downconverter also has an image frequency which needs to be filtered
        at the RF frontend.
    </div>

    <h2>Dual-Conversion Receiver Architecture</h2>
    <p>A dual-conversion receiver performs frequency conversion in two stages:</p>
    <ol>
        <li><strong>First Stage:</strong> RF signal → 1st IF</li>
        <li><strong>Second Stage:</strong> 1st IF → 2nd IF</li>
    </ol>

    <h2>General Formula (Low-Side Injection)</h2>
    <p>In mixers with low-side injection, the following equation applies:</p>

    <div class="equation">
        f<sub>IF</sub> = f<sub>RF</sub> - f<sub>LO</sub>
    </div>

    <h2>First Conversion Stage (RF → 1st IF)</h2>

    <div class="equation">
        <strong>LO1 Frequency:</strong><br>
        f<sub>LO1</sub> = f<sub>RF</sub> - f<sub>IF1</sub>
    </div>

    <p>The image frequency comes from the negative side of the spectrum and falls in the IF band:</p>

    <div class="equation">
        f<sub>IF1</sub> = -f<sub>IM1</sub> + f<sub>LO1</sub>
    </div>

    <p>Therefore:</p>

    <div class="equation">
        <strong>First Image Frequency:</strong><br>
        f<sub>IM1</sub> = f<sub>LO1</sub> - f<sub>IF1</sub>
    </div>

    <h2>Second Conversion Stage (1st IF → 2nd IF)</h2>

    <div class="equation">
        <strong>LO2 Frequency:</strong><br>
        f<sub>LO2</sub> = f<sub>IF1</sub> - f<sub>IF2</sub>
    </div>

    <p>Similarly, the second image frequency is:</p>

    <div class="equation">
        <strong>Second Image Frequency:</strong><br>
        f<sub>IM2</sub> = f<sub>LO2</sub> - f<sub>IF2</sub>
    </div>

    <h2>Example Calculation</h2>
    <table>
        <tr>
            <th>Parameter</th>
            <th>Value</th>
        </tr>
        <tr>
            <td>RF Frequency</td>
            <td>800 MHz</td>
        </tr>
        <tr>
            <td>1st IF Frequency</td>
            <td>200 MHz</td>
        </tr>
        <tr>
            <td>2nd IF Frequency</td>
            <td>10 MHz</td>
        </tr>
    </table>

    <p><strong>First Stage Results:</strong></p>
    <ul>
        <li>f<sub>LO1</sub> = 800 - 200 = <strong>600 MHz</strong></li>
        <li>f<sub>IM1</sub> = 600 - 200 = <strong>400 MHz</strong></li>
    </ul>

    <p><strong>Second Stage Results:</strong></p>
    <ul>
        <li>f<sub>LO2</sub> = 200 - 10 = <strong>190 MHz</strong></li>
        <li>f<sub>IM2</sub> = 190 - 10 = <strong>180 MHz</strong></li>
    </ul>

    <h2>Why Not Just One IF?</h2>
    <p>Choosing an IF frequency is a trade-off between image rejection and selectivity:</p>

    <h3>High IF</h3>
    <table>
        <tr>
            <th>Pros</th>
            <th>Cons</th>
        </tr>
        <tr>
            <td>Large separation between desired signal and image: The image can be rejected with a simple filter</td>
            <td>Narrow, high-Q filters ar still needed at the IF, and they are difficult to build at high frequencies</td>
        </tr>
    </table>

    <h3>Low IF</h3>
    <table>
        <tr>
            <th>Pros</th>
            <th>Cons</th>
        </tr>
        <tr>
            <td>Easier to built high rejection filters</td>
            <td>Image frequency is close to the wanted signal, so image rejection at RF becomes difficult</td>
        </tr>
    </table>

    <div class="note">
        <strong>Solution:</strong> Dual conversion uses a <strong>high first IF</strong> and
        then a <strong>low second IF</strong>
    </div>

    <h2>Role of the Second IF</h2>
    <p>Once the signal is at the first IF:</p>
    <ul>
        <li>The <strong>first IF filter</strong> is relatively wide and mainly cleans up mixer products and distant interferers</li>
        <li>The <strong>second mixer</strong> converts this first-IF signal down to a much lower second IF</li>
    </ul>

    <p>At the second IF, high selectivity filters are needed, but they are cheaper to build than in higher frequencies.</p>
</body>
</html>
)";

    browser->setHtml(htmlContent);
    layout->addWidget(browser);

    QPushButton* closeButton = new QPushButton("Close");
    connect(closeButton, &QPushButton::clicked, docDialog, &QDialog::accept);

    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->addWidget(closeButton);
    layout->addLayout(buttonLayout);

    docDialog->exec();
    delete docDialog;
}
