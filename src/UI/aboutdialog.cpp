#include "aboutdialog.h"

#include <QTextBrowser>
#include <QDialogButtonBox>
#include <QVBoxLayout>

#include "config.h" // PACKAGE_VERSION is defined here

AboutDialog::AboutDialog(QWidget *parent)
    : QDialog(parent),
    m_textBrowser(new QTextBrowser(this)),
    m_buttonBox(new QDialogButtonBox(QDialogButtonBox::Ok, this))
{
    setWindowTitle(tr("About…"));

    m_textBrowser->setOpenExternalLinks(true);
    m_textBrowser->setHtml(buildAboutHtml());

    connect(m_buttonBox, &QDialogButtonBox::accepted,
            this, &QDialog::accept);

    auto *layout = new QVBoxLayout(this);
    layout->addWidget(m_textBrowser);
    layout->addWidget(m_buttonBox);

    resize(500, 400);
    setMinimumSize(400, 300);
}

QString AboutDialog::buildAboutHtml() const
{
    const QString html = R"(
        <h2>Qucs‑S S‑parameter Viewer &amp; RF Circuit Synthesis Tool</h2>
        <p><b>Version </b> )" +
                         QString(PACKAGE_VERSION) + R"(</p>

        <p>&copy; 2026 Andrés Martínez Mera</p>

        <hr/>

        <h3>Useful links</h3>
        <ul>
          <li><a href="https://andresmmera.github.io/qucs-s-spar-viewer/">Online documentation</a></li>
          <li><a href="https://github.com/andresmmera/qucs-s-spar-viewer/releases/">Release page</a></li>
          <li><a href="https://github.com/ra3xdh/qucs_s">Qucs-S Project</a></li>
        </ul>

        <hr/>

        <h3>License</h3>
        <p>
            This program is free software: you can redistribute it and/or modify
            it under the terms of the <a href="https://www.gnu.org/licenses/gpl-3.0.html">
            GNU General Public License</a> as published by the Free Software
            Foundation, either version 3 of the License, or (at your option) any later version.
        </p>

        <p>
            This program is distributed in the hope that it will be useful,
            but <b>WITHOUT ANY WARRANTY</b>; without even the implied warranty of
            <i>merchantability</i> or <i>fitness for a particular purpose</i>.
        </p>

        <p>
            You should have received a copy of the GNU GPL along with this program.
            If not, see <a href="https://www.gnu.org/licenses/">https://www.gnu.org/licenses/</a>.
        </p>

        <hr/>

        <h3>Platform Support</h3>
        <p>
            This software runs best on <b>Linux</b>. It is developed and primarily tested
            using <a href="https://www.tuxedocomputers.com/en/TUXEDO-OS_1.tuxedo">Tuxedo OS</a>.
        </p>
        <p>
            Windows builds are provided via CI and have received basic testing. Some
            issues may occur.
        </p>
        <p>
            It has <b>not been tested on macOS at all</b>.
        </p>

        <p>
            Users are encouraged to support Linux and moving away from proprietary operating systems.
        </p>


        <hr/>

        <h3>Acknowledgments</h3>
          <ul>
            <li>Special thanks to <b>Vadim Kuznetsov</b>, the <a href="https://github.com/ra3xdh/qucs_s">Qucs-S</a> project leader.</li>
            <li><b>Sam Gallagher</b> - PR #1571 fix </li>
          </ul>

        <hr/>

        <h3>Third party code</h3>
        <p>This application uses <a href="https://www.qcustomplot.com/"
                                    style="color:#0066CC;">QCustomPlot</a> –
           a Qt C++ widget for plotting and data visualization.</p>
        <p>QCustomPlot is authored by <b>Emanuel Eichhammer</b> and is
           released under the GPL license.</p>
    )";

    return html;
}
