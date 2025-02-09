#ifndef MESH_H
#define MESH_H

#include <vector>
#include <array>

struct Vertex {
    std::array<float, 3> position;
};

struct Face {
    std::array<int, 3> indices;
    int index;
};

class Mesh {
public:
    std::vector<Vertex> vertices;
    std::vector<Face> faces;

    void clear();
    void computeFaceNormals();
    void computeVertexNormals();

    std::vector<std::array<float, 3>> getFaceNormals() const;
    std::vector<std::array<float, 3>> getVertexNormals() const;

private:
    std::array<float, 3> crossProduct(const std::array<float, 3>& a, const std::array<float, 3>& b);
};

#endif // MESH_H