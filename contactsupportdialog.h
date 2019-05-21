#ifndef CONTACTSUPPORTDIALOG_H
#define CONTACTSUPPORTDIALOG_H

#include <QDialog>
#include <QAbstractButton>
#include "smtp.h"

namespace Ui {
class ContactSupportDialog;
}

class ContactSupportDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ContactSupportDialog(QWidget *parent = nullptr);
    ~ContactSupportDialog();

private slots:
    void on_ContactSupportDialogButtonBox_clicked(QAbstractButton *button);

private:
    Ui::ContactSupportDialog *ui;

    void sendMail();
    void mailSent(QString);
    void writeToPDF();
    void checkMinimumCharacterCount();
    bool minimumCharactersMet = false;
};

#endif // CONTACTSUPPORTDIALOG_H
