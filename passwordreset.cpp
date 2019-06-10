#include "passwordreset.h"
#include "ui_passwordreset.h"
#include <QSqlQuery>
#include <QRandomGenerator64>

passwordReset::passwordReset(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::passwordReset)
{
    setWindowTitle("Passowrd Reset");
    setWindowIcon(QIcon("://icons/logo_O9H_2.ico"));
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
        changePassword();
        accept();
    }
    if (resetButton == QDialogButtonBox::Cancel){
        reject();
    }
}

void passwordReset::sendMail(QString userEmail, QString newPassword)
{
    //    qDebug() << "in sendMail";
        Smtp *smtp = new Smtp("hutemph3@gmail.com", "MnJhUy&^67", "smtp.gmail.com", 465);
        connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));
        QString subjectLine = "HuTemp - Password Reset -->(DO NOT REPLY TO THIS EMAIL)";
        QString message = "Your password has been reset. Enter your new temporary password at the login screen.\n\n";
        message += "New Temporary Password:\t";
        message += newPassword;
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

}

void passwordReset::mailSent(QString status)
{
    if(status == "Message sent"){
        QMessageBox::warning(this, "New Account", "Notify the account holder to check their email for their login credentials.");
    }
}

QString passwordReset::alphaNumGenerator()
{
    srand(QDateTime::currentMSecsSinceEpoch());
    QString tempWord = "";
    for (int i = 0; i < 10; i++){
        tempWord += charList[rand() % charList.count()];
    }
    return tempWord;
}

void passwordReset::changePassword()
{
    QString username = ui->emailLineEdit->text();
    QSqlQuery selectQuery;
    QString selectQueryStatement = QString("SELECT * FROM login WHERE username = '%1'").arg(username);
    if (selectQuery.exec(selectQueryStatement)){
        QString newPassword = alphaNumGenerator();
        QString offset = generateOffset(newPassword);
        QString newPasswordEncrypted = encrypt(newPassword);
        QString offsetEncrypted = encrypt(offset);
        QString finalPassword = newPasswordEncrypted + offsetEncrypted;
        QString finalPasswordEncrypted = encrypt(finalPassword);
        QSqlQuery updateQuery;
        QString updateQueryStatement = QString("UPDATE login SET password = AES_ENCRYPT('%1', '%2'), offset = AES_ENCRYPT('%4', '%2'),"
                                               " temporarypassword = 1, lockout = 0 WHERE username = '%3'")
                .arg(finalPasswordEncrypted).arg(KEY).arg(username).arg(offsetEncrypted);
        if (updateQuery.exec(updateQueryStatement)){
            sendMail(username, newPassword);
        }
    } else{
        QMessageBox::warning(this, tr("ERROR"), "Invalid email");
    }

}

QString passwordReset::encrypt(QString input)
{
    return input.toLocal8Bit().toHex().toBase64();
}


QString passwordReset::generateOffset(QString password)
{
    qDebug() << "in generateOffset";

    int length = 64 - password.length();

    QString offsetFill = "";
    for (int i = 0; i < length; i++){
        std::uniform_int_distribution<int> distribution(1, charList.count());
        int value = distribution(*QRandomGenerator::global()) - 1;

        QChar character = charList[value];

        offsetFill.append(character);
    }
    qDebug() << "offsetFill:\t" << offsetFill;
    return offsetFill;
}
