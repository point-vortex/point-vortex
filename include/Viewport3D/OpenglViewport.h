#ifndef POINT_VORTEX_OPENGLVIEWPORT_H
#define POINT_VORTEX_OPENGLVIEWPORT_H

#include <QOpenGLWindow>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>

class OpenglViewport : public QOpenGLWindow, protected QOpenGLFunctions {
protected:
    QOpenGLShaderProgram *shadingProgram = nullptr;
public:
    int m_frame = 0;
public:
    explicit OpenglViewport();
protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void paintUnderGL() override;
    void paintOverGL() override;
};


#endif //POINT_VORTEX_OPENGLVIEWPORT_H
