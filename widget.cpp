#include "widget.h"
#include "ui_widget.h"

#include "devicesdialogbox.h"
#include "periodsdialogbox.h"
#include "quickviewsdialogbox.h"
#include "readingsdialogbox.h"
#include "zonesdialogbox.h"
#include "helpdialog.h"
#include "previoususersdialog.h"
#include "passwordreset.h"
#include "newpasswordpostresetdialog.h"
#include <QDir>
#include <fileapi.h>

#include <QHostAddress>
#include <QNetworkInterface>





Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWidgetConfigs();
}

QString Widget::getLogFolder()
{
    return logsDirectory;
}

QString Widget::getPDFFolder()
{
    return pdfDirectory;
}

Widget::~Widget()
{
    delete ui;
}

void Widget::setWidgetConfigs()
{
    connectToDatabase();
    setWindowTitle(title);
    QRect rect = QGuiApplication::primaryScreen()->geometry();
    int screenHeight = rect.height();
    int screenWidth = rect.width();

    //set widget to 80% of screen size
    int widgetHeight = qCeil(screenHeight*.80);
    int widgetWidth = qCeil(screenWidth*.80);
    setFixedSize(widgetWidth, widgetHeight);


    //set tab widget and tabs geometries
    setTabWidgetConfigs(widgetWidth, widgetHeight);

    //set login tab geometries
    setLoginTabConfigs();

    //set UAC tab geometries
    setUACTabConfigs();

    //set devices tab geometries
    setDevicesTabConfigs();

    //set reports tab geometries
    setReportsTabConfigs();

    //set settings tab geometries
    setSettingsTabConfigs();

    //set default program upon opening
    setAllDefaultsOff();

    createDirectories();
}

void Widget::setTabWidgetConfigs(int widgetWidth, int widgetHeight)
{
    //set tab widgets and tabs to width(99%) and height(98%) of widget size
    ui->mainTabsWidget->setFixedSize(qCeil(widgetWidth*.99), qCeil(widgetHeight*.98));
    ui->loginTab->setFixedSize(qCeil(widgetWidth*.99), qCeil(widgetHeight*.98));
    ui->UACTab->setFixedSize(qCeil(widgetWidth*.99), qCeil(widgetHeight*.98));
    ui->devicesTab->setFixedSize(qCeil(widgetWidth*.99), qCeil(widgetHeight*.98));
    ui->reportsTab->setFixedSize(qCeil(widgetWidth*.99), qCeil(widgetHeight*.98));
    ui->settingsTab->setFixedSize(qCeil(widgetWidth*.99), qCeil(widgetHeight*.98));
//    ui->tabWidget->setFixedSize(qCeil(widgetWidth*.99), qCeil(widgetHeight*.98));

}

void Widget::setLoginTabConfigs()
{
    //set loginScreenViewsStack to loginTab size
    int loginTabWidth = ui->loginTab->width();
    int loginTabHeight = ui->loginTab->height();
    ui->loginScreenViewsStack->setFixedSize(qCeil(loginTabWidth*.99), qCeil(loginTabHeight*.98));
    ui->loginScreenPageNestedWidget->setFixedSize(ui->loginScreenViewsStack->width(), ui->loginScreenViewsStack->height());
    ui->logoutScreenPageNestedWidget->setFixedSize(ui->loginScreenViewsStack->width(), ui->loginScreenViewsStack->height());

}

void Widget::setUACTabConfigs()
{
    //set UACScreenViewsStack to UACTab size
    int UACTabWidth = ui->UACTab->width();
    int UACTabHeight = ui->UACTab->height();
    ui->UACScreenViewsStack->setFixedSize(qCeil(UACTabWidth*.99), qCeil(UACTabHeight*.98));
    ui->UACadminViewScreenPageNestedWidget->setFixedSize(ui->UACScreenViewsStack->width(), ui->UACScreenViewsStack->height());
    ui->UACuserViewScreenPageNestedWidget->setFixedSize(ui->UACScreenViewsStack->width(), ui->UACScreenViewsStack->height());
    for(int i = 0; i < ui->UACTableWidget->columnCount(); i++){
        ui->UACTableWidget->setColumnWidth(i, 120);
    }
    ui->UACTableWidget->setAlternatingRowColors(true);
    ui->UACadminViewScreenPageNestedWidgetEditButton->setEnabled(false);
    ui->UACadminViewScreenPageNestedWidgetSaveButton->setEnabled(false);
    populateUACTableWidget();
}

void Widget::setDevicesTabConfigs()
{
    ui->devicesTabNestedWidget->setFixedSize(ui->devicesTab->width(), ui->devicesTab->height());
    for(int i = 0; i < ui->devicesTabTableWidget->columnCount(); i++){
//        qDebug() << "column width = " << ui->devicesTabTableWidget->columnWidth(i);
        ui->devicesTabTableWidget->setColumnWidth(i, 120);
    }
    ui->devicesTabTableWidget->horizontalHeaderItem(0)->setText("Zone\nID");
    ui->devicesTabTableWidget->horizontalHeaderItem(1)->setText("Device\nID");
    ui->devicesTabTableWidget->horizontalHeaderItem(2)->setText("Connectivity\nStatus");
    ui->devicesTabTableWidget->horizontalHeaderItem(3)->setText("Active\nStatus");
    ui->devicesTabTableWidget->horizontalHeaderItem(4)->setText("Reading\nInterval");
    ui->devicesTabTableWidget->horizontalHeaderItem(5)->setText("Date/\nTime");
    ui->devicesTabTableWidget->horizontalHeaderItem(6)->setText("Temperature\n(°F)");
    ui->devicesTabTableWidget->horizontalHeaderItem(7)->setText("Humidity\n(%)");
    ui->devicesTabTableWidget->horizontalHeaderItem(8)->setText("Low\nTemperature\n(°F)");
    ui->devicesTabTableWidget->horizontalHeaderItem(9)->setText("High\nTemperature\n(°F)");
    ui->devicesTabTableWidget->horizontalHeaderItem(10)->setText("Low\nHumidity\n(%)");
    ui->devicesTabTableWidget->horizontalHeaderItem(11)->setText("High\nHumidity\n(%)");
    ui->devicesTabTableWidget->horizontalHeaderItem(12)->setText("Power");

    ui->devicesTabUpdateButton->setEnabled(false);
    ui->devicesTabDeleteButton->setEnabled(false);

    ui->devicesTabTableWidget->setSortingEnabled(true);
    ui->devicesTabTableWidget->setAlternatingRowColors(true);
    populateDevicesTableWidget();
}

void Widget::setReportsTabConfigs()
{
    ui->reportsTabNestedWidget->setFixedSize(ui->reportsTab->width(), ui->reportsTab->height());
    ui->reportsTabNestedWidgetEndDateDateEdit->setDate(QDate::currentDate());
    ui->reportsTabNestedWidgetStartDateDateEdit->setCalendarPopup(true);
    ui->reportsTabNestedWidgetEndDateDateEdit->setCalendarPopup(true);
    ui->reportsTabNestedWidgetTableWidget->setAlternatingRowColors(true);

}

void Widget::setSettingsTabConfigs()
{
    ui->settingsTabNestedWidget->setFixedSize(ui->settingsTab->width(), ui->settingsTab->height());
}

void Widget::setAllDefaultsOff()
{
    ui->mainTabsWidget->setCurrentIndex(0);
    ui->loginScreenViewsStack->setCurrentIndex(0);

    ui->mainTabsWidget->setTabEnabled(1, false);
    ui->UACScreenViewsStack->setCurrentIndex(0);
    ui->UACuserViewScreenPageNestedWidgetUserProfileToolToAdminViewButton->setEnabled(false);

    ui->mainTabsWidget->setTabEnabled(2, false);
    ui->devicesTabAddButton->setEnabled(false);
    ui->devicesTabUpdateButton->setEnabled(false);
    ui->devicesTabDeleteButton->setEnabled(false);
    ui->UACuserViewScreenPageNestedWidgetDevicesCheckBox->setChecked(false);
    ui->UACuserViewScreenPageNestedWidgetAddCheckBox->setChecked(false);
    ui->UACuserViewScreenPageNestedWidgetModifyCheckBox->setChecked(false);
    ui->UACuserViewScreenPageNestedWidgetRemoveCheckBox->setChecked(false);

    ui->mainTabsWidget->setTabEnabled(3, false);
    ui->UACuserViewScreenPageNestedWidgetReportsCheckBox->setChecked(false);
    ui->UACuserViewScreenPageNestedWidgetEmailCheckBox->setChecked(false);

    ui->mainTabsWidget->setTabEnabled(4, false);
    ui->settingsTabNestedWidgetnotificationsPushButton->setEnabled(false);
    ui->settingsTabNestedWidgetnetworkPushButton->setEnabled(false);
    ui->UACuserViewScreenPageNestedWidgetSettingsCheckBox->setChecked(false);
    ui->UACuserViewScreenPageNestedWidgetNotificationsCheckBox->setChecked(false);
    ui->UACuserViewScreenPageNestedWidgetNetworkCheckBox->setChecked(false);
}

