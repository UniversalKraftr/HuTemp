#include "quickviewsdialogbox.h"
#include "ui_quickviewsdialogbox.h"
#include <QDebug>

quickViewsDialogBox::quickViewsDialogBox(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::quickViewsDialogBox)
{
    ui->setupUi(this);

    setWindowTitle("Quick Views");
    adjustSize();


    connect(ui->quickViewsDialogBoxAllDayRadioButton, &QRadioButton::released, [=](){
        quickViewsDialogBox::captureCurrentButtons();
        quickViewsDialogBox::setCurrentRadioButton(1);
    });


    connect(ui->quickViewsDialogBoxBusinessHoursRadioBox, &QRadioButton::released, [=](){
        quickViewsDialogBox::captureCurrentButtons();
        quickViewsDialogBox::setCurrentRadioButton(2);
    });


    connect(ui->quickViewsDialogBoxOvernightHoursRadioBox, &QRadioButton::released, [=](){
        quickViewsDialogBox::captureCurrentButtons();
        quickViewsDialogBox::setCurrentRadioButton(3);
    });


    connect(ui->quickViewsDialogBoxSpecificHoursRadioBox, &QRadioButton::released, [=](){
        quickViewsDialogBox::captureCurrentButtons();
        quickViewsDialogBox::setCurrentRadioButton(4);
    });
}

quickViewsDialogBox::~quickViewsDialogBox()
{
    delete ui;
}

int quickViewsDialogBox::getCurrentRadioButton()
{
    return currentButtonByAssociation;
}

void quickViewsDialogBox::setCurrentRadioButton(int radioButton)
{
    currentButtonByAssociation = radioButton;
    if (currentButtonByAssociation == 0){
        ui->quickViewsDialogBoxBusinessHoursRadioBox->setChecked(true);
    } else{
        if (currentButtonByAssociation == 1){
            ui->quickViewsDialogBoxAllDayRadioButton->setChecked(true);
        } else if (currentButtonByAssociation == 2) {
            ui->quickViewsDialogBoxBusinessHoursRadioBox->setChecked(true);
        } else if (currentButtonByAssociation == 3){
            ui->quickViewsDialogBoxOvernightHoursRadioBox->setChecked(true);
        } else if (currentButtonByAssociation == 4){
            ui->quickViewsDialogBoxSpecificHoursRadioBox->setChecked(true);
        }
    }
}

void quickViewsDialogBox::on_quickViewsDialogBoxButtons_clicked(QAbstractButton *button)
{
    QDialogButtonBox::StandardButton quickViewsStdButton = ui->quickViewsDialogBoxButtons->standardButton(button);

    if(quickViewsStdButton == QDialogButtonBox::Reset){
        ui->quickViewsDialogBoxBusinessHoursRadioBox->setChecked(true);
    }
    if(quickViewsStdButton == QDialogButtonBox::Ok){
        accept();
    }
    if(quickViewsStdButton == QDialogButtonBox::Cancel){
        reject();
    }
}

void quickViewsDialogBox::captureCurrentButtons()
{
    if (!buttonStates.isEmpty()){
        buttonStates.clear();
    }
    buttonStates.insert("All day", ui->quickViewsDialogBoxAllDayRadioButton);
    buttonStates.insert("Business Hours", ui->quickViewsDialogBoxBusinessHoursRadioBox);
    buttonStates.insert("Overnight Hours", ui->quickViewsDialogBoxOvernightHoursRadioBox);
    buttonStates.insert("Specific Hours", ui->quickViewsDialogBoxSpecificHoursRadioBox);
}
