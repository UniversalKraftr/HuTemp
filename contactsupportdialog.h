#ifndef CONTACTSUPPORTDIALOG_H
#define CONTACTSUPPORTDIALOG_H

#include <QDialog>
#include <QAbstractButton>
#include "smtp.h"
#include "widget.h"

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
    void sendMail();
    void mailSent(QString);
    void attachPDF(QString);

private:
    Ui::ContactSupportDialog *ui;
    QFile file;
    QDataStream dataStream;
    QString directory;
    Widget *widget = new Widget();
    QStringList files;

    void writeToPDF();
    QString captureLogs();
    void checkMinimumCharacterCount();
    bool minimumCharactersMet = false;
};

#endif // CONTACTSUPPORTDIALOG_H
