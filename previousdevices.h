#ifndef PREVIOUSDEVICES_H
#define PREVIOUSDEVICES_H

#include <QDialog>

namespace Ui {
class PreviousDevices;
}

class PreviousDevices : public QDialog
{
    Q_OBJECT

public:
    explicit PreviousDevices(QWidget *parent = nullptr);
    ~PreviousDevices();

private slots:
    void on_archivedDevicesRestoreButton_clicked();

    void on_archivedDevicesExitButton_clicked();

    void populateListWidget();

private:
    Ui::PreviousDevices *ui;
};

#endif // PREVIOUSDEVICES_H
