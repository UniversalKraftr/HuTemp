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
    setAllDefaults();
}

AdditionalAdminSettingsDialog::~AdditionalAdminSettingsDialog()
{
    delete ui;
}

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

            file.close();
        } else{
            qDebug() << "File currently does not exist";
        }
    }
}

void AdditionalAdminSettingsDialog::setAllDefaults()
{
    setTabOrder(ui->AdditionalAdminSettingsDialogCompanyNameLineEdit, ui->AdditionalAdminSettingsDialogCompanyAddressLine1LineEdit);
    setTabOrder(ui->AdditionalAdminSettingsDialogCompanyAddressLine1LineEdit, ui->AdditionalAdminSettingsDialogCompanyAddressLine2LineEdit);
    setTabOrder(ui->AdditionalAdminSettingsDialogCompanyAddressLine2LineEdit, ui->AdditionalAdminSettingsDialogCompanyPhoneNumberLineEdit);
    ui->AdditionalAdminSettingsDialogCompanyNameLineEdit->setFocus();

    ui->AdditionalAdminSettingsDialogDataLoggerChangesCheckBox->setChecked(true);
    ui->AdditionalAdminSettingsDialogDataLoggerChangesCheckBox->setEnabled(false);

    ui->AdditionalAdminSettingsDialogReportExportCheckBox->setChecked(true);
    ui->AdditionalAdminSettingsDialogReportExportCheckBox->setEnabled(false);

    ui->AdditionalAdminSettingsDialogProfileChangesCheckBox->setChecked(true);
    ui->AdditionalAdminSettingsDialogProfileChangesCheckBox->setEnabled(false);

    ui->AdditionalAdminSettingsDialogLoginActivityCheckBox->setChecked(true);
    ui->AdditionalAdminSettingsDialogLoginActivityCheckBox->setEnabled(false);

    ui->AdditionalAdminSettingsDialogSupportContactedCheckBox->setChecked(true);
    ui->AdditionalAdminSettingsDialogSupportContactedCheckBox->setEnabled(false);

    ui->AdditionalAdminSettingsDialogUserAdjustedSettingsCheckBox->setChecked(true);
    ui->AdditionalAdminSettingsDialogUserAdjustedSettingsCheckBox->setEnabled(false);
}
