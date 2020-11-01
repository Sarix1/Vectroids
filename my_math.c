#include "my_math.h"

#include <stdlib.h>

float randomFloat(float min, float max)
{
    return min + ((float)rand() / (float)RAND_MAX) * (max - min);
}

void randomColor(uint8_t color[])
{
    for (int i = 0; i < 4; i++)
        color[i] = rand() % 255;
}
