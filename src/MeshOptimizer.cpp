#include "MeshOptimizer.h"
#include <unordered_map>
#include <vector>
#include <tuple>
#include <functional>

struct hash<std::tuple<float, float, float>> {
    size_t operator()(const std::tuple<float, float, float>& key) const {
        size_t h1 = hash<float>{}(std::get<0>(key));
        size_t h2 = hash<float>{}(std::get<1>(key));
        size_t h3 = hash<float>{}(std::get<2>(key));

        return h1 ^ (h2 << 1) ^ (h3 << 2);
    }
};

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