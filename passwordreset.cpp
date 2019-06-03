#include "passwordreset.h"
#include "ui_passwordreset.h"
#include <QSqlQuery>

passwordReset::passwordReset(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::passwordReset)
{
    ui->setupUi(this);
}

passwordReset::~passwordReset()
{
    delete ui;
}

void passwordReset::on_passwordResetButtonBox_clicked(QAbstractButton *button)
{
    QDialogButtonBox::StandardButton resetButton = ui->passwordResetButtonBox->standardButton(button);

    if (resetButton == QDialogButtonBox::Ok){
        sendMail(ui->emailLineEdit->text());
        accept();
    }
    if (resetButton == QDialogButtonBox::Cancel){
        reject();
    }
}

void passwordReset::sendMail(QString userEmail)
{
    //    qDebug() << "in sendMail";
        Smtp *smtp = new Smtp("hutemph3@gmail.com", "MnJhUy&^67", "smtp.gmail.com", 465);
        connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));
        QString subjectLine = "HuTemp - Password Reset -->(DO NOT REPLY TO THIS EMAIL)";
        QString message = "Your password has been reset. Enter your new temporary password at the login screen.\n\n";
        message += "New Temporary Password:\t";

        QSqlQuery getPasswordQuery;
        QString getPasswordQueryStatement = QString("SELECT password FROM login WHERE username = '%1'").arg(userEmail);
        if (getPasswordQuery.exec(getPasswordQueryStatement)){
            message += getPasswordQuery.value(0).toString();
            message += "\n\n";
            message += "HuTemp Support";
            message += "\nDO NOT REPLY TO THIS EMAIL";

            if(!files.isEmpty()){
        //        qDebug() << "!files.isEmpty()";
                smtp->sendMail("hutempcs@gmail.com", userEmail , subjectLine, message, files );
            } else{
        //        qDebug() << "files.isEmpty()";
                smtp->sendMail("hutempcs@gmail.com", userEmail , subjectLine, message);
            }
        } else{
            QMessageBox::warning(this, tr("Email Error"), "The email you entered is invalid.\nPlease check the email you typed.");
        }
}

void passwordReset::mailSent(QString status)
{
    if(status == "Message sent"){
        QMessageBox::warning(this, "New Account", "Notify the account holder to check their email for their login credentials.");
    }
}
