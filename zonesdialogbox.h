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

private slots:
    void on_ZonesDialogBoxButtons_clicked(QAbstractButton *button);

private:
    Ui::ZonesDialogBox *ui;
};

#endif // ZONESDIALOGBOX_H
