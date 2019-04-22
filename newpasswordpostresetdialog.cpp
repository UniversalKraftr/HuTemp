#include "newpasswordpostresetdialog.h"
#include "ui_newpasswordpostresetdialog.h"

NewPasswordPostResetDialog::NewPasswordPostResetDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewPasswordPostResetDialog)
{
    ui->setupUi(this);
}

NewPasswordPostResetDialog::~NewPasswordPostResetDialog()
{
    delete ui;
}
