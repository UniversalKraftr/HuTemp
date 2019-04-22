#include "additionaladminsettingsdialog.h"
#include "ui_additionaladminsettingsdialog.h"

AdditionalAdminSettingsDialog::AdditionalAdminSettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdditionalAdminSettingsDialog)
{
    ui->setupUi(this);
}

AdditionalAdminSettingsDialog::~AdditionalAdminSettingsDialog()
{
    delete ui;
}

void AdditionalAdminSettingsDialog::on_AdditionalAdminSettingsDialogButtonBox_clicked(QAbstractButton *button)
{
    QDialogButtonBox::StandardButton adminSettingsStdButton = ui->AdditionalAdminSettingsDialogButtonBox->standardButton(button);

    if(adminSettingsStdButton == QDialogButtonBox::Save){
        accept();
    }
    if(adminSettingsStdButton == QDialogButtonBox::Cancel){
        reject();
    }
}
