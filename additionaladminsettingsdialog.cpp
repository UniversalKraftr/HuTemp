#include "additionaladminsettingsdialog.h"
#include "ui_additionaladminsettingsdialog.h"
#include "widget.h"
#include <QFile>
#include <QTextStream>
#include <QTextDocument>

AdditionalAdminSettingsDialog::AdditionalAdminSettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdditionalAdminSettingsDialog)
{
    ui->setupUi(this);

    setWindowTitle("Additional Administrator Settings");
    adjustSize();
    extractFromLogFile();
}

AdditionalAdminSettingsDialog::~AdditionalAdminSettingsDialog()
{
    delete ui;
}

//int AdditionalAdminSettingsDialog::getOpenTimeMinute()
//{
//    return ui->AdditionalAdminSettingsDialogOpenTimeTimeEdit->time().minute();
//}

//int AdditionalAdminSettingsDialog::getOpenTimeHour()
//{
//    return ui->AdditionalAdminSettingsDialogOpenTimeTimeEdit->time().hour();
//}

//int AdditionalAdminSettingsDialog::getCloseTimeHour()
//{
//    return ui->AdditionalAdminSettingsDialogClosingTimeTimeEdit->time().hour();
//}

//int AdditionalAdminSettingsDialog::getCloseTimeMinute()
//{
//    return ui->AdditionalAdminSettingsDialogClosingTimeTimeEdit->time().minute();;
//}

//QString AdditionalAdminSettingsDialog::getCompanyName()
//{
//    return ui->AdditionalAdminSettingsDialogCompanyNameLineEdit->text();
//}

//QString AdditionalAdminSettingsDialog::getCompanyAddress()
//{
//    QString companyAddress = ui->AdditionalAdminSettingsDialogCompanyAddressLine1LineEdit->text() + QString("\n") +
//            ui->AdditionalAdminSettingsDialogCompanyAddressLine2LineEdit->text();
//    return companyAddress;
//}

//QString AdditionalAdminSettingsDialog::getCompanyPhoneNumber()
//{
//    return ui->AdditionalAdminSettingsDialogCompanyPhoneNumberLineEdit->text();
//}

void AdditionalAdminSettingsDialog::on_AdditionalAdminSettingsDialogButtonBox_clicked(QAbstractButton *button)
{
    QDialogButtonBox::StandardButton adminSettingsStdButton = ui->AdditionalAdminSettingsDialogButtonBox->standardButton(button);

    if(adminSettingsStdButton == QDialogButtonBox::Ok){
        writeToLogFile();
        accept();
    }
    if(adminSettingsStdButton == QDialogButtonBox::Cancel){
        reject();
    }
}

void AdditionalAdminSettingsDialog::writeToLogFile()
{
    Widget *widget = new Widget();
    QString fileName = widget->getLogFolder() + "/CompanyInfo.txt";
    QFile file(fileName);
    if (file.exists()){
        file.remove();
    }
    if(file.open(QIODevice::ReadWrite)){
        QTextStream stream(&file);
        stream << ui->AdditionalAdminSettingsDialogCompanyNameLineEdit->text() << endl;
        stream << ui->AdditionalAdminSettingsDialogCompanyAddressLine1LineEdit->text() << endl;
        stream << ui->AdditionalAdminSettingsDialogCompanyAddressLine2LineEdit->text() << endl;
        stream << ui->AdditionalAdminSettingsDialogCompanyPhoneNumberLineEdit->text() << endl;
        stream << ui->AdditionalAdminSettingsDialogOpenTimeTimeEdit->time().toString() << endl;
        stream << ui->AdditionalAdminSettingsDialogClosingTimeTimeEdit->time().toString() << endl;
    }
    else if (!file.open(QIODevice::ReadWrite)){
        qDebug() << "failed to open";
    }
    file.close();

}

void AdditionalAdminSettingsDialog::extractFromLogFile()
{
    Widget *widget = new Widget();
    QString fileName = widget->getLogFolder() + "/CompanyInfo.txt";
    QFile file(fileName);
    if (!file.exists()){
        qDebug() << "file does not exist";
    } else{
        if (file.open(QIODevice::ReadOnly)){
            QTextStream in(&file);
            QString myFileText = in.readAll();
            qDebug() << myFileText;
            QStringList myText = myFileText.split("\n");
            qDebug() << myText;
            ui->AdditionalAdminSettingsDialogCompanyNameLineEdit->setText(myText[0]);
            ui->AdditionalAdminSettingsDialogCompanyAddressLine1LineEdit->setText(myText[1]);
            ui->AdditionalAdminSettingsDialogCompanyAddressLine2LineEdit->setText(myText[2]);
            ui->AdditionalAdminSettingsDialogCompanyPhoneNumberLineEdit->setText(myText[3]);
            QList<QString> timeList =  myText[4].split(":");
            ui->AdditionalAdminSettingsDialogOpenTimeTimeEdit->setTime(QTime(timeList[0].toInt(), timeList[1].toInt()));
            timeList = myText[5].split(":");
            ui->AdditionalAdminSettingsDialogClosingTimeTimeEdit->setTime(QTime(timeList[0].toInt(), timeList[1].toInt()));
        } else{
            qDebug() << "File currently does not exist";
        }
    }



//    QTextDocument doc;
//    QFile file2(fileName);
//    if (file2.open(QIODevice::ReadOnly|QIODevice::Text)){

//        QTextStream in(&file2);
//        QString myText = in.readAll();
//        doc.setPlainText(myText);
//    }

//    file2.remove();
}

//void AdditionalAdminSettingsDialog::setOpenTime(int hour, int minute)
//{
//    ui->AdditionalAdminSettingsDialogOpenTimeTimeEdit->setTime(QTime(hour, minute));
//}

//void AdditionalAdminSettingsDialog::setCloseTime(int hour, int minute)
//{
//    ui->AdditionalAdminSettingsDialogClosingTimeTimeEdit->setTime(QTime(hour, minute));
//}

//void AdditionalAdminSettingsDialog::setCompanyName(QString cname)
//{
//    ui->AdditionalAdminSettingsDialogCompanyNameLineEdit->setText(cname);
//}

//void AdditionalAdminSettingsDialog::setCompanyAddress(QString caddress)
//{
//    QString line1 = caddress.split('\n').front();
//    QString line2 = caddress.split('\n').back();
//    ui->AdditionalAdminSettingsDialogCompanyAddressLine1LineEdit->setText(line1);
//    ui->AdditionalAdminSettingsDialogCompanyAddressLine2LineEdit->setText(line2);
//}

//void AdditionalAdminSettingsDialog::setCompanyPhoneNumber(QString cnumber)
//{
//    ui->AdditionalAdminSettingsDialogCompanyPhoneNumberLineEdit->setText(cnumber);
//}
