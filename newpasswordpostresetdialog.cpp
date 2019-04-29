#include "newpasswordpostresetdialog.h"
#include "ui_newpasswordpostresetdialog.h"

NewPasswordPostResetDialog::NewPasswordPostResetDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewPasswordPostResetDialog)
{
    ui->setupUi(this);

    setWindowTitle("Password Reset");
    adjustSize();
}

NewPasswordPostResetDialog::~NewPasswordPostResetDialog()
{
    delete ui;
}
