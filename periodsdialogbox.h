#ifndef PERIODSDIALOGBOX_H
#define PERIODSDIALOGBOX_H

#include <QDialog>
#include <QAbstractButton>

namespace Ui {
class PeriodsDialogBox;
}

class PeriodsDialogBox : public QDialog
{
    Q_OBJECT

public:
    explicit PeriodsDialogBox(QWidget *parent = nullptr);
    ~PeriodsDialogBox();

private slots:
    void on_PeriodsDialogBoxButtons_clicked(QAbstractButton *button);

private:
    Ui::PeriodsDialogBox *ui;
};

#endif // PERIODSDIALOGBOX_H
