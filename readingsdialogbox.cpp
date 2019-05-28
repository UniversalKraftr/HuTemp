#include "readingsdialogbox.h"
#include "ui_readingsdialogbox.h"

ReadingsDialogBox::ReadingsDialogBox(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReadingsDialogBox)
{
    ui->setupUi(this);

    setWindowTitle("Data Readings");
    adjustSize();
}

ReadingsDialogBox::~ReadingsDialogBox()
{
    delete ui;
}

QList<bool> ReadingsDialogBox::getCheckBoxes()
{
    return checkboxes;
}

void ReadingsDialogBox::setCheckBoxes(QList<bool> checkBoxes)
{
    if (!checkboxes.isEmpty()){
        checkboxes.clear();
    }
    checkboxes = checkBoxes;
    ui->ReadingsDialogBoxAllDataCheckBox->setChecked(checkboxes[0]);
    ui->ReadingsDialogBoxHumidityCheckBox->setChecked(checkboxes[1]);
    ui->ReadingsDialogBoxTemperatureCheckBox->setChecked(checkboxes[2]);
}

void ReadingsDialogBox::on_ReadingsDialogBoxButtons_clicked(QAbstractButton *button)
{
    QDialogButtonBox::StandardButton readingsStdButton = ui->ReadingsDialogBoxButtons->standardButton(button);

    if(readingsStdButton == QDialogButtonBox::Reset){
        ui->ReadingsDialogBoxAllDataCheckBox->setChecked(true);
    }
    if(readingsStdButton == QDialogButtonBox::Ok){
        accept();
    }
    if(readingsStdButton == QDialogButtonBox::Cancel){
        reject();
    }
}

void ReadingsDialogBox::on_ReadingsDialogBoxAllDataCheckBox_stateChanged(int arg1)
{
    if (arg1 == 2){
        ui->ReadingsDialogBoxHumidityCheckBox->setChecked(true);
        ui->ReadingsDialogBoxTemperatureCheckBox->setChecked(true);
    }
    checkboxes[0] = ui->ReadingsDialogBoxAllDataCheckBox->isChecked();
}

void ReadingsDialogBox::on_ReadingsDialogBoxTemperatureCheckBox_stateChanged(int arg1)
{
    if (arg1 == 0){
        ui->ReadingsDialogBoxAllDataCheckBox->setChecked(false);
    }
    checkboxes[1] = ui->ReadingsDialogBoxHumidityCheckBox->isChecked();
}

void ReadingsDialogBox::on_ReadingsDialogBoxHumidityCheckBox_stateChanged(int arg1)
{
    if (arg1 == 0){
        ui->ReadingsDialogBoxAllDataCheckBox->setChecked(false);
    }
    checkboxes[2] = ui->ReadingsDialogBoxTemperatureCheckBox->isChecked();
}
