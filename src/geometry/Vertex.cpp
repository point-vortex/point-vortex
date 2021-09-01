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

#include "geometry/Vertex.h"

Vertex::Vertex(const QVector4D &position, const QVector4D &normal, const QVector2D &texCoords) {
    this->position = position;
    this->normal = normal;
    this->texCoords = texCoords;

}

Vertex::Vertex(float x, float y, float z, float nx, float ny, float nz, float u, float v) {
    this->position = QVector4D(x, y, z, 1);
    this->normal = QVector4D(nx, ny, nz, 1);
    this->texCoords = QVector2D(u, v);
}

void Vertex::showToConsole() const {
    qDebug() << this->position.x() << " " << this->position.y() << " " << this->position.z();
    qDebug() << " | " << this->normal.x() << " " << this->normal.y() << " " << this->normal.z();
    qDebug() << " | " << this->texCoords.x() << " " << this->texCoords.y();
    qDebug() << "\n";
}
