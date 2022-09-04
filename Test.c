#include <stdio.h>
#include "ModelImporter.h"

int main()
{
    float* VertexArray = NULL;
    int* NumPosCoord = NULL;
    int* NumTexCoord = NULL;
    Import_x3d("Triangle.x3d", &VertexArray, &NumPosCoord, &NumTexCoord);

    assert(VertexArray);
    for (int i = 0; i < 15; ++i)
        printf("Coord is %f\n", VertexArray[i]);

    assert(NumPosCoord);
    assert(NumTexCoord);
    printf("Num pos coords %d\n", *NumPosCoord);
    printf("Num tex coords %d\n", *NumTexCoord);

    free(VertexArray);
    free(NumPosCoord);
    free(NumTexCoord);
    return 0;
}
