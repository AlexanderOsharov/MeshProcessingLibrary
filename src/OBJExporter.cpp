#include "OBJExporter.h"
#include <fstream>

bool OBJExporter::exportToFile(const Mesh& mesh, const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) return false;

    const auto& vertices = mesh.getVertices();
    const auto& faces = mesh.getFaces();

    for (const auto& vertex : vertices) {
        file << "v " << vertex.x << " " << vertex.y << " " << vertex.z << "\n";
        file << "vt " << vertex.u << " " << vertex.v << "\n"; // UV-координаты
    }

    for (const auto& face : faces) {
        file << "f " << face.indices[0] + 1 << " " << face.indices[1] + 1 << " " << face.indices[2] + 1 << "\n";
    }

    return true;
}