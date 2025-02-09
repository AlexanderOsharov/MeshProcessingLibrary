#ifndef PLYEXPORTER_H
#define PLYEXPORTER_H

#include "IMeshExporter.h"

class PLYExporter : public IMeshExporter {
public:
    bool exportToFile(const Mesh& mesh, const std::string& filename) const override;
};

#endif // PLYEXPORTER_H