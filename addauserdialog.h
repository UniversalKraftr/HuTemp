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
    bool getUserAdminPermission() const;
    bool getDataLoggerPermission() const;
    bool getAddDevicePermission() const;
    bool getModifyDevicePermission() const;
    bool getRemoveDevicePermission() const;
    bool getSettingsPermission() const;
    bool getNotificationsPermission() const;
    bool getNetworksPermission() const;
    bool getReportsPermission() const;
    bool getEmailPermission() const;
    QStringList getUserInfo() const;

    void setUserAdminPermissions(Ui::AddAUserDialog *ui, bool truth);
    void setDefaultPermissions(Ui::AddAUserDialog *ui);
    void setCustomPermissions(Ui::AddAUserDialog *ui);
    void getUserPermissions(Ui::AddAUserDialog *ui);

private slots:
    void on_AddAUserDialogButtonBox_clicked(QAbstractButton *button);

    void on_AddAUserDialogFirstNameLineEdit_textChanged(const QString &arg1);

    void on_AddAUserDialogLastNameLineEdit_textChanged(const QString &arg1);

    void on_AddAUserDialogPhoneNumberLineEdit_textChanged(const QString &arg1);

    void on_AddAUserDialogEmailLineEdit_textChanged(const QString &arg1);

private:
    Ui::AddAUserDialog *ui;
    void adminEasyGuide(Ui::AddAUserDialog *ui);
    void setUserInfoRequirements(Ui::AddAUserDialog *ui);
    void checkUserInfoInput(Ui::AddAUserDialog *ui);
    void customInfoMessageBox(QString title, QString message);
    QString customQuestionMessageBox(QString title, QString message);



};

#endif // ADDAUSERDIALOG_H