void Widget::populateUACTableWidget()
{
//    qDebug() << "in populateUACTableWidget()";
    if (ui->UACTableWidget->rowCount() > 0){
//        qDebug() << "rowCount() > 0";
        ui->UACTableWidget->clearContents();
        ui->UACTableWidget->setRowCount(0);
    }
    QSqlQuery getUserTableQuery;
    QString selectStatement = "SELECT * FROM users WHERE activestatus = 1";
    if (getUserTableQuery.exec(selectStatement)){
//        qDebug() << "query successful";


//    int rowCount = 0;
        if (getUserTableQuery.size() > 0){
//            qDebug() << "userTable size > 0";
            while (getUserTableQuery.next()){
//                qDebug() << "getUserTableQuery.next()";
    //            rowCount += 1;
    //            qDebug() << ui->UACTableWidget->rowCount();
                ui->UACTableWidget->insertRow(ui->UACTableWidget->rowCount());
//                qDebug() << "ui->UACTableWidget->rowCount() = " << ui->UACTableWidget->rowCount();
//                qDebug() << "monitorAdminIndexRow = " << monitorAdminIndexRow;


                QString firstName = getUserTableQuery.value(1).toString();
                QString lastName = getUserTableQuery.value(2).toString();
                QTableWidgetItem *userName = new QTableWidgetItem(firstName + " " + lastName);
                QTableWidgetItem *userEmailItem = new QTableWidgetItem(getUserTableQuery.value(4).toString());
                QTableWidgetItem *userNumber = new QTableWidgetItem(getUserTableQuery.value(6).toString());
                QTableWidgetItem *userHireDate = new QTableWidgetItem(getUserTableQuery.value(5).toString());
                userName->setFlags(Qt::NoItemFlags);
                userEmailItem->setFlags(Qt::NoItemFlags);
                userNumber->setFlags(Qt::NoItemFlags);
                userHireDate->setFlags(Qt::NoItemFlags);
                ui->UACTableWidget->setItem(ui->UACTableWidget->rowCount()-1,0, userName);
                ui->UACTableWidget->setItem(ui->UACTableWidget->rowCount()-1, 11, userEmailItem);
                ui->UACTableWidget->setItem(ui->UACTableWidget->rowCount()-1, 12, userNumber);
                ui->UACTableWidget->setItem(ui->UACTableWidget->rowCount()-1, 13, userHireDate);

                QString binary = convertToBinary(getUserTableQuery.value(7).toString());
                for (int i = 0; i < binary.count(); i++){
//                    qDebug() << "permissions being set";
                    QWidget *checkBoxWidget = new QWidget();
                    QCheckBox *checkBox = new QCheckBox();
                    QHBoxLayout *layout = new QHBoxLayout(checkBoxWidget);
                    if (binary[i] == '1'){
                        checkBox->setCheckState(Qt::Checked);
                    } else if (binary[i] == '0'){
                        checkBox->setCheckState(Qt::Unchecked);
                    }
                    checkBox->setEnabled(false);
                    checkBox->setObjectName("checkbox");
                    layout->addWidget(checkBox);
                    layout->setAlignment(Qt::AlignCenter);
                    layout->setContentsMargins(0,0,0,0);
                    checkBoxWidget->setLayout(layout);
                    ui->UACTableWidget->setCellWidget(ui->UACTableWidget->rowCount()-1, i+1, checkBoxWidget);
                }

                QWidget *resetButtonWidget = new QWidget();
                QPushButton *resetButton = new QPushButton();
                resetButton->setText("Reset Password");
                QHBoxLayout *resetButtonlayout = new QHBoxLayout(resetButtonWidget);
                connect(resetButton, &QPushButton::clicked, this, &Widget::resetPassword, Qt::UniqueConnection);
                resetButtonlayout->addWidget(resetButton);
                resetButtonlayout->setAlignment(Qt::AlignCenter);
                resetButtonlayout->setContentsMargins(0,0,0,0);
                resetButtonWidget->setLayout(resetButtonlayout);
                resetButtonWidget->setEnabled(false);
                ui->UACTableWidget->setCellWidget(ui->UACTableWidget->rowCount()-1, 14, resetButtonWidget);
//                qDebug() << "after reset button created";

                QWidget *deleteButtonWidget = new QWidget();
                QPushButton *deleteButton = new QPushButton();
                deleteButton->setText("Delete");
                QHBoxLayout *deleteButtonlayout = new QHBoxLayout(deleteButtonWidget);
                connect(deleteButton, &QPushButton::clicked, this, &Widget::archiveUser, Qt::UniqueConnection);
                deleteButtonlayout->addWidget(deleteButton);
                deleteButtonlayout->setAlignment(Qt::AlignCenter);
                deleteButtonlayout->setContentsMargins(0,0,0,0);
                deleteButtonWidget->setLayout(deleteButtonlayout);
                deleteButtonWidget->setEnabled(false);
                ui->UACTableWidget->setCellWidget(ui->UACTableWidget->rowCount()-1, 15, deleteButtonWidget);
//                qDebug() << "after delete button created";
            }
        }
    } else{
        qDebug() << "query failed";
    }
    //    qDebug() << "user added";
}

void Widget::populateDevicesTableWidget()
{
//    qDebug() << "in populateDevicesTableWidget()";
    if (ui->devicesTabTableWidget->rowCount() > 0){
        ui->devicesTabTableWidget->clearContents();
        ui->devicesTabTableWidget->setRowCount(0);
    }

    QSqlQuery selectConfigQuery;
    QString selectConfigQueryStatement = "SELECT * FROM config";



    if (selectConfigQuery.exec(selectConfigQueryStatement)){
//        qDebug() << "selectConfigQuery successful";
//        qDebug() << selectConfigQuery.size();


        while (selectConfigQuery.next()){
//            qDebug() << "in selectConfigQuery.next()";
            ui->devicesTabTableWidget->insertRow(ui->devicesTabTableWidget->rowCount());
            QString deviceID = selectConfigQuery.value(4).toString();//
            QString interval = selectConfigQuery.value(6).toString();//
            QString zoneID = selectConfigQuery.value(7).toString();//
            QString highTempThreshold = selectConfigQuery.value(8).toString();
            QString lowTempThreshold = selectConfigQuery.value(9).toString();
            QString highHumidityThreshold = selectConfigQuery.value(10).toString();
            QString lowHumidityThreshold = selectConfigQuery.value(11).toString();

            QTableWidgetItem *zoneIDItem = new QTableWidgetItem(zoneID);
            zoneIDItem->setTextAlignment(Qt::AlignCenter);
//            zoneIDItem->setFlags(Qt::ItemIsEditable);
            QTableWidgetItem *deviceIDItem = new QTableWidgetItem(deviceID);
            deviceIDItem->setTextAlignment(Qt::AlignCenter);
//            deviceIDItem->setFlags(Qt::ItemIsEditable);
            QTableWidgetItem *intervalItem = new QTableWidgetItem(interval);
            intervalItem->setTextAlignment(Qt::AlignCenter);
//            intervalItem->setFlags(Qt::ItemIsEditable);
            QTableWidgetItem *highTempThresholdItem = new QTableWidgetItem(highTempThreshold);
            highTempThresholdItem->setTextAlignment(Qt::AlignCenter);
//            highTempThresholdItem->setFlags(Qt::ItemIsEditable);
            QTableWidgetItem *lowTempThresholdItem = new QTableWidgetItem(lowTempThreshold);
            lowTempThresholdItem->setTextAlignment(Qt::AlignCenter);
//            lowTempThresholdItem->setFlags(Qt::ItemIsEditable);
            QTableWidgetItem *highHumidityThresholdItem = new QTableWidgetItem(highHumidityThreshold);
            highHumidityThresholdItem->setTextAlignment(Qt::AlignCenter);
//            highHumidityThresholdItem->setFlags(Qt::ItemIsEditable);
            QTableWidgetItem *lowHumidityThresholdItem = new QTableWidgetItem(lowHumidityThreshold);
            lowHumidityThresholdItem->setTextAlignment(Qt::AlignCenter);
//            lowHumidityThresholdItem->setFlags(Qt::ItemIsEditable);

            QSqlQuery selectDataQuery;
            QString selectDataQueryStatment = QString("SELECT * FROM data WHERE MAC = '%1' ORDER BY event DESC LIMIT 1").arg(selectConfigQuery.value(1).toString());
            QString dateTimeData;//device table widget column: 5
            QString temperatureData;//device table widget column: 6
            QString humidityData;//device table widget column: 7
            QString powerLevelData;//device table widget column: 12
            //CALCULATION WILL HAVE 4.2 FOR THE HIGHEST, ANYTHING ABOVE WILL JUST READ 100%
            //STILL NEED THE LOW END TO GET THE PROPER CALCULATION FOR REFLECTING THE PERCENTAGE ACCURATELY
            //MOST LIKELY GOING TO BE 3.3, BUT GET CONFIRMATION FROM BRANDON
            //3.3 IS THE LOW END
            //THE EQUATION FOR DISPLAYING THE BATTERY PERCENTAGE IS AS FOLLOWS
            //100*((.9-(4.2-powerLevelData))/.9) -->round to 2 decimal places
            if (selectDataQuery.exec(selectDataQueryStatment)){
//                qDebug() << "selectDataQuery successful";
                while (selectDataQuery.next()){
//                    qDebug() << selectDataQuery.value(2).toString();
//                    qDebug() << selectDataQuery.value(4).toString();
//                    qDebug() << selectDataQuery.value(5).toString();
//                    qDebug() << selectDataQuery.value(6).toString();
                    dateTimeData = selectDataQuery.value(2).toString();
                    temperatureData = selectDataQuery.value(4).toString();
                    humidityData = selectDataQuery.value(5).toString();
                    powerLevelData = selectDataQuery.value(6).toString();
                }
            } else{
//                qDebug() << "selectDataQuery unsuccessful";
                continue;
            }


            QSqlQuery secondSelectDataQuery;
            QString secondSelectDataQueryStatement = QString("SELECT * FROM data WHERE MAC = '%1' ORDER BY event DESC LIMIT 2").arg(selectConfigQuery.value(1).toString());
            QStringList bothDateTimes;
            if (secondSelectDataQuery.exec(secondSelectDataQueryStatement)){
                while (secondSelectDataQuery.next()){
                    bothDateTimes.append(secondSelectDataQuery.value(2).toString());
                }
            }
//            qDebug() << "capturing top two date times of a device";
//            qDebug() << bothDateTimes;
//            QString firstDate = bothDateTimes[0].split('T').front();
//            QString firstTime = bothDateTimes[0].split('T').back();
//            QString secondDate = bothDateTimes[1].split('T').front();
//            QString secondTime = bothDateTimes[1].split('T').back();
//            qDebug () << "firstDate:\t" << firstDate;
//            qDebug() << "secondDate:\t" << secondDate;
//            qDebug() << "firstTime:\t" << firstTime;
//            qDebug() << "secondTime:\t" << secondTime;
//            QDate dateOne = QDate::fromString(firstDate, "yyyy-MM-dd");
//            QDate dateTwo = QDate::fromString(secondDate, "yyyy-MM-dd");
//            QTime timeOne = QTime::fromString(firstTime, "hh:mm:ss.zzz");
//            QTime timeTwo = QTime::fromString(secondTime, "hh:mm:ss.zzz");
//            qDebug() << "dateOne:\t" << dateOne;
//            qDebug() << "dateTwo:\t" << dateTwo;
//            qDebug() << "timeOne:\t" << timeOne;
//            qDebug() << "timeTwo:\t" << timeTwo << "\n";
            QDateTime firstDateTime = QDateTime::fromString(bothDateTimes[0], "yyyy-MM-ddThh:mm:ss.zzz");
            QDateTime secondDateTime = QDateTime::fromString(bothDateTimes[1], "yyyy-MM-ddThh:mm:ss.zzz");
//            qDebug() << "firstDateTime:\t" << firstDateTime;
//            qDebug() << "secondDateTime:\t" << secondDateTime;
            qint64 timeDiff = secondDateTime.secsTo(firstDateTime);
//            qDebug() << "timeDiff:\t" << timeDiff;
            int timeDiffConvertedToMinutes = timeDiff/60;

            QTableWidgetItem *connectivityItem;
            QTableWidgetItem *activeStatusItem;
            if (timeDiffConvertedToMinutes > interval){
                QString connectivityStatus = "Disconnected";
                QString activeStatus = "Inactive";
                connectivityItem = new QTableWidgetItem(connectivityStatus);
                activeStatusItem = new QTableWidgetItem(activeStatus);
            } else{
                QString connectivityStatus = "Connected";
                QString activeStatus = "Active";
                connectivityItem = new QTableWidgetItem(connectivityStatus);
                activeStatusItem = new QTableWidgetItem(activeStatus);
            }

            QDateTime dateTime = QDateTime::fromString(dateTimeData, "yyyy-MM-ddTHH:mm:ss.zzz");
            QString inputDateTime = dateTime.date().toString() + "\n" + dateTime.time().toString();

            connectivityItem->setTextAlignment(Qt::AlignCenter);
            connectivityItem->setFlags(Qt::NoItemFlags);

            activeStatusItem->setTextAlignment(Qt::AlignCenter);
            activeStatusItem->setFlags(Qt::NoItemFlags);

            QTableWidgetItem *dateTimeDataItem = new QTableWidgetItem(inputDateTime);
            dateTimeDataItem->setTextAlignment(Qt::AlignCenter);
            dateTimeDataItem->setFlags(Qt::NoItemFlags);

            QTableWidgetItem *temperatureDataItem = new QTableWidgetItem(temperatureData);
            temperatureDataItem->setTextAlignment(Qt::AlignCenter);
            temperatureDataItem->setFlags(Qt::NoItemFlags);

            QTableWidgetItem *humidityDataItem = new QTableWidgetItem(humidityData);
            humidityDataItem->setTextAlignment(Qt::AlignCenter);
            humidityDataItem->setFlags(Qt::NoItemFlags);

            QTableWidgetItem *powerLevelDataItem = new QTableWidgetItem(powerLevelData);
            powerLevelDataItem->setTextAlignment(Qt::AlignCenter);
            powerLevelDataItem->setFlags(Qt::NoItemFlags);

            ui->devicesTabTableWidget->setItem(ui->devicesTabTableWidget->rowCount()-1, 0, zoneIDItem);
            ui->devicesTabTableWidget->setItem(ui->devicesTabTableWidget->rowCount()-1, 1, deviceIDItem);
            ui->devicesTabTableWidget->setItem(ui->devicesTabTableWidget->rowCount()-1, 2, connectivityItem);
            ui->devicesTabTableWidget->setItem(ui->devicesTabTableWidget->rowCount()-1, 3, activeStatusItem);
            ui->devicesTabTableWidget->setItem(ui->devicesTabTableWidget->rowCount()-1, 4, intervalItem);
            ui->devicesTabTableWidget->setItem(ui->devicesTabTableWidget->rowCount()-1, 5, dateTimeDataItem);
            ui->devicesTabTableWidget->setItem(ui->devicesTabTableWidget->rowCount()-1, 6, temperatureDataItem);
            ui->devicesTabTableWidget->setItem(ui->devicesTabTableWidget->rowCount()-1, 7, humidityDataItem);
            ui->devicesTabTableWidget->setItem(ui->devicesTabTableWidget->rowCount()-1, 8, lowTempThresholdItem);
            ui->devicesTabTableWidget->setItem(ui->devicesTabTableWidget->rowCount()-1, 9, highTempThresholdItem);
            ui->devicesTabTableWidget->setItem(ui->devicesTabTableWidget->rowCount()-1, 10, lowHumidityThresholdItem);
            ui->devicesTabTableWidget->setItem(ui->devicesTabTableWidget->rowCount()-1, 11, highHumidityThresholdItem);
            ui->devicesTabTableWidget->setItem(ui->devicesTabTableWidget->rowCount()-1, 12, powerLevelDataItem);
        }
    }
}

