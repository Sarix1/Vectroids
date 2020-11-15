#include "my_math.h"

#include <stdlib.h>

float randomFloat(float min, float max)
{
    return min + ((float)rand() / (float)RAND_MAX) * (max-min);
}

void setColor(uint8_t target[], int color[])
{
    for (int i = 0; i < 4; i++)
        target[i] = (int)(color[i]);
}

void addToColor(uint8_t target[], int color[])
{
    int tempColor[4];

    for (int i = 0; i < 4; i++)
    {
        tempColor[i] = (int)(target[i]) + color[i];

        if (tempColor[i] < 0)
            target[i] = 0;
        else if (tempColor[i] > 255)
            target[i] = 255;
        else
            target[i] = (uint8_t)(tempColor[i]);
    }
}


uint32_t randomColor()
{
    union Color
    {
        uint8_t values[4];
        uint32_t bytes;
    } color;

    for (int i = 0; i < 4; i++)
        color.values[i] = rand() % 255;

    return color.bytes;
}
