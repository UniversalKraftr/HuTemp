#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDesktopWidget>
#include <QScreen>
#include <QCheckBox>
#include <QModelIndex>
#include <QTableWidgetItem>
#include <QProcess>
#include <QMessageBox>
#include <QRadioButton>
#include <QtMath>
#include <QDebug>
#include <QTime>
#include <QFont>
#include <QFile>
#include <QtSql>
#include <QSqlDatabase>
#include <QCryptographicHash>
#include <QRandomGenerator64>
#include <stdlib.h>


#include "smtp.h"
#include "addauserdialog.h"
#include "additionaladminsettingsdialog.h"
#include "additionalsettingsnotificationsdialog.h"


#include "xlsxdocument.h"
#include "xlsxchartsheet.h"
#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include "xlsxrichstring.h"
#include "xlsxworkbook.h"
using namespace QXlsx;


namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    QString getLogFolder();
    QString getPDFFolder();
    QString getUserName();
    QString getUserEmail();
    QString getUserType();
    ~Widget();


private slots:
    void on_reportsTabNestedWidgetQuickViewsPushButton_clicked();
    void on_reportsTabNestedWidgetZonesPushButton_clicked();
    void on_reportsTabNestedWidgetDevicesPushButton_clicked();
    void on_reportsTabNestedWidgetReadingsPushButton_clicked();
    void on_reportsTabNestedWidgetPeriodsPushButton_clicked();
    void on_settingsTabNestedWidgethelpPushButton_clicked();
    void on_UACAddAUserButton_clicked();
    void on_logoutScreenPageClearNotificationsButton_clicked();
    void on_UACPreviousUsersButton_clicked();
    void on_UACTableWidget_itemClicked(QTableWidgetItem *item);
    void on_settingsTabNestedWidgetnotificationsPushButton_clicked();
    void on_UACadminViewScreenPageNestedWidgetEditButton_clicked();
    void on_devicesTabAddButton_clicked();
    void on_devicesTabSortOptionsDropDownBox_currentIndexChanged(int index);
    void on_devicesTabRefreshButton_clicked();
    void on_reportsTabNestedWidgetEndDateDateEdit_userDateChanged(const QDate &date);
    void on_reportsTabNestedWidgetEndTimeTimeEdit_userTimeChanged(const QTime &time);
    void on_reportsTabNestedWidgetResetButton_clicked();
    void on_reportsTabNestedWidgetSnapshotButton_clicked();
    void on_UACadminViewScreenPageNestedWidgetSaveButton_clicked();
    void sendMail(QString, QString, QString, QString);
    void mailSent(QString);
    void on_loginButton_clicked();
    void on_loginScreenPageNestedWidgetPasswordResetButton_clicked();
    void on_devicesTabTableWidget_itemClicked(QTableWidgetItem *item);
    void on_reportsTabNestedWidgetCaptureButton_clicked();
    void on_UACadminViewScreenPageNestedWidgetMyProfileButton_clicked();
    void on_UACuserViewScreenPageNestedWidgetUserProfileToolToAdminViewButton_clicked();
    void on_mainTabsWidget_tabBarClicked(int index);
    void on_logoutScreenPageNestedWidgetLogoutButton_clicked();
    void on_reportsTabNestedWidgetExportButton_clicked();
    void on_settingsTabNestedWidgetnetworkPushButton_clicked();
    void on_reportsTabNestedWidgetUpdateButton_clicked();
    void on_mainTabsWidget_currentChanged(int index);
    void on_loginScreenPageNestedWidgetPasswordRevealConcealPushButton_clicked();
    void on_UACuserViewScreenPageNestedWidgetUpdateButton_clicked();
    void on_UACuserViewScreenPageNestedWidgetHelpButton_clicked();
    void on_UACadminViewScreenPageNestedWidgetHelpButton_clicked();
    void on_devicesTabHelpButton_clicked();
    void on_reportsTabHelpButton_clicked();

private:
    Ui::Widget *ui;
    QString vmDBIPAddress = "10.0.0.14";
    QString KEY = "*:2Q-S9AX||NkvVg<q&i";
    int loginAttempts = 0;
    QString u = QChar(0x00B3);
    const QString title = "HuTemp Life Cycle – H" + u + " Product";
    QString charList = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()-_=+/?><";
    int monitorAdminIndexRow;
    int monitorAdminIndexColumn = 0;
    QTableWidgetItem *UACTableWidgetItem = new QTableWidgetItem(nullptr);
    AddAUserDialog *addUser;
    QCheckBox *monitorAdminCheckBox;
    QCheckBox *monitorDevicesCheckBox;
    QCheckBox *monitorSettingsCheckBox;
    QPushButton *monitorAdminDeleteButton;
    int quickViewsRadioButton = 0;
    int periodsRadioButton = 0;
    QList<int> openCloseHoursMinutes;
    QFont selectedItemFont;
    QString logsDirectory;
    QString pdfDirectory;
    QString reportsDirectory;
    QString newTempPassword;
    QString userFirstName;
    QString userLastName;
    QString userPhoneNumber;
    QString userEmail;
    QString userType;
    bool dbOpen;
    bool deviceModifyPermission;
    bool deviceDeletePermission;
    QList<bool> zonesCheckBoxes;
    QList<bool> devicesCheckBoxes;
    QList<int> readingsCheckBoxes;
    int overallUserCount = 0;
    QStringList files;
    int rowCount = 0;
    int devicesTableWidgetCellRow;
    int devicesTableWidgetCellColumn;
    QString deviceMacAddress;
    QTableWidgetItem *currentDeviceTableWidgetItem = nullptr;
    QTableWidgetItem *previousDeviceTableWidgetItem = new QTableWidgetItem(nullptr);
    QList<bool> reportsTabFilterStatuses {false, false, false};
    QList<QString> messages;



    bool checkFilters();
    void activateExportAndUpdateButtons();
    void configureReportsDateByPeriods();
    void monitorDevicePermissions();
    void monitorSettingsPermissions();
    QString generateHexString(int);
    void loginCurrentUser(QString);
    void activatePermissions(QString);
    void activateBasicConfigurations();
    void activateAllPermissions();
    void disableAdminPermissions();
    void setDevicePermissions(int, int, int, int);
    void setSettingsPermissions(int, int, int);
    void setReportsAndEmailPermission(int, int);
    void addUserToLoginTable(QString);
    void addUserToUserTable();
    void connectToDatabase();
    void extractAllCompanyInfo();
    void extractAllUserInfo();
    QString alphaNumGenerator();
    void createDirectories();
    void toggleAdminUACCheckBoxStatuses();
    void setWidgetConfigs();
    void setTabWidgetConfigs(int widgetWidth, int widgetHeight);
    void setLoginTabConfigs();
    void setUACTabConfigs();
    void setDevicesTabConfigs();
    void setReportsTabConfigs();
    void setSettingsTabConfigs();
    void setAllDefaultsOff();
    void populateUACTableWidget();
    void populateDevicesTableWidget();
    void populateReportsTableWidget();
    void monitorAdminStatus();
    void checkAdminBox();
    void archiveUser();
    void monitorUserPasswordResets();
    void setDefaultPermissions(int i);
    void resetPassword();
    QString convertToHex(QString);
    QString convertToBinary(QString);
    QString encrypt(QString);
    QString decrypt(QString);
    QString generateOffset(QString);
    void captureCellChange();
    void removeDevice();
    void checkDevicesForInfo();
    void createNewTempPassword();

};

#endif // WIDGET_H
