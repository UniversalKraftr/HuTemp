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


private slots:
    void on_DevicesDialogBoxButtons_clicked(QAbstractButton *button);


    void on_DevicesDialogBoxAllDataLoggersCheckBox_toggled(bool checked);

private:
    Ui::DevicesDialogBox *ui;
};

#endif // DEVICESDIALOGBOX_H
