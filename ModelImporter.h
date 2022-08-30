#pragma once
#include <stdio.h>
#include <assert.h>
#include <math.h>
#define MAX_LINE_LENGTH 1024
#define MAX_LINES 1024

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

void Import_x3d(char* Filename)
{
    FILE *fp;
    fp = fopen(Filename, "r");

    char line[MAX_LINES][MAX_LINE_LENGTH];
    char TargetLine[MAX_LINE_LENGTH];

    int CurrLineNum = 0;
    int TargetLineNum = -1;
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
                if (*++cp != '"')
                {
                    printf("Error in x3d file - expecting a \"\n");
                    return;
                }
                
                ++cp;

                char Length_IntPart = 0; 
                char Length_FracPart = 0; 
                
                int FracPartSwitch = 0;
                int Minus = 0;
                // First pass - get the length
                while (*cp != ' ')
                {
                    if (*cp == '-')
                       Minus = 1;
                    else if (!FracPartSwitch && *cp != '.')
                        ++Length_IntPart;
                    else if (!FracPartSwitch && *cp == '.')
                    {
                        FracPartSwitch = 1;
                    }
                    else if (FracPartSwitch)
                        ++Length_FracPart;
                        
                    ++cp;
                }

                // Second pass - populate the parts

                float IntegerPart = 0;

                // Reset the pointer
                if (Minus)
                    cp = &line[CurrLineNum][i + 8];
                else
                    cp = &line[CurrLineNum][i + 7];


                assert (*cp != ' ');
                printf("Length of int part %d\n", Length_IntPart);
                printf("%c\n", *cp);
                printf("%d\n", CharToIntDigit(*cp));
                while (*cp != '.')
                {
                    for (char i = Length_IntPart - 1; i > -1; --i)
                    {
                        IntegerPart += CharToIntDigit(*cp) * pow(10, i);
                        printf("Curr int part, %f", IntegerPart);
                        ++cp;
                    }
                }

                if (Minus)
                    IntegerPart *= -1;

                printf("Integer part %f\n", IntegerPart);

                
                ++cp;
                float FracPart = 0;

                printf("Length of frac part %d\n", Length_FracPart);
                while (*cp != ' ')
                {
                    for (char i = Length_FracPart - 1; i > -1; --i)
                    {
                        FracPart += CharToIntDigit(*cp) * pow(10, i);
                        ++cp;
                    }
                }

                printf("Frac part %f\n", FracPart);
                FracPart /= pow(10, Length_FracPart);
                printf("Frac part %f\n", FracPart);

                printf("Int part %f\n", IntegerPart);
                float FinalNum = 0;
                if (Minus)
                    FinalNum = IntegerPart - FracPart;
                else
                    FinalNum = IntegerPart + FracPart;


                printf("Final Num %f\n", FinalNum);






                TargetLineNum = CurrLineNum;
                break;
            }

         }

         if (TargetLineNum >= 0) break;

         ++CurrLineNum;
    }



    //printf("%s\n", line[TargetLineNum]);

    printf("\n");
    //printf("All good\n");


}


