#ifndef HELPDIALOG_H
#define HELPDIALOG_H

#include <QDialog>
#include <QAbstractButton>

namespace Ui {
class HelpDialog;
}

class HelpDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HelpDialog(QWidget *parent = nullptr);
    ~HelpDialog();

private slots:
    void on_HelpDialogUserManualButton_clicked();

    void on_HelpDialogContactSupportButton_clicked();

    void on_HelpDialogButtonBox_clicked(QAbstractButton *button);

private:
    Ui::HelpDialog *ui;
};

#endif // HELPDIALOG_H
