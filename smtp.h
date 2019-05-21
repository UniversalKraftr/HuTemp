#ifndef SMTP_H
#define SMTP_H

#include <QObject>

class Smtp : public QObject
{
    Q_OBJECT
public:
    explicit Smtp(QObject *parent = nullptr);

signals:

public slots:
};

#endif // SMTP_H
