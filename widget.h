#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDesktopWidget>
#include <QScreen>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_reportsTabNestedWidgetQuickViewsPushButton_clicked();

    void on_reportsTabNestedWidgetZonesPushButton_clicked();

    void on_reportsTabNestedWidgetDevicesPushButton_clicked();

    void on_reportsTabNestedWidgetReadingsPushButton_clicked();

    void on_reportsTabNestedWidgetPeriodsPushButton_clicked();

private:
    Ui::Widget *ui;
    QString u = QChar(0x00B3);
    const QString &title = "HuTemp Life Cycle – H" + u + " Product";
    void setWidgetConfigs(Ui::Widget *ui);
    void setTabWidgetConfigs(Ui::Widget *ui, int widgetWidth, int widgetHeight);
    void setLoginTabConfigs(Ui::Widget *ui);
    void setUACTabConfigs(Ui::Widget *ui);
    void setDevicesTabConfigs(Ui::Widget *ui);
    void setReportsTabConfigs(Ui::Widget *ui);
    void setSettingsTabConfigs(Ui::Widget *ui);
    void setDefaults(Ui::Widget *ui);

};

#endif // WIDGET_H
