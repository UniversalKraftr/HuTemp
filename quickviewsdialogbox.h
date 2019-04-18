#ifndef QUICKVIEWSDIALOGBOX_H
#define QUICKVIEWSDIALOGBOX_H

#include <QDialog>
#include <QAbstractButton>

namespace Ui {
class quickViewsDialogBox;
}

class quickViewsDialogBox : public QDialog
{
    Q_OBJECT

public:
    explicit quickViewsDialogBox(QWidget *parent = nullptr);
    ~quickViewsDialogBox();

private slots:
    void on_quickViewsDialogBoxButtons_clicked(QAbstractButton *button);

private:
    Ui::quickViewsDialogBox *ui;

};

#endif // QUICKVIEWSDIALOGBOX_H
