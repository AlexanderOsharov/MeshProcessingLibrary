#include "PLYExporter.h"
#include <fstream>

bool PLYExporter::exportToFile(const Mesh& mesh, const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) return false;

    const auto& vertices = mesh.getVertices();
    const auto& faces = mesh.getFaces();

    file << "ply\n";
    file << "format ascii 1.0\n";
    file << "element vertex " << vertices.size() << "\n";
    file << "property float x\n";
    file << "property float y\n";
    file << "property float z\n";
    file << "element face " << faces.size() << "\n";
    file << "property list uchar int vertex_indices\n";
    file << "end_header\n";

    for (const auto& vertex : vertices) {
        file << vertex.x << " " << vertex.y << " " << vertex.z << "\n";
    }

    for (const auto& face : faces) {
        file << "3 " << face.indices[0] << " " << face.indices[1] << " " << face.indices[2] << "\n";
    }

    return true;
}