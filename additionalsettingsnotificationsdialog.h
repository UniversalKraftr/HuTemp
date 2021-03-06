#ifndef ADDITIONALSETTINGSNOTIFICATIONSDIALOG_H
#define ADDITIONALSETTINGSNOTIFICATIONSDIALOG_H

#include <QDialog>
#include <QAbstractButton>
#include <QTime>
#include "additionaladminsettingsdialog.h"

namespace Ui {
class AdditionalSettingsNotificationsDialog;
}

class AdditionalSettingsNotificationsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AdditionalSettingsNotificationsDialog(QWidget *parent = nullptr);
    ~AdditionalSettingsNotificationsDialog();

private slots:
    void on_AdditionalSettingsNotificationsDialogAdditionalAdminSettings_clicked();

    void on_AdditionalSettingsNotificationsDialogButtonBox_clicked(QAbstractButton *button);

private:
    Ui::AdditionalSettingsNotificationsDialog *ui;
    void setAllDefaults();
};

#endif // ADDITIONALSETTINGSNOTIFICATIONSDIALOG_H
