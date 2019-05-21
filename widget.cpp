#include "widget.h"
#include "ui_widget.h"

#include "devicesdialogbox.h"
#include "periodsdialogbox.h"
#include "quickviewsdialogbox.h"
#include "readingsdialogbox.h"
#include "zonesdialogbox.h"
#include "helpdialog.h"
#include "previoususersdialog.h"
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
    return createdDirectory;
}

Widget::~Widget()
{
    delete ui;
}

void Widget::setWidgetConfigs()
{
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
    setDefaults();

    createDirectories();
    connectToDatabase();
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

    ui->devicesTabTableWidget->setSortingEnabled(true);
}

void Widget::setReportsTabConfigs()
{
    ui->reportsTabNestedWidget->setFixedSize(ui->reportsTab->width(), ui->reportsTab->height());
    QPixmap pix(":/icons/calendar.png");
    QIcon icon(pix);
    ui->reportsTabNestedWidgetEndDateDateEdit->setDate(QDate::currentDate());
    ui->reportsTabNestedWidgetStartDateDateEdit->setCalendarPopup(true);
    ui->reportsTabNestedWidgetEndDateDateEdit->setCalendarPopup(true);
}

void Widget::setSettingsTabConfigs()
{
    ui->settingsTabNestedWidget->setFixedSize(ui->settingsTab->width(), ui->settingsTab->height());
}

void Widget::setDefaults()
{
    //set default view of application upon open
    ui->mainTabsWidget->setCurrentIndex(0);
    ui->loginScreenViewsStack->setCurrentIndex(1);
//    ui->tabWidget->setTabEnabled(1, false);
//    ui->tabWidget->setTabEnabled(2, false);
//    ui->tabWidget->setTabEnabled(3, false);
    //    ui->tabWidget->setTabEnabled(4, false);
}