void Widget::populateReportsTableWidget()
{
    QDateTime startDateTime = QDateTime(ui->reportsTabNestedWidgetStartDateDateEdit->date(), ui->reportsTabNestedWidgetStartTimeTimeEdit->time());
    QDateTime endDateTime = QDateTime(ui->reportsTabNestedWidgetEndDateDateEdit->date(), ui->reportsTabNestedWidgetEndTimeTimeEdit->time());

    QString start = startDateTime.toString();
    QString end = endDateTime.toString();

    QSqlQuery selectDataQuery;
    QString selectDataQueryStatement = QString("SELECT * FROM data");
    if (selectDataQuery.exec(selectDataQueryStatement)){
        while (selectDataQuery.next()){
            ui->reportsTabNestedWidgetTableWidget->insertRow(ui->reportsTabNestedWidgetTableWidget->rowCount());

            QString deviceIDColumn = selectDataQuery.value(3).toString();
            QString dateTimeColumn = selectDataQuery.value(2).toString();
            QString temperatureColumn = selectDataQuery.value(4).toString();
            QString humidityColumn = selectDataQuery.value(5).toString();

            QTableWidgetItem *deviceIDItem = new QTableWidgetItem(deviceIDColumn);
            deviceIDItem->setTextAlignment(Qt::AlignCenter);
            deviceIDItem->setFlags(Qt::NoItemFlags);

            QTableWidgetItem *temperatureItem = new QTableWidgetItem(temperatureColumn);
            temperatureItem->setTextAlignment(Qt::AlignCenter);
            temperatureItem->setFlags(Qt::NoItemFlags);

            QTableWidgetItem *humidityItem = new QTableWidgetItem(humidityColumn);
            humidityItem->setTextAlignment(Qt::AlignCenter);
            humidityItem->setFlags(Qt::NoItemFlags);

            QDateTime dateTime = QDateTime::fromString(dateTimeColumn, "yyyy-MM-ddThh:mm:ss.zzz");
            qDebug() << "dateTime.secsTo(startDateTime):\t" << dateTime.secsTo(startDateTime)/60;
            qDebug() << "dateTime.secsTo(endDateTime):\t" << dateTime.secsTo(endDateTime)/60;
            qDebug() << "startDateTime.secsTo(dateTime):\t" << startDateTime.secsTo(dateTime)/60;
            qDebug() << "endDateTime.secsTo(dateTime):\t" << endDateTime.secsTo(dateTime)/60;


            QString inputDateTime = dateTime.date().toString() + " " + dateTime.time().toString();
            QTableWidgetItem *dateTimeItem = new QTableWidgetItem(inputDateTime);
            dateTimeItem->setTextAlignment(Qt::AlignCenter);
            dateTimeItem->setFlags(Qt::NoItemFlags);


            QString zoneIDColumn;
            QString intervalColumn;
            QSqlQuery selectConfigQuery;
            QString selectConfigQueryStatement = QString("SELECT * FROM config WHERE sensorID = '%1'").arg(deviceIDColumn);
            if (selectConfigQuery.exec(selectConfigQueryStatement)){
                while (selectConfigQuery.next()){
                    zoneIDColumn = selectConfigQuery.value(7).toString();
                    intervalColumn = selectConfigQuery.value(6).toString();
                }
            }

            QTableWidgetItem *zoneIDItem = new QTableWidgetItem(zoneIDColumn);
            zoneIDItem->setTextAlignment(Qt::AlignCenter);
            zoneIDItem->setFlags(Qt::NoItemFlags);

            QTableWidgetItem *intervalItem = new QTableWidgetItem(intervalColumn);
            intervalItem->setTextAlignment(Qt::AlignCenter);
            intervalItem->setFlags(Qt::NoItemFlags);


            ui->reportsTabNestedWidgetTableWidget->setItem(ui->reportsTabNestedWidgetTableWidget->rowCount()-1, 0, zoneIDItem);
            ui->reportsTabNestedWidgetTableWidget->setItem(ui->reportsTabNestedWidgetTableWidget->rowCount()-1, 1, deviceIDItem);
            ui->reportsTabNestedWidgetTableWidget->setItem(ui->reportsTabNestedWidgetTableWidget->rowCount()-1, 2, intervalItem);
            ui->reportsTabNestedWidgetTableWidget->setItem(ui->reportsTabNestedWidgetTableWidget->rowCount()-1, 3, dateTimeItem);
            ui->reportsTabNestedWidgetTableWidget->setItem(ui->reportsTabNestedWidgetTableWidget->rowCount()-1, 4, temperatureItem);
            ui->reportsTabNestedWidgetTableWidget->setItem(ui->reportsTabNestedWidgetTableWidget->rowCount()-1, 5, humidityItem);
        }
    }
}


void Widget::monitorAdminStatus()
{
//    qDebug() << "in monitorAdminStatus";
//    qDebug() << "current index is: " << monitorAdminIndexRow;
    QWidget *widget = ui->UACTableWidget->cellWidget(monitorAdminIndexRow, 5);
    monitorAdminCheckBox = widget->findChild<QCheckBox *>();
    connect(monitorAdminCheckBox, &QCheckBox::toggled, this, &Widget::checkAdminBox, Qt::UniqueConnection);
}

void Widget::checkAdminBox()
{
//    qDebug() << "in checkAdminBox";

    if (monitorAdminCheckBox->isChecked()){
//        qDebug() << "admin box is checked";
        for (int j = 1; j < 11; j++){
            QWidget *widget = ui->UACTableWidget->cellWidget(monitorAdminIndexRow, j);
            QCheckBox *checkBox = widget->findChild<QCheckBox *>();
            checkBox->setCheckState(Qt::Checked);
        }
    } else if (!monitorAdminCheckBox->isChecked()){
//        qDebug() << "admin box is unchecked";
        for (int j = 1; j < 11; j++){
            QWidget *widget = ui->UACTableWidget->cellWidget(monitorAdminIndexRow, j);
            QCheckBox *checkBox = widget->findChild<QCheckBox *>();
            checkBox->setCheckState(Qt::Unchecked);
        }
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, tr("Restore Default"), "Do you wish to restore to default settings?", QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes){
            setDefaultPermissions(monitorAdminIndexRow);
            QMessageBox::information(this, tr("Restore Default"), "Default Permissions are restored");
        } else if (reply == QMessageBox::No){
            QMessageBox::information(this, tr("Restore Default"), "No Permissions are set.");
        }
    }
}


void Widget::archiveUser()
{
//    qDebug() << "in archiveUser";
    QString fullName = ui->UACTableWidget->item(monitorAdminIndexRow, 0)->text();
    QString firstName = fullName.split(" ").front();
    QString lastName = fullName.split(" ").back();
    QSqlQuery archiveQuery;
    QString archiveQueryStatement = QString("UPDATE users SET activestatus = 0 WHERE firstname = '%2' and lastname = '%3'")
            .arg(firstName).arg(lastName);
    if (archiveQuery.exec(archiveQueryStatement)){
        QMessageBox::information(this, tr("Archived"), "This user has been archived to previous users.");
    } else{
        QMessageBox::warning(this, tr("Archive Error"), "Archiving failed! Please try again later.");
    }
    populateUACTableWidget();
    ui->UACadminViewScreenPageNestedWidgetSaveButton->setEnabled(false);
    UACTableWidgetItem = nullptr;
}

