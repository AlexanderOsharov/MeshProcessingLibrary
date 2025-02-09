#ifndef OBJEXPORTER_H
#define OBJEXPORTER_H

#include "IMeshExporter.h"

class OBJExporter : public IMeshExporter {
public:
    bool exportToFile(const Mesh& mesh, const std::string& filename) const override;
};

#endif // OBJEXPORTER_H