#include "zonesdialogbox.h"
#include "ui_zonesdialogbox.h"
#include <QDebug>

ZonesDialogBox::ZonesDialogBox(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ZonesDialogBox)
{
    ui->setupUi(this);

    setWindowTitle("Zones");
    setWindowIcon(QIcon("://icons/logo_O9H_2.ico"));
    adjustSize();
}

ZonesDialogBox::~ZonesDialogBox()
{
    delete ui;
}

QList<bool> ZonesDialogBox::getCheckBoxes()
{
    return checkBoxes;
}

void ZonesDialogBox::setCheckBoxes(QList<bool> checkboxes)
{
    if (!checkBoxes.isEmpty()){
        checkBoxes.clear();
    }
    checkBoxes = checkboxes;
    ui->ZonesDialogBoxAllZonesCheckBox->setChecked(checkBoxes[0]);
    ui->ZonesDialogBoxCollectionsCheckBox->setChecked(checkBoxes[1]);
    ui->ZonesDialogBoxDockAreaCheckBox->setChecked(checkBoxes[2]);
    ui->ZonesDialogBoxGallery1CheckBox->setChecked(checkBoxes[3]);
    ui->ZonesDialogBoxGallery2CheckBox->setChecked(checkBoxes[4]);
    ui->ZonesDialogBoxGallery3CheckBox->setChecked(checkBoxes[5]);
    ui->ZonesDialogBoxGallery4CheckBox->setChecked(checkBoxes[6]);
    ui->ZonesDialogBoxGallery5CheckBox->setChecked(checkBoxes[7]);
    ui->ZonesDialogBoxGallery6CheckBox->setChecked(checkBoxes[8]);
    ui->ZonesDialogBoxLobbyCheckBox->setChecked(checkBoxes[9]);
}

void ZonesDialogBox::on_ZonesDialogBoxButtons_clicked(QAbstractButton *button)
{
    QDialogButtonBox::StandardButton zonesStdButton = ui->ZonesDialogBoxButtons->standardButton(button);

    if(zonesStdButton == QDialogButtonBox::Reset){
        ui->ZonesDialogBoxAllZonesCheckBox->setChecked(true);
    }
    if(zonesStdButton == QDialogButtonBox::Ok){
        accept();
    }
    if(zonesStdButton == QDialogButtonBox::Cancel){
        reject();
    }
}

void ZonesDialogBox::on_ZonesDialogBoxAllZonesCheckBox_stateChanged(int arg1)
{
    if (arg1 == 2){
        ui->ZonesDialogBoxLobbyCheckBox->setChecked(true);
        ui->ZonesDialogBoxCollectionsCheckBox->setChecked(true);
        ui->ZonesDialogBoxDockAreaCheckBox->setChecked(true);
        ui->ZonesDialogBoxGallery1CheckBox->setChecked(true);
        ui->ZonesDialogBoxGallery2CheckBox->setChecked(true);
        ui->ZonesDialogBoxGallery3CheckBox->setChecked(true);
        ui->ZonesDialogBoxGallery4CheckBox->setChecked(true);
        ui->ZonesDialogBoxGallery5CheckBox->setChecked(true);
        ui->ZonesDialogBoxGallery6CheckBox->setChecked(true);
        ui->ZonesDialogBoxZone10CheckBox->setChecked(true);
    }
    checkBoxes[0] = ui->ZonesDialogBoxAllZonesCheckBox->isChecked();
}

void ZonesDialogBox::on_ZonesDialogBoxCollectionsCheckBox_stateChanged(int arg1)
{
    if (arg1 == 0){
        ui->ZonesDialogBoxAllZonesCheckBox->setChecked(false);
    }
    checkBoxes[1] = ui->ZonesDialogBoxCollectionsCheckBox->isChecked();
    allCheckBoxesClicked();
}

void ZonesDialogBox::on_ZonesDialogBoxDockAreaCheckBox_stateChanged(int arg1)
{
    if (arg1 == 0){
        ui->ZonesDialogBoxAllZonesCheckBox->setChecked(false);
    }
    checkBoxes[2] = ui->ZonesDialogBoxDockAreaCheckBox->isChecked();
    allCheckBoxesClicked();
}

