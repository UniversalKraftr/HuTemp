#ifndef DEVICESDIALOGBOX_H
#define DEVICESDIALOGBOX_H

#include <QDialog>
#include <QAbstractButton>

namespace Ui {
class DevicesDialogBox;
}

class DevicesDialogBox : public QDialog
{
    Q_OBJECT

public:
    explicit DevicesDialogBox(QWidget *parent = nullptr);
    ~DevicesDialogBox();

    QList<bool> getCheckBoxes();
    void setCheckBoxes(QList<bool>);

private slots:
    void on_DevicesDialogBoxButtons_clicked(QAbstractButton *button);

    void on_DevicesDialogBoxAllDataLoggersCheckBox_stateChanged(int arg1);

    void on_DevicesDialogBoxDataLogger1CheckBox_stateChanged(int arg1);

    void on_DevicesDialogBoxDataLogger2CheckBox_stateChanged(int arg1);

    void on_DevicesDialogBoxDataLogger3CheckBox_stateChanged(int arg1);

    void on_DevicesDialogBoxDataLogger4CheckBox_stateChanged(int arg1);

    void on_DevicesDialogBoxDataLogger5CheckBox_stateChanged(int arg1);

    void on_DevicesDialogBoxDataLogger6CheckBox_stateChanged(int arg1);

    void on_DevicesDialogBoxDataLogger7CheckBox_stateChanged(int arg1);

    void on_DevicesDialogBoxDataLogger8CheckBox_stateChanged(int arg1);

private:
    Ui::DevicesDialogBox *ui;
    QList<bool> checkboxes;
};

#endif // DEVICESDIALOGBOX_H
