#ifndef PASSWORDRESET_H
#define PASSWORDRESET_H

#include <QDialog>
#include <QAbstractButton>
#include <QDialogButtonBox>
#include "smtp.h"

namespace Ui {
class passwordReset;
}

class passwordReset : public QDialog
{
    Q_OBJECT

public:
    explicit passwordReset(QWidget *parent = nullptr);
    ~passwordReset();

private slots:
    void on_passwordResetButtonBox_clicked(QAbstractButton *button);
    void sendMail(QString);
    void mailSent(QString);

private:
    Ui::passwordReset *ui;
    QStringList files;
};

#endif // PASSWORDRESET_H
