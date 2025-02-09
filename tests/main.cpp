#include <iostream>
#include "HeightMap.h"
#include "PerlinNoiseGenerator.h"
#include "HeightMapToMeshConverter.h"
#include "OBJExporter.h"

int main() {
    PerlinNoiseGenerator generator;
    HeightMap heightMap(100, 100);
    heightMap.setData(generator.generate(100, 100));

    Mesh mesh = HeightMapToMeshConverter::convert(heightMap);

    OBJExporter exporter;
    if (!exporter.exportToFile(mesh, "output.obj")) {
        std::cerr << "Failed to export mesh" << std::endl;
        return 1;
    }

    std::cout << "Mesh exported successfully!" << std::endl;
    return 0;
}