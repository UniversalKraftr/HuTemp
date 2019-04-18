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

void DevicesDialogBox::on_DevicesDialogBoxButtons_clicked(QAbstractButton *button)
{
    QDialogButtonBox::StandardButton devicesStdButton = ui->DevicesDialogBoxButtons->standardButton(button);

    if(devicesStdButton == QDialogButtonBox::Reset){

    }
    if(devicesStdButton == QDialogButtonBox::Ok){

    }
    if(devicesStdButton == QDialogButtonBox::Cancel){

    }
    if(devicesStdButton == QDialogButtonBox::Apply){

    }
}