void Widget::setDefaultPermissions(int i)
{
//    qDebug() << "in setDefaultPermissions";
    QWidget *widget = ui->UACTableWidget->cellWidget(i, 1);
    QCheckBox *checkBox = widget->findChild<QCheckBox *>();
    checkBox->setChecked(true);

    widget = ui->UACTableWidget->cellWidget(i, 2);
    checkBox = widget->findChild<QCheckBox *>();
    checkBox->setChecked(true);

    widget = ui->UACTableWidget->cellWidget(i, 3);
    checkBox = widget->findChild<QCheckBox *>();
    checkBox->setChecked(true);

    widget = ui->UACTableWidget->cellWidget(i, 4);
    checkBox = widget->findChild<QCheckBox *>();
    checkBox->setChecked(false);

    widget = ui->UACTableWidget->cellWidget(i, 5);
    checkBox = widget->findChild<QCheckBox *>();
    checkBox->setChecked(false);

    widget = ui->UACTableWidget->cellWidget(i, 6);
    checkBox = widget->findChild<QCheckBox *>();
    checkBox->setChecked(true);

    widget = ui->UACTableWidget->cellWidget(i, 7);
    checkBox = widget->findChild<QCheckBox *>();
    checkBox->setChecked(true);

    widget = ui->UACTableWidget->cellWidget(i, 8);
    checkBox = widget->findChild<QCheckBox *>();
    checkBox->setChecked(true);

    widget = ui->UACTableWidget->cellWidget(i, 9);
    checkBox = widget->findChild<QCheckBox *>();
    checkBox->setChecked(false);

    widget = ui->UACTableWidget->cellWidget(i, 10);
    checkBox = widget->findChild<QCheckBox *>();
    checkBox->setChecked(true);
}

void Widget::resetPassword()
{
//    qDebug() << "in resetPassword()";
//    qDebug() << "reset password button clicked for row";
    newTempPassword = alphaNumGenerator();
    //    qDebug() << newTempPassword;
}

QString Widget::convertToHex(QString binaryToHex)
{
    bool ok;
    int hex = binaryToHex.toInt(&ok, 2);
    return QString::number(hex, 16);
}

QString Widget::convertToBinary(QString hexToBinary)
{
    bool ok;
    int hex = hexToBinary.toInt(&ok, 16);
    return QString::number(hex, 2);
}


QString Widget::encrypt(QString input)
{
    return input.toLocal8Bit().toHex().toBase64();
}

QString Widget::decrypt(QString input)
{
//    qDebug() << "input = " << input;
    QByteArray reverseInput = QByteArray::fromStdString(input.toStdString());
//    qDebug() << "reverseInput = " << reverseInput;
    QByteArray b64FromStdStringInput = QByteArray::fromBase64(reverseInput);
//    qDebug() << "b64FromStdStringInput = " << b64FromStdStringInput;
    QByteArray fromHexInput = QByteArray::fromHex(b64FromStdStringInput);
//    qDebug() << fromHexInput;
    QString toDecrypt = fromHexInput;
    return toDecrypt;
}

QString Widget::generateOffset(QString password)
{
    qDebug() << "in generateOffset";

    int length = 64 - password.length();

    QString offsetFill = "";
    for (int i = 0; i < length; i++){
        std::uniform_int_distribution<int> distribution(1, charList.count());
        int value = distribution(*QRandomGenerator::global()) - 1;

        QChar character = charList[value];

        offsetFill.append(character);
    }
    qDebug() << "offsetFill:\t" << offsetFill;
    return offsetFill;
}

void Widget::on_reportsTabNestedWidgetQuickViewsPushButton_clicked()
{
    quickViewsDialogBox *quickViews = new quickViewsDialogBox(this);

    quickViews->setCurrentRadioButton(quickViewsRadioButton);

    connect(quickViews, &quickViewsDialogBox::accepted, [=](){
        quickViewsRadioButton = quickViews->getCurrentRadioButton();
        if (quickViewsRadioButton == 1){
            QDateTime fullDay = QDateTime::currentDateTime();
            QDateTime yesterday = fullDay.addDays(-1);
            ui->reportsTabNestedWidgetEndDateDateEdit->setDate(fullDay.date());
            ui->reportsTabNestedWidgetStartDateDateEdit->setDate(yesterday.date());
            ui->reportsTabNestedWidgetStartTimeTimeEdit->setTime(fullDay.time());
            ui->reportsTabNestedWidgetEndTimeTimeEdit->setTime(fullDay.time());
        } else if (quickViewsRadioButton == 2){
            QTime time = QTime(openCloseHoursMinutes[0], openCloseHoursMinutes[1]);
            ui->reportsTabNestedWidgetStartTimeTimeEdit->setTime(time);
            time = QTime(openCloseHoursMinutes[2], openCloseHoursMinutes[3]);
            ui->reportsTabNestedWidgetEndTimeTimeEdit->setTime(time);
        } else if (quickViewsRadioButton == 3){
            QTime time = QTime(openCloseHoursMinutes[2], openCloseHoursMinutes[3]+1);
            ui->reportsTabNestedWidgetEndTimeTimeEdit->setTime(time);
            if (openCloseHoursMinutes[1] == 0){
                time = QTime(openCloseHoursMinutes[0]-1, 59);
            } else{
                time = QTime(openCloseHoursMinutes[0], openCloseHoursMinutes[1]-1);
            }
            ui->reportsTabNestedWidgetStartTimeTimeEdit->setTime(time);
        } else if (quickViewsRadioButton == 4){
            ui->reportsTabNestedWidgetStartTimeTimeEdit->setTime(QTime(0,0));
            ui->reportsTabNestedWidgetEndTimeTimeEdit->setTime(QTime(0,0));
        }
    });
    quickViews->show();
}

void Widget::on_reportsTabNestedWidgetZonesPushButton_clicked()
{
    ZonesDialogBox *zones = new ZonesDialogBox(this);
    if (zonesCheckBoxes.isEmpty()){
        for (int i = 0; i < 10; i++){
            zonesCheckBoxes.append(true);
        }
    }
    zones->setCheckBoxes(zonesCheckBoxes);
    connect(zones, &ZonesDialogBox::accepted, [=](){
        zonesCheckBoxes.clear();
        zonesCheckBoxes = zones->getCheckBoxes();
    });
    zones->show();
}

void Widget::on_reportsTabNestedWidgetDevicesPushButton_clicked()
{
    DevicesDialogBox *devices = new DevicesDialogBox(this);
    if (devicesCheckBoxes.isEmpty()){
        for (int i = 0; i < 9; i++){
            devicesCheckBoxes.append(true);
        }
    }
    devices->setCheckBoxes(devicesCheckBoxes);
    connect(devices, &DevicesDialogBox::accepted, [=](){
        devicesCheckBoxes.clear();
        devicesCheckBoxes = devices->getCheckBoxes();
    });
    devices->show();
}

void Widget::on_reportsTabNestedWidgetReadingsPushButton_clicked()
{
    ReadingsDialogBox *readings = new ReadingsDialogBox(this);
    if (readingsCheckBoxes.isEmpty()){
        for (int i = 0; i < 3; i++){
            readingsCheckBoxes.append(true);
        }
    }
    readings->setCheckBoxes(readingsCheckBoxes);
    connect(readings, &ReadingsDialogBox::accepted, [=](){
        readingsCheckBoxes.clear();
        readingsCheckBoxes = readings->getCheckBoxes();
    });
    readings->show();
}

void Widget::on_reportsTabNestedWidgetPeriodsPushButton_clicked()
{
    PeriodsDialogBox *periods = new PeriodsDialogBox(this);
    periods->setCurrentRadioButton(periodsRadioButton);

    connect(periods, &PeriodsDialogBox::accepted, [=](){
        periodsRadioButton = periods->getCurrentRadioButton();
    });
    periods->show();
}

void Widget::on_settingsTabNestedWidgethelpPushButton_clicked()
{
    HelpDialog *helpScreen = new HelpDialog(this);
    helpScreen->show();
}

void Widget::on_UACAddAUserButton_clicked()
{
//    qDebug() << "in UACAddAUserButton_clicked()";
    AddAUserDialog *addUser = new AddAUserDialog(this);
    connect(addUser, &AddAUserDialog::accepted, [=](){
        addUserToUserTable(addUser);
        populateUACTableWidget();
    });

    addUser->show();
}

void Widget::on_logoutScreenPageClearNotificationsButton_clicked()
{
    ui->logoutScreenPageNotificationsListWidget->clear();
}

void Widget::on_UACPreviousUsersButton_clicked()
{
//    qDebug() << "in UACPreviousUsersButton_clicked()";
    PreviousUsersDialog *previousUsers = new PreviousUsersDialog(this);
    connect(previousUsers, &PreviousUsersDialog::accepted, [=](){
        populateUACTableWidget();
    });
    previousUsers->show();
}

void Widget::on_UACTableWidget_itemClicked(QTableWidgetItem *item)
{
//    qDebug() << "in UACTableWidget_itemClicked()";
    if (ui->UACadminViewScreenPageNestedWidgetEditButton->isEnabled() || ui->UACadminViewScreenPageNestedWidgetSaveButton->isEnabled())
    {
//        qDebug() << "one of the buttons is active";
        QMessageBox::warning(this, tr("Error"), "You can only select one user at a time!");
    } else{
//        qDebug() << "neither button is active";
//        qDebug() << "item = " << item->text();
        item->setTextColor("green");
//        qDebug() << "post item color change";
        selectedItemFont = item->font();
//        qDebug() << "selectedItemFont = " << selectedItemFont.toString();
        QFont font;
        font.setBold(true);
        font.setFamily("Consolas");
//        qDebug() << "new font created";
//        qDebug() << "UACTableWidgetItem = " << UACTableWidgetItem;
//        qDebug() << "UACTableWidgetItem = " << UACTableWidgetItem->text();
        if (UACTableWidgetItem == nullptr){
//            qDebug() << "UACTableWidgetItem has no text";
            UACTableWidgetItem = item;
        } else{
//            qDebug() << "has something";
            if (UACTableWidgetItem != item){
//                qDebug() << "UACTableWidgetItem != item";
//                qDebug() << "UACTableWidgetItem = " << UACTableWidgetItem;
                UACTableWidgetItem->setTextColor("black");
                UACTableWidgetItem->setFont(selectedItemFont);
                UACTableWidgetItem = item;
//                qDebug() << "UACTableWidgetItem = " << UACTableWidgetItem;
            }
        }
//        qDebug() << "previous monitorAdminIndexRow = " << monitorAdminIndexRow;
        monitorAdminIndexRow = UACTableWidgetItem->row();
//        qDebug() << "current monitorAdminIndexRow = " << monitorAdminIndexRow;
        ui->UACadminViewScreenPageNestedWidgetEditButton->setEnabled(true);
    }
}

