#include "devicesdialogbox.h"
#include "ui_devicesdialogbox.h"


DevicesDialogBox::DevicesDialogBox(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DevicesDialogBox)
{
    ui->setupUi(this);

    setWindowTitle("Data Loggers");
    setWindowIcon(QIcon("://icons/logo_O9H_2.ico"));
    adjustSize();
}

DevicesDialogBox::~DevicesDialogBox()
{
    delete ui;
}

QList<bool> DevicesDialogBox::getCheckBoxes()
{
    return checkboxes;
}

void DevicesDialogBox::setCheckBoxes(QList<bool> checkBoxes)
{
    if (!checkboxes.isEmpty()){
        checkboxes.clear();
    }
    checkboxes = checkBoxes;
    ui->DevicesDialogBoxAllDataLoggersCheckBox->setChecked(checkboxes[0]);
    ui->DevicesDialogBoxDataLogger1CheckBox->setChecked(checkboxes[1]);
    ui->DevicesDialogBoxDataLogger2CheckBox->setChecked(checkboxes[2]);
    ui->DevicesDialogBoxDataLogger3CheckBox->setChecked(checkboxes[3]);
    ui->DevicesDialogBoxDataLogger4CheckBox->setChecked(checkboxes[4]);
    ui->DevicesDialogBoxDataLogger5CheckBox->setChecked(checkboxes[5]);
    ui->DevicesDialogBoxDataLogger6CheckBox->setChecked(checkboxes[6]);
    ui->DevicesDialogBoxDataLogger7CheckBox->setChecked(checkboxes[7]);
    ui->DevicesDialogBoxDataLogger8CheckBox->setChecked(checkboxes[8]);
    ui->DevicesDialogBoxDataLogger9CheckBox->setChecked(checkboxes[9]);
    ui->DevicesDialogBoxDataLogger10CheckBox->setChecked(checkboxes[10]);
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


void DevicesDialogBox::on_DevicesDialogBoxAllDataLoggersCheckBox_stateChanged(int arg1)
{
    if (arg1 == 2){
        ui->DevicesDialogBoxDataLogger1CheckBox->setChecked(true);
        ui->DevicesDialogBoxDataLogger2CheckBox->setChecked(true);
        ui->DevicesDialogBoxDataLogger3CheckBox->setChecked(true);
        ui->DevicesDialogBoxDataLogger4CheckBox->setChecked(true);
        ui->DevicesDialogBoxDataLogger5CheckBox->setChecked(true);
        ui->DevicesDialogBoxDataLogger6CheckBox->setChecked(true);
        ui->DevicesDialogBoxDataLogger7CheckBox->setChecked(true);
        ui->DevicesDialogBoxDataLogger8CheckBox->setChecked(true);
        ui->DevicesDialogBoxDataLogger9CheckBox->setChecked(true);
        ui->DevicesDialogBoxDataLogger10CheckBox->setChecked(true);
    }
    checkboxes[0] = ui->DevicesDialogBoxAllDataLoggersCheckBox->isChecked();
}

void DevicesDialogBox::on_DevicesDialogBoxDataLogger1CheckBox_stateChanged(int arg1)
{
    if (arg1 == 0){
        ui->DevicesDialogBoxAllDataLoggersCheckBox->setChecked(false);
    }
    checkboxes[1] = ui->DevicesDialogBoxDataLogger1CheckBox->isChecked();
    allCheckBoxesClicked();
}

void DevicesDialogBox::on_DevicesDialogBoxDataLogger2CheckBox_stateChanged(int arg1)
{
    if (arg1 == 0){
        ui->DevicesDialogBoxAllDataLoggersCheckBox->setChecked(false);
    }
    checkboxes[2] = ui->DevicesDialogBoxDataLogger2CheckBox->isChecked();
    allCheckBoxesClicked();
}

void DevicesDialogBox::on_DevicesDialogBoxDataLogger3CheckBox_stateChanged(int arg1)
{
    if (arg1 == 0){
        ui->DevicesDialogBoxAllDataLoggersCheckBox->setChecked(false);
    }
    checkboxes[3] = ui->DevicesDialogBoxDataLogger3CheckBox->isChecked();
    allCheckBoxesClicked();
}

void DevicesDialogBox::on_DevicesDialogBoxDataLogger4CheckBox_stateChanged(int arg1)
{
    if (arg1 == 0){
        ui->DevicesDialogBoxAllDataLoggersCheckBox->setChecked(false);
    }
    checkboxes[4] = ui->DevicesDialogBoxDataLogger4CheckBox->isChecked();
    allCheckBoxesClicked();
}

void DevicesDialogBox::on_DevicesDialogBoxDataLogger5CheckBox_stateChanged(int arg1)
{
    if (arg1 == 0){
        ui->DevicesDialogBoxAllDataLoggersCheckBox->setChecked(false);
    }
    checkboxes[5] = ui->DevicesDialogBoxDataLogger5CheckBox->isChecked();
    allCheckBoxesClicked();
}

void DevicesDialogBox::on_DevicesDialogBoxDataLogger6CheckBox_stateChanged(int arg1)
{
    if (arg1 == 0){
        ui->DevicesDialogBoxAllDataLoggersCheckBox->setChecked(false);
    }
    checkboxes[6] = ui->DevicesDialogBoxDataLogger6CheckBox->isChecked();
    allCheckBoxesClicked();
}

void DevicesDialogBox::on_DevicesDialogBoxDataLogger7CheckBox_stateChanged(int arg1)
{
    if (arg1 == 0){
        ui->DevicesDialogBoxAllDataLoggersCheckBox->setChecked(false);
    }
    checkboxes[7] = ui->DevicesDialogBoxDataLogger7CheckBox->isChecked();
    allCheckBoxesClicked();
}

void DevicesDialogBox::on_DevicesDialogBoxDataLogger8CheckBox_stateChanged(int arg1)
{
    if (arg1 == 0){
        ui->DevicesDialogBoxAllDataLoggersCheckBox->setChecked(false);
    }
    checkboxes[8] = ui->DevicesDialogBoxDataLogger8CheckBox->isChecked();
    allCheckBoxesClicked();
}

void DevicesDialogBox::on_DevicesDialogBoxDataLogger9CheckBox_stateChanged(int arg1)
{
    if (arg1 == 0){
        ui->DevicesDialogBoxAllDataLoggersCheckBox->setChecked(false);
    }
    checkboxes[9] = ui->DevicesDialogBoxDataLogger9CheckBox->isChecked();
    allCheckBoxesClicked();
}

void DevicesDialogBox::on_DevicesDialogBoxDataLogger10CheckBox_stateChanged(int arg1)
{
    if (arg1 == 0){
        ui->DevicesDialogBoxAllDataLoggersCheckBox->setChecked(false);
    }
    checkboxes[10] = ui->DevicesDialogBoxDataLogger10CheckBox->isChecked();
    allCheckBoxesClicked();
}

void DevicesDialogBox::allCheckBoxesClicked()
{
    if (ui->DevicesDialogBoxDataLogger1CheckBox->isChecked() &&
            ui->DevicesDialogBoxDataLogger2CheckBox->isChecked() &&
            ui->DevicesDialogBoxDataLogger3CheckBox->isChecked() &&
            ui->DevicesDialogBoxDataLogger4CheckBox->isChecked() &&
            ui->DevicesDialogBoxDataLogger5CheckBox->isChecked() &&
            ui->DevicesDialogBoxDataLogger6CheckBox->isChecked() &&
            ui->DevicesDialogBoxDataLogger7CheckBox->isChecked() &&
            ui->DevicesDialogBoxDataLogger8CheckBox->isChecked() &&
            ui->DevicesDialogBoxDataLogger9CheckBox->isChecked() &&
            ui->DevicesDialogBoxDataLogger10CheckBox->isChecked()){
        ui->DevicesDialogBoxAllDataLoggersCheckBox->setChecked(true);
    }
}
