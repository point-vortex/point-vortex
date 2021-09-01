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

#include "Viewport3D/OpenglViewport.h"

#include <QScreen>

OpenglViewport::OpenglViewport() {

}

void OpenglViewport::initializeGL() {
    shadingProgram = new QOpenGLShaderProgram(this);
    shadingProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, "shaders/viewport3d.vert");
    shadingProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, "shaders/viewport3d.frag");
    shadingProgram->link();
//    m_posAttr = shadingProgram->attributeLocation("posAttr");
//    Q_ASSERT(m_posAttr != -1);
//    m_colAttr = shadingProgram->attributeLocation("colAttr");
//    Q_ASSERT(m_colAttr != -1);
//    m_matrixUniform = shadingProgram->uniformLocation("matrix");
//    Q_ASSERT(m_matrixUniform != -1);

}

void OpenglViewport::resizeGL(int w, int h) {

}

void OpenglViewport::paintGL() {
    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);

    glClear(GL_COLOR_BUFFER_BIT);

    shadingProgram->bind();

    QMatrix4x4 matrix;
    matrix.perspective(60.0f, 4.0f / 3.0f, 0.1f, 100.0f);
    matrix.translate(0, 0, -2);
    matrix.rotate(100.0f * static_cast<float>(m_frame) / screen()->refreshRate(), 0, 1, 0);

    shadingProgram->setUniformValue(m_matrixUniform, matrix);

    static const GLfloat vertices[] = {
            0.0f,  0.707f,
            -0.5f, -0.5f,
            0.5f, -0.5f
    };

    static const GLfloat colors[] = {
            1.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 1.0f
    };

    glVertexAttribPointer(m_posAttr, 2, GL_FLOAT, GL_FALSE, 0, vertices);
    glVertexAttribPointer(m_colAttr, 3, GL_FLOAT, GL_FALSE, 0, colors);

    glEnableVertexAttribArray(m_posAttr);
    glEnableVertexAttribArray(m_colAttr);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableVertexAttribArray(m_colAttr);
    glDisableVertexAttribArray(m_posAttr);

    shadingProgram->release();

    ++m_frame;
}

void OpenglViewport::paintUnderGL() {

}

void OpenglViewport::paintOverGL() {

}
