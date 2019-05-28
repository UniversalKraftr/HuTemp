#include "periodsdialogbox.h"
#include "ui_periodsdialogbox.h"

PeriodsDialogBox::PeriodsDialogBox(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PeriodsDialogBox)
{
    ui->setupUi(this);

    setWindowTitle("Time Periods");
    adjustSize();

    connect(ui->PeriodsDialogBoxNoneRadioButton, &QRadioButton::released, [=](){
        PeriodsDialogBox::setCurrentRadioButton(1);
    });

    connect(ui->PeriodsDialogBoxDayRadioButton, &QRadioButton::released, [=](){
        PeriodsDialogBox::setCurrentRadioButton(2);
    });

    connect(ui->PeriodsDialogBoxWeekRadioButton, &QRadioButton::released, [=](){
        PeriodsDialogBox::setCurrentRadioButton(3);
    });

    connect(ui->PeriodsDialogBoxMonthRadioButton, &QRadioButton::released, [=](){
        PeriodsDialogBox::setCurrentRadioButton(4);
    });

    connect(ui->PeriodsDialogBoxYearRadioButton, &QRadioButton::released, [=](){
        PeriodsDialogBox::setCurrentRadioButton(5);
    });

    connect(ui->PeriodsDialogBoxAllRadioButton, &QRadioButton::released, [=](){
        PeriodsDialogBox::setCurrentRadioButton(6);
    });
}

PeriodsDialogBox::~PeriodsDialogBox()
{
    delete ui;
}

int PeriodsDialogBox::getCurrentRadioButton()
{
    return currentButtonByAssociation;
}

void PeriodsDialogBox::setCurrentRadioButton(int radioButton)
{
    currentButtonByAssociation = radioButton;
    if (currentButtonByAssociation == 0){
        ui->PeriodsDialogBoxNoneRadioButton->setChecked(true);
    } else{
        if (currentButtonByAssociation == 1){
            ui->PeriodsDialogBoxNoneRadioButton->setChecked(true);
        } else if (currentButtonByAssociation == 2){
            ui->PeriodsDialogBoxDayRadioButton->setChecked(true);
        } else if (currentButtonByAssociation == 3){
            ui->PeriodsDialogBoxWeekRadioButton->setChecked(true);
        } else if (currentButtonByAssociation == 4){
            ui->PeriodsDialogBoxMonthRadioButton->setChecked(true);
        } else if (currentButtonByAssociation == 5){
            ui->PeriodsDialogBoxYearRadioButton->setChecked(true);
        } else if (currentButtonByAssociation == 6){
            ui->PeriodsDialogBoxAllRadioButton->setChecked(true);
        }
    }
}

void PeriodsDialogBox::on_PeriodsDialogBoxButtons_clicked(QAbstractButton *button)
{
    QDialogButtonBox::StandardButton periodsStdButton = ui->PeriodsDialogBoxButtons->standardButton(button);

    if(periodsStdButton == QDialogButtonBox::Reset){
        ui->PeriodsDialogBoxNoneRadioButton->setChecked(true);
        currentButtonByAssociation = 1;
    }
    if(periodsStdButton == QDialogButtonBox::Ok){
        accept();
    }
    if(periodsStdButton == QDialogButtonBox::Cancel){
        reject();
    }
}
