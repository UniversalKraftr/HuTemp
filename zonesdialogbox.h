#ifndef ZONESDIALOGBOX_H
#define ZONESDIALOGBOX_H

#include <QDialog>
#include <QAbstractButton>

namespace Ui {
class ZonesDialogBox;
}

class ZonesDialogBox : public QDialog
{
    Q_OBJECT

public:
    explicit ZonesDialogBox(QWidget *parent = nullptr);
    ~ZonesDialogBox();
    QList<bool> getCheckBoxes();
    void setCheckBoxes(QList<bool>);

private slots:
    void on_ZonesDialogBoxButtons_clicked(QAbstractButton *button);

    void on_ZonesDialogBoxAllZonesCheckBox_stateChanged(int arg1);

    void on_ZonesDialogBoxCollectionsCheckBox_stateChanged(int arg1);

    void on_ZonesDialogBoxDockAreaCheckBox_stateChanged(int arg1);

    void on_ZonesDialogBoxGallery1CheckBox_stateChanged(int arg1);

    void on_ZonesDialogBoxGallery2CheckBox_stateChanged(int arg1);

    void on_ZonesDialogBoxGallery3CheckBox_stateChanged(int arg1);

    void on_ZonesDialogBoxGallery4CheckBox_stateChanged(int arg1);

    void on_ZonesDialogBoxGallery5CheckBox_stateChanged(int arg1);

    void on_ZonesDialogBoxGallery6CheckBox_stateChanged(int arg1);

    void on_ZonesDialogBoxLobbyCheckBox_stateChanged(int arg1);

private:
    Ui::ZonesDialogBox *ui;
    QList<bool> checkBoxes;
};

#endif // ZONESDIALOGBOX_H
