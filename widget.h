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

#include "smtp.h"
#include "addauserdialog.h"
#include "additionaladminsettingsdialog.h"
#include "additionalsettingsnotificationsdialog.h"




namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    QString getLogFolder();
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

    QString getUserName();
    QString getUserEmail();
    QString getUserType();
    QString getCompanyName();
    QString getCompanyAddressLine1();
    QString getCompanyAddressLine2();
    QString getCompanyPhoneNumber();

    void on_devicesTabAddButton_clicked();

    void on_devicesTabSortOptionsDropDownBox_currentIndexChanged(int index);

    void on_devicesTabRefreshButton_clicked();

    void on_reportsTabNestedWidgetEndDateDateEdit_userDateChanged(const QDate &date);

    void on_reportsTabNestedWidgetEndTimeTimeEdit_userTimeChanged(const QTime &time);

private:
    Ui::Widget *ui;
    QString u = QChar(0x00B3);
    const QString title = "HuTemp Life Cycle – H" + u + " Product";
    int monitorAdminIndexRow;
    int monitorAdminIndexColumn = 0;
    QTableWidgetItem *UACTableWidgetItem;
    QCheckBox *monitorAdminCheckBox;
    QPushButton *monitorAdminDeleteButton;
    int currentButtonByAssociation = 0;
    QList<int> openCloseHoursMinutes;
    QString companyName = "";
    QString companyAddress = "";
    QString companyPhoneNumber = "";
    QFont selectedItemFont;
    QString createdDirectory;
    QString newTempPassword;
    QString userFirstName;
    QString userLastName;
    QString userPhoneNumber;
    QString userEmail;
    QString userType;
    bool dbOpen;
    QList<bool> zonesCheckBoxes;
    QList<bool> devicesCheckBoxes;


    void addUserToUserTable(AddAUserDialog *addUser);
    void connectToDatabase();
    void extractAllCompanyInfo();
    void extractAllUserInfo();
    QString alphaNumGenerator();
    void createDirectories();
    void toggleAdminUACCheckBoxStatuses();
    void setAdditionalAdminData(AdditionalSettingsNotificationsDialog *additionalSettings);
    void captureAdditionalAdminData(AdditionalSettingsNotificationsDialog *additionalSettings);
    void setWidgetConfigs();
    void setTabWidgetConfigs(int widgetWidth, int widgetHeight);
    void setLoginTabConfigs();
    void setUACTabConfigs();
    void setDevicesTabConfigs();
    void setReportsTabConfigs();
    void setSettingsTabConfigs();
    void setDefaults();
    void addUserRowToTableWidget(AddAUserDialog *user);
    void monitorAdminStatus();
    void checkAdminBox();
    void monitorDeleteUsers();
    void archiveUser();
    void monitorUserPasswordResets();
    void setDefaultPermissions(int i);
    void resetPassword();

};

#endif // WIDGET_H
