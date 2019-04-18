#include "periodsdialogbox.h"
#include "ui_periodsdialogbox.h"

PeriodsDialogBox::PeriodsDialogBox(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PeriodsDialogBox)
{
    ui->setupUi(this);

    setWindowTitle("Time Periods");
    adjustSize();
}

PeriodsDialogBox::~PeriodsDialogBox()
{
    delete ui;
}

void PeriodsDialogBox::on_PeriodsDialogBoxButtons_clicked(QAbstractButton *button)
{
    QDialogButtonBox::StandardButton periodsStdButton = ui->PeriodsDialogBoxButtons->standardButton(button);

    if(periodsStdButton == QDialogButtonBox::Reset){

    }
    if(periodsStdButton == QDialogButtonBox::Ok){

    }
    if(periodsStdButton == QDialogButtonBox::Cancel){

    }
    if(periodsStdButton == QDialogButtonBox::Apply){

    }
}
