#ifndef PREVIOUSUSERSDIALOG_H
#define PREVIOUSUSERSDIALOG_H

#include <QDialog>

namespace Ui {
class PreviousUsersDialog;
}

class PreviousUsersDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PreviousUsersDialog(QWidget *parent = nullptr);
    ~PreviousUsersDialog();

private slots:
    void on_PreviousUsersDialogExitButton_clicked();

private:
    Ui::PreviousUsersDialog *ui;
};

#endif // PREVIOUSUSERSDIALOG_H
