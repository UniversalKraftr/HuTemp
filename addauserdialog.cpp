#include "addauserdialog.h"
#include "ui_addauserdialog.h"

AddAUserDialog::AddAUserDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddAUserDialog)
{
    ui->setupUi(this);

    QStringList userContent = {"First Name", "Second Name", "Phone Number", "Email"};
    ui->AddAUserDialogFirstNameLineEdit->setPlaceholderText(userContent[0]);
    ui->AddAUserDialogLastNameLineEdit->setPlaceholderText(userContent[1]);
    ui->AddAUserDialogPhoneNumberLineEdit->setPlaceholderText(userContent[2]);
    ui->AddAUserDialogEmailLineEdit->setPlaceholderText(userContent[3]);
}

AddAUserDialog::~AddAUserDialog()
{
    delete ui;
}

void AddAUserDialog::on_AddAUserDialogButtonBox_clicked(QAbstractButton *button)
{
    QDialogButtonBox::StandardButton addUserStdButton = ui->AddAUserDialogButtonBox->standardButton(button);

    if (addUserStdButton == QDialogButtonBox::Ok){
        accept();
    }
    if (addUserStdButton == QDialogButtonBox::Cancel){
        reject();
    }

}
