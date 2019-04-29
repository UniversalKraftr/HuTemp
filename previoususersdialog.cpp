#include "previoususersdialog.h"
#include "ui_previoususersdialog.h"

PreviousUsersDialog::PreviousUsersDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PreviousUsersDialog)
{
    ui->setupUi(this);

    setWindowTitle("Previous Users");
    adjustSize();
}

PreviousUsersDialog::~PreviousUsersDialog()
{
    delete ui;
}
