#ifndef QUICKVIEWSDIALOGBOX_H
#define QUICKVIEWSDIALOGBOX_H

#include <QDialog>
#include <QAbstractButton>
#include "widget.h"

namespace Ui {
class quickViewsDialogBox;
}

class quickViewsDialogBox : public QDialog
{
    Q_OBJECT

public:
    explicit quickViewsDialogBox(QWidget *parent = nullptr);
    ~quickViewsDialogBox();
    int getCurrentRadioButton();
    void setCurrentRadioButton(int radioButton);

private slots:
    void on_quickViewsDialogBoxButtons_clicked(QAbstractButton *button);

private:
    Ui::quickViewsDialogBox *ui;
    QMap<QString, QRadioButton *> buttonStates;
    int currentButtonByAssociation;

};

#endif // QUICKVIEWSDIALOGBOX_H
