#ifndef ADDAUSERDIALOG_H
#define ADDAUSERDIALOG_H

#include <QDialog>
#include <QAbstractButton>

namespace Ui {
class AddAUserDialog;
}

class AddAUserDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddAUserDialog(QWidget *parent = nullptr);
    ~AddAUserDialog();

private slots:
    void on_AddAUserDialogButtonBox_clicked(QAbstractButton *button);

private:
    Ui::AddAUserDialog *ui;
};

#endif // ADDAUSERDIALOG_H
