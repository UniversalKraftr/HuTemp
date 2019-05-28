#ifndef READINGSDIALOGBOX_H
#define READINGSDIALOGBOX_H

#include <QDialog>
#include <QAbstractButton>

namespace Ui {
class ReadingsDialogBox;
}

class ReadingsDialogBox : public QDialog
{
    Q_OBJECT

public:
    explicit ReadingsDialogBox(QWidget *parent = nullptr);
    ~ReadingsDialogBox();

    QList<bool> getCheckBoxes();
    void setCheckBoxes(QList<bool>);

private slots:
    void on_ReadingsDialogBoxButtons_clicked(QAbstractButton *button);

    void on_ReadingsDialogBoxAllDataCheckBox_stateChanged(int arg1);

    void on_ReadingsDialogBoxTemperatureCheckBox_stateChanged(int arg1);

    void on_ReadingsDialogBoxHumidityCheckBox_stateChanged(int arg1);

private:
    Ui::ReadingsDialogBox *ui;
    QList<bool> checkboxes;
};

#endif // READINGSDIALOGBOX_H
