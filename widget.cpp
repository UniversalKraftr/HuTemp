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
    setDefaults();


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
    populateTableWidget();
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

void Widget::populateTableWidget()
{
    if (ui->UACTableWidget->rowCount() > 0){
        ui->UACTableWidget->clear();
    }
    QSqlQuery getUserTableQuery;
    QString selectStatement = "SELECT * FROM users WHERE activestatus = 1";
    getUserTableQuery.exec(selectStatement);
//    int rowCount = 0;
    if (getUserTableQuery.size() > 0){
        while (getUserTableQuery.next()){
//            rowCount += 1;
            ui->UACTableWidget->insertRow(ui->UACTableWidget->rowCount());

            QString firstName = getUserTableQuery.value(1).toString();
            QString lastName = getUserTableQuery.value(2).toString();
            QTableWidgetItem *userName = new QTableWidgetItem(firstName + " " + lastName);
            QTableWidgetItem *userEmail = new QTableWidgetItem(getUserTableQuery.value(4).toString());
            QTableWidgetItem *userNumber = new QTableWidgetItem(getUserTableQuery.value(6).toString());
            QTableWidgetItem *userHireDate = new QTableWidgetItem(getUserTableQuery.value(5).toString());
            userName->setFlags(Qt::NoItemFlags);
            userEmail->setFlags(Qt::NoItemFlags);
            userNumber->setFlags(Qt::NoItemFlags);
            userHireDate->setFlags(Qt::NoItemFlags);
            ui->UACTableWidget->setItem(ui->UACTableWidget->rowCount()-1,0, userName);
            ui->UACTableWidget->setItem(ui->UACTableWidget->rowCount()-1, 11, userEmail);
            ui->UACTableWidget->setItem(ui->UACTableWidget->rowCount()-1, 12, userNumber);
            ui->UACTableWidget->setItem(ui->UACTableWidget->rowCount()-1, 13, userHireDate);

            bool ok;
            QString userPermissions = getUserTableQuery.value(7).toString();
            int hexToBinary = userPermissions.toInt(&ok, 16);
            QString binary = QString::number(hexToBinary, 2);
            for (int i = 0; i < binary.count(); i++){
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
            ui->UACTableWidget->setCellWidget(ui->UACTableWidget->rowCount()-1, 15, deleteButtonWidget);
        }
    }
//    qDebug() << "user added";
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

void Widget::monitorDeleteUsers()
{
    qDebug() << "Delete button clicked for row";
    archiveUser();
}

void Widget::archiveUser()
{
    //locate user in user USER TABLE using USER ID
    //change active status to false
    //update table widget with user table
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
//    qDebug() << "reset password button clicked for row";
    newTempPassword = alphaNumGenerator();
//    qDebug() << newTempPassword;
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
    AddAUserDialog *addUser = new AddAUserDialog(this);
    connect(addUser, &AddAUserDialog::accepted, [=](){
        addUserToUserTable(addUser);
        populateTableWidget();
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
//    qDebug() << "in itemClicked";
    if (ui->UACadminViewScreenPageNestedWidgetEditButton->isEnabled() || ui->UACadminViewScreenPageNestedWidgetSaveButton->isEnabled())
    {
        QMessageBox::warning(this, tr("Error"), "You can only select one user at a time!");
    } else{
        item->setTextColor("green");
        selectedItemFont = item->font();
        QFont font;
        font.setBold(true);
        font.setFamily("Consolas");
        if (UACTableWidgetItem->text() == nullptr){
            UACTableWidgetItem = item;
        } else{
            if (UACTableWidgetItem != item){
                UACTableWidgetItem->setTextColor("black");
                UACTableWidgetItem->setFont(selectedItemFont);
                UACTableWidgetItem = item;
            }
        }
        monitorAdminIndexRow = UACTableWidgetItem->row();
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
    qDebug() << "editButton clicked";
    qDebug() << "current index = " << monitorAdminIndexRow;
    ui->UACadminViewScreenPageNestedWidgetEditButton->setEnabled(false);
    ui->UACadminViewScreenPageNestedWidgetSaveButton->setEnabled(true);
    monitorAdminStatus();
    toggleAdminUACCheckBoxStatuses();
}

void Widget::on_UACadminViewScreenPageNestedWidgetSaveButton_clicked()
{
    qDebug() << "save button clicked";
    qDebug() << "current index = " << monitorAdminIndexRow;
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
    bool ok;
    int hex = binaryToHex.toInt(&ok, 2);
    QString finalHex = QString::number(hex, 16);

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

void Widget::sendMail(QString userEmail, QString tempPassword)
{
    //    qDebug() << "in sendMail";
        Smtp *smtp = new Smtp("hutempcs@gmail.com", "|WjzL]sa[|3", "smtp.gmail.com", 465);
        connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));
        QString subjectLine = "HuTemp - New Account -->(DO NOT REPLY TO THIS EMAIL)";
        QString message = "You account has been activated for HuTemp use. "
                          "Please review the following information below.\n\n";
        message += "Login Credentials:\n\t";
        message += "Username:\t";
        message += userEmail;
        message += "\n\tTemporary Password:\t";
        message += tempPassword;
        message += "\n\n\n\n";
        message += "Please make an attempt to login with these credentials.\n";
        message += "For support, review the User Manual, or contact your manager.\n";
        message += "\n\n\n=========================================";
        message += "DO NOT REPLY TO THIS EMAIL";


        if(!files.isEmpty()){
    //        qDebug() << "!files.isEmpty()";
            smtp->sendMail("hutempcs@gmail.com", userEmail , subjectLine, message, files );
        } else{
    //        qDebug() << "files.isEmpty()";
            smtp->sendMail("hutempcs@gmail.com", userEmail , subjectLine, message);
        }
}

void Widget::mailSent(QString status)
{
    if(status == "Message sent"){
        QMessageBox::warning(this, "New Account", "Notify the account holder to check their email for their login credentials.");
    }
}

void Widget::addUserToLoginTable(QString userEmail)
{
    QSqlQuery checkQuery;
    checkQuery.exec("SELECT * FROM login");
    bool check = true;
    while (checkQuery.next()){
        QString username = checkQuery.value(1).toString();
        if (userEmail == username){
            QMessageBox::warning(this, tr("CRITICAL ERROR"), "This user email has already been used! Provide a different email!");
            check = false;
            break;
        }
    }
    if (check == true){
        qDebug() << "check is true";
        QSqlQuery insertQuery;
        resetPassword();
        QString insertStatement = QString("INSERT INTO login (username, password, temporarypassword) VALUES ('%1', '%2', 1)").arg(userEmail).arg(newTempPassword);
        if (insertQuery.exec(insertStatement)){
            qDebug() << "successful logins table query";
        } else{
            qDebug() << "unsuccessful logins table query";
        }
    } else{
        qDebug() << "check is false";
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
//    qDebug() << binaryToHex;
    bool ok;
    int hex = binaryToHex.toInt(&ok, 2);
    QString finalHex = QString::number(hex, 16);
//    qDebug() << finalHex;
//    int bin = finalHex.toInt(&ok, 16);
//    QString hexToBinary = QString::number(bin, 2);
//    qDebug() << hexToBinary;
    bool activeStatus = true;

    QString queryStatement = QString("INSERT INTO users (firstname, lastname, activestatus, email, hiredate, phonenumber, permissions) "
                             "VALUES ('%1', '%2', %3, '%4', '%5', '%6', '%7')").arg(firstName).arg(lastName).arg(QString::number(activeStatus))
            .arg(email).arg(hireDate).arg(userNumber).arg(finalHex);

    insertQuery.exec(queryStatement);

    addUserToLoginTable(userEmail);
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
    db.setHostName("10.0.0.10");
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

void Widget::on_reportsTabNestedWidgetResetButton_clicked()
{
    ui->reportsTabNestedWidgetTableWidget->clearContents();
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
}


