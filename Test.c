#include <stdio.h>
#include "ModelImporter.h"

int main()
{
    float VertexArray[1];
    Import_x3d("Triangle.x3d", VertexArray);
    for (int i = 0; i < 1; ++i)
        printf("Coord is %f\n", VertexArray[0]);
    return 0;
}
