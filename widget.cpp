#include "widget.h"
#include "ui_widget.h"
#include <QtMath>
#include <QDebug>
#include "devicesdialogbox.h"
#include "periodsdialogbox.h"
#include "quickviewsdialogbox.h"
#include "readingsdialogbox.h"
#include "zonesdialogbox.h"
#include "helpdialog.h"
#include "previoususersdialog.h"
#include <QProcess>
#include <QMessageBox>




Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWidgetConfigs(ui);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::setWidgetConfigs(Ui::Widget *ui)
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
    setTabWidgetConfigs(ui, widgetWidth, widgetHeight);

    //set login tab geometries
    setLoginTabConfigs(ui);

    //set UAC tab geometries
    setUACTabConfigs(ui);

    //set devices tab geometries
    setDevicesTabConfigs(ui);

    //set reports tab geometries
    setReportsTabConfigs(ui);

    //set settings tab geometries
    setSettingsTabConfigs(ui);

    //set default program upon opening
    setDefaults(ui);
}

void Widget::setTabWidgetConfigs(Ui::Widget *ui, int widgetWidth, int widgetHeight)
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

void Widget::setLoginTabConfigs(Ui::Widget *ui)
{
    //set loginScreenViewsStack to loginTab size
    int loginTabWidth = ui->loginTab->width();
    int loginTabHeight = ui->loginTab->height();
    ui->loginScreenViewsStack->setFixedSize(qCeil(loginTabWidth*.99), qCeil(loginTabHeight*.98));
    ui->loginScreenPageNestedWidget->setFixedSize(ui->loginScreenViewsStack->width(), ui->loginScreenViewsStack->height());
    ui->logoutScreenPageNestedWidget->setFixedSize(ui->loginScreenViewsStack->width(), ui->loginScreenViewsStack->height());

}

void Widget::setUACTabConfigs(Ui::Widget *ui)
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

void Widget::setDevicesTabConfigs(Ui::Widget *ui)
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
}

void Widget::setReportsTabConfigs(Ui::Widget *ui)
{
    ui->reportsTabNestedWidget->setFixedSize(ui->reportsTab->width(), ui->reportsTab->height());
    QPixmap pix(":/icons/calendar.png");
    QIcon icon(pix);
    ui->reportsTabNestedWidgetStartDateButton->setIcon(icon);
    ui->reportsTabNestedWidgetStartDateButton->setIconSize(QSize(ui->reportsTabNestedWidgetStartDateButton->width()-10, ui->reportsTabNestedWidgetStartDateButton->height()-10));
    ui->reportsTabNestedWidgetEndDateButton->setIcon(icon);
    ui->reportsTabNestedWidgetEndDateButton->setIconSize(QSize(ui->reportsTabNestedWidgetEndDateButton->width()-10, ui->reportsTabNestedWidgetEndDateButton->height()-10));
}

void Widget::setSettingsTabConfigs(Ui::Widget *ui)
{
    ui->settingsTabNestedWidget->setFixedSize(ui->settingsTab->width(), ui->settingsTab->height());
}

void Widget::setDefaults(Ui::Widget *ui)
{
    //set default view of application upon open
    ui->mainTabsWidget->setCurrentIndex(0);
    ui->loginScreenViewsStack->setCurrentIndex(1);
//    ui->tabWidget->setTabEnabled(1, false);
//    ui->tabWidget->setTabEnabled(2, false);
//    ui->tabWidget->setTabEnabled(3, false);
    //    ui->tabWidget->setTabEnabled(4, false);
}

void Widget::addUserRowToTableWidget(Ui::Widget *ui, AddAUserDialog *user)
{
    ui->UACTableWidget->insertRow(ui->UACTableWidget->rowCount());


    QStringList usersInfo = user->getUserInfo();
    ui->UACTableWidget->setItem(ui->UACTableWidget->rowCount()-1 ,0, new QTableWidgetItem(usersInfo[0] + " " + usersInfo[1]));
    ui->UACTableWidget->setItem(ui->UACTableWidget->rowCount()-1, 11, new QTableWidgetItem(usersInfo[3]));
    ui->UACTableWidget->setItem(ui->UACTableWidget->rowCount()-1, 12, new QTableWidgetItem(usersInfo[2]));


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
    resetButtonlayout->addWidget(resetButton);
    resetButtonlayout->setAlignment(Qt::AlignCenter);
    resetButtonlayout->setContentsMargins(0,0,0,0);
    resetButtonWidget->setLayout(resetButtonlayout);
    ui->UACTableWidget->setCellWidget(ui->UACTableWidget->rowCount()-1, 13, resetButtonWidget);



    QWidget *deleteButtonWidget = new QWidget();
    QPushButton *deleteButton = new QPushButton();
    deleteButton->setText("Delete");
    QHBoxLayout *deleteButtonlayout = new QHBoxLayout(deleteButtonWidget);
    deleteButtonlayout->addWidget(deleteButton);
    deleteButtonlayout->setAlignment(Qt::AlignCenter);
    deleteButtonlayout->setContentsMargins(0,0,0,0);
    deleteButtonWidget->setLayout(deleteButtonlayout);
    ui->UACTableWidget->setCellWidget(ui->UACTableWidget->rowCount()-1, 14, deleteButtonWidget);
}

void Widget::on_reportsTabNestedWidgetQuickViewsPushButton_clicked()
{
    quickViewsDialogBox *quickViews = new quickViewsDialogBox(this);
    quickViews->exec();
}

void Widget::on_reportsTabNestedWidgetZonesPushButton_clicked()
{
    ZonesDialogBox *zones = new ZonesDialogBox(this);
    zones->exec();
}

void Widget::on_reportsTabNestedWidgetDevicesPushButton_clicked()
{
    DevicesDialogBox *devices = new DevicesDialogBox(this);
    devices->exec();
}

void Widget::on_reportsTabNestedWidgetReadingsPushButton_clicked()
{
    ReadingsDialogBox *readings = new ReadingsDialogBox(this);
    readings->exec();
}

void Widget::on_reportsTabNestedWidgetPeriodsPushButton_clicked()
{
    PeriodsDialogBox *periods = new PeriodsDialogBox(this);
    periods->exec();
}


void Widget::on_settingsTabNestedWidgethelpPushButton_clicked()
{
    HelpDialog *helpScreen = new HelpDialog(this);
    helpScreen->exec();
}


void Widget::on_UACAddAUserButton_clicked()
{
    AddAUserDialog *addUser = new AddAUserDialog(this);
    connect(addUser, &AddAUserDialog::accepted, [=](){
        addUserRowToTableWidget(ui, addUser);
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
    previousUsers->exec();
}
