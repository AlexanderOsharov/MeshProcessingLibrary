# MeshProcessingLibrary

## Описание
Библиотека для работы с 3D-сетками. Поддерживает преобразование карт высот в 3D-модели и экспорт в различные форматы.

## Установка
1. Клонируйте репозиторий:
   ```bash
   git clone https://github.com/AlexanderOsharov/MeshProcessingLibrary.git
   ```
2. Скомпилируйте библиотеку
   ```bash
   cmake .
   make
   ```
## Использование
Пример кода
```C++
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
    exporter.exportToFile(mesh, "output.obj");

    return 0;
}
```

## Форматы
1. Экспорт: OBJ, STL, PLY.
