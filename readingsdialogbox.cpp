#include "readingsdialogbox.h"
#include "ui_readingsdialogbox.h"

ReadingsDialogBox::ReadingsDialogBox(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReadingsDialogBox)
{
    ui->setupUi(this);

    setWindowTitle("Data Readings");
    setWindowIcon(QIcon("://icons/logo_O9H_2.ico"));
    adjustSize();
}

ReadingsDialogBox::~ReadingsDialogBox()
{
    delete ui;
}

QList<int> ReadingsDialogBox::getCheckBoxes()
{
    return checkboxes;
}

void ReadingsDialogBox::setCheckBoxes(QList<int> checkBoxes)
{
    if (!checkboxes.isEmpty()){
        checkboxes.clear();
    }
    checkboxes = checkBoxes;
    if (checkboxes[0] == 1){
        ui->ReadingsDialogBoxAllDataCheckBox->setChecked(true);
    } else if (checkboxes[0] == 0){
        ui->ReadingsDialogBoxAllDataCheckBox->setChecked(false);
    }
    if (checkboxes[1] == 1){
        ui->ReadingsDialogBoxTemperatureCheckBox->setChecked(true);
    } else if (checkboxes[1] == 0){
        ui->ReadingsDialogBoxTemperatureCheckBox->setChecked(false);
    }
    if (checkboxes[2] == 1){
        ui->ReadingsDialogBoxHumidityCheckBox->setChecked(true);
    } else if (checkboxes[2] == 0){
        ui->ReadingsDialogBoxHumidityCheckBox->setChecked(false);
    }


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
        checkboxes[0] = 1;
    }else if (arg1 == 0){
        checkboxes[0] = 0;
    }
}

void ReadingsDialogBox::on_ReadingsDialogBoxTemperatureCheckBox_stateChanged(int arg1)
{
    if (arg1 == 0){
        ui->ReadingsDialogBoxAllDataCheckBox->setChecked(false);
        checkboxes[1] = 0;
    } else if (arg1 == 2){
        checkboxes[1] = 1;
    }

    allCheckBoxesClicked();
}

void ReadingsDialogBox::on_ReadingsDialogBoxHumidityCheckBox_stateChanged(int arg1)
{
    if (arg1 == 0){
        ui->ReadingsDialogBoxAllDataCheckBox->setChecked(false);
        checkboxes[2] = 0;
    } else if (arg1 == 2){
        checkboxes[2] = 1;
    }
    allCheckBoxesClicked();
}

void ReadingsDialogBox::allCheckBoxesClicked()
{
    if (ui->ReadingsDialogBoxHumidityCheckBox->isChecked() &&
            ui->ReadingsDialogBoxTemperatureCheckBox->isChecked()){
        ui->ReadingsDialogBoxAllDataCheckBox->setChecked(true);
    }
}
