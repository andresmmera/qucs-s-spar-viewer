/// @file CustomDoubleSpinBox.h
/// @brief Custom QDoubleSpinBox. It includes a context menu (right-click) for setting the minimum, maximum and step values (definition)
/// @author Andrés Martínez Mera - andresmmera@protonmail.com
/// @date Jan 24, 2026
/// @copyright Copyright (C) 2026 Andrés Martínez Mera
/// @license GPL-3.0-or-later

#ifndef CUSTOMDOUBLESPINBOX_H
#define CUSTOMDOUBLESPINBOX_H

#include <QDoubleSpinBox>
#include <QMenu>
#include <QDialog>
#include <QFormLayout>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QLabel>
#include <QContextMenuEvent>

/// @class CustomDoubleSpinBox
/// @brief A QDoubleSpinBox subclass that provides a context menu for configuring range and step
///
/// This widget extends QDoubleSpinBox by adding a right-click context menu that allows users
/// to dynamically adjust the minimum value, maximum value, and single step increment at runtime.
/// This is useful for applications where spinbox parameters need to be adjustable without
/// recompiling or accessing separate settings dialogs.
class CustomDoubleSpinBox : public QDoubleSpinBox
{
    Q_OBJECT

public:

    /// @brief Constructs a CustomDoubleSpinBox
    /// @param parent The parent widget (optional)
    explicit CustomDoubleSpinBox(QWidget *parent = nullptr) {}

protected:
    /// @brief Handles context menu events (right-click)
    /// @param event The context menu event
    ///
    /// Overrides the default context menu to provide configuration options
    /// for minimum, maximum, and step values.
    void contextMenuEvent(QContextMenuEvent *event) override;

private slots:
    /// @brief Opens the configuration dialog
    ///
    /// Displays a modal dialog allowing the user to modify the spinbox's
    /// minimum value, maximum value, and single step increment. Changes
    /// are validated and applied only if the user accepts the dialog.
    void openConfigDialog();
};

#endif // CUSTOMDOUBLESPINBOX_H
