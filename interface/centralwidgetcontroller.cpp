#include "centralwidgetcontroller.h"

CentralWidgetController::CentralWidgetController(QObject *parent) : QObject(parent)
{
    orion = std::make_shared<Orion>();
    load();
}

void CentralWidgetController::load()
{
    connect(&orionThread, &QThread::started, this, &CentralWidgetController::run);

    orionThread.setObjectName("Orion worker thread");
    orionThread.start();
}

void CentralWidgetController::run()
{
    orion -> run();
}

CentralWidgetController::~CentralWidgetController()
{
    orionThread.quit();
    orionThread.wait();
}
