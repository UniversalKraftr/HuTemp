#ifndef ADDITIONALADMINSETTINGSDIALOG_H
#define ADDITIONALADMINSETTINGSDIALOG_H

#include <QDialog>
#include <QAbstractButton>

namespace Ui {
class AdditionalAdminSettingsDialog;
}

class AdditionalAdminSettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AdditionalAdminSettingsDialog(QWidget *parent = nullptr);
    ~AdditionalAdminSettingsDialog();

private slots:
    void on_AdditionalAdminSettingsDialogButtonBox_clicked(QAbstractButton *button);

private:
    Ui::AdditionalAdminSettingsDialog *ui;
};

#endif // ADDITIONALADMINSETTINGSDIALOG_H
