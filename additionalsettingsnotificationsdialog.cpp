#include "additionalsettingsnotificationsdialog.h"
#include "ui_additionalsettingsnotificationsdialog.h"
#include "additionaladminsettingsdialog.h"

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

void AdditionalSettingsNotificationsDialog::on_AdditionalSettingsNotificationsDialogAdditionalAdminSettings_clicked()
{
    AdditionalAdminSettingsDialog *adminSettings = new AdditionalAdminSettingsDialog(this);
    adminSettings->exec();
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
