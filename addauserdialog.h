#ifndef ADDAUSERDIALOG_H
#define ADDAUSERDIALOG_H

#include <QDialog>
#include <QAbstractButton>
#include <QMap>

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
    void setUserAdminPermission(bool truth);
    bool getDataLoggerPermission() const;
    void setDataLoggerPermission(bool truth);
    bool getAddDevicePermission() const;
    void setAddDevicePermission(bool truth);
    bool getModifyDevicePermission() const;
    void setModifyDevicePermission(bool truth);
    bool getRemoveDevicePermission() const;
    void setRemoveDevicePermission(bool truth);
    bool getSettingsPermission() const;
    void setSettingsPermission(bool truth);
    bool getNotificationsPermission() const;
    void setNotificationsPermission(bool truth);
    bool getNetworksPermission() const;
    void setNetworksPermission(bool truth);
    bool getReportsPermission() const;
    void setReportsPermission(bool truth);
    bool getEmailPermission() const;
    void setEmailPermission(bool truth);

    QStringList getUserInfo() const;
    void checkAllBoxes();

    void setUserAdminPermissions(bool truth);
    void setDefaultPermissions();
    void setCustomPermissions();
    void getUserPermissions();

private slots:
    void on_AddAUserDialogButtonBox_clicked(QAbstractButton *button);

    void on_AddAUserDialogFirstNameLineEdit_textChanged(const QString &arg1);

    void on_AddAUserDialogLastNameLineEdit_textChanged(const QString &arg1);

    void on_AddAUserDialogPhoneNumberLineEdit_textChanged(const QString &arg1);

    void on_AddAUserDialogEmailLineEdit_textChanged(const QString &arg1);

    void on_AddAUserDialogAdminCheckBox_stateChanged(int arg1);

    void on_AddAUserDialogDataLoggersCheckBox_stateChanged(int arg1);

    void on_AddAUserDialogSettingsCheckBox_stateChanged(int arg1);

private:
    Ui::AddAUserDialog *ui;
    QMap<QString, bool> checkBoxStates;
    void adminEasyGuide();
    void setUserInfoRequirements();
    void checkUserInfoInput();
    void customInfoMessageBox(QString title, QString message);
    QString customQuestionMessageBox(QString title, QString message);
    void captureCheckBoxStates();



};

#endif // ADDAUSERDIALOG_H
