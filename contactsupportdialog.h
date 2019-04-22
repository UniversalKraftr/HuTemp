#ifndef CONTACTSUPPORTDIALOG_H
#define CONTACTSUPPORTDIALOG_H

#include <QDialog>
#include <QAbstractButton>

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
    void writeToPDF(Ui::ContactSupportDialog *ui);
};

#endif // CONTACTSUPPORTDIALOG_H
