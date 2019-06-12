#include "previousdevices.h"
#include "ui_previousdevices.h"
#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>

PreviousDevices::PreviousDevices(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PreviousDevices)
{
    ui->setupUi(this);


    setWindowTitle("Archived Devices");
    setWindowIcon(QIcon("://icons/logo_O9H_2.ico"));
    adjustSize();
    populateListWidget();
}

PreviousDevices::~PreviousDevices()
{
    delete ui;
}

void PreviousDevices::on_archivedDevicesRestoreButton_clicked()
{
    QString sensorID = ui->archivedDevicesListWidget->currentItem()->text();
    QSqlQuery updateQuery;
    QString updateQueryStatement = QString("UPDATE config SET activestatus = 1 WHERE sensorID = '%1'").arg(sensorID);
    if (updateQuery.exec(updateQueryStatement)){
        QMessageBox::information(this, tr("Device Restored"), "Your selected device has been restored. It will appear in your table momentarily.");
    } else{
        QMessageBox::warning(this, tr("Restore Error"), "An error occurred. Please try again later.");
    }
    accept();
}

void PreviousDevices::on_archivedDevicesExitButton_clicked()
{
    reject();
}

void PreviousDevices::populateListWidget()
{
    if (ui->archivedDevicesListWidget->count() > 0){
        ui->archivedDevicesListWidget->clear();
    }

    QSqlQuery selectQuery;
    QString selectQueryStatement = "SELECT sensorID FROM config WHERE activestatus = 0";
    if (selectQuery.exec(selectQueryStatement)){
        while(selectQuery.next()){
            QString sensorID = selectQuery.value(0).toString();
            ui->archivedDevicesListWidget->addItem(sensorID);
        }
    }
}
