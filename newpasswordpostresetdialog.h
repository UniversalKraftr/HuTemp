#ifndef NEWPASSWORDPOSTRESETDIALOG_H
#define NEWPASSWORDPOSTRESETDIALOG_H

#include <QDialog>
#include <QAbstractButton>
#include <QDebug>
#include <QMessageBox>
#include <QRandomGenerator64>
#include <QSqlQuery>


namespace Ui {
class NewPasswordPostResetDialog;
}

class NewPasswordPostResetDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewPasswordPostResetDialog(QString, QWidget *parent = nullptr);
    ~NewPasswordPostResetDialog();

private slots:
    void on_NewPasswordPostResetDialogButtons_clicked(QAbstractButton *button);
    void on_NewPasswordPostResetDialogNewPasswordRevealButton_clicked();
    void on_NewPasswordPostResetDialogReEnterPasswordRevealButton_clicked();

private:
    Ui::NewPasswordPostResetDialog *ui;
    int upper;
    int lower;
    int number;
    int specialChar;
    QString KEY = "*:2Q-S9AX||NkvVg<q&i";
    QString charList = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()-_=+/?><";
    QString userName;


    void setTextSuggestions();
    void setDefaults();
    bool validatePassword();
    bool validateReenteredPassword();
    bool updatePassword();
    QString encrypt(QString);
    QString decrypt(QString);
    QString generateOffset(QString);


};

#endif // NEWPASSWORDPOSTRESETDIALOG_H
