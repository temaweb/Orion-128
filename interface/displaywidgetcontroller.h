#ifndef DISPLAYWIDGETCONTROLLER_H
#define DISPLAYWIDGETCONTROLLER_H

#include <QObject>

class DisplayWidgetController : public QObject
{
    Q_OBJECT
public:
    explicit DisplayWidgetController(QObject *parent = nullptr);

signals:

};

#endif // DISPLAYWIDGETCONTROLLER_H
