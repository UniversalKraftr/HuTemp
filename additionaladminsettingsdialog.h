#ifndef ADDITIONALADMINSETTINGSDIALOG_H
#define ADDITIONALADMINSETTINGSDIALOG_H

#include <QDialog>
#include <QAbstractButton>


namespace Ui {
class AdditionalAdminSettingsDialog;
}

class AdditionalAdminSettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AdditionalAdminSettingsDialog(QWidget *parent = nullptr);
    ~AdditionalAdminSettingsDialog();
//    int getOpenTimeHour();
//    int getOpenTimeMinute();
//    int getCloseTimeHour();
//    int getCloseTimeMinute();
////    QString getCompanyName();
////    QString getCompanyAddress();
////    QString getCompanyPhoneNumber();
//    void setOpenTime(int hour, int minute);
//    void setCloseTime(int hour, int minute);
//    void setCompanyName(QString cname);
//    void setCompanyAddress(QString caddress);
//    void setCompanyPhoneNumber(QString cnumber);

private slots:
    void on_AdditionalAdminSettingsDialogButtonBox_clicked(QAbstractButton *button);

private:
    Ui::AdditionalAdminSettingsDialog *ui;
    void writeToLogFile();
    void extractFromLogFile();
//    Widget *widget = new Widget(this);



};

#endif // ADDITIONALADMINSETTINGSDIALOG_H
