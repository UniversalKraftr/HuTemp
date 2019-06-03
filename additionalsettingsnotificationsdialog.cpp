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
    setAllDefaults();
}

AdditionalSettingsNotificationsDialog::~AdditionalSettingsNotificationsDialog()
{
    delete ui;
}


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

void AdditionalSettingsNotificationsDialog::setAllDefaults()
{
    ui->AdditionalSettingsNotificationsDialogHighTempThresholdCheckBox->setChecked(true);
    ui->AdditionalSettingsNotificationsDialogHighTempThresholdCheckBox->setEnabled(false);
    ui->AdditionalSettingsNotificationsDialogLowTempThresholdCheckBox->setChecked(true);
    ui->AdditionalSettingsNotificationsDialogLowTempThresholdCheckBox->setEnabled(false);

    ui->AdditionalSettingsNotificationsDialogHighHumThresholdCheckbox->setChecked(true);
    ui->AdditionalSettingsNotificationsDialogHighHumThresholdCheckbox->setEnabled(false);
    ui->AdditionalSettingsNotificationsDialogLowHumThresholdCheckBox->setChecked(true);
    ui->AdditionalSettingsNotificationsDialogLowHumThresholdCheckBox->setEnabled(false);

    ui->AdditionalSettingsNotificationsDialogLowPowerCheckbox->setChecked(true);
    ui->AdditionalSettingsNotificationsDialogLowPowerCheckbox->setEnabled(false);

    ui->AdditionalSettingsNotificationsDialogActiveStatusCheckBox->setChecked(true);
    ui->AdditionalSettingsNotificationsDialogActiveStatusCheckBox->setEnabled(false);

    ui->AdditionalSettingsNotificationsDialogWifiConnectionCheckBox->setChecked(true);
    ui->AdditionalSettingsNotificationsDialogWifiConnectionCheckBox->setEnabled(false);

    ui->AdditionalSettingsNotificationsDialogDisconnectedInternetCheckBox->setChecked(true);
    ui->AdditionalSettingsNotificationsDialogDisconnectedInternetCheckBox->setEnabled(false);

    ui->AdditionalSettingsNotificationsDialogDatabaseConnectionCheckBox->setChecked(true);
    ui->AdditionalSettingsNotificationsDialogDatabaseConnectionCheckBox->setEnabled(false);
}

