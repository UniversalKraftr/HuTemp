#include "newpasswordpostresetdialog.h"
#include "ui_newpasswordpostresetdialog.h"


NewPasswordPostResetDialog::NewPasswordPostResetDialog(QString username, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewPasswordPostResetDialog)
{
    ui->setupUi(this);

    userName = username;
    setWindowTitle("Password Reset");
    setWindowIcon(QIcon("://icons/logo_O9H_2.ico"));
    adjustSize();
    setTextSuggestions();
    setDefaults();
}

NewPasswordPostResetDialog::~NewPasswordPostResetDialog()
{
    delete ui;
}

void NewPasswordPostResetDialog::setTextSuggestions()
{
    ui->NewPasswordPostResetDialogTemporaryPasswordLineEdit->setPlaceholderText("Temporary Password");
    ui->NewPasswordPostResetDialogEnterNewPasswordLineEdit->setPlaceholderText("Enter a new password");
    ui->NewPasswordPostResetDialogReenterNewPasswordLineEdit->setPlaceholderText("Re-enter your new password");
}

void NewPasswordPostResetDialog::setDefaults()
{
    setTabOrder(ui->NewPasswordPostResetDialogTemporaryPasswordLineEdit, ui->NewPasswordPostResetDialogEnterNewPasswordLineEdit);
    setTabOrder(ui->NewPasswordPostResetDialogEnterNewPasswordLineEdit, ui->NewPasswordPostResetDialogReenterNewPasswordLineEdit);
    ui->NewPasswordPostResetDialogTemporaryPasswordLineEdit->setFocus();
}

bool NewPasswordPostResetDialog::validatePassword()
{
    QString newPassword = ui->NewPasswordPostResetDialogEnterNewPasswordLineEdit->text();

    upper = 0;
    lower = 0;
    number = 0;
    specialChar = 0;

    for (const auto &character: newPassword){
        if (character.isUpper()){
            //    qDebug() << "upper";
            upper++;
        } else if (character.isLower()){
            //    qDebug() << "lower";
            lower++;
        } else if (character.isDigit()){
            //    qDebug() << "digit";
            number++;
        } else{
            //    qDebug() << "special";
            specialChar++;
        }
    }

    if (upper >= 2 && lower >= 2 && number >= 1 && specialChar >= 1 && newPassword.length() >= 8){
        return true;
    } else{
        return false;
    }
}

bool NewPasswordPostResetDialog::validateReenteredPassword()
{
    return ui->NewPasswordPostResetDialogReenterNewPasswordLineEdit->text() == ui->NewPasswordPostResetDialogEnterNewPasswordLineEdit->text();
}

bool NewPasswordPostResetDialog::updatePassword()
{
    QString newPassword = ui->NewPasswordPostResetDialogEnterNewPasswordLineEdit->text();
    QString offset = generateOffset(newPassword);
    QString offsetEncrypted = encrypt(offset);
    QString newPasswordEncrypted = encrypt(newPassword);
    QString finalPassword = newPasswordEncrypted + offsetEncrypted;
    QString finalPasswordEncrypted = encrypt(finalPassword);



    QSqlQuery updateQuery;
    QString updateQueryStatement = QString("UPDATE login SET password = AES_ENCRYPT('%1', '%2'), offset = AES_ENCRYPT('%4', '%2'), "
                                           "temporarypassword = 0, lockout = 0 WHERE username = '%3'")
            .arg(finalPasswordEncrypted).arg(KEY).arg(userName).arg(offsetEncrypted);
    if (updateQuery.exec(updateQueryStatement)){
        return true;
    } else{
        return false;
    }
}

QString NewPasswordPostResetDialog::encrypt(QString input)
{
    return input.toLocal8Bit().toHex().toBase64();
}

QString NewPasswordPostResetDialog::decrypt(QString input)
{
    QByteArray reverseInput = QByteArray::fromStdString(input.toStdString());
    QByteArray b64FromStdStringInput = QByteArray::fromBase64(reverseInput);
    QByteArray fromHexInput = QByteArray::fromHex(b64FromStdStringInput);
    QString toDecrypt = fromHexInput;
    return toDecrypt;
}

