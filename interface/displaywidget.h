#ifndef DISPLAYWIDGET_H
#define DISPLAYWIDGET_H

#include <QTimer>
#include <QOpenGLWidget>

#include "Graphics.hpp"

class DisplayWidget : public QOpenGLWidget
{
    Q_OBJECT
    
private:
    std::shared_ptr<Graphics> graphics;

    int width;
    int height;
    
public:
    explicit DisplayWidget(QWidget * parent = nullptr);
    ~DisplayWidget() {};

protected:
    virtual void initializeGL() override;
    virtual void resizeGL(int width, int height) override;
    virtual void paintGL() override;
};


#endif // DISPLAYWIDGET_H
