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

    QList<int> getCheckBoxes();
    void setCheckBoxes(QList<int>);

private slots:
    void on_ReadingsDialogBoxButtons_clicked(QAbstractButton *button);

    void on_ReadingsDialogBoxAllDataCheckBox_stateChanged(int arg1);

    void on_ReadingsDialogBoxTemperatureCheckBox_stateChanged(int arg1);

    void on_ReadingsDialogBoxHumidityCheckBox_stateChanged(int arg1);

    void allCheckBoxesClicked();

private:
    Ui::ReadingsDialogBox *ui;
    QList<int> checkboxes;
};

#endif // READINGSDIALOGBOX_H
