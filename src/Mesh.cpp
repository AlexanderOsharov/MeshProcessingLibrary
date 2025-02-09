#include "Mesh.h"

void Mesh::addVertex(float x, float y, float z) {
    m_vertices.push_back({x, y, z});
}

void Mesh::addFace(int v1, int v2, int v3) {
    m_faces.push_back({{v1, v2, v3}});
}

const std::vector<Mesh::Vertex>& Mesh::getVertices() const {
    return m_vertices;
}

const std::vector<Mesh::Face>& Mesh::getFaces() const {
    return m_faces;
}

void Mesh::clear() {
    getFaces().clear();
    getVertices().assign(vertices.size(), {0.0f, 0.0f, 0.0f});
}

void Mesh::computeFaceNormals() {
    for (const auto& face : faces) {
        std::array<float, 3> v1 = vertices[face.indices[1]] - vertices[face.indices[0]];
        std::array<float, 3> v2 = vertices[face.indices[2]] - vertices[face.indices[0]];
        std::array<float, 3> normal = crossProduct(v1, v2);

        getFaceNormals().push_back(normal);
    }
}

void Mesh::computeVertexNormals() {
    for (const auto& face : faces) {
        std::array<float, 3> normal = getFaceNormals()[face.index];
        for (int i = 0; i < 3; ++i) {
            getVertexNormals()[face.indices[i]][0] += normal[0];
            getVertexNormals()[face.indices[i]][1] += normal[1];
            getVertexNormals()[face.indices[i]][2] += normal[2];
        }
    }

    for (auto& normal : getVertexNormals()) {
        float length = std::sqrt(normal[0] * normal[0] + normal[1] * normal[1] + normal[2] * normal[2]);
        if (length > 0.0f) {
            normal[0] /= length;
            normal[1] /= length;
            normal[2] /= length;
        }
    }
}

std::array<float, 3> Mesh::crossProduct(const std::array<float, 3>& a, const std::array<float, 3>& b) {
    return {{
        a[1] * b[2] - a[2] * b[1],
        a[2] * b[0] - a[0] * b[2],
        a[0] * b[1] - a[1] * b[0]
    }};
}