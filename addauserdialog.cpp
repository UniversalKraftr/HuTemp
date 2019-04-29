#include "addauserdialog.h"
#include "ui_addauserdialog.h"
#include <QMessageBox>
#include <QRegExp>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QDebug>



AddAUserDialog::AddAUserDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddAUserDialog)
{
    ui->setupUi(this);

    setWindowTitle("Add A User");
    adjustSize();

    QStringList userContent = {"First Name", "Second Name", "000-000-0000", "someone@example.com"};
    ui->AddAUserDialogFirstNameLineEdit->setPlaceholderText(userContent[0]);
    ui->AddAUserDialogLastNameLineEdit->setPlaceholderText(userContent[1]);
    ui->AddAUserDialogPhoneNumberLineEdit->setPlaceholderText(userContent[2]);
    ui->AddAUserDialogEmailLineEdit->setPlaceholderText(userContent[3]);
    setUserInfoRequirements(ui);

    customInfoMessageBox("Start", "Start with entering in the User's Name and Contact Information");
}

AddAUserDialog::~AddAUserDialog()
{
    delete ui;
}

bool AddAUserDialog::getUserAdminPermission() const
{
    return ui->AddAUserDialogAdminCheckBox->isChecked();
}

bool AddAUserDialog::getDataLoggerPermission() const
{
    return ui->AddAUserDialogDataLoggersCheckBox->isChecked();
}

bool AddAUserDialog::getAddDevicePermission() const
{
    return ui->AddAUserDialogAddCheckBox->isChecked();
}

bool AddAUserDialog::getModifyDevicePermission() const
{
    return ui->AddAUserDialogModifyCheckBox->isChecked();
}

bool AddAUserDialog::getRemoveDevicePermission() const
{
    return ui->AddAUserDialogRemoveCheckBox->isChecked();
}

bool AddAUserDialog::getSettingsPermission() const
{
    return ui->AddAUserDialogSettingsCheckBox->isChecked();
}

bool AddAUserDialog::getNotificationsPermission() const
{
    return ui->AddAUserDialogNotificationsCheckBox->isChecked();
}

bool AddAUserDialog::getNetworksPermission() const
{
    return ui->AddAUserDialogNetworkCheckBox->isChecked();
}

bool AddAUserDialog::getReportsPermission() const
{
    return ui->AddAUserDialogReportsCheckBox->isChecked();
}

bool AddAUserDialog::getEmailPermission() const
{
    return ui->AddAUserDialogEmailCheckBox->isChecked();
}

QStringList AddAUserDialog::getUserInfo() const
{
    QStringList userInfo {};
    userInfo.append(ui->AddAUserDialogFirstNameLineEdit->text());
    userInfo.append(ui->AddAUserDialogLastNameLineEdit->text());
    userInfo.append(ui->AddAUserDialogPhoneNumberLineEdit->text());
    userInfo.append(ui->AddAUserDialogEmailLineEdit->text());
    return userInfo;
}



void AddAUserDialog::on_AddAUserDialogButtonBox_clicked(QAbstractButton *button)
{
    QDialogButtonBox::StandardButton addUserStdButton = ui->AddAUserDialogButtonBox->standardButton(button);

    if (addUserStdButton == QDialogButtonBox::Ok){
        accept();
    }
    if (addUserStdButton == QDialogButtonBox::Cancel){
        QMessageBox::StandardButton reply;
        reply = QMessageBox::warning(this, tr("Warning"), "Wait!\nAre you sure you wish to cancel?", QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes){
            reject();
        }
    }
}


void AddAUserDialog::setUserInfoRequirements(Ui::AddAUserDialog *ui)
{
    QRegularExpression rxName("\\b[A-Z]*\\b", QRegularExpression::CaseInsensitiveOption);
    QRegularExpression rxPhone("\\b[0-9]*\\b", QRegularExpression::CaseInsensitiveOption);
    QRegularExpression rxEmail("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{3,4}\\b", QRegularExpression::CaseInsensitiveOption);
    ui->AddAUserDialogFirstNameLineEdit->setValidator(new QRegularExpressionValidator(rxName, this));
    ui->AddAUserDialogLastNameLineEdit->setValidator(new QRegularExpressionValidator(rxName, this));
    ui->AddAUserDialogPhoneNumberLineEdit->setValidator(new QRegularExpressionValidator(rxPhone, this));
    ui->AddAUserDialogEmailLineEdit->setValidator(new QRegularExpressionValidator(rxEmail, this));
    setTabOrder(ui->AddAUserDialogFirstNameLineEdit, ui->AddAUserDialogLastNameLineEdit);
    setTabOrder(ui->AddAUserDialogLastNameLineEdit, ui->AddAUserDialogPhoneNumberLineEdit);
    setTabOrder(ui->AddAUserDialogPhoneNumberLineEdit, ui->AddAUserDialogEmailLineEdit);
}

