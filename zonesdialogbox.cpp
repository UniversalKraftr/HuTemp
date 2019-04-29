#include "zonesdialogbox.h"
#include "ui_zonesdialogbox.h"

ZonesDialogBox::ZonesDialogBox(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ZonesDialogBox)
{
    ui->setupUi(this);

    setWindowTitle("Zones");
    adjustSize();
}

ZonesDialogBox::~ZonesDialogBox()
{
    delete ui;
}

void ZonesDialogBox::on_ZonesDialogBoxButtons_clicked(QAbstractButton *button)
{
    QDialogButtonBox::StandardButton zonesStdButton = ui->ZonesDialogBoxButtons->standardButton(button);

    if(zonesStdButton == QDialogButtonBox::Reset){

    }
    if(zonesStdButton == QDialogButtonBox::Ok){

    }
    if(zonesStdButton == QDialogButtonBox::Cancel){

    }
    if(zonesStdButton == QDialogButtonBox::Apply){

    }
}
