#pragma once
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#define MAX_LINE_LENGTH 1024
#define MAX_LINES 1024
#define MODEL_IMPORTER_SUCCESS 0
enum E_MODEL_IMPORTER_ERROR_CODE
{
    MODEL_IMPORTER_ERROR_CODE_UNSET = -1,
    MODEL_IMPORTER_GETCWD_ERROR = 2,
    MODEL_IMPORTER_FILE_NOT_FOUND_ERROR = 3,
    MODEL_IMPORTER_X3D_FILE_FORMAT_ERROR = 4
}MODEL_IMPORTER_ERROR_CODE;

int CharToIntDigit(char c)
{
    if (c == 48) return 0;
    if (c == 49) return 1;
    if (c == 50) return 2;
    if (c == 51) return 3;
    if (c == 52) return 4;
    if (c == 53) return 5;
    if (c == 54) return 6;
    if (c == 55) return 7;
    if (c == 56) return 8;
    if (c == 57) return 9;
    else return -999;
}

int Import_x3d(char* Filename, float** VertexArray, int** NumVertex, int** NumTexCoord)
{
    MODEL_IMPORTER_ERROR_CODE = MODEL_IMPORTER_ERROR_CODE_UNSET;
    FILE *fp;
    fp = fopen(Filename, "r");
    if (!fp)
    {
        char cwd[PATH_MAX];
        if (!getcwd(cwd, sizeof(cwd)))
        {
            MODEL_IMPORTER_ERROR_CODE = MODEL_IMPORTER_GETCWD_ERROR;
            return MODEL_IMPORTER_ERROR_CODE;
        }
        printf("No file named %s found in %s\n", Filename, cwd);
        MODEL_IMPORTER_ERROR_CODE = MODEL_IMPORTER_FILE_NOT_FOUND_ERROR;
        return MODEL_IMPORTER_ERROR_CODE;
    }

    char line[MAX_LINES][MAX_LINE_LENGTH];
    char TargetLine[MAX_LINE_LENGTH];

    float VertexArray_Internal[100];
    int CurrLineNum = 0;
    int TargetLineCount = 0;
    int PositionCoordLineLength = 0;
    int TextureCoordLineLength = 0;
    int NumVertices = 0;
    while (1)
    {
        char* LineReadRes = fgets(line[CurrLineNum], MAX_LINE_LENGTH, fp);
        if(!LineReadRes)
            break;

        char* cp = NULL;
        for (int i = 0; i < MAX_LINE_LENGTH; ++i) 
        {
            cp = &line[CurrLineNum][i];
            assert(cp);

            if (*cp == '\n') break;

            if ( *cp == 'p' &&
                 *++cp == 'o' &&
                 *++cp  == 'i' &&
                 *++cp == 'n' &&
                 *++cp == 't' &&
                 *++cp == '=') 
            {
                ++TargetLineCount;

                if (*++cp != '"')
                {
                    printf("Error in x3d file - expecting a \"\n");
                    MODEL_IMPORTER_ERROR_CODE = MODEL_IMPORTER_X3D_FILE_FORMAT_ERROR;
                    return MODEL_IMPORTER_ERROR_CODE;
                }
                
                cp = &line[CurrLineNum][i + 6];
                while (*++cp != '"')
                {
                    if (TargetLineCount == 1) ++PositionCoordLineLength;
                    if (TargetLineCount == 2) ++TextureCoordLineLength;

                    char* Base_cp = cp;

                    char Length_IntPart = 0; 
                    char Length_FracPart = 0; 
                    
                    int FracPartSwitch = 0;
                    int Minus = 0;
                    // First pass - get the length of the vertex coordinate
                    while (*cp != ' ')
                    {
                        if (*cp == '-')
                           Minus = 1;
                        else if (!FracPartSwitch && *cp != '.')
                            ++Length_IntPart;
                        else if (!FracPartSwitch && *cp == '.')
                            FracPartSwitch = 1;
                        else if (FracPartSwitch)
                            ++Length_FracPart;
                            
                        ++cp;
                    }

                    // Second pass - create the number  
                    float IntegerPart = 0;
                    float FracPart = 0;

                    // Reset the pointer
                    if (Minus)
                        cp = Base_cp + 1;
                    else
                        cp = Base_cp;

                    assert (*cp != ' ');
                    while (*cp != ' ')
                    {
                        // Integer part
                        while (*cp != '.')
                            for (char i = Length_IntPart - 1; i > -1; --i)
                                IntegerPart += CharToIntDigit(*cp++) * pow(10, i);

                        // Fractional part
                        ++cp;
                        for (char i = Length_FracPart - 1; i > -1; --i)
                            FracPart += CharToIntDigit(*cp++) * pow(10, i);
                    }


                    FracPart /= pow(10, Length_FracPart);

                    float FinalNum = IntegerPart + FracPart;
                    if (Minus)
                        FinalNum *= -1; ;

                    VertexArray_Internal[NumVertices] = FinalNum;
                    ++NumVertices;

                }

            }

         }

        
         if (TargetLineCount == 2) break;

         ++CurrLineNum;
    }

    fclose(fp);


    *VertexArray = (float*)calloc(NumVertices, sizeof(float));
    for (int i = 0; i < NumVertices; ++i)
        (*VertexArray)[i] = VertexArray_Internal[i];

    *NumVertex = (int*)calloc(1, sizeof(int));
    *NumTexCoord = (int*)calloc(1, sizeof(int));

    **NumVertex = PositionCoordLineLength / 3;
    **NumTexCoord = TextureCoordLineLength / 2;


    return MODEL_IMPORTER_SUCCESS;

}

