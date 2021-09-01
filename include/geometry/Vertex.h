#ifndef POINT_VORTEX_VERTEX_H
#define POINT_VORTEX_VERTEX_H

#include <ostream>

#include <QVector4D>
#include <QVector3D>
#include <QVector2D>
#include <QDebug>

struct Vertex {
public:
    QVector4D position;
    QVector4D normal;
    QVector2D texCoords;
public:
    explicit Vertex(const QVector4D &position, const QVector4D &normal, const QVector2D &texCoords);
    explicit Vertex(
            float x = 0,
            float y = 0,
            float z = 0,
            float nx = 0,
            float ny = 0,
            float nz = 0,
            float u = 0,
            float v = 0);
public:
    void showToConsole() const;
};

#endif //POINT_VORTEX_VERTEX_H
