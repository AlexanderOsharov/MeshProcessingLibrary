#include "STLExporter.h"
#include <fstream>

bool STLExporter::exportToFile(const Mesh& mesh, const std::string& filename) const {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) return false;

    const auto& vertices = mesh.getVertices();
    const auto& faces = mesh.getFaces();

    char header[80] = "HeightMapGenerator STL Exporter";
    file.write(header, 80);

    uint32_t numTriangles = faces.size();
    file.write(reinterpret_cast<const char*>(&numTriangles), sizeof(numTriangles));

    for (const auto& face : faces) {
        float normal[3] = {0.0f, 1.0f, 0.0f};
        file.write(reinterpret_cast<const char*>(normal), sizeof(normal));

        for (int i = 0; i < 3; ++i) {
            const auto& vertex = vertices[face.indices[i]];
            float data[3] = {vertex.x, vertex.y, vertex.z};
            file.write(reinterpret_cast<const char*>(data), sizeof(data));
        }

        uint16_t attribute = 0;
        file.write(reinterpret_cast<const char*>(&attribute), sizeof(attribute));
    }

    return true;
}