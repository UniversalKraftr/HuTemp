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

void ReadingsDialogBox::on_ReadingsDialogBoxButtons_clicked(QAbstractButton *button)
{
    QDialogButtonBox::StandardButton readingsStdButton = ui->ReadingsDialogBoxButtons->standardButton(button);

    if(readingsStdButton == QDialogButtonBox::Reset){

    }
    if(readingsStdButton == QDialogButtonBox::Ok){

    }
    if(readingsStdButton == QDialogButtonBox::Cancel){

    }
    if(readingsStdButton == QDialogButtonBox::Apply){

    }
}
