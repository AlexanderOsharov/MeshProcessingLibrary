#include "Mesh.h"
#include <cmath>
#include <queue>

void Mesh::addVertex(float x, float y, float z) {
    m_vertices.push_back({x, y, z});
}

void Mesh::addFace(int v1, int v2, int v3) {
    m_faces.push_back({{v1, v2, v3}});
}

void Mesh::calculateNormals() {
    m_faceNormals.clear();
    m_vertexNormals.assign(m_vertices.size(), {0.0f, 0.0f, 0.0f});

    for (const auto& face : m_faces) {
        const auto& v1 = m_vertices[face.indices[0]];
        const auto& v2 = m_vertices[face.indices[1]];
        const auto& v3 = m_vertices[face.indices[2]];

        // Векторы сторон треугольника
        std::array<float, 3> edge1 = {v2.x - v1.x, v2.y - v1.y, v2.z - v1.z};
        std::array<float, 3> edge2 = {v3.x - v1.x, v3.y - v1.y, v3.z - v1.z};

        // Векторное произведение
        std::array<float, 3> normal = {
            edge1[1] * edge2[2] - edge1[2] * edge2[1],
            edge1[2] * edge2[0] - edge1[0] * edge2[2],
            edge1[0] * edge2[1] - edge1[1] * edge2[0]
        };

        // Нормализация
        float length = std::sqrt(normal[0] * normal[0] + normal[1] * normal[1] + normal[2] * normal[2]);
        if (length > 0.0f) {
            normal[0] /= length;
            normal[1] /= length;
            normal[2] /= length;
        }

        m_faceNormals.push_back(normal);

        // Суммируем нормали для вершин
        for (int i = 0; i < 3; ++i) {
            m_vertexNormals[face.indices[i]][0] += normal[0];
            m_vertexNormals[face.indices[i]][1] += normal[1];
            m_vertexNormals[face.indices[i]][2] += normal[2];
        }
    }

    // Нормализация вершинных нормалей
    for (auto& normal : m_vertexNormals) {
        float length = std::sqrt(normal[0] * normal[0] + normal[1] * normal[1] + normal[2] * normal[2]);
        if (length > 0.0f) {
            normal[0] /= length;
            normal[1] /= length;
            normal[2] /= length;
        }
    }
}

void Mesh::simplify(float targetPercentage) {
    if (targetPercentage <= 0.0f || targetPercentage >= 1.0f) return;

    int targetFaces = static_cast<int>(m_faces.size() * targetPercentage);

    struct EdgeCollapse {
        float cost;
        int v1, v2;
    };

    // Создание очереди с приоритетом для рёбер
    std::priority_queue<EdgeCollapse, std::vector<EdgeCollapse>, std::greater<EdgeCollapse>> queue;

    // Вычисление стоимости каждого ребра
    for (const auto& face : m_faces) {
        for (int i = 0; i < 3; ++i) {
            int v1 = face.indices[i];
            int v2 = face.indices[(i + 1) % 3];

            float cost = computeEdgeCost(v1, v2); // Реализуйте функцию для вычисления стоимости
            queue.push({cost, v1, v2});
        }
    }

    while (!queue.empty() && m_faces.size() > targetFaces) {
        auto collapse = queue.top();
        queue.pop();

        collapseEdge(collapse.v1, collapse.v2); // Реализуйте функцию для коллапса ребра
    }
}

std::vector<std::array<float, 3>> Mesh::getFaceNormals() const {
    return m_faceNormals;
}

std::vector<std::array<float, 3>> Mesh::getVertexNormals() const {
    return m_vertexNormals;
}

const std::vector<Mesh::Vertex>& Mesh::getVertices() const {
    return m_vertices;
}

const std::vector<Mesh::Face>& Mesh::getFaces() const {
    return m_faces;
}