#ifndef PASSWORDRESET_H
#define PASSWORDRESET_H

#include <QDialog>
#include <QAbstractButton>
#include <QDialogButtonBox>
#include "smtp.h"

namespace Ui {
class passwordReset;
}

class passwordReset : public QDialog
{
    Q_OBJECT

public:
    explicit passwordReset(QWidget *parent = nullptr);
    ~passwordReset();

private slots:
    void on_passwordResetButtonBox_clicked(QAbstractButton *button);
    void sendMail(QString, QString);
    void mailSent(QString);
    QString alphaNumGenerator();
    void changePassword();
    QString encrypt(QString);
    QString generateOffset(QString);

private:
    Ui::passwordReset *ui;
    QStringList files;
    QString charList = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()-_=+/?><";
    QString KEY = "*:2Q-S9AX||NkvVg<q&i";
};

#endif // PASSWORDRESET_H
