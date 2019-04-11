#include "widget.h"
#include "ui_widget.h"
#include <QtMath>
#include <QDebug>



Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWidgetGeometries(ui);

}

Widget::~Widget()
{
    delete ui;
}

void Widget::setWidgetGeometries(Ui::Widget *ui)
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
    setTabWidgetGeometries(ui, widgetWidth, widgetHeight);

    //set login tab geometries
    setLoginTabGeometries(ui);

    //set UAC tab geometries
    setUACTabGeometries(ui);

    //set devices tab geometries
    setDevicesTabGeometries(ui);

    //set reports tab geometries
    setReportsTabGeometries(ui);

    //set settings tab geometries
    setSettingsTabGeometries(ui);

    //set default program upon opening
    setDefaults(ui);
}

void Widget::setTabWidgetGeometries(Ui::Widget *ui, int widgetWidth, int widgetHeight)
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

void Widget::setLoginTabGeometries(Ui::Widget *ui)
{
    //set loginScreenViewsStack to loginTab size
    int loginTabWidth = ui->loginTab->width();
    int loginTabHeight = ui->loginTab->height();
    ui->loginScreenViewsStack->setFixedSize(qCeil(loginTabWidth*.99), qCeil(loginTabHeight*.98));
    ui->loginScreenPageNestedWidget->setFixedSize(ui->loginScreenViewsStack->width(), ui->loginScreenViewsStack->height());
    ui->logoutScreenPageNestedWidget->setFixedSize(ui->loginScreenViewsStack->width(), ui->loginScreenViewsStack->height());

}

void Widget::setUACTabGeometries(Ui::Widget *ui)
{
    //set UACScreenViewsStack to UACTab size
    int UACTabWidth = ui->UACTab->width();
    int UACTabHeight = ui->UACTab->height();
    ui->UACScreenViewsStack->setFixedSize(qCeil(UACTabWidth*.99), qCeil(UACTabHeight*.98));
    ui->adminViewScreenPageNestedWidget->setFixedSize(ui->UACScreenViewsStack->width(), ui->UACScreenViewsStack->height());
    ui->userViewScreenPageNestedWidget->setFixedSize(ui->UACScreenViewsStack->width(), ui->UACScreenViewsStack->height());
}

void Widget::setDevicesTabGeometries(Ui::Widget *ui)
{
    ui->devicesTabNestedWidget->setFixedSize(ui->devicesTab->width(), ui->devicesTab->height());
}

void Widget::setReportsTabGeometries(Ui::Widget *ui)
{
    ui->reportsTabNestedWidget->setFixedSize(ui->reportsTab->width(), ui->reportsTab->height());
}

void Widget::setSettingsTabGeometries(Ui::Widget *ui)
{
    ui->settingsTabNestedWidget->setFixedSize(ui->settingsTab->width(), ui->settingsTab->height());
}

void Widget::setDefaults(Ui::Widget *ui)
{
    //set default view of application upon open
    ui->mainTabsWidget->setCurrentIndex(0);
    ui->loginScreenViewsStack->setCurrentIndex(0);
//    ui->tabWidget->setTabEnabled(1, false);
//    ui->tabWidget->setTabEnabled(2, false);
//    ui->tabWidget->setTabEnabled(3, false);
//    ui->tabWidget->setTabEnabled(4, false);
}
