#include <stdio.h>
#include "ModelImporter.h"

int main()
{
    float* VertexArray = NULL;
    int* NumVertex = NULL;
    int* NumTexCoord = NULL;
    Import_x3d("Triangle.x3d", &VertexArray, &NumVertex, &NumTexCoord);

    assert(VertexArray);
    for (int i = 0; i < 15; ++i)
        printf("Coord is %f\n", VertexArray[i]);

    assert(NumVertex);
    assert(NumTexCoord);
    printf("Num of vertices %d\n", *NumVertex);
    printf("Num tex coords %d\n", *NumTexCoord);

    free(VertexArray);
    free(NumVertex);
    free(NumTexCoord);
    return 0;
}
