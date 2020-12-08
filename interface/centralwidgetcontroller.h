#ifndef CENTRALWIDGETCONTROLLER_H
#define CENTRALWIDGETCONTROLLER_H

#include <QObject>
#include <QThread>

#include "Orion.hpp"

class CentralWidgetController : public QObject
{
    Q_OBJECT
public:
    explicit CentralWidgetController(QObject *parent = nullptr);
    ~CentralWidgetController();

private:
    QThread orionThread;
    std::shared_ptr<Orion> orion;

    void load();

private slots:
    void run();
};

#endif // CENTRALWIDGETCONTROLLER_H
