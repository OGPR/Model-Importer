#include <stdio.h>
#include "ModelImporter.h"

int main()
{
    float* VertexArray = NULL;
    int* NumVertex = NULL;
    int* NumTexCoord = NULL;
    unsigned int* Model_Indices = NULL;
    unsigned int* Model_IndexArray = NULL;
    Import_x3d("Triangle.x3d", &VertexArray, &NumVertex, &NumTexCoord, &Model_Indices, &Model_IndexArray);

    assert(NumVertex);
    assert(NumTexCoord);
    printf("Num of vertices %d\n", *NumVertex);
    printf("Num tex coords %d\n", *NumTexCoord);
    assert(VertexArray);
    for (int i = 0; i < *NumVertex * 3 + *NumTexCoord * 2; ++i)
        printf("Coord is %f\n", VertexArray[i]);


    assert(Model_Indices);
    printf("Model_Indices %d\n", *Model_Indices);

    assert(Model_IndexArray);
    for (int i = 0; i < *Model_Indices; ++i)
        printf("Model_IndexArray %d\n", Model_IndexArray[i]);

    free(VertexArray);
    VertexArray = NULL;
    free(NumVertex);
    NumVertex = NULL;
    free(NumTexCoord);
    NumTexCoord = NULL;
    free(Model_Indices);
    Model_Indices = NULL;
    free(Model_IndexArray);
    Model_IndexArray = NULL;

    printf("--------------------------\n");

    Import_x3d("Plane.x3d", &VertexArray, &NumVertex, &NumTexCoord, &Model_Indices, &Model_IndexArray);

    assert(NumVertex);
    assert(NumTexCoord);
    printf("Num of vertices %d\n", *NumVertex);
    printf("Num tex coords %d\n", *NumTexCoord);
    assert(VertexArray);
    for (int i = 0; i < *NumVertex * 3 + *NumTexCoord * 2; ++i)
        printf("Coord is %f\n", VertexArray[i]);


    assert(Model_Indices);
    printf("Model_Indices %d\n", *Model_Indices);

    assert(Model_IndexArray);
    for (int i = 0; i < *Model_Indices; ++i)
        printf("Model_IndexArray %d\n", Model_IndexArray[i]);

    free(VertexArray);
    VertexArray = NULL;
    free(NumVertex);
    NumVertex = NULL;
    free(NumTexCoord);
    NumTexCoord = NULL;
    free(Model_Indices);
    Model_Indices = NULL;
    free(Model_IndexArray);
    Model_IndexArray = NULL;

    return 0;
}