void AddAUserDialog::checkUserInfoInput(Ui::AddAUserDialog *ui)
{
    if (!ui->AddAUserDialogFirstNameLineEdit->text().isEmpty() && !ui->AddAUserDialogLastNameLineEdit->text().isEmpty() &&
            !ui->AddAUserDialogPhoneNumberLineEdit->text().isEmpty() && !ui->AddAUserDialogEmailLineEdit->text().isEmpty() &&
            ui->AddAUserDialogFirstNameLineEdit->hasAcceptableInput() && ui->AddAUserDialogLastNameLineEdit->hasAcceptableInput() &&
            ui->AddAUserDialogPhoneNumberLineEdit->hasAcceptableInput() && ui->AddAUserDialogEmailLineEdit->hasAcceptableInput()){
        customInfoMessageBox("Permissions", "Moving on to the permissions for this user.");

        getUserPermissions(ui);
    }

}

void AddAUserDialog::customInfoMessageBox(QString title, QString message)
{
    QMessageBox *messageBox = new QMessageBox(this);
    messageBox->setWindowTitle(title);
    messageBox->setInformativeText(message);
    messageBox->setStandardButtons(QMessageBox::Ok);
    messageBox->setStyleSheet("QLabel{min-width: 500px; font-size: 16px;} ");
    messageBox->exec();
}

QString AddAUserDialog::customQuestionMessageBox(QString title, QString message)
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, title, message, QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes){
        return "Yes";
    }else{
        return "No";
    }
}

void AddAUserDialog::setUserAdminPermissions(Ui::AddAUserDialog *ui, bool truth)
{
    ui->AddAUserDialogAdminCheckBox->setChecked(truth);
    ui->AddAUserDialogDataLoggersCheckBox->setChecked(truth);
    ui->AddAUserDialogAddCheckBox->setChecked(truth);
    ui->AddAUserDialogModifyCheckBox->setChecked(truth);
    ui->AddAUserDialogRemoveCheckBox->setChecked(truth);
    ui->AddAUserDialogSettingsCheckBox->setChecked(truth);
    ui->AddAUserDialogNotificationsCheckBox->setChecked(truth);
    ui->AddAUserDialogNetworkCheckBox->setChecked(truth);
    ui->AddAUserDialogEmailCheckBox->setChecked(truth);
    ui->AddAUserDialogReportsCheckBox->setChecked(truth);
}

void AddAUserDialog::setDefaultPermissions(Ui::AddAUserDialog *ui)
{
    ui->AddAUserDialogAdminCheckBox->setChecked(false);
    ui->AddAUserDialogDataLoggersCheckBox->setChecked(true);
    ui->AddAUserDialogAddCheckBox->setChecked(true);
    ui->AddAUserDialogModifyCheckBox->setChecked(true);
    ui->AddAUserDialogRemoveCheckBox->setChecked(false);
    ui->AddAUserDialogSettingsCheckBox->setChecked(true);
    ui->AddAUserDialogNotificationsCheckBox->setChecked(true);
    ui->AddAUserDialogNetworkCheckBox->setChecked(false);
    ui->AddAUserDialogEmailCheckBox->setChecked(true);
    ui->AddAUserDialogReportsCheckBox->setChecked(true);
}

void AddAUserDialog::setCustomPermissions(Ui::AddAUserDialog *ui)
{
    QStringList replies {"", "", "", "", "", "", "", "", ""};
    ui->AddAUserDialogAdminCheckBox->setChecked(false);

    replies[0] = customQuestionMessageBox("Data Logger", "Do you want to give the user access to the devices?");
    if (replies[0] == "Yes"){
        ui->AddAUserDialogDataLoggersCheckBox->setChecked(true);

        replies[1] = customQuestionMessageBox("Add A Device", "Do you want to let this user add devices?");
        if (replies[1] == "Yes"){
            ui->AddAUserDialogAddCheckBox->setChecked(true);
        }else {
            ui->AddAUserDialogAddCheckBox->setChecked(false);
        }

        replies[2] = customQuestionMessageBox("Modify A Device", "Do you want to let this user modify device information?");
        if (replies[2] == "Yes"){
            ui->AddAUserDialogModifyCheckBox->setChecked(true);
        }else {
            ui->AddAUserDialogModifyCheckBox->setChecked(false);
        }

        replies[3] = customQuestionMessageBox("Remove A Device", "Do you want to let this user remove devices?");
        if (replies[3] == "Yes"){
            ui->AddAUserDialogRemoveCheckBox->setChecked(true);
        }else {
            ui->AddAUserDialogRemoveCheckBox->setChecked(false);
        }

    }else {
        ui->AddAUserDialogDataLoggersCheckBox->setChecked(false);
        ui->AddAUserDialogAddCheckBox->setChecked(false);
        ui->AddAUserDialogModifyCheckBox->setChecked(false);
        ui->AddAUserDialogRemoveCheckBox->setChecked(false);
    }


    replies[4] = customQuestionMessageBox("Settings", "Do you want to let this user adjust their settings?");
    if (replies[4] == "Yes"){
        ui->AddAUserDialogSettingsCheckBox->setChecked(true);

        replies[5] = customQuestionMessageBox("Notifications", "Do you want to let this user adjust their notifications?");
        if (replies[5] == "Yes"){
            ui->AddAUserDialogNotificationsCheckBox->setChecked(true);
        }else {
            ui->AddAUserDialogNotificationsCheckBox->setChecked(false);
        }

        replies[6] = customQuestionMessageBox("Network", "Do you want to let this user access the network connections?");
        if (replies[6] == "Yes"){
            ui->AddAUserDialogNetworkCheckBox->setChecked(true);
        }else {
            ui->AddAUserDialogNetworkCheckBox->setChecked(false);
        }

    }else {
        ui->AddAUserDialogSettingsCheckBox->setChecked(false);
        ui->AddAUserDialogNotificationsCheckBox->setChecked(false);
        ui->AddAUserDialogNetworkCheckBox->setChecked(false);
    }


    replies[7] = customQuestionMessageBox("Email", "Do you want to let this user receive emails?");
    if (replies[7] == "Yes"){
        ui->AddAUserDialogEmailCheckBox->setChecked(true);
    }else {
        ui->AddAUserDialogEmailCheckBox->setChecked(false);
    }

    replies[8] = customQuestionMessageBox("Reports", "Do you want to let this user handle reports?");
    if (replies[8] == "Yes"){
        ui->AddAUserDialogReportsCheckBox->setChecked(true);
    }else {
        ui->AddAUserDialogReportsCheckBox->setChecked(false);
    }

}


