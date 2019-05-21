#include "contactsupportdialog.h"
#include "ui_contactsupportdialog.h"
#include <QFileDialog>
#include <QDialogButtonBox>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QPrinter>
#include <QMessageBox>
#include <widget.h>

ContactSupportDialog::ContactSupportDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ContactSupportDialog)
{
    ui->setupUi(this);

    setWindowTitle("Contact Support");
    adjustSize();
    ui->ContactSupportDialogDetailedDescriptionLabel->setText("Please provide a detailed description.\nPlease include any actions attempted with User Manual.");

    Widget *user = new Widget(this);

    ui->ContactSupportDialogDateTimeStampLabel->setText(QDateTime::currentDateTime().toString("MM dd yyyy h:mm:ss ap"));
//    ui->ContactSupportDialogUserNameLabel->setText();
//    ui->ContactSupportDialogUserEmailLabel->setText();
//    ui->ContactSupportDialogUserTypeLabel->setText();
//    ui->ContactSupportDialogCompanyNameLabel->setText();
//    ui->ContactSupportDialogCompanyAddressLine1Label->setText();
//    ui->ContactSupportDialogCompanyAddressLine2Label->setText();
//    ui->ContactSupportDialogCompanyPhoneNumberLabel->setText();

    connect(ui->ContactSupportDialogTextEdit, &QTextEdit::textChanged, this, &ContactSupportDialog::checkMinimumCharacterCount);
}

ContactSupportDialog::~ContactSupportDialog()
{
    delete ui;
}


void ContactSupportDialog::writeToPDF()
{
    Widget *widget = new Widget(this);
    QString directory = widget->getLogFolder();
    QString fileName =  directory + "Test.txt";
    QFile file(fileName);
    if (file.open(QIODevice::ReadWrite)){
        QTextStream stream(&file);
        stream << ui->ContactSupportDialogDateTimeStampLabel->text() << endl;
        stream << ui->ContactSupportDialogUserNameLabel->text() << endl;
        stream << ui->ContactSupportDialogUserEmailLabel->text() << endl;
        stream << ui->ContactSupportDialogUserTypeLabel->text() << endl << endl;

        stream << ui->ContactSupportDialogCompanyNameLabel->text() << endl;
        stream << ui->ContactSupportDialogCompanyAddressLine1Label->text() << endl;
        stream << ui->ContactSupportDialogCompanyAddressLine2Label->text() << endl;
        stream << ui->ContactSupportDialogCompanyPhoneNumberLabel->text() << endl << endl;

        stream << ui->ContactSupportDialogCategoryLabel->text() << ":\t";
        stream << ui->ContactSupportDialogCategoryComboBox->currentText() << endl << endl;

        stream << ui->ContactSupportDialogDetailedDescriptionLabel->text() << endl;
        stream << ui->ContactSupportDialogTextEdit->toPlainText() << endl;
    }
    file.close();

    QTextDocument doc;
    QFile file2(fileName);
    if (file2.open(QIODevice::ReadOnly|QIODevice::Text)){

        QTextStream in(&file2);
        QString myText = in.readAll();
        doc.setPlainText(myText);
    }

    file2.remove();

    QPrinter pdfFile;
    pdfFile.setOutputFormat(QPrinter::PdfFormat);
    pdfFile.setOutputFileName(directory + "/Test.pdf");
    doc.print(&pdfFile);
}

void ContactSupportDialog::checkMinimumCharacterCount()
{
    int characterCount = ui->ContactSupportDialogTextEdit->toPlainText().length();
    int minimumLabelCount = 250-characterCount;
    if (minimumLabelCount > 0){
        QString statement = QString::number(minimumLabelCount) + " character count";
        ui->ContactSupportDialogCharacterMinimumLabel->setText(statement);
        minimumCharactersMet = false;
    } else if(minimumLabelCount <= 0){
        ui->ContactSupportDialogCharacterMinimumLabel->setText("0 character count");
        minimumCharactersMet = true;
    }

}



void ContactSupportDialog::on_ContactSupportDialogButtonBox_clicked(QAbstractButton *button)
{
    QDialogButtonBox::StandardButton stdButton = ui->ContactSupportDialogButtonBox->standardButton(button);

    if(stdButton == QDialogButtonBox::Ok){
        if (minimumCharactersMet == true){
            writeToPDF();
            accept();
        } else{
            QMessageBox::warning(this, tr("Incomplete"), "You must meet the 250 minimum character count.");
        }

    }
    if(stdButton == QDialogButtonBox::Cancel){
        QMessageBox::StandardButton warningReply = QMessageBox::warning(this, tr("Warning!"),
                             "Are you sure you wish to cancel this form?",
                             QMessageBox::Yes | QMessageBox::No);
        if (warningReply == QMessageBox::Yes){
            accept();
        }
        if (warningReply == QMessageBox::No){
            reject();
        }
    }
}

//void ContactSupportDialog::sendMail()
//{
//    Smtp* smtp = new Smtp(ui->uname->text(), ui->paswd->text(), ui->server->text(), ui->port->text().toInt());
//    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));


//    smtp->sendMail(ui->uname->text(), ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText());
//}

//void ContactSupportDialog::mailSent(QString status)
//{
//    if(status == "Message sent"){
//        QMessageBox::information(this,tr("Confirmation"), "Message sent!\n\n");
//    }
//}
