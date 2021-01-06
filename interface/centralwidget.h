#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include <QWidget>
#include <QThread>
#include <QTimer>

#include "Orion.hpp"

void somefunc();

class CentralWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CentralWidget(QWidget *parent = nullptr);
    ~CentralWidget();

    std::shared_ptr<Graphics> getGraphics() const;

private:
    QTimer  * timer;
    QThread * thread;

    std::shared_ptr<Orion> orion;
    std::shared_ptr<Graphics> graphics;
    
protected:
    virtual void keyPressEvent(QKeyEvent *event) override;
    virtual void keyReleaseEvent(QKeyEvent *event) override;
    
private slots:
    void onTimer();
    void onRun();

public slots:
    void onOpenFile(std::string path);
    
signals:
    void updateFrequency(double frequency);
    void updateFrame();
};

#endif // CENTRALWIDGET_H