void Widget::on_settingsTabNestedWidgetnotificationsPushButton_clicked()
{
    AdditionalSettingsNotificationsDialog *additionalSettings = new AdditionalSettingsNotificationsDialog(this);


//    setAdditionalAdminData(additionalSettings);

    connect(additionalSettings, &AdditionalSettingsNotificationsDialog::accepted, [=](){
//        captureAdditionalAdminData(additionalSettings);
//        qDebug() << "main widget layer";
//        qDebug() << openCloseHoursMinutes;
    });
    additionalSettings->show();
}

void Widget::toggleAdminUACCheckBoxStatuses()
{
//    qDebug() << "in toggleAdminUACCheckBoxStatuses";
    for (int i = 1; i < 11; i++){
        QWidget *widget = ui->UACTableWidget->cellWidget(monitorAdminIndexRow, i);
        QCheckBox *checkBox = widget->findChild<QCheckBox *>();
        if (!checkBox->isEnabled()){
            checkBox->setEnabled(true);
        } else if (checkBox->isEnabled()){
            checkBox->setEnabled(false);
        }
    }

    QWidget *widgetButton = ui->UACTableWidget->cellWidget(monitorAdminIndexRow, 14);
    if(!widgetButton->isEnabled()){
        widgetButton->setEnabled(true);
    } else if (widgetButton->isEnabled()){
        widgetButton->setEnabled(false);
    }

    QWidget *widgetButton2 = ui->UACTableWidget->cellWidget(monitorAdminIndexRow, 15);
    if(!widgetButton2->isEnabled()){
        widgetButton2->setEnabled(true);
    } else if (widgetButton2->isEnabled()){
        widgetButton2->setEnabled(false);
    }
}

void Widget::on_UACadminViewScreenPageNestedWidgetEditButton_clicked()
{
//    qDebug() << "editButton clicked";
//    qDebug() << "current index = " << monitorAdminIndexRow;
    ui->UACadminViewScreenPageNestedWidgetEditButton->setEnabled(false);
    ui->UACadminViewScreenPageNestedWidgetSaveButton->setEnabled(true);
    monitorAdminStatus();
    toggleAdminUACCheckBoxStatuses();
    monitorDevicePermissions();
}

void Widget::on_UACadminViewScreenPageNestedWidgetSaveButton_clicked()
{
//    qDebug() << "save button clicked";
//    qDebug() << "current index = " << monitorAdminIndexRow;
    UACTableWidgetItem->setTextColor("black");
    UACTableWidgetItem->setFont(selectedItemFont);
    QList<bool> userPerms;
    for (int i = 1; i < 11; i++){
        QWidget *widget = ui->UACTableWidget->cellWidget(monitorAdminIndexRow, i);
        QCheckBox *checkBox = widget->findChild<QCheckBox *>();
        userPerms.append(checkBox->isChecked());
    }
    //convert to hex
    QString binaryToHex;
    for (int i = 0; i < userPerms.count(); i++){
        binaryToHex.append(QString::number(userPerms[i]));
    }
    QString finalHex = convertToHex(binaryToHex);

    QString fullName = ui->UACTableWidget->item(monitorAdminIndexRow, 0)->text();
    QString updateQueryStatement = QString("UPDATE users SET permissions = '%1' WHERE firstname = '%2' and lastname = '%3'")
            .arg(finalHex)
            .arg(fullName.split(" ").front())
            .arg(fullName.split(" ").back());
    QSqlQuery updateQuery;
    updateQuery.exec(updateQueryStatement);
    ui->UACadminViewScreenPageNestedWidgetSaveButton->setEnabled(false);
    toggleAdminUACCheckBoxStatuses();
}

void Widget::sendMail(QString userEmailMail, QString tempPassword)
{
    //NEED TO CHECK THIS AND SEE IF IT WORKS OUTSIDE OF THE SCHOOL
    //COULD BE THE NETWORK SETUP THE SCHOOL HAS
//        qDebug() << "in sendMail";
//        qDebug() << userEmailMail << " : " << tempPassword;
        Smtp *smtp = new Smtp("hutemph3@gmail.com", "MnJhUy&^67", "smtp.gmail.com", 465);
        connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));


//        qDebug() << "socketStatus is true";
        QString subjectLine = "HuTemp - New Account -->(DO NOT REPLY TO THIS EMAIL)";
        QString message = "You account has been activated for HuTemp use. "
                          "Please review the following information below.\n\n";
        message += "Login Credentials:\n\t";
        message += "Username:\t";
        message += userEmailMail;
        message += "\n\tTemporary Password:\t";
        message += tempPassword;
        message += "\n\n\n\n";
        message += "Please make an attempt to login with these credentials.\n";
        message += "For support, review the User Manual, or contact your manager.\n";
        message += "\n\n\n=========================================";
        message += "DO NOT REPLY TO THIS EMAIL";


        if(!files.isEmpty()){
//            qDebug() << "!files.isEmpty()";
            smtp->sendMail("hutemph3@gmail.com", userEmailMail, subjectLine, message, files);
        } else{
//            qDebug() << "files.isEmpty()";
            smtp->sendMail("hutemph3@gmail.com", userEmailMail, subjectLine, message);
        }

        bool socketStatus = smtp->getSocketStatus();
        if (socketStatus == false){
//            qDebug() << "socket Status is false";
            QString message = "Email failed to send to user!";
            message += "\nPlease provide this new user with their login information:";
            message += "\n\tUsername:\t";
            message += userEmailMail;
            message += "\n\tPassword:\t";
            message += tempPassword;
            QMessageBox::warning(this, tr("Failed Email"), message);
        }
}

void Widget::mailSent(QString status)
{
    if(status == "Message sent"){
        QMessageBox::warning(this, "New Account", "Notify the account holder to check their email for their login credentials.");
    }
}

void Widget::addUserToLoginTable(QString inputUserEmail)
{
    qDebug() << "in addUserToLoginTable";
    QSqlQuery checkQuery;
    checkQuery.exec("SELECT * FROM login");
    bool check = true;
    while (checkQuery.next()){
        QString username = checkQuery.value(1).toString();
        if (inputUserEmail == username){
            QMessageBox::warning(this, tr("CRITICAL ERROR"), "This user email has already been used! Provide a different email!");
            check = false;
            break;
        }
    }
    if (check == true){
//        qDebug() << "check is true";
        QSqlQuery insertQuery;
        resetPassword();
        qDebug() << "newTempPassword = " << newTempPassword;
//        qDebug() << inputUserEmail << "-:-" << newTempPassword;
        QString offset = generateOffset(newTempPassword);
        qDebug() << "offset = " << offset;
        QString offsetEncrypted = encrypt(offset);
        qDebug() << "offsetEncrypted = " << offsetEncrypted;
        QString passwordEncrypted = encrypt(newTempPassword);
        qDebug() << "passwordEncrypted = " << passwordEncrypted;
        QString finalPassword = passwordEncrypted + offsetEncrypted;
        qDebug() << "finalPassword = " << finalPassword;
        QString finalPasswordEncrypted = encrypt(finalPassword);
        qDebug() << "finalPasswordEncrypted = " << finalPasswordEncrypted;
//        QString passwordEncrypted = encrypt("");
//        QString finalHash = encrypt("");


        //DOUBLE CHECK THE COLUMN NAME IN THIS STATEMENT TO MAKE SURE IT'S THE RIGHT SPELLING
//        qDebug() << "userEmail:\t" << inputUserEmail;
        QString selectQueryStatement = QString("SELECT * FROM users WHERE email = '%1'").arg(inputUserEmail);
        QSqlQuery selectQuery;
        selectQuery.exec(selectQueryStatement);
        QString userID;
//        qDebug() << userID;
        while (selectQuery.next()){
            userID = selectQuery.value(0).toString();
        }

        int convertedUserID = userID.toInt();
//        qDebug() << userID;
//        qDebug() << convertedUserID;

        //NEED TO FIX THIS QUERY TO THE NEW STRUCTURE OF THE LOGIN TABLE

        //use MYSQL's 256 AES_ENCRYPT() on password, username, and offset columns
        //use generateHexString for the AES_ENCRYPT() stuff
        //review links for proper setup:
            //https://security.stackexchange.com/questions/190611/mysql-aes-encrypt-string-key-length
            //https://dev.mysql.com/doc/refman/8.0/en/encryption-functions#function_aes-encrypt
            //https://www.w3resource.com/mysql/encryption-and-compression-functions/aes_().php
//        qDebug() << "QString::fromStdString(offsetEncrypted.toStdString()) --> " << QString::fromStdString(offsetEncrypted.toStdString());
        QString insertStatement = QString("INSERT INTO login (userID, username, password, offset, temporarypassword, lockout)"
                                          " VALUES (%1, '%2', AES_ENCRYPT('%3', '%7'), AES_ENCRYPT('%4','%7'), %5, %6)").arg(QString::number(convertedUserID))
                .arg(inputUserEmail).arg(finalPasswordEncrypted).arg(offsetEncrypted).arg(QString::number(true)).arg(QString::number(false)).arg(KEY);
        if (insertQuery.exec(insertStatement)){
            qDebug() << "successful logins table query";
//            qDebug() << "userEmail:\t" << inputUserEmail;
//            qDebug() << "finalHash:\t" << finalHash;
//            qDebug() << "offsetEncrypted:\t" << offsetEncrypted;
            sendMail(inputUserEmail, newTempPassword);
        } else{
            qDebug() << "unsuccessful logins table query";
        }

    } else{
//        qDebug() << "check is false";
    }
}

QString Widget::getUserName()
{
    QString userName = userFirstName + userLastName;
    return userName;
}

QString Widget::getUserEmail()
{
    return userEmail;
}

QString Widget::getUserType()
{
    return userType;
}

