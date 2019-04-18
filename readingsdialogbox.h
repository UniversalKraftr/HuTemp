#ifndef READINGSDIALOGBOX_H
#define READINGSDIALOGBOX_H

#include <QDialog>
#include <QAbstractButton>

namespace Ui {
class ReadingsDialogBox;
}

class ReadingsDialogBox : public QDialog
{
    Q_OBJECT

public:
    explicit ReadingsDialogBox(QWidget *parent = nullptr);
    ~ReadingsDialogBox();

private slots:
    void on_ReadingsDialogBoxButtons_clicked(QAbstractButton *button);

private:
    Ui::ReadingsDialogBox *ui;
};

#endif // READINGSDIALOGBOX_H
