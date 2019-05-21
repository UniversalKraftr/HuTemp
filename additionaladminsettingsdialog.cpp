#include "additionaladminsettingsdialog.h"
#include "ui_additionaladminsettingsdialog.h"

AdditionalAdminSettingsDialog::AdditionalAdminSettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdditionalAdminSettingsDialog)
{
    ui->setupUi(this);

    setWindowTitle("Additional Administrator Settings");
    adjustSize();
}

AdditionalAdminSettingsDialog::~AdditionalAdminSettingsDialog()
{
    delete ui;
}

int AdditionalAdminSettingsDialog::getOpenTimeMinute()
{
    return ui->AdditionalAdminSettingsDialogOpenTimeTimeEdit->time().minute();
}

int AdditionalAdminSettingsDialog::getOpenTimeHour()
{
    return ui->AdditionalAdminSettingsDialogOpenTimeTimeEdit->time().hour();
}

int AdditionalAdminSettingsDialog::getCloseTimeHour()
{
    return ui->AdditionalAdminSettingsDialogClosingTimeTimeEdit->time().hour();
}

int AdditionalAdminSettingsDialog::getCloseTimeMinute()
{
    return ui->AdditionalAdminSettingsDialogClosingTimeTimeEdit->time().minute();;
}

QString AdditionalAdminSettingsDialog::getCompanyName()
{
    return ui->AdditionalAdminSettingsDialogCompanyNameLineEdit->text();
}

QString AdditionalAdminSettingsDialog::getCompanyAddress()
{
    QString companyAddress = ui->AdditionalAdminSettingsDialogCompanyAddressLine1LineEdit->text() + QString("\n") +
            ui->AdditionalAdminSettingsDialogCompanyAddressLine2LineEdit->text();
    return companyAddress;
}

QString AdditionalAdminSettingsDialog::getCompanyPhoneNumber()
{
    return ui->AdditionalAdminSettingsDialogCompanyPhoneNumberLineEdit->text();
}

void AdditionalAdminSettingsDialog::on_AdditionalAdminSettingsDialogButtonBox_clicked(QAbstractButton *button)
{
    QDialogButtonBox::StandardButton adminSettingsStdButton = ui->AdditionalAdminSettingsDialogButtonBox->standardButton(button);

    if(adminSettingsStdButton == QDialogButtonBox::Ok){
        accept();
    }
    if(adminSettingsStdButton == QDialogButtonBox::Cancel){
        reject();
    }
}

void AdditionalAdminSettingsDialog::setOpenTime(int hour, int minute)
{
    ui->AdditionalAdminSettingsDialogOpenTimeTimeEdit->setTime(QTime(hour, minute));
}

void AdditionalAdminSettingsDialog::setCloseTime(int hour, int minute)
{
    ui->AdditionalAdminSettingsDialogClosingTimeTimeEdit->setTime(QTime(hour, minute));
}

void AdditionalAdminSettingsDialog::setCompanyName(QString cname)
{
    ui->AdditionalAdminSettingsDialogCompanyNameLineEdit->setText(cname);
}

void AdditionalAdminSettingsDialog::setCompanyAddress(QString caddress)
{
    QString line1 = caddress.split('\n').front();
    QString line2 = caddress.split('\n').back();
    ui->AdditionalAdminSettingsDialogCompanyAddressLine1LineEdit->setText(line1);
    ui->AdditionalAdminSettingsDialogCompanyAddressLine2LineEdit->setText(line2);
}

void AdditionalAdminSettingsDialog::setCompanyPhoneNumber(QString cnumber)
{
    ui->AdditionalAdminSettingsDialogCompanyPhoneNumberLineEdit->setText(cnumber);
}
