// MIT License
//
// Copyright (c) 2021 Point Vortex | Danil Maksimovich Andrieiev
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

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