void ZonesDialogBox::on_ZonesDialogBoxGallery1CheckBox_stateChanged(int arg1)
{
    if (arg1 == 0){
        ui->ZonesDialogBoxAllZonesCheckBox->setChecked(false);
    }
    checkBoxes[3] = ui->ZonesDialogBoxGallery1CheckBox->isChecked();
    allCheckBoxesClicked();
}

void ZonesDialogBox::on_ZonesDialogBoxGallery2CheckBox_stateChanged(int arg1)
{
    if (arg1 == 0){
        ui->ZonesDialogBoxAllZonesCheckBox->setChecked(false);
    }
    checkBoxes[4] = ui->ZonesDialogBoxGallery2CheckBox->isChecked();
    allCheckBoxesClicked();
}

void ZonesDialogBox::on_ZonesDialogBoxGallery3CheckBox_stateChanged(int arg1)
{
    if (arg1 == 0){
        ui->ZonesDialogBoxAllZonesCheckBox->setChecked(false);
    }
    checkBoxes[5] = ui->ZonesDialogBoxGallery3CheckBox->isChecked();
    allCheckBoxesClicked();
}

void ZonesDialogBox::on_ZonesDialogBoxGallery4CheckBox_stateChanged(int arg1)
{
    if (arg1 == 0){
        ui->ZonesDialogBoxAllZonesCheckBox->setChecked(false);
    }
    checkBoxes[6] = ui->ZonesDialogBoxGallery4CheckBox->isChecked();
    allCheckBoxesClicked();
}

void ZonesDialogBox::on_ZonesDialogBoxGallery5CheckBox_stateChanged(int arg1)
{
    if (arg1 == 0){
        ui->ZonesDialogBoxAllZonesCheckBox->setChecked(false);
    }
    checkBoxes[7] = ui->ZonesDialogBoxGallery5CheckBox->isChecked();
    allCheckBoxesClicked();
}

void ZonesDialogBox::on_ZonesDialogBoxGallery6CheckBox_stateChanged(int arg1)
{
    if (arg1 == 0){
        ui->ZonesDialogBoxAllZonesCheckBox->setChecked(false);
    }
    checkBoxes[8] = ui->ZonesDialogBoxGallery6CheckBox->isChecked();
    allCheckBoxesClicked();
}

void ZonesDialogBox::on_ZonesDialogBoxLobbyCheckBox_stateChanged(int arg1)
{
    if (arg1 == 0){
        ui->ZonesDialogBoxAllZonesCheckBox->setChecked(false);
    }
    checkBoxes[9] = ui->ZonesDialogBoxLobbyCheckBox->isChecked();
    allCheckBoxesClicked();
}

void ZonesDialogBox::allCheckBoxesClicked()
{
    if (ui->ZonesDialogBoxCollectionsCheckBox->isChecked() &&
            ui->ZonesDialogBoxDockAreaCheckBox->isChecked() &&
            ui->ZonesDialogBoxGallery1CheckBox->isChecked() &&
            ui->ZonesDialogBoxGallery2CheckBox->isChecked() &&
            ui->ZonesDialogBoxGallery3CheckBox->isChecked() &&
            ui->ZonesDialogBoxGallery4CheckBox->isChecked() &&
            ui->ZonesDialogBoxGallery5CheckBox->isChecked() &&
            ui->ZonesDialogBoxGallery6CheckBox->isChecked() &&
            ui->ZonesDialogBoxLobbyCheckBox->isChecked() &&
            ui->ZonesDialogBoxZone10CheckBox->isChecked()){
        ui->ZonesDialogBoxAllZonesCheckBox->setChecked(true);
    }
}

void ZonesDialogBox::on_ZonesDialogBoxZone10CheckBox_stateChanged(int arg1)
{
    if (arg1 == 0){
        ui->ZonesDialogBoxZone10CheckBox->setChecked(false);
    }
    checkBoxes[10] = ui->ZonesDialogBoxZone10CheckBox->isChecked();
    allCheckBoxesClicked();
}
