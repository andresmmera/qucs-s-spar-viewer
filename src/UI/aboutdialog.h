#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QDialog>

class QTextBrowser;
class QDialogButtonBox;

class AboutDialog : public QDialog {
    Q_OBJECT
public:
    explicit AboutDialog(QWidget *parent = nullptr);

private:
    QString buildAboutHtml() const;

    QTextBrowser    *m_textBrowser;
    QDialogButtonBox *m_buttonBox;
};

#endif // ABOUTDIALOG_H
