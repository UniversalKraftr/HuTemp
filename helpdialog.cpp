#include "helpdialog.h"
#include "ui_helpdialog.h"
#include <QFileDialog>
#include <QDesktopServices>
#include <QUrl>
#include <QMessageBox>
#include <contactsupportdialog.h>

HelpDialog::HelpDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HelpDialog)
{
    ui->setupUi(this);

    setWindowTitle("Help");
    setWindowIcon(QIcon("://icons/logo_O9H_2.ico"));
    adjustSize();
}

HelpDialog::~HelpDialog()
{
    delete ui;
}

void HelpDialog::on_HelpDialogUserManualButton_clicked()
{
    QString myFileText = QCoreApplication::applicationDirPath()+"/Master User Manual2.pdf";
//    qDebug() << myFileText;
    QDesktopServices::openUrl(QUrl("file:///" + myFileText, QUrl::TolerantMode));
}

void HelpDialog::on_HelpDialogContactSupportButton_clicked()
{
    ContactSupportDialog *contact = new ContactSupportDialog(this);
    contact->show();
}

void HelpDialog::on_HelpDialogButtonBox_clicked(QAbstractButton *button)
{
    QDialogButtonBox::StandardButton helpStdButton = ui->HelpDialogButtonBox->standardButton(button);

    if(helpStdButton == QDialogButtonBox::Close){
        reject();
    }
}
