#include "additionalsettingsnotificationsdialog.h"
#include "ui_additionalsettingsnotificationsdialog.h"
#include <QDebug>


AdditionalSettingsNotificationsDialog::AdditionalSettingsNotificationsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdditionalSettingsNotificationsDialog)
{
    ui->setupUi(this);

    setWindowTitle("Additional Settings & Notifications");
    adjustSize();
}

AdditionalSettingsNotificationsDialog::~AdditionalSettingsNotificationsDialog()
{
    delete ui;
}

//int AdditionalSettingsNotificationsDialog::getOpenTimeHour()
//{
//    return openCloseHoursMinutes[0];
//}

//int AdditionalSettingsNotificationsDialog::getOpenTimeMinute()
//{
//    return openCloseHoursMinutes[1];
//}

//int AdditionalSettingsNotificationsDialog::getCloseTimeHour()
//{
//    return openCloseHoursMinutes[2];
//}

//int AdditionalSettingsNotificationsDialog::getCloseTimeMinute()
//{
//    return openCloseHoursMinutes[3];
//}

//QString AdditionalSettingsNotificationsDialog::getCompanyName()
//{
//    return companyName;
//}

//QString AdditionalSettingsNotificationsDialog::getCompanyAddress()
//{
//    return companyAddress;
//}

//QString AdditionalSettingsNotificationsDialog::getCompanyPhoneNumber()
//{
//    return companyPhoneNumber;
//}

void AdditionalSettingsNotificationsDialog::on_AdditionalSettingsNotificationsDialogAdditionalAdminSettings_clicked()
{
    AdditionalAdminSettingsDialog *adminSettings = new AdditionalAdminSettingsDialog(this);

//    setInfo(adminSettings);

    connect(adminSettings, &AdditionalAdminSettingsDialog::accepted, [=](){
//        captureInfo(adminSettings);
//        qDebug() << "additional settings & notifications layer";
//        qDebug() << openCloseHoursMinutes;
//        qDebug() << companyName;
//        qDebug() << companyAddress;
//        qDebug() << companyPhoneNumber;
    });
    adminSettings->show();
}

void AdditionalSettingsNotificationsDialog::on_AdditionalSettingsNotificationsDialogButtonBox_clicked(QAbstractButton *button)
{
    QDialogButtonBox::StandardButton adminSettingsStdButton = ui->AdditionalSettingsNotificationsDialogButtonBox->standardButton(button);
    if(adminSettingsStdButton == QDialogButtonBox::Ok){
        accept();
    }
    if(adminSettingsStdButton == QDialogButtonBox::Cancel){
        reject();
    }
}


//void AdditionalSettingsNotificationsDialog::captureInfo(AdditionalAdminSettingsDialog *adminSettings)
//{
//    if (!openCloseHoursMinutes.isEmpty()){
//        openCloseHoursMinutes.clear();
//        openCloseHoursMinutes.append(0);
//        openCloseHoursMinutes.append(0);
//        openCloseHoursMinutes.append(0);
//        openCloseHoursMinutes.append(0);
//    } else{
//        openCloseHoursMinutes.append(0);
//        openCloseHoursMinutes.append(0);
//        openCloseHoursMinutes.append(0);
//        openCloseHoursMinutes.append(0);
//    }
//    int hour = adminSettings->getOpenTimeHour();
//    int minute = adminSettings->getOpenTimeMinute();
//    openCloseHoursMinutes[0] = hour;
//    openCloseHoursMinutes[1] = minute;

//    hour = adminSettings->getCloseTimeHour();
//    minute = adminSettings->getCloseTimeMinute();
//    openCloseHoursMinutes[2] = hour;
//    openCloseHoursMinutes[3] = minute;

//    companyName = adminSettings->getCompanyName();
//    companyAddress = adminSettings->getCompanyAddress();
//    companyPhoneNumber = adminSettings->getCompanyPhoneNumber();
//}

//void AdditionalSettingsNotificationsDialog::setInfo(AdditionalAdminSettingsDialog *adminSettings)
//{
//    adminSettings->setOpenTime(openCloseHoursMinutes[0], openCloseHoursMinutes[1]);
//    adminSettings->setCloseTime(openCloseHoursMinutes[2], openCloseHoursMinutes[3]);
//    adminSettings->setCompanyName(companyName);
//    adminSettings->setCompanyAddress(companyAddress);
//    adminSettings->setCompanyPhoneNumber(companyPhoneNumber);
//}

//void AdditionalSettingsNotificationsDialog::setOpenTime(int hour, int minute)
//{
//    openCloseHoursMinutes[0] = hour;
//    openCloseHoursMinutes[1] = minute;
//}

//void AdditionalSettingsNotificationsDialog::setCloseTime(int hour, int minute)
//{
//    openCloseHoursMinutes[2] = hour;
//    openCloseHoursMinutes[3] = minute;
//}

//void AdditionalSettingsNotificationsDialog::setCompanyName(QString cname)
//{
//    companyName = cname;
//}

//void AdditionalSettingsNotificationsDialog::setCompanyAddress(QString caddress)
//{
//    companyAddress = caddress;
//}

//void AdditionalSettingsNotificationsDialog::setCompanyPhoneNumber(QString cnumber)
//{
//    companyPhoneNumber = cnumber;
//}
