/// @file ImageFrequencyDocs.cpp
/// @brief Documentation for the secondary image frequency calculator
/// @author Andrés Martínez Mera - andresmmera@protonmail.com
/// @date Jan 31, 2026
/// @copyright Copyright (C) 2026 Andrés Martínez Mera
/// @license GPL-3.0-or-later


#include "ImageFrequencyCalculatorDialog.h"
#include <QTextBrowser>

void ImageFrequencyCalculatorDialog::showDocumentation()
{
    QDialog* docDialog = new QDialog(this);
    docDialog->setWindowTitle("Image Frequency Calculator - Documentation");
    docDialog->setMinimumWidth(700);
    docDialog->setMinimumHeight(500);

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
    <h1>Image Frequency Calculator</h1>

    <p>In a superheterodyne receiver, the <strong>image frequency</strong> is an unwanted frequency that,
    when mixed with the local oscillator (LO), produces the same intermediate frequency (IF) as the
    desired RF signal.</p>

    <div class="note">
        <strong>Problem:</strong> Consequently, if it is not properly filtered out <em>before</em> the mixer,
        any signal present in the image band will appear at the IF output along with the wanted signal, causing interference.
    </div>

    <h2>How Mixers Work</h2>
    <p>A mixer produces sum and difference frequencies:</p>
    <div class="equation">
        f<sub>out</sub> = |f<sub>RF</sub> ± f<sub>LO</sub>|
    </div>

    <p>For downconversion purposes:</p>
    <div class="equation">
        f<sub>IF</sub> = |f<sub>RF</sub> - f<sub>LO</sub>|
    </div>

    <h2>Injection Modes</h2>

    <h3>Low-Side Injection</h3>
    <p>The LO frequency is <strong>below</strong> the RF frequency:</p>
    <div class="equation">
        f<sub>IF</sub> = f<sub>RF</sub> - f<sub>LO</sub>
    </div>

    <p>Then:</p>

    <div class="equation">
        f<sub>LO</sub> = f<sub>RF</sub> - f<sub>IF</sub>
    </div>

    <p>The image frequency is taken from the negative side of the spectrum:</p>
    <div class="equation">
        f<sub>IF</sub> = -f<sub>IM</sub> + f<sub>LO</sub>
    </div>
    <div class="equation">
        <strong>f<sub>IM</sub> = f<sub>LO</sub> - f<sub>IF</sub> = f<sub>RF</sub> - 2×f<sub>IF</sub> </strong>
    </div>

    <h3>High-Side Injection</h3>
    <p>The LO frequency is <strong>above</strong> the RF frequency:</p>

    <div class="equation">
        f<sub>IF</sub> = f<sub>LO</sub> - f<sub>RF</sub>
    </div>

    <p>Then:</p>

    <div class="equation">
        f<sub>LO</sub> = f<sub>RF</sub> + f<sub>IF</sub>
    </div>

    <p>The image frequency in high-side injection comes from the positive side of the spectrum and fall in the IF frequency but in the negative side of the spectrum:</p>

    <div class="equation">
        -f<sub>IF</sub> = f<sub>IM</sub> - f<sub>LO</sub>
    </div>

    <div class="equation">
        <strong>f<sub>IM</sub> = f<sub>RF</sub> + 2×f<sub>IF</sub></strong>
    </div>

    <p><em>Why?</em> Because f<sub>LO</sub> - f<sub>IM</sub> = f<sub>IF</sub></p>

    <h2>Example Calculation</h2>
    <table>
        <tr>
            <th>Parameter</th>
            <th>Value</th>
        </tr>
        <tr>
            <td>RF Frequency</td>
            <td>1000 MHz</td>
        </tr>
        <tr>
            <td>IF Frequency</td>
            <td>200 MHz</td>
        </tr>
    </table>

    <h3>Low-Side Injection</h3>
    <ul>
        <li>f<sub>LO</sub> = 1000 - 200 = <strong>800 MHz</strong></li>
        <li>f<sub>IM</sub> = 1000 - 2×200 = <strong>600 MHz</strong></li>
    </ul>
    <p>Verification: 800 - 600 = 200 MHz ✓</p>

    <h3>High-Side Injection</h3>
    <ul>
        <li>f<sub>LO</sub> = 1000 + 200 = <strong>1200 MHz</strong></li>
        <li>f<sub>IM</sub> = 1000 + 2×200 = <strong>1400 MHz</strong></li>
    </ul>
    <p>Verification: 1400 - 1200 = 200 MHz ✓</p>

    <h2>Choosing the IF Frequency: The Trade-Off</h2>

    <h3>High IF</h3>
    <table>
        <tr>
            <th>Pros</th>
            <th>Cons</th>
        </tr>
        <tr>
            <td>
                • Large separation (2×f<sub>IF</sub>) between signal and image<br>
                • RF preselector can easily reject the image<br>
                • Simpler, cheaper RF filters required
            </td>
            <td>
                • Harder to build very narrow, high-Q channel filters at high frequency<br>
                • Poor adjacent-channel selectivity<br>
                • More expensive components
            </td>
        </tr>
    </table>

    <h3>Low IF</h3>
    <table>
        <tr>
            <th>Pros</th>
            <th>Cons</th>
        </tr>
        <tr>
            <td>
                • Easy to build very narrow, high-quality filters<br>
                • Excellent adjacent-channel selectivity<br>
                • Better performance and lower cost
            </td>
            <td>
                • Small separation between signal and image<br>
                • Image frequency is close to wanted signal<br>
                • May require sharp, expensive RF preselection
            </td>
        </tr>
    </table>
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