void AddAUserDialog::getUserPermissions(Ui::AddAUserDialog *ui)
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, tr("Administrator Permission"), "Is this user an administrator", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes){
        setUserAdminPermissions(ui, true);
    } else if(reply == QMessageBox::No){
        setUserAdminPermissions(ui, false);
        QMessageBox::StandardButton defaultSettings;
        defaultSettings = QMessageBox::question(this, tr("Default Settings"), "Do you wish to use the default settings?", QMessageBox::Yes | QMessageBox::No);
        if (defaultSettings == QMessageBox::Yes){
            setDefaultPermissions(ui);
        } else if (defaultSettings == QMessageBox::No){
            setCustomPermissions(ui);
        }

    }
}

void AddAUserDialog::on_AddAUserDialogFirstNameLineEdit_textChanged(const QString &arg1)
{
    if (!ui->AddAUserDialogFirstNameLineEdit->hasAcceptableInput() || ui->AddAUserDialogFirstNameLineEdit->text().isEmpty()){
        ui->AddAUserDialogFirstNameLineEdit->setStyleSheet("QLineEdit {color : red;}");
    } else if (ui->AddAUserDialogFirstNameLineEdit->hasAcceptableInput() && !ui->AddAUserDialogFirstNameLineEdit->text().isEmpty()) {
        ui->AddAUserDialogFirstNameLineEdit->setStyleSheet("QLineEdit {color : green;}");
    }
    checkUserInfoInput(ui);
}

void AddAUserDialog::on_AddAUserDialogLastNameLineEdit_textChanged(const QString &arg1)
{
    if (!ui->AddAUserDialogLastNameLineEdit->hasAcceptableInput() || ui->AddAUserDialogLastNameLineEdit->text().isEmpty()){
        ui->AddAUserDialogLastNameLineEdit->setStyleSheet("QLineEdit {color : red;}");
    } else if (ui->AddAUserDialogLastNameLineEdit->hasAcceptableInput() && !ui->AddAUserDialogLastNameLineEdit->text().isEmpty()){
        ui->AddAUserDialogLastNameLineEdit->setStyleSheet("QLineEdit {color : green;}");
    }
    checkUserInfoInput(ui);
}

void AddAUserDialog::on_AddAUserDialogPhoneNumberLineEdit_textChanged(const QString &arg1)
{
    if (!ui->AddAUserDialogPhoneNumberLineEdit->hasAcceptableInput() || ui->AddAUserDialogPhoneNumberLineEdit->text().isEmpty()){
        ui->AddAUserDialogPhoneNumberLineEdit->setStyleSheet("QLineEdit {color : red;}");
    } else if (ui->AddAUserDialogPhoneNumberLineEdit->hasAcceptableInput() && !ui->AddAUserDialogPhoneNumberLineEdit->text().isEmpty()){
        ui->AddAUserDialogPhoneNumberLineEdit->setStyleSheet("QLineEdit {color : green;}");
    }
    checkUserInfoInput(ui);
}

void AddAUserDialog::on_AddAUserDialogEmailLineEdit_textChanged(const QString &arg1)
{
    if (!ui->AddAUserDialogEmailLineEdit->hasAcceptableInput() || ui->AddAUserDialogEmailLineEdit->text().isEmpty()){
        ui->AddAUserDialogEmailLineEdit->setStyleSheet("QLineEdit {color : red;}");
    } else if (ui->AddAUserDialogEmailLineEdit->hasAcceptableInput() && !ui->AddAUserDialogEmailLineEdit->text().isEmpty()){
        ui->AddAUserDialogEmailLineEdit->setStyleSheet("QLineEdit {color : green;}");
    }
    checkUserInfoInput(ui);
}
