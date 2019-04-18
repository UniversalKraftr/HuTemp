#include "quickviewsdialogbox.h"
#include "ui_quickviewsdialogbox.h"

quickViewsDialogBox::quickViewsDialogBox(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::quickViewsDialogBox)
{
    ui->setupUi(this);

    setWindowTitle("Quick Views");
    adjustSize();


}

quickViewsDialogBox::~quickViewsDialogBox()
{
    delete ui;
}

void quickViewsDialogBox::on_quickViewsDialogBoxButtons_clicked(QAbstractButton *button)
{
    QDialogButtonBox::StandardButton quickViewsStdButton = ui->quickViewsDialogBoxButtons->standardButton(button);

    if(quickViewsStdButton == QDialogButtonBox::Reset){

    }
    if(quickViewsStdButton == QDialogButtonBox::Ok){

    }
    if(quickViewsStdButton == QDialogButtonBox::Cancel){

    }
    if(quickViewsStdButton == QDialogButtonBox::Apply){

    }
}
