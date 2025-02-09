#ifndef STLEXPORTER_H
#define STLEXPORTER_H

#include "IMeshExporter.h"

class STLExporter : public IMeshExporter {
public:
    bool exportToFile(const Mesh& mesh, const std::string& filename) const override;
};

#endif // STLEXPORTER_H