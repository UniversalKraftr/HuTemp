#ifndef PERIODSDIALOGBOX_H
#define PERIODSDIALOGBOX_H

#include <QDialog>
#include <QAbstractButton>
#include "widget.h"

namespace Ui {
class PeriodsDialogBox;
}

class PeriodsDialogBox : public QDialog
{
    Q_OBJECT

public:
    explicit PeriodsDialogBox(QWidget *parent = nullptr);
    ~PeriodsDialogBox();
    int getCurrentRadioButton();
    void setCurrentRadioButton(int radioButton);

private slots:
    void on_PeriodsDialogBoxButtons_clicked(QAbstractButton *button);

private:
    Ui::PeriodsDialogBox *ui;
    QMap<QString, QRadioButton *> buttonStates;
    int currentButtonByAssociation;
};

#endif // PERIODSDIALOGBOX_H
