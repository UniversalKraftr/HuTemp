#include "devicesdialogbox.h"
#include "ui_devicesdialogbox.h"


DevicesDialogBox::DevicesDialogBox(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DevicesDialogBox)
{
    ui->setupUi(this);

    setWindowTitle("Data Loggers");
    adjustSize();
}

DevicesDialogBox::~DevicesDialogBox()
{
    delete ui;
}

QList<bool> DevicesDialogBox::getCheckBoxes()
{
    checkboxes.append(ui->DevicesDialogBoxAllDataLoggersCheckBox->isChecked());
    checkboxes.append(ui->DevicesDialogBoxDataLogger1CheckBox->isChecked());
    checkboxes.append(ui->DevicesDialogBoxDataLogger2CheckBox->isChecked());
    checkboxes.append(ui->DevicesDialogBoxDataLogger3CheckBox->isChecked());
    checkboxes.append(ui->DevicesDialogBoxDataLogger4CheckBox->isChecked());
    checkboxes.append(ui->DevicesDialogBoxDataLogger5CheckBox->isChecked());
    checkboxes.append(ui->DevicesDialogBoxDataLogger6CheckBox->isChecked());
    checkboxes.append(ui->DevicesDialogBoxDataLogger7CheckBox->isChecked());
    checkboxes.append(ui->DevicesDialogBoxDataLogger8CheckBox->isChecked());
    return checkboxes;
}

void DevicesDialogBox::setCheckBoxes(QList<bool> checkBoxes)
{
    checkboxes = checkBoxes;
}


void DevicesDialogBox::on_DevicesDialogBoxButtons_clicked(QAbstractButton *button)
{
    QDialogButtonBox::StandardButton devicesStdButton = ui->DevicesDialogBoxButtons->standardButton(button);

    if(devicesStdButton == QDialogButtonBox::Reset){
        ui->DevicesDialogBoxAllDataLoggersCheckBox->setChecked(true);
    }
    if(devicesStdButton == QDialogButtonBox::Ok){
        accept();
    }
    if(devicesStdButton == QDialogButtonBox::Cancel){
        reject();
    }
}

void DevicesDialogBox::on_DevicesDialogBoxAllDataLoggersCheckBox_toggled(bool checked)
{
    if(checked == true){
        ui->DevicesDialogBoxDataLogger1CheckBox->setChecked(true);
        ui->DevicesDialogBoxDataLogger2CheckBox->setChecked(true);
        ui->DevicesDialogBoxDataLogger3CheckBox->setChecked(true);
        ui->DevicesDialogBoxDataLogger4CheckBox->setChecked(true);
        ui->DevicesDialogBoxDataLogger5CheckBox->setChecked(true);
        ui->DevicesDialogBoxDataLogger6CheckBox->setChecked(true);
        ui->DevicesDialogBoxDataLogger7CheckBox->setChecked(true);
        ui->DevicesDialogBoxDataLogger8CheckBox->setChecked(true);
    }
    if(checked == false){
        ui->DevicesDialogBoxDataLogger1CheckBox->setChecked(false);
        ui->DevicesDialogBoxDataLogger2CheckBox->setChecked(false);
        ui->DevicesDialogBoxDataLogger3CheckBox->setChecked(false);
        ui->DevicesDialogBoxDataLogger4CheckBox->setChecked(false);
        ui->DevicesDialogBoxDataLogger5CheckBox->setChecked(false);
        ui->DevicesDialogBoxDataLogger6CheckBox->setChecked(false);
        ui->DevicesDialogBoxDataLogger7CheckBox->setChecked(false);
        ui->DevicesDialogBoxDataLogger8CheckBox->setChecked(false);
    }
}
