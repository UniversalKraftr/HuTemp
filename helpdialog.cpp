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
    adjustSize();
}

HelpDialog::~HelpDialog()
{
    delete ui;
}

void HelpDialog::on_HelpDialogUserManualButton_clicked()
{
    QMessageBox::information(this, tr("Folder Selection"), "Select the folder your PDF Reader is located in");
    QString directory = QFileDialog::getExistingDirectory();
    QMessageBox::information(this, "Application Selection", "Select your preferred PDF Reader");
    QString filename = QFileDialog::getOpenFileName(
                this,
                tr("Select PDF Reader"),
                directory,
                "All Files (*.*);;Applications (*.exe)");

    QDesktopServices::openUrl(QUrl("file:///" + filename, QUrl::TolerantMode));
}

void HelpDialog::on_HelpDialogContactSupportButton_clicked()
{
    ContactSupportDialog *contact = new ContactSupportDialog(this);
    contact->exec();
}

void HelpDialog::on_HelpDialogButtonBox_clicked(QAbstractButton *button)
{
    QDialogButtonBox::StandardButton helpStdButton = ui->HelpDialogButtonBox->standardButton(button);

    if(helpStdButton == QDialogButtonBox::Close){
        reject();
    }
}
