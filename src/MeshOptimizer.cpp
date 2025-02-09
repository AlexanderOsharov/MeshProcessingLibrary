#include "MeshOptimizer.h"
#include <unordered_map>
#include <vector>

void MeshOptimizer::removeDuplicateVertices(Mesh& mesh) {
    std::unordered_map<std::tuple<float, float, float>, int> vertexMap;
    std::vector<Vertex> newVertices;
    std::vector<Face> newFaces;

    for (const auto& vertex : mesh.getVertices()) {
        auto key = std::make_tuple(vertex.x, vertex.y, vertex.z);
        if (vertexMap.find(key) == vertexMap.end()) {
            vertexMap[key] = newVertices.size();
            newVertices.push_back(vertex);
        }
    }

    for (const auto& face : mesh.getFaces()) {
        std::array<int, 3> newIndices;
        for (int i = 0; i < 3; ++i) {
            auto key = std::make_tuple(mesh.getVertices()[face.indices[i]].x,
                                       mesh.getVertices()[face.indices[i]].y,
                                       mesh.getVertices()[face.indices[i]].z);
            newIndices[i] = vertexMap[key];
        }
        newFaces.push_back({newIndices});
    }

    mesh.m_vertices = newVertices;
    mesh.m_faces = newFaces;
}