void Widget::addUserToUserTable(AddAUserDialog *addUser)
{
    qDebug() << "in addUserToUserTable";
    QSqlQuery insertQuery;
    insertQuery.exec("SELECT * FROM users");
//    int userCount = insertQuery.size();
//    qDebug() << userCount;
    QStringList usersInfo = addUser->getUserInfo();
    QString firstName = usersInfo[0];
    QString lastName = usersInfo[1];
    QString userNumber = usersInfo[2];
//    qDebug() << userNumber;
    QString email = usersInfo[3];
    QString hireDate = usersInfo[4];

    QList<bool> userPermissions {};
    userPermissions.append(addUser->getDataLoggerPermission());//0
    userPermissions.append(addUser->getAddDevicePermission());//1
    userPermissions.append(addUser->getModifyDevicePermission());//2
    userPermissions.append(addUser->getRemoveDevicePermission());//3
    userPermissions.append(addUser->getUserAdminPermission());//4
    userPermissions.append(addUser->getReportsPermission());//5
    userPermissions.append(addUser->getSettingsPermission());//6
    userPermissions.append(addUser->getNotificationsPermission());//7
    userPermissions.append(addUser->getNetworksPermission());//8
    userPermissions.append(addUser->getEmailPermission());//9

    QList<int> binaryPermissions;
    for (int i = 0; i < userPermissions.count(); i++){
        if (userPermissions[i] == true){
            binaryPermissions.append(1);
        } else{
            binaryPermissions.append(0);
        }
    }
    QString binaryToHex;
    for (int j = 0; j < binaryPermissions.count(); j++){
        binaryToHex.append(QString::number(binaryPermissions[j]));
    }

    QString finalHex = convertToHex(binaryToHex);
//    qDebug() << finalHex;
//    int bin = finalHex.toInt(&ok, 16);
//    QString hexToBinary = QString::number(bin, 2);
//    qDebug() << hexToBinary;
    bool activeStatus = true;

    QString queryStatement = QString("INSERT INTO users (firstname, lastname, activestatus, email, hiredate, phonenumber, permissions) "
                             "VALUES ('%1', '%2', %3, '%4', '%5', '%6', '%7')").arg(firstName).arg(lastName).arg(QString::number(activeStatus))
            .arg(email).arg(hireDate).arg(userNumber).arg(finalHex);

    insertQuery.exec(queryStatement);

    addUserToLoginTable(email);
//    insertQuery.exec("INSERT INTO users (firstname, lastname, activestatus, email, hiredate, phonenumber, permissions) "
//                     "VALUES ('Dude', 'Wheres My Car?', 1, 'something@example.com', '2019-05-24 10:44:35', 7204363017, '3ff')");

//    insertQuery.exec("SELECT * FROM users");
//    while (insertQuery.next()){
//        QString firstName = insertQuery.value(1).toString();
//        qDebug() << firstName;
//    }
}

void Widget::connectToDatabase()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setDatabaseName("HuTemp");
    db.setHostName(vmDBIPAddress);
    db.setUserName("HuTempApp");
    db.setPassword("cookie");

    dbOpen = db.open();
    if(dbOpen){
        QSqlQuery mainquery(db);
//        QMessageBox::information(this, "Connection", "Successful connection");
        qDebug() << "successful connection";
        QSqlQuery query;
        int numRows;
        query.exec("SELECT * FROM data");

        if (db.driver()->hasFeature(QSqlDriver::QuerySize)) {
            numRows = query.size();
            qDebug() << "The number of Rows in the Database is: " << numRows;
        } else {
            // this can be very slow
            query.last();
            numRows = query.at() + 1;
        }

//        const QHostAddress &localhost = QHostAddress(QHostAddress::LocalHost);
////        qDebug() << QNetworkInterface::allAddresses() << "\n";
//        for (const QHostAddress &address: QNetworkInterface::allAddresses()) {
//            if (address.protocol() == QAbstractSocket::IPv4Protocol && address != localhost)
//                 qDebug() << address.toString();
//        }
    } else{
//        QMessageBox::warning(this, "Connection", QString(db.lastError().text()));
        qDebug() << "Failed to connect to database";
    }

}

void Widget::extractAllCompanyInfo()
{
    //after connection with database is successful, capture all data from a file located in a hidden folder in the database and assign to variables
}

void Widget::extractAllUserInfo()
{
    //after connection with database, once the database sends back all user info, extract from that and assign to variables
    userFirstName = "";
    userLastName = "";
    userEmail = "";
    userPhoneNumber = "";
    userType = "";
}

QString Widget::alphaNumGenerator()
{
//    qDebug() << "in alphaNumGenerator";
    srand(QDateTime::currentMSecsSinceEpoch());
    QString tempWord = "";
    for (int i = 0; i < 10; i++){
        tempWord += charList[rand() % charList.count()];
    }
    return tempWord;
}

void Widget::createDirectories()
{
    logsDirectory = "C:/ShareToUbuntu/logs";
    QDir dir;
    dir.mkdir(logsDirectory);
    SetFileAttributesA(logsDirectory.toStdString().c_str(), FILE_ATTRIBUTE_HIDDEN);

    pdfDirectory = "C:/ShareToUbuntu/PDFs";
    dir.mkdir(pdfDirectory);
    SetFileAttributesA(pdfDirectory.toStdString().c_str(), FILE_ATTRIBUTE_HIDDEN);
}

void Widget::on_devicesTabAddButton_clicked()
{
    QMessageBox::information(this, tr("Add A Device"), "Inspect your user's manual for the proper procedure for adding a data logger.");
}

void Widget::on_devicesTabSortOptionsDropDownBox_currentIndexChanged(int index)
{
    ui->devicesTabTableWidget->sortByColumn(index);
}

void Widget::on_devicesTabRefreshButton_clicked()
{
    populateDevicesTableWidget();
}

void Widget::on_reportsTabNestedWidgetEndDateDateEdit_userDateChanged(const QDate &date)
{
    if (date > QDate::currentDate()){
        ui->reportsTabNestedWidgetEndDateDateEdit->setDate(QDate::currentDate());
    }
}

void Widget::on_reportsTabNestedWidgetEndTimeTimeEdit_userTimeChanged(const QTime &time)
{
    if (time > QTime::currentTime()){
        ui->reportsTabNestedWidgetEndTimeTimeEdit->setTime(QTime::currentTime());
    }
}

void Widget::on_reportsTabNestedWidgetResetButton_clicked()
{
    ui->reportsTabNestedWidgetTableWidget->clearContents();
    ui->reportsTabNestedWidgetTableWidget->setRowCount(0);
}

void Widget::on_reportsTabNestedWidgetSnapshotButton_clicked()
{
    QDateTime dateTime = QDateTime::currentDateTime();
    QTime currentTime = dateTime.time();
    QTime backTime;
    backTime.setHMS(currentTime.hour(), currentTime.minute()-1, currentTime.second());
    QDate currentDate = dateTime.date();
    QDate backDate;
    backDate.setDate(currentDate.year(), currentDate.month(), currentDate.day()-1);

    ui->reportsTabNestedWidgetStartDateDateEdit->setDate(backDate);
    ui->reportsTabNestedWidgetEndDateDateEdit->setDate(currentDate);
    ui->reportsTabNestedWidgetStartTimeTimeEdit->setTime(backTime);
    ui->reportsTabNestedWidgetEndTimeTimeEdit->setTime(currentTime);
    populateReportsTableWidget();
}

void Widget::on_loginButton_clicked()
{
    //if attempt is at or greater than 5, check to see if email is matched.
    QString enteredUserName = ui->loginScreenPageNestedWidgetUserNameLineEdit->text();
    QString enteredPassWord = ui->loginScreenPageNestedWidgetPasswordLineEdit->text();


    //select all (username, password, temporarypassword, offset, and lockout) from logins with AES_DECRYPT()
    //extract all five columns into their respective variables (QString for varchars/bool for tinyint\boolean)
    //run each string through the decryption algorithm
    //compare the result to the user input
    //define and declare integer attempt at 0
    //define and declare boolean flag as false
    //if matched, break from while(loginTableQuery.next()) and set boolean flag to true
    //after while loop is complete, inspect boolean flag
    //if boolean flag is true, run select query to get user's permissions
    //adjust enabled flags on objects based on user permissions
    //if boolean flag is false, clear line edits
    //in false check, check to see if either username or password matched
    //if either one of them matched, increment attempt by one and tell user with warning window that they entered an incorrect username or password
    //if neither of them matched, tell user with warning window that they entered an incorrect username of password




    QSqlQuery loginTableLockoutQuery;
    QString loginTableLockoutQueryStatement = QString("SELECT lockout FROM login WHERE username = '%1'").arg(enteredUserName);
    int lockout = 0;
    if (loginTableLockoutQuery.exec(loginTableLockoutQueryStatement)){
        while(loginTableLockoutQuery.next()){
            lockout = loginTableLockoutQuery.value(0).toInt();
        }
    } else{
        QMessageBox::warning(this, tr("Error!"), "Invalid username entry");
        //WILL NEED TO ADD MORE HERE EVENTUALLY TO HANDLE WHEN SOMEONE MAKES THREE TO FIVE FALSE ATTEMPTS WITH AN INVALID USERNAME ENTRY
        //CREATE A LOCKOUT MECHANISM THAT CHECKS UPON OPENING OF APPLICATION FOR A TIMER VARIABLE THAT RUNS FOR AN HOUR WHEN
        //SOMEONE TRIES TO FALSELY LOGIN. NEED TO FIGURE OUT WHERE TO STORE THE TIMER. NEED TO MAKE SURE THE TIMER IS RUNNING FOR THE
        //SET TIME FOR WHEN THE SYSTEM IS ON. THE TIMER NEEDS TO PAUSE WHEN THE SYSTEM IS TURNED OFF. AND THEN CONTINUES WHEN THE SYSTEM
        //GETS TURNED BACK ON. IF OR WHEN THE TIMER IS AT 0, THEN THE APPLICATION CAN START UP.
        //IF THE TIMER IS NOT AT 0, THEN A MESSAGEBOX WILL APPEAR THAT SAYS THE APPLICATION HAS BEEN FULLY LOCKED OUT AND TO REVIEW THE USER
        //MANUAL FOR FURTHER EXPLANATION
    }

    if (lockout == 1){
        //trigger password reset protocol
    } else{
        //Start process of gathering remaining information for comparison check
        QSqlQuery loginTableQuery;
        QString loginTableQueryStatement = QString("SELECT AES_DECRYPT(password, '%2'), AES_DECRYPT(offset, '%2'), temporarypassword FROM login WHERE username = '%1'").arg(enteredUserName).arg(KEY);
        QString password;//0
        QString offset;//1
        int temporaryPasswordStatus = 0;//2
        if (loginTableQuery.exec(loginTableQueryStatement)){
            while(loginTableQuery.next()){
                password = loginTableQuery.value(0).toString();
                offset = loginTableQuery.value(1).toString();
                temporaryPasswordStatus = loginTableQuery.value(2).toInt();
            }
        } else{
            QMessageBox::warning(this, tr("ERROR"), "Connection to database failed. Please try again shortly.");
        }

        QString offsetDecrypted = decrypt(offset);
        QString passwordDecrypted = decrypt(password);
        QString passwordSplit = passwordDecrypted.replace(offset, "");
        QString finalPassword = decrypt(passwordSplit);
//        qDebug() << "enteredPassWord = " << enteredPassWord;
//        qDebug() << "finalPassword = " << finalPassword;

        if (enteredPassWord == finalPassword){
            qDebug() << "SUCCESS!!!";
            if (temporaryPasswordStatus == 1){
                NewPasswordPostResetDialog *newPassword = new NewPasswordPostResetDialog(enteredUserName);
                newPassword->show();
            } else{
                loginCurrentUser(enteredUserName);
            }
        } else{
            qDebug() << "FAILED";
            QMessageBox::warning(this, tr("FAILED!"), "An incorrect username or password was used.");
            loginAttempts++;
        }

        if (loginAttempts == 5){
            QSqlQuery updateQuery;
            QString updateQueryStatement = QString("UPDATE login SET lockout = 1 WHERE username = '%1'").arg(enteredUserName);
            loginAttempts = 0;
        }
    }
}

