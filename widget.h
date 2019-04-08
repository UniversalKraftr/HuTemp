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

private:
    Ui::Widget *ui;
    void setWidgetGeometries(Ui::Widget *ui);
    void setTabWidgetGeometries(Ui::Widget *ui, int widgetWidth, int widgetHeight);
    void setLoginTabGeometries(Ui::Widget *ui);
    void setUACTabGeometries(Ui::Widget *ui);
    void setDevicesTabGeometries(Ui::Widget *ui);
    void setReportsTabGeometries(Ui::Widget *ui);
    void setSettingsTabGeometries(Ui::Widget *ui);
    void setDefaults(Ui::Widget *ui);
};

#endif // WIDGET_H
