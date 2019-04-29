#include "contactsupportdialog.h"
#include "ui_contactsupportdialog.h"
#include <QFileDialog>
#include <QDialogButtonBox>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QPrinter>
#include <QMessageBox>
#include <fileapi.h>

ContactSupportDialog::ContactSupportDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ContactSupportDialog)
{
    ui->setupUi(this);

    setWindowTitle("Contact Support");
    adjustSize();
}

ContactSupportDialog::~ContactSupportDialog()
{
    delete ui;
}


void ContactSupportDialog::writeToPDF(Ui::ContactSupportDialog *ui)
{
    QString createdDirectory = QCoreApplication::applicationDirPath() + "/ContactSupportLogs";
    QDir dir;
    dir.mkdir(createdDirectory);
    SetFileAttributesA(createdDirectory.toStdString().c_str(), FILE_ATTRIBUTE_HIDDEN);

    QString fileName = createdDirectory + "Test.txt";
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
    pdfFile.setOutputFileName(createdDirectory + "/Test.pdf");
    doc.print(&pdfFile);
}



void ContactSupportDialog::on_ContactSupportDialogButtonBox_clicked(QAbstractButton *button)
{
    QDialogButtonBox::StandardButton stdButton = ui->ContactSupportDialogButtonBox->standardButton(button);

    if(stdButton == QDialogButtonBox::Ok){
        writeToPDF(ui);
        accept();
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
