#ifndef MESH_H
#define MESH_H

#include <vector>
#include <array>

struct Vertex {
    float x, y, z;

    Vertex operator-(const Vertex& other) const {
        return {x - other.x, y - other.y, z - other.z};
    }
};

struct Face {
    std::array<int, 3> indices;
    int index;
};

class Mesh {
public:
    void addVertex(float x, float y, float z);
    void addFace(int v1, int v2, int v3);

    void clear();
    void computeFaceNormals();
    void computeVertexNormals();

    const std::vector<Vertex>& getFaces() const;
    const std::vector<Face>& getVertices() const;

private:
    std::vector<Vertex> m_vertices;
    std::vector<Face> m_faces;
    std::array<float, 3> crossProduct(const std::array<float, 3>& a, const std::array<float, 3>& b);
};

#endif // MESH_H