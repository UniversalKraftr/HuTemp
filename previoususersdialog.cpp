#include "previoususersdialog.h"
#include "ui_previoususersdialog.h"
#include <QSqlQuery>
#include <QDebug>
#include "widget.h"

PreviousUsersDialog::PreviousUsersDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PreviousUsersDialog)
{
    ui->setupUi(this);

    setWindowTitle("Previous Users");
    setWindowIcon(QIcon("://icons/logo_O9H_2.ico"));
    adjustSize();
    populateListWidget();
}

PreviousUsersDialog::~PreviousUsersDialog()
{
    delete ui;
}

void PreviousUsersDialog::on_PreviousUsersDialogExitButton_clicked()
{
    reject();
}

void PreviousUsersDialog::populateListWidget()
{
    if (ui->PreviousUsersDialogListWidget->count() > 0){
        ui->PreviousUsersDialogListWidget->clear();
    }

    QSqlQuery selectQuery;
    QString selectQueryStatement = QString("SELECT firstname, lastname FROM users WHERE activestatus = 0");
    if (selectQuery.exec(selectQueryStatement)){
        while (selectQuery.next()){
            QString firstName = selectQuery.value(0).toString();
            QString lastName = selectQuery.value(1).toString();

            QString fullName = firstName + " " + lastName;


            ui->PreviousUsersDialogListWidget->addItem(fullName);
        }
    }
}

void PreviousUsersDialog::on_PreviousUsersDialogRestoreButton_clicked()
{
    QString fullName =  ui->PreviousUsersDialogListWidget->currentItem()->text();
    QString firstName = fullName.split(" ").front();
    QString lastName = fullName.split(" ").back();
    QSqlQuery updateQuery;
    QString updateQuerystatement = QString("UPDATE users SET activestatus = 1 WHERE firstname = '%1' AND lastname = '%2'").arg(firstName).arg(lastName);
    if (updateQuery.exec(updateQuerystatement)){
        QMessageBox::information(this, tr("User Restored"), "Your selected user has been restored. User will appear in your table momentarily.");
    } else{
        QMessageBox::warning(this, tr("Restore Error"), "An error occurred. Please try again later");
    }
    accept();
}
