#ifndef IMESHEXPORTER_H
#define IMESHEXPORTER_H

#include "Mesh.h"
#include <string>

class IMeshExporter {
public:
    virtual ~IMeshExporter() = default;

    virtual bool exportToFile(const Mesh& mesh, const std::string& filename) const = 0;
};

#endif // IMESHEXPORTER_H