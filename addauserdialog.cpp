#include "addauserdialog.h"
#include "ui_addauserdialog.h"
#include <QMessageBox>
#include <QRegExp>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QDebug>
#include <QSqlQuery>



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
    QDate tomorrow(QDate::currentDate().year(), QDate::currentDate().month(), QDate::currentDate().day()+1);
    ui->AddAUserDialogHireDateDateEdit->setDate(tomorrow);
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

void AddAUserDialog::setUserAdminPermission(bool truth)
{
    ui->AddAUserDialogAdminCheckBox->setChecked(truth);
}

bool AddAUserDialog::getDataLoggerPermission() const
{
    return ui->AddAUserDialogDataLoggersCheckBox->isChecked();
}

void AddAUserDialog::setDataLoggerPermission(bool truth)
{
    ui->AddAUserDialogDataLoggersCheckBox->setChecked(truth);
}

bool AddAUserDialog::getAddDevicePermission() const
{
    return ui->AddAUserDialogAddCheckBox->isChecked();
}

void AddAUserDialog::setAddDevicePermission(bool truth)
{
    ui->AddAUserDialogAddCheckBox->setChecked(truth);
}

bool AddAUserDialog::getModifyDevicePermission() const
{
    return ui->AddAUserDialogModifyCheckBox->isChecked();
}

void AddAUserDialog::setModifyDevicePermission(bool truth)
{
    ui->AddAUserDialogModifyCheckBox->setChecked(truth);
}

bool AddAUserDialog::getRemoveDevicePermission() const
{
    return ui->AddAUserDialogRemoveCheckBox->isChecked();
}

void AddAUserDialog::setRemoveDevicePermission(bool truth)
{
    ui->AddAUserDialogRemoveCheckBox->setChecked(truth);
}

bool AddAUserDialog::getSettingsPermission() const
{
    return ui->AddAUserDialogSettingsCheckBox->isChecked();
}

void AddAUserDialog::setSettingsPermission(bool truth)
{
    ui->AddAUserDialogSettingsCheckBox->setChecked(truth);
}

bool AddAUserDialog::getNotificationsPermission() const
{
    return ui->AddAUserDialogNotificationsCheckBox->isChecked();
}

void AddAUserDialog::setNotificationsPermission(bool truth)
{
    ui->AddAUserDialogNotificationsCheckBox->setChecked(truth);
}

bool AddAUserDialog::getNetworksPermission() const
{
    return ui->AddAUserDialogNetworkCheckBox->isChecked();
}

void AddAUserDialog::setNetworksPermission(bool truth)
{
    ui->AddAUserDialogNetworkCheckBox->setChecked(truth);
}

bool AddAUserDialog::getReportsPermission() const
{
    return ui->AddAUserDialogReportsCheckBox->isChecked();
}

void AddAUserDialog::setReportsPermission(bool truth)
{
    ui->AddAUserDialogReportsCheckBox->setChecked(truth);
}

bool AddAUserDialog::getEmailPermission() const
{
    return ui->AddAUserDialogEmailCheckBox->isChecked();
}

void AddAUserDialog::setEmailPermission(bool truth)
{
    ui->AddAUserDialogEmailCheckBox->setChecked(truth);
}


QStringList AddAUserDialog::getUserInfo() const
{
    QStringList userInfo {};
    userInfo.append(ui->AddAUserDialogFirstNameLineEdit->text());
    userInfo.append(ui->AddAUserDialogLastNameLineEdit->text());
    userInfo.append(ui->AddAUserDialogPhoneNumberLineEdit->text());
    userInfo.append(ui->AddAUserDialogEmailLineEdit->text());
    userInfo.append(ui->AddAUserDialogHireDateDateEdit->date().toString("MM-dd-yyyy"));
    return userInfo;
}



