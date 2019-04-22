#ifndef NEWPASSWORDPOSTRESETDIALOG_H
#define NEWPASSWORDPOSTRESETDIALOG_H

#include <QDialog>

namespace Ui {
class NewPasswordPostResetDialog;
}

class NewPasswordPostResetDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewPasswordPostResetDialog(QWidget *parent = nullptr);
    ~NewPasswordPostResetDialog();

private:
    Ui::NewPasswordPostResetDialog *ui;
};

#endif // NEWPASSWORDPOSTRESETDIALOG_H
