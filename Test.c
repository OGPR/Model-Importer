#include <stdio.h>
#include "ModelImporter.h"

int main()
{
    float VertexArray[9];
    Import_x3d("Triangle.x3d", VertexArray);
    for (int i = 0; i < 9; ++i)
        printf("Coord is %f\n", VertexArray[i]);
    return 0;
}