void AddAUserDialog::on_AddAUserDialogButtonBox_clicked(QAbstractButton *button)
{
    QDialogButtonBox::StandardButton addUserStdButton = ui->AddAUserDialogButtonBox->standardButton(button);

    if (addUserStdButton == QDialogButtonBox::Ok){
        QMessageBox::StandardButton reply;
        if (!ui->AddAUserDialogFirstNameLineEdit->text().isEmpty() &&
                !ui->AddAUserDialogLastNameLineEdit->text().isEmpty() &&
                !ui->AddAUserDialogPhoneNumberLineEdit->text().isEmpty() &&
                !ui->AddAUserDialogEmailLineEdit->text().isEmpty() &&
                !(ui->AddAUserDialogHireDateDateEdit->date() > QDate::currentDate())){
            reply = QMessageBox::question(this, tr("Confirmation"), "Is all the information you entered correct?", QMessageBox::Yes | QMessageBox::No);
            if (reply == QMessageBox::Yes){
                accept();
            }
        } else {
            QMessageBox::warning(this, tr("Warning"), "First Name, Last Name, Phone Number, and Email are required!\nDate also cannot be any sooner than today!");
        }

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
    QRegularExpression rxPhone("\\b[0-9]{10}\\b", QRegularExpression::CaseInsensitiveOption);
    QRegularExpression rxEmail("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{3,4}\\b", QRegularExpression::CaseInsensitiveOption);
    ui->AddAUserDialogFirstNameLineEdit->setValidator(new QRegularExpressionValidator(rxName, this));
    ui->AddAUserDialogLastNameLineEdit->setValidator(new QRegularExpressionValidator(rxName, this));
    ui->AddAUserDialogPhoneNumberLineEdit->setValidator(new QRegularExpressionValidator(rxPhone, this));
    ui->AddAUserDialogEmailLineEdit->setValidator(new QRegularExpressionValidator(rxEmail, this));
    setTabOrder(ui->AddAUserDialogFirstNameLineEdit, ui->AddAUserDialogLastNameLineEdit);
    setTabOrder(ui->AddAUserDialogLastNameLineEdit, ui->AddAUserDialogPhoneNumberLineEdit);
    setTabOrder(ui->AddAUserDialogPhoneNumberLineEdit, ui->AddAUserDialogEmailLineEdit);
    ui->AddAUserDialogAddCheckBox->setCheckable(false);
    ui->AddAUserDialogModifyCheckBox->setCheckable(false);
    ui->AddAUserDialogRemoveCheckBox->setCheckable(false);
    ui->AddAUserDialogNotificationsCheckBox->setCheckable(false);
    ui->AddAUserDialogNetworkCheckBox->setCheckable(false);
    ui->AddAUserDialogFirstNameLineEdit->setFocus();
}

void AddAUserDialog::checkUserInfoInput(Ui::AddAUserDialog *ui)
{
    if (!ui->AddAUserDialogFirstNameLineEdit->text().isEmpty() && !ui->AddAUserDialogLastNameLineEdit->text().isEmpty() &&
            !ui->AddAUserDialogPhoneNumberLineEdit->text().isEmpty() && !ui->AddAUserDialogEmailLineEdit->text().isEmpty() &&
            ui->AddAUserDialogFirstNameLineEdit->hasAcceptableInput() && ui->AddAUserDialogLastNameLineEdit->hasAcceptableInput() &&
            ui->AddAUserDialogPhoneNumberLineEdit->hasAcceptableInput() && ui->AddAUserDialogEmailLineEdit->hasAcceptableInput()){

        QSqlQuery selectQuery;
        selectQuery.exec("SELECT * FROM users");
        bool validation = true;
        while (selectQuery.next()){
            QString firstName = selectQuery.value(1).toString();
            QString lastName = selectQuery.value(2).toString();
            QString email = selectQuery.value(4).toString();
            QString phoneNumber = selectQuery.value(6).toString();
            if (ui->AddAUserDialogFirstNameLineEdit->text() == firstName ||
                    ui->AddAUserDialogLastNameLineEdit->text() == lastName ||
                    ui->AddAUserDialogEmailLineEdit->text() == email ||
                    ui->AddAUserDialogPhoneNumberLineEdit->text() == phoneNumber){
                QString statement = "You must enter unique information for the following:\n";
                statement += "\t- First Name\n";
                statement += "\t- Last Name\n";
                statement += "\t- Email\n";
                statement += "\t- Phone Number\n";
                QMessageBox::warning(this, tr("INVALID ENTRY"), statement);
                validation = false;
                ui->AddAUserDialogFirstNameLineEdit->clear();
                ui->AddAUserDialogLastNameLineEdit->clear();
                ui->AddAUserDialogEmailLineEdit->clear();
                ui->AddAUserDialogPhoneNumberLineEdit->clear();
                break;
            }
        }
        if (validation == true){
            customInfoMessageBox("Permissions", "Moving on to the permissions for this user.");

            getUserPermissions(ui);
        }
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

void AddAUserDialog::checkAllBoxes(Ui::AddAUserDialog *ui)
{
    if (ui->AddAUserDialogAdminCheckBox->isChecked()){
        captureCheckBoxStates(ui);
        setDataLoggerPermission(true);
        setAddDevicePermission(true);
        setModifyDevicePermission(true);
        setRemoveDevicePermission(true);
        setSettingsPermission(true);
        setNotificationsPermission(true);
        setNetworksPermission(true);
        setReportsPermission(true);
        setEmailPermission(true);
    } else if(!ui->AddAUserDialogAdminCheckBox->isChecked()){
        setDataLoggerPermission(checkBoxStates["Data Loggers"]);
        setAddDevicePermission(checkBoxStates["Add"]);
        setModifyDevicePermission(checkBoxStates["Modify"]);
        setRemoveDevicePermission(checkBoxStates["Remove"]);
        setSettingsPermission(checkBoxStates["Settings"]);
        setNotificationsPermission(checkBoxStates["Notifications"]);
        setNetworksPermission(checkBoxStates["Network"]);
        setReportsPermission(checkBoxStates["Reports"]);
        setEmailPermission(checkBoxStates["Email"]);
    }
}

void AddAUserDialog::captureCheckBoxStates(Ui::AddAUserDialog *ui)
{
    if (!checkBoxStates.isEmpty()){
        checkBoxStates.clear();
    }
    checkBoxStates.insert("Admin",ui->AddAUserDialogAdminCheckBox->checkState());
    checkBoxStates.insert("Data Loggers",ui->AddAUserDialogDataLoggersCheckBox->checkState());
    checkBoxStates.insert("Add",ui->AddAUserDialogAddCheckBox->checkState());
    checkBoxStates.insert("Modify",ui->AddAUserDialogModifyCheckBox->checkState());
    checkBoxStates.insert("Remove",ui->AddAUserDialogRemoveCheckBox->checkState());
    checkBoxStates.insert("Settings",ui->AddAUserDialogSettingsCheckBox->checkState());
    checkBoxStates.insert("Notifications",ui->AddAUserDialogNotificationsCheckBox->checkState());
    checkBoxStates.insert("Network",ui->AddAUserDialogNetworkCheckBox->checkState());
    checkBoxStates.insert("Email",ui->AddAUserDialogEmailCheckBox->checkState());
    checkBoxStates.insert("Reports",ui->AddAUserDialogReportsCheckBox->checkState());
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
    setUserAdminPermission(false);
    setDataLoggerPermission(true);
    setAddDevicePermission(true);
    setModifyDevicePermission(true);
    setRemoveDevicePermission(false);
    setSettingsPermission(true);
    setNotificationsPermission(true);
    setNetworksPermission(false);
    setEmailPermission(true);
    setReportsPermission(true);
}

void AddAUserDialog::setCustomPermissions(Ui::AddAUserDialog *ui)
{
    QStringList replies {"", "", "", "", "", "", "", "", ""};
    setUserAdminPermission(false);

    replies[0] = customQuestionMessageBox("Data Logger", "Do you want to give the user access to the devices?");
    if (replies[0] == "Yes"){
        setDataLoggerPermission(true);

        replies[1] = customQuestionMessageBox("Add A Device", "Do you want to let this user add devices?");
        if (replies[1] == "Yes"){
            setAddDevicePermission(true);
        }else {
            setAddDevicePermission(false);
        }

        replies[2] = customQuestionMessageBox("Modify A Device", "Do you want to let this user modify device information?");
        if (replies[2] == "Yes"){
            setModifyDevicePermission(true);
        }else {
            setModifyDevicePermission(false);
        }

        replies[3] = customQuestionMessageBox("Remove A Device", "Do you want to let this user remove devices?");
        if (replies[3] == "Yes"){
            setRemoveDevicePermission(true);
        }else {
            setRemoveDevicePermission(false);
        }

    }else {
        setDataLoggerPermission(false);
        setAddDevicePermission(false);
        setModifyDevicePermission(false);
        setRemoveDevicePermission(false);
    }


    replies[4] = customQuestionMessageBox("Settings", "Do you want to let this user adjust their settings?");
    if (replies[4] == "Yes"){
        setSettingsPermission(true);

        replies[5] = customQuestionMessageBox("Notifications", "Do you want to let this user adjust their notifications?");
        if (replies[5] == "Yes"){
            setNotificationsPermission(true);
        }else {
            setNotificationsPermission(false);
        }

        replies[6] = customQuestionMessageBox("Network", "Do you want to let this user access the network connections?");
        if (replies[6] == "Yes"){
            setNetworksPermission(true);
        }else {
            setNetworksPermission(false);
        }

    }else {
        setSettingsPermission(false);
        setNotificationsPermission(false);
        setNetworksPermission(false);
    }


    replies[7] = customQuestionMessageBox("Email", "Do you want to let this user receive emails?");
    if (replies[7] == "Yes"){
        setEmailPermission(true);
    }else {
        setEmailPermission(false);
    }

    replies[8] = customQuestionMessageBox("Reports", "Do you want to let this user handle reports?");
    if (replies[8] == "Yes"){
        setReportsPermission(true);
    }else {
        setReportsPermission(false);
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

void AddAUserDialog::on_AddAUserDialogAdminCheckBox_stateChanged(int arg1)
{
    checkAllBoxes(ui);
}

void AddAUserDialog::on_AddAUserDialogDataLoggersCheckBox_stateChanged(int arg1)
{
    if (arg1 == 2){
        ui->AddAUserDialogAddCheckBox->setCheckable(true);
        ui->AddAUserDialogModifyCheckBox->setCheckable(true);
        ui->AddAUserDialogRemoveCheckBox->setCheckable(true);
    } else if (arg1 == 0){
        ui->AddAUserDialogAddCheckBox->setChecked(false);
        ui->AddAUserDialogModifyCheckBox->setChecked(false);
        ui->AddAUserDialogRemoveCheckBox->setChecked(false);
        ui->AddAUserDialogAddCheckBox->setCheckable(false);
        ui->AddAUserDialogModifyCheckBox->setCheckable(false);
        ui->AddAUserDialogRemoveCheckBox->setCheckable(false);
    }
}

void AddAUserDialog::on_AddAUserDialogSettingsCheckBox_stateChanged(int arg1)
{
    if (arg1 == 2){
        ui->AddAUserDialogNotificationsCheckBox->setCheckable(true);
        ui->AddAUserDialogNetworkCheckBox->setCheckable(true);
    } else if(arg1 == 0){
        ui->AddAUserDialogNotificationsCheckBox->setChecked(false);
        ui->AddAUserDialogNetworkCheckBox->setChecked(false);
        ui->AddAUserDialogNotificationsCheckBox->setCheckable(false);
        ui->AddAUserDialogNetworkCheckBox->setCheckable(false);
    }
}
