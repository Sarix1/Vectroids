#include <SDL2/SDL_types.h>
#include <math.h>

#define degToRad(degrees) ((degrees) * M_PI / 180.0)
#define radToDeg(radians) ((radians) * 180.0 / M_PI)

float randomFloat(float min, float max);
void randomColor(uint8_t color[]);
