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

    int getOpenTimeHour();
    int getOpenTimeMinute();
    int getCloseTimeHour();
    int getCloseTimeMinute();
    QString getCompanyName();
    QString getCompanyAddress();
    QString getCompanyPhoneNumber();

    void setOpenTime(int hour, int minute);
    void setCloseTime(int hour, int minute);
    void setCompanyName(QString cname);
    void setCompanyAddress(QString caddress);
    void setCompanyPhoneNumber(QString cnumber);

private slots:
    void on_AdditionalSettingsNotificationsDialogAdditionalAdminSettings_clicked();

    void on_AdditionalSettingsNotificationsDialogButtonBox_clicked(QAbstractButton *button);

private:
    Ui::AdditionalSettingsNotificationsDialog *ui;
    QList<int> openCloseHoursMinutes {0,0,0,0};
    QString companyName;
    QString companyAddress;
    QString companyPhoneNumber;

    void captureInfo(AdditionalAdminSettingsDialog *adminSettings);
    void setInfo(AdditionalAdminSettingsDialog *adminSettings);
};

#endif // ADDITIONALSETTINGSNOTIFICATIONSDIALOG_H
