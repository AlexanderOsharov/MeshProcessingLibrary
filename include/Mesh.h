#ifndef MESH_H
#define MESH_H

#include <vector>
#include <array>

struct Vertex {
    float x, y, z;
    float u, v; // UV-координаты
};

struct Face {
    std::array<int, 3> indices; // Индексы вершин
};

class Mesh {
public:
    void addVertex(float x, float y, float z);
    void addFace(int v1, int v2, int v3);
    void calculateNormals();
    void simplify(float targetPercentage);
    
    std::vector<std::array<float, 3>> getFaceNormals() const;
    std::vector<std::array<float, 3>> getVertexNormals() const;

    const std::vector<Vertex>& getVertices() const;
    const std::vector<Face>& getFaces() const;

private:
    std::vector<Vertex> m_vertices;
    std::vector<Face> m_faces;
};

#endif // MESH_H