void Widget::on_loginScreenPageNestedWidgetPasswordResetButton_clicked()
{
    passwordReset *reset = new passwordReset(this);

    reset->show();
}

QString Widget::generateHexString(int hexSize)
{
//    qDebug() << "in generateHexString";
    srand(QDateTime::currentMSecsSinceEpoch());
    QString hexString = "";
    QString hexCharacters = "123456789ABCDEF";
    for (int i = 0; i < hexSize; i++){
         hexString += hexCharacters[rand() % hexCharacters.count()];
    }
    return hexString;
}

void Widget::loginCurrentUser(QString username)
{
    QSqlQuery extractUserInfoQuery;
    QString extractUserInfoQueryStatement = QString("SELECT firstname, lastname, email, hiredate, phonenumber, permissions "
                                                    "FROM users WHERE email = '%1'").arg(username);
    if (extractUserInfoQuery.exec(extractUserInfoQueryStatement)){
        QString loginUserFirstName;
        QString loginUserLastName;
        QString loginUserEmail;
        QString loginUserHireDate;
        QString loginUserPhoneNumber;
        QString loginUserPermissions;
        while(extractUserInfoQuery.next()){
            loginUserFirstName = extractUserInfoQuery.value(0).toString();
            loginUserLastName = extractUserInfoQuery.value(1).toString();
            loginUserEmail = extractUserInfoQuery.value(2).toString();
            loginUserHireDate = extractUserInfoQuery.value(3).toString();
            loginUserPhoneNumber = extractUserInfoQuery.value(4).toString();
            loginUserPermissions = extractUserInfoQuery.value(5).toString();
        }


        //create file
        QString fileName = logsDirectory + "/tempUserInfoLog.txt";
        QFile file(fileName);
        if (file.open(QIODevice::ReadWrite)){
            QTextStream inStream(&file);
            inStream << loginUserFirstName << endl;
            inStream << loginUserLastName << endl;
            inStream << loginUserEmail << endl;
            inStream << loginUserHireDate << endl;
            inStream << loginUserPhoneNumber << endl;
            inStream << loginUserPermissions << endl;
        }
        file.close();

        loginUserFirstName = nullptr;
        loginUserLastName = nullptr;
        loginUserEmail = nullptr;
        loginUserHireDate = nullptr;
        loginUserPhoneNumber = nullptr;

        loginUserPermissions = convertToBinary(loginUserPermissions);
        activatePermissions(loginUserPermissions);
//        qDebug() << "loginUserPermissions = " << loginUserPermissions;


//SAVE FOR POPULATING THE USER INFO IN THE USER PROFILE VIEW
//        if(file.open(QIODevice::ReadOnly)){
//            QTextStream fromFile(&file);
//            QString myFileText = fromFile.readAll();
//            QStringList myText = myFileText.split("\n");

//        }
//        file.close();




//        if (file.open(QIODevice::ReadOnly)){
//            QTextStream in(&file);
//            QString myFileText = in.readAll();
//            qDebug() << myFileText;
//            QStringList myText = myFileText.split("\n");
//            ui->ContactSupportDialogCompanyNameLabel->setText(myText[0]);
//            ui->ContactSupportDialogCompanyAddressLine1Label->setText(myText[1]);
//            ui->ContactSupportDialogCompanyAddressLine2Label->setText(myText[2]);
//            ui->ContactSupportDialogCompanyPhoneNumberLabel->setText(myText[3]);
//        }else{
//            qDebug() << "File currently does not exist";
//        }
    }
}

void Widget::activatePermissions(QString permissions)
{
    int devicesPermission = permissions[0].digitValue();//0
    int devicesAddPermission = permissions[1].digitValue();//1
    int devicesModifyPermission = permissions[2].digitValue();//2
    int devicesRemovePermission = permissions[3].digitValue();//3
    int adminPermission = permissions[4].digitValue();//4
    int reportsPermission = permissions[5].digitValue();//5
    int settingsPermission = permissions[6].digitValue();//6
    int notificationsPermission = permissions[7].digitValue();//7
    int networkPermission = permissions[8].digitValue();//8
    int emailPermission = permissions[9].digitValue();//9

//    qDebug() << "devicesPermission = " << devicesPermission;
//    qDebug() << "devicesAddPermission = " << devicesAddPermission;
//    qDebug() << "devicesModifyPermission = " << devicesModifyPermission;
//    qDebug() << "devicesRemovePermission = " << devicesRemovePermission;
//    qDebug() << "adminPermission = " << adminPermission;
//    qDebug() << "reportsPermission = " << reportsPermission;
//    qDebug() << "settingsPermission = " << settingsPermission;
//    qDebug() << "notificationsPermission = " << notificationsPermission;
//    qDebug() << "networkPermission = " << networkPermission;
//    qDebug() << "emailPermission = " << emailPermission;

    activateBasicConfigurations();

    if (adminPermission == 1){
        ui->logoutScreenPageNestedWidgetUserTypeLabel->setText("Admin");
        ui->mainTabsWidget->setTabText(1, "Users");
        activateAllPermissions();
    } else{
        ui->logoutScreenPageNestedWidgetUserTypeLabel->setText("User");
        ui->mainTabsWidget->setTabText(1, "Profile");
        disableAdminPermissions();
        setDevicePermissions(devicesPermission, devicesAddPermission, devicesModifyPermission, devicesRemovePermission);
        setSettingsPermissions(settingsPermission, notificationsPermission, networkPermission);
        setReportsAndEmailPermission(reportsPermission, emailPermission);
    }
}

void Widget::activateBasicConfigurations()
{
    ui->mainTabsWidget->setTabEnabled(1, true);
    ui->loginScreenViewsStack->setCurrentIndex(1);
    ui->UACScreenViewsStack->setCurrentIndex(0);
    QString fileName = logsDirectory + "/tempUserInfoLog.txt";
    QFile file(fileName);
    QString profileFirstName;
    QString profileLastName;
    QString profilePhoneNumber;
    QString profileEmail;
    if (file.open(QIODevice::ReadOnly)){
        QTextStream nameStream(&file);
        QString myFileText = nameStream.readAll();
        QStringList myText = myFileText.split("\n");
        profileFirstName = myText[0];
        profileLastName = myText[1];
        profilePhoneNumber = myText[4];
        profileEmail = myText[2];
    }
    file.close();
    ui->logoutUserNameLabel->setText(profileFirstName + " " + profileLastName);
    ui->UACuserViewScreenPageNestedWidgetUserFirstLastNameLabel->setText(profileFirstName + " " + profileLastName);
    ui->UACuserViewScreenPageNestedWidgetUserPhoneNumberLineEdit->setText(profilePhoneNumber);
    ui->UACuserViewScreenPageNestedWidgetUserEmailLineEdit->setText(profileEmail);
}

void Widget::activateAllPermissions()
{
    ui->UACuserViewScreenPageNestedWidgetUserProfileToolToAdminViewButton->setEnabled(true);

    ui->mainTabsWidget->setTabEnabled(2, true);
    ui->devicesTabAddButton->setEnabled(true);
    ui->devicesTabUpdateButton->setEnabled(true);
    ui->devicesTabDeleteButton->setEnabled(true);
    ui->UACuserViewScreenPageNestedWidgetDevicesCheckBox->setChecked(true);
    ui->UACuserViewScreenPageNestedWidgetAddCheckBox->setChecked(true);
    ui->UACuserViewScreenPageNestedWidgetModifyCheckBox->setChecked(true);
    ui->UACuserViewScreenPageNestedWidgetRemoveCheckBox->setChecked(true);

    ui->mainTabsWidget->setTabEnabled(3, true);
    ui->UACuserViewScreenPageNestedWidgetReportsCheckBox->setChecked(true);
    ui->UACuserViewScreenPageNestedWidgetEmailCheckBox->setChecked(true);

    ui->mainTabsWidget->setTabEnabled(4, true);
    ui->settingsTabNestedWidgetnotificationsPushButton->setEnabled(true);
    ui->settingsTabNestedWidgetnetworkPushButton->setEnabled(true);
    ui->UACuserViewScreenPageNestedWidgetSettingsCheckBox->setChecked(true);
    ui->UACuserViewScreenPageNestedWidgetNotificationsCheckBox->setChecked(true);
    ui->UACuserViewScreenPageNestedWidgetNetworkCheckBox->setChecked(true);
}

void Widget::disableAdminPermissions()
{
    ui->UACuserViewScreenPageNestedWidgetUserProfileToolToAdminViewButton->setEnabled(false);
}

void Widget::setDevicePermissions(int device, int add, int modify, int remove)
{
    if (device == 1){
        ui->mainTabsWidget->setTabEnabled(2, true);
        ui->UACuserViewScreenPageNestedWidgetDevicesCheckBox->setChecked(true);

        if (add == 1){
            ui->devicesTabAddButton->setEnabled(true);
            ui->UACuserViewScreenPageNestedWidgetAddCheckBox->setChecked(true);
        } else if (add == 0){
            ui->devicesTabAddButton->setEnabled(false);
            ui->UACuserViewScreenPageNestedWidgetAddCheckBox->setChecked(false);
        }

        if (modify == 1){
            ui->devicesTabUpdateButton->setEnabled(true);
            ui->UACuserViewScreenPageNestedWidgetModifyCheckBox->setChecked(true);
        } else if (modify == 0){
            ui->devicesTabUpdateButton->setEnabled(false);
            ui->UACuserViewScreenPageNestedWidgetModifyCheckBox->setChecked(false);
        }

        if (remove == 1){
            ui->devicesTabDeleteButton->setEnabled(true);
            ui->UACuserViewScreenPageNestedWidgetRemoveCheckBox->setChecked(true);
        } else if (remove == 0){
            ui->devicesTabDeleteButton->setEnabled(false);
            ui->UACuserViewScreenPageNestedWidgetRemoveCheckBox->setChecked(false);
        }

    } else if (device == 0){
        ui->mainTabsWidget->setTabEnabled(2, false);
        ui->devicesTabAddButton->setEnabled(false);
        ui->devicesTabUpdateButton->setEnabled(false);
        ui->devicesTabDeleteButton->setEnabled(false);
        ui->UACuserViewScreenPageNestedWidgetDevicesCheckBox->setChecked(false);
        ui->UACuserViewScreenPageNestedWidgetAddCheckBox->setChecked(false);
        ui->UACuserViewScreenPageNestedWidgetModifyCheckBox->setChecked(false);
        ui->UACuserViewScreenPageNestedWidgetRemoveCheckBox->setChecked(false);
    }

}

