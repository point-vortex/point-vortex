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