void Widget::addUserRowToTableWidget(AddAUserDialog *user)
{
    ui->UACTableWidget->insertRow(ui->UACTableWidget->rowCount());

    QStringList usersInfo = user->getUserInfo();
    QTableWidgetItem *userName = new QTableWidgetItem(usersInfo[0] + " " + usersInfo[1]);
    QTableWidgetItem *userEmail = new QTableWidgetItem(usersInfo[3]);
    QTableWidgetItem *userNumber = new QTableWidgetItem(usersInfo[2]);
    userName->setFlags(Qt::NoItemFlags);
    userEmail->setFlags(Qt::NoItemFlags);
    userNumber->setFlags(Qt::NoItemFlags);
    ui->UACTableWidget->setItem(ui->UACTableWidget->rowCount()-1 ,0, userName);
    ui->UACTableWidget->setItem(ui->UACTableWidget->rowCount()-1, 11, userEmail);
    ui->UACTableWidget->setItem(ui->UACTableWidget->rowCount()-1, 12, userNumber);


    QList<bool> permissions {};
    permissions.append(user->getDataLoggerPermission());//0
    permissions.append(user->getAddDevicePermission());//1
    permissions.append(user->getModifyDevicePermission());//2
    permissions.append(user->getRemoveDevicePermission());//3
    permissions.append(user->getUserAdminPermission());//4
    permissions.append(user->getReportsPermission());//5
    permissions.append(user->getSettingsPermission());//6
    permissions.append(user->getNotificationsPermission());//7
    permissions.append(user->getNetworksPermission());//8
    permissions.append(user->getEmailPermission());//9
    for (int i = 0; i < permissions.length(); i++){
        QWidget *checkBoxWidget = new QWidget();
        QCheckBox *checkBox = new QCheckBox();
        QHBoxLayout *layout = new QHBoxLayout(checkBoxWidget);
        if (permissions[i] == true){
            checkBox->setCheckState(Qt::Checked);
        } else {
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
    ui->UACTableWidget->setCellWidget(ui->UACTableWidget->rowCount()-1, 13, resetButtonWidget);



    QWidget *deleteButtonWidget = new QWidget();
    QPushButton *deleteButton = new QPushButton();
    deleteButton->setText("Delete");
    QHBoxLayout *deleteButtonlayout = new QHBoxLayout(deleteButtonWidget);
    connect(deleteButton, &QPushButton::clicked, this, &Widget::monitorDeleteUsers, Qt::UniqueConnection);
    deleteButtonlayout->addWidget(deleteButton);
    deleteButtonlayout->setAlignment(Qt::AlignCenter);
    deleteButtonlayout->setContentsMargins(0,0,0,0);
    deleteButtonWidget->setLayout(deleteButtonlayout);
    deleteButtonWidget->setEnabled(false);
    ui->UACTableWidget->setCellWidget(ui->UACTableWidget->rowCount()-1, 14, deleteButtonWidget);

    qDebug() << "user added";


}

void Widget::monitorAdminStatus()
{
    qDebug() << "in monitorAdminStatus";
    qDebug() << "current index is: " << monitorAdminIndexRow;

    QWidget *widget = ui->UACTableWidget->cellWidget(monitorAdminIndexRow, 5);
    monitorAdminCheckBox = widget->findChild<QCheckBox *>();
    connect(monitorAdminCheckBox, &QCheckBox::toggled, this, &Widget::checkAdminBox, Qt::UniqueConnection);
}

void Widget::checkAdminBox()
{
    qDebug() << "in checkAdminBox";

    if (monitorAdminCheckBox->isChecked()){
        qDebug() << "admin box is checked";
        for (int j = 1; j < 11; j++){
            QWidget *widget = ui->UACTableWidget->cellWidget(monitorAdminIndexRow, j);
            QCheckBox *checkBox = widget->findChild<QCheckBox *>();
            checkBox->setCheckState(Qt::Checked);
        }
    } else if (!monitorAdminCheckBox->isChecked()){
        qDebug() << "admin box is unchecked";
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

void Widget::monitorDeleteUsers()
{
    qDebug() << "Delete button clicked for row";
    archiveUser();
}

void Widget::archiveUser()
{
    //connect to database
    //locate user in user USER TABLE using USER ID
    //change active status to false
    //capture user's first and last name
    //remove from UACTableWidget
}

void Widget::setDefaultPermissions(int i)
{
    qDebug() << "in setDefaultPermissions";
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
    qDebug() << "reset password button clicked for row";
    newTempPassword = alphaNumGenerator();
    qDebug() << newTempPassword;


}

void Widget::on_reportsTabNestedWidgetQuickViewsPushButton_clicked()
{
    quickViewsDialogBox *quickViews = new quickViewsDialogBox(this);

    quickViews->setCurrentRadioButton(currentButtonByAssociation);

    connect(quickViews, &quickViewsDialogBox::accepted, [=](){
        currentButtonByAssociation = quickViews->getCurrentRadioButton();
        if (currentButtonByAssociation == 1){
            QDateTime fullDay = QDateTime::currentDateTime();
            QDateTime yesterday = fullDay.addDays(-1);
            ui->reportsTabNestedWidgetEndDateDateEdit->setDate(fullDay.date());
            ui->reportsTabNestedWidgetStartDateDateEdit->setDate(yesterday.date());
            ui->reportsTabNestedWidgetStartTimeTimeEdit->setTime(fullDay.time());
            ui->reportsTabNestedWidgetEndTimeTimeEdit->setTime(fullDay.time());
        } else if (currentButtonByAssociation == 2){
            QTime time = QTime(openCloseHoursMinutes[0], openCloseHoursMinutes[1]);
            ui->reportsTabNestedWidgetStartTimeTimeEdit->setTime(time);
            time = QTime(openCloseHoursMinutes[2], openCloseHoursMinutes[3]);
            ui->reportsTabNestedWidgetEndTimeTimeEdit->setTime(time);
        } else if (currentButtonByAssociation == 3){
            QTime time = QTime(openCloseHoursMinutes[2], openCloseHoursMinutes[3]+1);
            ui->reportsTabNestedWidgetEndTimeTimeEdit->setTime(time);
            if (openCloseHoursMinutes[1] == 0){
                time = QTime(openCloseHoursMinutes[0]-1, 59);
            } else{
                time = QTime(openCloseHoursMinutes[0], openCloseHoursMinutes[1]-1);
            }
            ui->reportsTabNestedWidgetStartTimeTimeEdit->setTime(time);
        } else if (currentButtonByAssociation == 4){
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
    connect(devices, &DevicesDialogBox::accepted, [=](){
        devicesCheckBoxes.clear();
        devicesCheckBoxes = devices->getCheckBoxes();
    });
    devices->show();
}

void Widget::on_reportsTabNestedWidgetReadingsPushButton_clicked()
{
    ReadingsDialogBox *readings = new ReadingsDialogBox(this);
    readings->show();
}

void Widget::on_reportsTabNestedWidgetPeriodsPushButton_clicked()
{
    PeriodsDialogBox *periods = new PeriodsDialogBox(this);
    periods->show();
}

void Widget::on_settingsTabNestedWidgethelpPushButton_clicked()
{
    HelpDialog *helpScreen = new HelpDialog(this);
    helpScreen->show();
}

void Widget::on_UACAddAUserButton_clicked()
{
    AddAUserDialog *addUser = new AddAUserDialog(this);
    connect(addUser, &AddAUserDialog::accepted, [=](){
        addUserToUserTable(addUser);
        addUserRowToTableWidget(addUser);
    });

    addUser->show();
}

void Widget::on_logoutScreenPageClearNotificationsButton_clicked()
{
    ui->logoutScreenPageNotificationsListWidget->clear();
}

void Widget::on_UACPreviousUsersButton_clicked()
{
    PreviousUsersDialog *previousUsers = new PreviousUsersDialog(this);
    previousUsers->show();
}

void Widget::on_UACTableWidget_itemClicked(QTableWidgetItem *item)
{
    monitorAdminIndexRow = item->row();
    item->setTextColor("green");
    selectedItemFont = item->font();
    QFont font;
    font.setBold(true);
    font.setFamily("Consolas");
    item->setFont(font);
    UACTableWidgetItem = item;
    ui->UACadminViewScreenPageNestedWidgetEditButton->setEnabled(true);
}

void Widget::captureAdditionalAdminData(AdditionalSettingsNotificationsDialog *additionalSettings)
{
    if (!openCloseHoursMinutes.isEmpty()){
        openCloseHoursMinutes.clear();
        openCloseHoursMinutes.append(0);
        openCloseHoursMinutes.append(0);
        openCloseHoursMinutes.append(0);
        openCloseHoursMinutes.append(0);
    } else{
        openCloseHoursMinutes.append(0);
        openCloseHoursMinutes.append(0);
        openCloseHoursMinutes.append(0);
        openCloseHoursMinutes.append(0);
    }

    int hour = additionalSettings->getOpenTimeHour();
    int minute = additionalSettings->getOpenTimeMinute();
    openCloseHoursMinutes[0] = hour;
    openCloseHoursMinutes[1] = minute;

    hour = additionalSettings->getCloseTimeHour();
    minute = additionalSettings->getCloseTimeMinute();
    openCloseHoursMinutes[2] = hour;
    openCloseHoursMinutes[3] = minute;

    companyAddress = additionalSettings->getCompanyAddress();
    companyName = additionalSettings->getCompanyName();
    companyPhoneNumber = additionalSettings->getCompanyPhoneNumber();
}

void Widget::on_settingsTabNestedWidgetnotificationsPushButton_clicked()
{
    AdditionalSettingsNotificationsDialog *additionalSettings = new AdditionalSettingsNotificationsDialog(this);


    setAdditionalAdminData(additionalSettings);

    connect(additionalSettings, &AdditionalSettingsNotificationsDialog::accepted, [=](){
        captureAdditionalAdminData(additionalSettings);
        qDebug() << "main widget layer";
        qDebug() << openCloseHoursMinutes;
        qDebug() << companyName;
        qDebug() << companyAddress;
        qDebug() << companyPhoneNumber;
    });
    additionalSettings->show();
}

void Widget::toggleAdminUACCheckBoxStatuses()
{

    for (int i = 1; i < 11; i++){
        QWidget *widget = ui->UACTableWidget->cellWidget(monitorAdminIndexRow, i);
        QCheckBox *checkBox = widget->findChild<QCheckBox *>();
        if (!checkBox->isEnabled()){
            checkBox->setEnabled(true);
        } else if (checkBox->isEnabled()){
            checkBox->setEnabled(false);
        }
    }

    QWidget *widgetButton = ui->UACTableWidget->cellWidget(monitorAdminIndexRow, 13);
    if(!widgetButton->isEnabled()){
        widgetButton->setEnabled(true);
    } else if (widgetButton->isEnabled()){
        widgetButton->setEnabled(false);
    }

    QWidget *widgetButton2 = ui->UACTableWidget->cellWidget(monitorAdminIndexRow, 14);
    if(!widgetButton2->isEnabled()){
        widgetButton2->setEnabled(true);
    } else if (widgetButton2->isEnabled()){
        widgetButton2->setEnabled(false);
    }
}

void Widget::setAdditionalAdminData(AdditionalSettingsNotificationsDialog *additionalSettings)
{
    additionalSettings->setOpenTime(openCloseHoursMinutes[0], openCloseHoursMinutes[1]);
    additionalSettings->setCloseTime(openCloseHoursMinutes[2], openCloseHoursMinutes[3]);
    additionalSettings->setCompanyName(companyName);
    additionalSettings->setCompanyAddress(companyAddress);
    additionalSettings->setCompanyPhoneNumber(companyPhoneNumber);
}

void Widget::on_UACadminViewScreenPageNestedWidgetEditButton_clicked()
{
    toggleAdminUACCheckBoxStatuses();
    monitorAdminStatus();
    ui->UACadminViewScreenPageNestedWidgetEditButton->setText("Save");
    connect(ui->UACadminViewScreenPageNestedWidgetEditButton, &QPushButton::clicked, [=](){
        //capture the permissions that were just saved
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
        bool ok;
        int hex = binaryToHex.toInt(&ok, 2);
        QString finalHex = QString::number(hex, 16);
        //update database permission for user
        //WILL NEED TO CHECK THIS FOR SUCCESS ONCE FULL DATABASE COMMUNICATIONS ARE OCCURRING
        QString updateQuery;
        updateQuery = QString("UPDATE users SET perms = " + finalHex);
        updateQuery.append(" WHERE firstname = ");
        QString fullName = ui->UACTableWidget->item(monitorAdminIndexRow, 0)->text();
        updateQuery.append(fullName.split(" ").front());
        updateQuery.append(" AND lastname = ");
        updateQuery.append(fullName.split(" ").back());
        QSqlQuery update;
        update.exec(updateQuery);

        ui->UACadminViewScreenPageNestedWidgetEditButton->setText("Edit");
        ui->UACadminViewScreenPageNestedWidgetEditButton->setEnabled(false);
        UACTableWidgetItem->setTextColor("black");
        UACTableWidgetItem->setFont(selectedItemFont);
        monitorAdminIndexColumn = 0;
    });
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

QString Widget::getCompanyName()
{
    return companyName;
}

QString Widget::getCompanyAddressLine1()
{
    return companyAddress.split("\n").front();
}

QString Widget::getCompanyAddressLine2()
{
    return companyAddress.split("\n").back();
}

QString Widget::getCompanyPhoneNumber()
{
    return companyPhoneNumber;
}

void Widget::addUserToUserTable(AddAUserDialog *addUser)
{
    QSqlQuery insertQuery;
    insertQuery.exec("SELECT * FROM users");
    int userCount = insertQuery.size();
    qDebug() << userCount;
    QStringList usersInfo = addUser->getUserInfo();
    QString firstName = usersInfo[0];
    QString lastName = usersInfo[1];
    QString userNumber = usersInfo[2];
//    qDebug() << userNumber;
    QString email = usersInfo[3];

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
//    qDebug() << binaryToHex;
    bool ok;
    int hex = binaryToHex.toInt(&ok, 2);
    QString finalHex = QString::number(hex, 16);
//    qDebug() << finalHex;
//    int bin = finalHex.toInt(&ok, 16);
//    QString hexToBinary = QString::number(bin, 2);
//    qDebug() << hexToBinary;
    bool activeStatus = true;
    QDateTime hireDate = QDateTime::currentDateTime();
    int userID = userCount+1;
    QString queryStatement = QString("INSERT INTO users ");
    queryStatement.append("(userID, firstname, lastname, activestatus, ");
    queryStatement.append("email, hiredate, phonenumber, permissions) ");
    queryStatement.append("VALUES (");
    queryStatement.append(QString::number(userID));
    queryStatement.append(", ");
    queryStatement.append(firstName);
    queryStatement.append(", ");
    queryStatement.append(lastName);
    queryStatement.append(", ");
    queryStatement.append(QString::number(activeStatus));
    queryStatement.append(", ");
    queryStatement.append(email);
    queryStatement.append(", ");
    queryStatement.append(hireDate.toString("yyyy-MM-dd hh:mm:ss"));
    queryStatement.append(", ");
    queryStatement.append(userNumber);
    queryStatement.append(", ");
    queryStatement.append(finalHex);
    queryStatement.append(");");

//    insertQuery.prepare("INSERT INTO users (userID, firstname, lastname, activestatus, email, hiredate, phonenumber, permissions) VALUES (:pk, :fname, :lname, :status, :email, :hd, :pn, :perms");
//    insertQuery.bindValue(":id", userID);
//    insertQuery.bindValue(":fname", firstName);
//    insertQuery.bindValue(":lname", lastName);
//    insertQuery.bindValue(":status", activeStatus);
//    insertQuery.bindValue(":email", email);
//    insertQuery.bindValue(":hd", hireDate.toString("yyyy-MM-dd hh:mm:ss"));
//    insertQuery.bindValue(":pn", userNumber);
//    insertQuery.bindValue(":perms", finalHex);



    qDebug() << queryStatement << "\n";
    insertQuery.exec(queryStatement);
    if (!insertQuery.exec(queryStatement)){
        qDebug() << insertQuery.lastError().text();
    }

}

void Widget::connectToDatabase()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setDatabaseName("HuTemp");
    db.setHostName("10.0.0.4");
    db.setUserName("HuTempApp");
    db.setPassword("cookie");

    dbOpen = db.open();
    if(dbOpen){
        QSqlQuery mainquery(db);
        QMessageBox::information(this, "Connection", "Successful connection");
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
        QMessageBox::warning(this, "Connection", QString(db.lastError().text()));
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
    QString charList = "0123456789abcdefghijklmnopqrdtuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ?$@!;()&";
    QString tempWord = "";
    for (int i = 0; i < 10; i++){
        tempWord += charList[rand() % charList.count()];
    }
    return tempWord;
}

void Widget::createDirectories()
{
    createdDirectory = QCoreApplication::applicationDirPath() + "/logs";
    QDir dir;
    dir.mkdir(createdDirectory);
    SetFileAttributesA(createdDirectory.toStdString().c_str(), FILE_ATTRIBUTE_HIDDEN);
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
    //update the devicestabtablewidget based on the latest information from the database
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
