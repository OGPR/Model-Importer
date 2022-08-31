#include <stdio.h>
#include "ModelImporter.h"

int main()
{
    float* VertexArray = NULL;
    Import_x3d("Triangle.x3d", &VertexArray);

    assert(VertexArray);
    for (int i = 0; i < 15; ++i)
        printf("Coord is %f\n", VertexArray[i]);

    free(VertexArray);
    return 0;
}