void Widget::setSettingsPermissions(int settings, int notifications, int network)
{
    if (settings == 1){
        ui->mainTabsWidget->setTabEnabled(4, true);
        ui->UACuserViewScreenPageNestedWidgetSettingsCheckBox->setChecked(true);

        if (notifications == 1){
            ui->settingsTabNestedWidgetnotificationsPushButton->setEnabled(true);
            ui->UACuserViewScreenPageNestedWidgetNotificationsCheckBox->setChecked(true);
        } else if (notifications == 0){
            ui->settingsTabNestedWidgetnotificationsPushButton->setEnabled(false);
            ui->UACuserViewScreenPageNestedWidgetNotificationsCheckBox->setChecked(false);
        }

        if (network == 1){
            ui->settingsTabNestedWidgetnetworkPushButton->setEnabled(true);
            ui->UACuserViewScreenPageNestedWidgetNetworkCheckBox->setChecked(true);
        } else if (network == 0){
            ui->settingsTabNestedWidgetnetworkPushButton->setEnabled(false);
            ui->UACuserViewScreenPageNestedWidgetNetworkCheckBox->setChecked(false);
        }

    } else if (settings == 0){
        ui->mainTabsWidget->setTabEnabled(4, false);
        ui->settingsTabNestedWidgetnotificationsPushButton->setEnabled(false);
        ui->settingsTabNestedWidgetnetworkPushButton->setEnabled(false);
        ui->UACuserViewScreenPageNestedWidgetSettingsCheckBox->setChecked(false);
        ui->UACuserViewScreenPageNestedWidgetNotificationsCheckBox->setChecked(false);
        ui->UACuserViewScreenPageNestedWidgetNetworkCheckBox->setChecked(false);
    }
}

void Widget::setReportsAndEmailPermission(int reports, int email)
{
    if (reports == 1){
        ui->mainTabsWidget->setTabEnabled(3, true);
        ui->UACuserViewScreenPageNestedWidgetReportsCheckBox->setChecked(true);
    } else if (reports == 0){
        ui->mainTabsWidget->setTabEnabled(3, false);
        ui->UACuserViewScreenPageNestedWidgetReportsCheckBox->setChecked(false);
    }

    if (email == 1){
        ui->UACuserViewScreenPageNestedWidgetEmailCheckBox->setChecked(true);
    } else if (email == 0){
        ui->UACuserViewScreenPageNestedWidgetEmailCheckBox->setChecked(false);
    }
}


void Widget::on_devicesTabTableWidget_itemClicked(QTableWidgetItem *item)
{
    int row = item->row();
    int column = item->column();
//    qDebug() << currentDeviceTableWidgetItem;
    if (currentDeviceTableWidgetItem == nullptr){
//        qDebug() << "Null Item";
        currentDeviceTableWidgetItem = item;
    } else{
        previousDeviceTableWidgetItem = currentDeviceTableWidgetItem;
        currentDeviceTableWidgetItem = item;
        previousDeviceTableWidgetItem->setText("");
    }

    ui->devicesTabUpdateButton->setEnabled(true);
    if (column == 1){
        ui->devicesTabDeleteButton->setEnabled(true);
    }

    QString sensorID = ui->devicesTabTableWidget->item(row, 1)->text();
    QSqlQuery selectMACQuery;
    QString selectMACQueryStatement = QString("SELECT MAC FROM config WHERE sensorID = '%1'").arg(sensorID);
    selectMACQuery.exec(selectMACQueryStatement);

    while (selectMACQuery.next()){
        deviceMacAddress = selectMACQuery.value(0).toString();
    }

    connect(ui->devicesTabUpdateButton, &QPushButton::clicked, this, &Widget::captureCellChange, Qt::UniqueConnection);
    connect(ui->devicesTabDeleteButton, &QPushButton::clicked, this, &Widget::removeDevice, Qt::UniqueConnection);
}


void Widget::captureCellChange()
{
//    qDebug() << "macAddress:\t" << macAddress;
//    qDebug() << "sensorID:\t" << ui->devicesTabTableWidget->item(item->row(), 1)->text();
//    qDebug() << "in captureCellChange";
    ui->devicesTabUpdateButton->setEnabled(false);
    ui->devicesTabDeleteButton->setEnabled(false);
//    qDebug() << "after disabling update and delete buttons";

    QString configTableColumnName;
    int column = currentDeviceTableWidgetItem->column();
//    qDebug() << "item->column():\t" << column;
    if (column > -1){
        if (column == 0){
            configTableColumnName = "zoneID";
        }
        if (column == 1){
            configTableColumnName = "sensorID";
        }
        if (column == 4){
            configTableColumnName = "readInterval";
        }
        if (column == 8){
            configTableColumnName = "lowtempthreshold";
        }
        if (column == 9){
            configTableColumnName = "hightempthreshold";
        }
        if (column == 10){
            configTableColumnName = "lowhumiditythreshold";
        }
        if (column == 11){
            configTableColumnName = "highhumiditythreshold";
        }
//        qDebug() << "configTableColumnName:\t" << configTableColumnName;

        QSqlQuery updateQuery;
        QString updateQueryStatement = QString("UPDATE config SET %1 = '%2' WHERE MAC = '%3'")
                .arg(configTableColumnName).arg(currentDeviceTableWidgetItem->text()).arg(deviceMacAddress);
        if (updateQuery.exec(updateQueryStatement)){
//            qDebug() << "updateQuery successful";
            populateDevicesTableWidget();
        } else{
//            qDebug() << "updateQuery unsuccessful";
            QMessageBox::warning(this, tr("Warning!"), "Your current update(s) could not be saved at this time.");
        }
    } else {
        QMessageBox::information(this, tr("Notice"), "No changes have been made at this time.");
    }

    checkDevicesForInfo();
}

void Widget::removeDevice()
{
    ui->devicesTabUpdateButton->setEnabled(false);
    ui->devicesTabDeleteButton->setEnabled(false);

    QString criticalWarning = "Are you sure you wish to remove this data logger from your device list?"
                              "\nThis action cannot be undone.";
    QMessageBox::StandardButton reply;
    reply = QMessageBox::warning(this, tr("Critical Warning!"), criticalWarning, QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes){
        QSqlQuery deleteQuery;
        QString deleteQueryStatement = QString("DELETE FROM config WHERE sensorID = '%1'").arg(currentDeviceTableWidgetItem->text());
        if (deleteQuery.exec(deleteQueryStatement)){
            populateDevicesTableWidget();
            QMessageBox::information(this, tr("Device Removed"), "Your selected device has been removed.");
        } else{
            QMessageBox::warning(this, tr("Error"), "This action cannot be performed at this time.");
        }
    }
}

void Widget::checkDevicesForInfo()
{
    for (int i = 0; i < ui->devicesTabTableWidget->rowCount(); i++){
        if (ui->devicesTabTableWidget->itemAt(i, 0) &&
                ui->devicesTabTableWidget->itemAt(i, 8) &&
                ui->devicesTabTableWidget->itemAt(i, 9) &&
                ui->devicesTabTableWidget->itemAt(i, 10) &&
                ui->devicesTabTableWidget->itemAt(i, 11)){
            QString request = "Please enter in a ZoneID and thresholds for " + ui->devicesTabTableWidget->item(i, 1)->text();
            QMessageBox::warning(this, tr("Missing Data!"), request);
        }
    }
}

void Widget::on_reportsTabNestedWidgetCaptureButton_clicked()
{
    populateReportsTableWidget();
}

void Widget::on_UACadminViewScreenPageNestedWidgetMyProfileButton_clicked()
{
    ui->UACScreenViewsStack->setCurrentIndex(1);
    ui->mainTabsWidget->setTabText(1, "    Profile    ");

}

void Widget::on_UACuserViewScreenPageNestedWidgetUserProfileToolToAdminViewButton_clicked()
{
    ui->UACScreenViewsStack->setCurrentIndex(0);
    ui->mainTabsWidget->setTabText(1, "     Users     ");
}

void Widget::monitorDevicePermissions()
{
//    qDebug() << "in monitorDevicePermissions";
    QWidget *widget = ui->UACTableWidget->cellWidget(monitorAdminIndexRow, 1);
    monitorDevicesCheckBox = widget->findChild<QCheckBox *>();
    if (monitorDevicesCheckBox->isChecked()){
        for (int i = 2; i < 5; i++){
            QWidget *deviceWidget = ui->UACTableWidget->cellWidget(monitorAdminIndexRow, i);
            QCheckBox *deviceCheckBox = deviceWidget->findChild<QCheckBox *>();
            deviceCheckBox->setCheckable(true);
        }
    } else if (!monitorDevicesCheckBox->isChecked()){
        for (int i = 2; i < 5; i++){
            QWidget *deviceWidget = ui->UACTableWidget->cellWidget(monitorAdminIndexRow, i);
            QCheckBox *deviceCheckBox = deviceWidget->findChild<QCheckBox *>();
            deviceCheckBox->setCheckable(false);
        }
    }
}

void Widget::monitorSettingsPermissions()
{
//    qDebug() << "in monitorSettingsPermissions";
    QWidget *widget = ui->UACTableWidget->cellWidget(monitorAdminIndexRow, 7);
    monitorSettingsCheckBox = widget->findChild<QCheckBox *>();
    if (monitorSettingsCheckBox->isChecked()){
        for (int i = 8; i < 10; i++){
            QWidget *settingsWidget = ui->UACTableWidget->cellWidget(monitorAdminIndexRow, i);
            QCheckBox *settingsCheckBox = settingsWidget->findChild<QCheckBox *>();
            settingsCheckBox->setCheckable(true);
        }
    } else if (!monitorSettingsCheckBox->isChecked()){
        for (int i = 8; i < 10; i++){
            QWidget *settingsWidget = ui->UACTableWidget->cellWidget(monitorAdminIndexRow, i);
            QCheckBox *settingsCheckBox = settingsWidget->findChild<QCheckBox *>();
            settingsCheckBox->setCheckable(false);
        }
    }
}

void Widget::on_mainTabsWidget_tabBarClicked(int index)
{
//    qDebug() << "in mainTabsWidget";
    if (index == 1){
        populateUACTableWidget();
    }
}

void Widget::on_logoutScreenPageNestedWidgetLogoutButton_clicked()
{
    setAllDefaultsOff();
}