QString NewPasswordPostResetDialog::generateOffset(QString password)
{
    int length = 64 - password.length();

    QString offsetFill = "";
    for (int i = 0; i < length; i++){
        std::uniform_int_distribution<int> distribution(1, charList.count());
        int value = distribution(*QRandomGenerator::global()) - 1;

        QChar character = charList[value];

        offsetFill.append(character);
    }
    //    qDebug() << "offsetFill:\t" << offsetFill;
    return offsetFill;
}

void NewPasswordPostResetDialog::on_NewPasswordPostResetDialogButtons_clicked(QAbstractButton *button)
{
    QDialogButtonBox::StandardButton newPasswordButton = ui->NewPasswordPostResetDialogButtons->standardButton(button);

    if (newPasswordButton == QDialogButtonBox::Ok){
        if (validatePassword() == true){
            if (validateReenteredPassword() == true){
                if (updatePassword() == true){
                    QMessageBox::information(this, tr("SUCCESS"), "Your password has been successfully reset\nYour account is restored");
                    accept();;
                }else{
                    QMessageBox::warning(this, tr("ERROR"), "Your password cannot be changed at this time.");
                }
            } else{
                QMessageBox::warning(this, tr("ERROR"), "Your re-entry must match your new password");
                ui->NewPasswordPostResetDialogReenterNewPasswordLineEdit->clear();
            }
        } else{
            QMessageBox::warning(this, tr("ERROR"), "Your password must consist of at least:"
                                                    "\n - 2 uppercase letters\n - 2 lowercase letters"
                                                    "\n - 1 number\n - 1 special character\n\nand be 8 - 10 characters long");
            upper = 0;
            lower = 0;
            number = 0;
            specialChar = 0;
        }

    }
    if (newPasswordButton == QDialogButtonBox::Cancel){
        reject();
    }
}

void NewPasswordPostResetDialog::on_NewPasswordPostResetDialogNewPasswordRevealButton_clicked()
{
    QPixmap revealPixmap(":/icons/icons8-eye-30.png");
    QIcon revealIcon(revealPixmap);

    QPixmap concealPixmap(":/icons/icons8-invisible-30.png");
    QIcon concealIcon(concealPixmap);


    if (ui->NewPasswordPostResetDialogEnterNewPasswordLineEdit->echoMode() == QLineEdit::Password){
        ui->NewPasswordPostResetDialogEnterNewPasswordLineEdit->setEchoMode(QLineEdit::Normal);
        ui->NewPasswordPostResetDialogNewPasswordRevealButton->setIcon(concealIcon);
        ui->NewPasswordPostResetDialogNewPasswordRevealButton->setIconSize(QSize(38, 38));
    } else if (ui->NewPasswordPostResetDialogEnterNewPasswordLineEdit->echoMode() == QLineEdit::Normal){
        ui->NewPasswordPostResetDialogEnterNewPasswordLineEdit->setEchoMode(QLineEdit::Password);
        ui->NewPasswordPostResetDialogNewPasswordRevealButton->setIcon(revealIcon);
        ui->NewPasswordPostResetDialogNewPasswordRevealButton->setIconSize(QSize(38, 38));
    }
}

void NewPasswordPostResetDialog::on_NewPasswordPostResetDialogReEnterPasswordRevealButton_clicked()
{
    QPixmap revealPixmap(":/icons/icons8-eye-30.png");
    QIcon revealIcon(revealPixmap);

    QPixmap concealPixmap(":/icons/icons8-invisible-30.png");
    QIcon concealIcon(concealPixmap);


    if (ui->NewPasswordPostResetDialogReenterNewPasswordLineEdit->echoMode() == QLineEdit::Password){
        ui->NewPasswordPostResetDialogReenterNewPasswordLineEdit->setEchoMode(QLineEdit::Normal);
        ui->NewPasswordPostResetDialogReEnterPasswordRevealButton->setIcon(concealIcon);
        ui->NewPasswordPostResetDialogReEnterPasswordRevealButton->setIconSize(QSize(38, 38));
    } else if (ui->NewPasswordPostResetDialogReenterNewPasswordLineEdit->echoMode() == QLineEdit::Normal){
        ui->NewPasswordPostResetDialogReenterNewPasswordLineEdit->setEchoMode(QLineEdit::Password);
        ui->NewPasswordPostResetDialogReEnterPasswordRevealButton->setIcon(revealIcon);
        ui->NewPasswordPostResetDialogReEnterPasswordRevealButton->setIconSize(QSize(38, 38));
    }
}
