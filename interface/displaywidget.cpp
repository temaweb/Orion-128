#include "displaywidget.h"
#include "centralwidget.h"

#define FPS 60

DisplayWidget::DisplayWidget(QWidget * parent) : QOpenGLWidget(parent)
{
    auto central = static_cast<CentralWidget *>(parent);
    graphics = central -> getGraphics();
    
    connect(central, &CentralWidget::updateFrame, this, QOverload<>::of(&DisplayWidget::update));
}

void DisplayWidget::initializeGL()
{
    graphics -> initialize();
}

void DisplayWidget::resizeGL(int width, int height)
{
    this -> width  = width;
    this -> height = height;
}

void DisplayWidget::paintGL()
{
    graphics -> render (width, height);
}
