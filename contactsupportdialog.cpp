#include "contactsupportdialog.h"
#include "ui_contactsupportdialog.h"
#include <QFileDialog>
#include <QDialogButtonBox>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QPrinter>
#include <QMessageBox>
#include <QDir>


ContactSupportDialog::ContactSupportDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ContactSupportDialog)
{
    ui->setupUi(this);

    setWindowTitle("Contact Support");
    adjustSize();
    ui->ContactSupportDialogDetailedDescriptionLabel->setText("Please provide a detailed description.\nPlease include any actions attempted with User Manual.");


    ui->ContactSupportDialogDateTimeStampLabel->setText(QDateTime::currentDateTime().toString("MM dd yyyy h:mm:ss ap"));
    ui->ContactSupportDialogUserNameLabel->setText(widget->getUserName());
    ui->ContactSupportDialogUserEmailLabel->setText(widget->getUserEmail());
    ui->ContactSupportDialogUserTypeLabel->setText(widget->getUserType());
    QFile file(widget->getLogFolder() + "/CompanyInfo.txt");
    if (!file.exists()){
        qDebug() << "file does not exist";
    } else{
        if (file.open(QIODevice::ReadOnly)){
            QTextStream in(&file);
            QString myFileText = in.readAll();
            qDebug() << myFileText;
            QStringList myText = myFileText.split("\n");
            ui->ContactSupportDialogCompanyNameLabel->setText(myText[0]);
            ui->ContactSupportDialogCompanyAddressLine1Label->setText(myText[1]);
            ui->ContactSupportDialogCompanyAddressLine2Label->setText(myText[2]);
            ui->ContactSupportDialogCompanyPhoneNumberLabel->setText(myText[3]);
        }else{
            qDebug() << "File currently does not exist";
        }
    }
    connect(ui->ContactSupportDialogTextEdit, &QTextEdit::textChanged, this, &ContactSupportDialog::checkMinimumCharacterCount);
}

ContactSupportDialog::~ContactSupportDialog()
{
    delete ui;
}


void ContactSupportDialog::writeToPDF()
{
    directory = widget->getPDFFolder();

    QDir dir(directory);
    QStringList files = dir.entryList(QDir::NoDotAndDotDot | QDir::Files);
    int fileMatchedCount = 0;
    for (int f = 0; f < files.length(); f++){
        if (files[f].contains("ContactSupportForm")){
            fileMatchedCount++;
        }
    }


    QString fileName =  directory + "/ContactSupportForm" + QString::number(fileMatchedCount) +".txt";
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
        stream << endl << endl;

        stream << captureLogs();
    }
    file.close();

//    captureLogs();
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
    fileName = fileName.split(".").front();
    pdfFile.setOutputFileName(fileName + ".pdf");
    doc.print(&pdfFile);
    qDebug() << fileName;
    qDebug() << fileName + ".pdf";
    attachPDF(fileName + ".pdf");
}

QString ContactSupportDialog::captureLogs()
{
    QDir dir("C:/ShareToUbuntu/logs");
    QStringList files = dir.entryList(QDir::NoDotAndDotDot | QDir::Files);
    qDebug() << files;
    QString fileDetails = "";

    fileDetails.append("LOG FILES");
    fileDetails.append("\n==========================================================");
    fileDetails.append("\n==========================================================\n");


    for (int i = 0; i < files.length(); i++){
        qDebug() << files[i];
        QFile file("C:/ShareToUbuntu/logs/" + files[i]);
        fileDetails.append("FILE NAME:\t" + files[i]);
        fileDetails.append("\n==========================================================\n");
        QFileInfo fileInfo(file);
        QDateTime dateTimeA = fileInfo.lastModified();
        QString dateTimeB = dateTimeA.toString();
        fileDetails.append("DATE LAST MODIFIED:\t" + dateTimeB);
        fileDetails.append("\n==========================================================\n");
        fileDetails.append("FILE CONTENT:\n==========================================================\n");
        if (file.open(QIODevice::ReadOnly|QIODevice::Text)){
            QTextStream in(&file);
            QString fileText = in.readAll();
            fileDetails.append(fileText);
        } else{
            fileDetails.append("Log Details Unrecoverable");
        }
        fileDetails.append("==========================================================");
        fileDetails.append("\n\n");
    }
    return fileDetails;
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
            sendMail();
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

void ContactSupportDialog::sendMail()
{
//    qDebug() << "in sendMail";
    Smtp *smtp = new Smtp("hutempcs@gmail.com", "|WjzL]sa[|3", "smtp.gmail.com", 465);
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

    if(!files.isEmpty()){
//        qDebug() << "!files.isEmpty()";
        smtp->sendMail("hutempcs@gmail.com", "hutempcs@gmail.com" , ui->ContactSupportDialogCategoryComboBox->currentText(),"REVIEW ATTACHMENT(S)", files );
    } else{
//        qDebug() << "files.isEmpty()";
        smtp->sendMail("hutempcs@gmail.com", "hutempcs@gmail.com" , ui->ContactSupportDialogCategoryComboBox->currentText(),"REVIEW ATTACHMENT(S)");
    }
}

void ContactSupportDialog::mailSent(QString status)
{
    if(status == "Message sent"){
        QMessageBox::warning(this, "Contact Support", "Message sent!");
    }
}

void ContactSupportDialog::attachPDF(QString fileName)
{
    files.append(fileName);
}
