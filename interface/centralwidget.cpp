#include <QKeyEvent>
#include "centralwidget.h"

#define FPS 60

CentralWidget::CentralWidget(QWidget *parent) : QWidget(parent)
{
    orion = std::make_shared<Orion>();
    graphics = orion -> createGraphics();

    auto run = [this]() {
        orion -> run();
    };
    
    timer = new QTimer(this);
    thread = QThread::create(run);
    
    connect(timer,  &QTimer::timeout,  this, &CentralWidget::onTimer);
    connect(thread, &QThread::started, this, &CentralWidget::onRun);
    
    thread -> setObjectName("Orion thread");
    thread -> start();
    
    setFocusPolicy(Qt::StrongFocus);
}

void CentralWidget::onTimer()
{
    if (graphics -> isChanged())
    {
        emit updateFrame();
    }

    emit updateFrequency(orion -> getFrequency());
}

void CentralWidget::onRun()
{
    timer -> start(1000 / FPS);
}

void CentralWidget::onOpenFile(std::string path)
{
    orion -> createFile(path);
}

std::shared_ptr<Graphics> CentralWidget::getGraphics() const
{
    return graphics;
}

void CentralWidget::keyPressEvent(QKeyEvent *event)
{
    orion -> keyevent(event -> key(), true);
}

void CentralWidget::keyReleaseEvent(QKeyEvent *event)
{
    orion -> keyevent(event -> key(), false);
}

CentralWidget::~CentralWidget()
{
    orion -> stop();
    
    if (timer -> isActive())
        timer -> stop();
    
    if (thread -> isRunning())
    {
        thread -> quit();
        thread -> wait();
    }
    
    delete timer;
    delete thread;
}
