#ifndef MESHOPTIMIZER_H
#define MESHOPTIMIZER_H

#include "Mesh.h"

class MeshOptimizer {
public:
    static void removeDuplicateVertices(Mesh& mesh);
};

#endif // MESHOPTIMIZER_H