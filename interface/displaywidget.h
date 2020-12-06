#ifndef DISPLAYWIDGET_H
#define DISPLAYWIDGET_H

#include <QOpenGLWidget>

class DisplayWidget : public QOpenGLWidget
{
public:
    DisplayWidget(QWidget* parent = nullptr) : QOpenGLWidget(parent)
    { }

    virtual void initializeGL() override;
    virtual void resizeGL(int width, int height) override;
    virtual void paintGL() override;
};


#endif // DISPLAYWIDGET_H
