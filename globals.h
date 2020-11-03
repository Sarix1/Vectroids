#include <SDL2/SDL_types.h>

#define screenWidth     640
#define screenHeight    480
#define fullScreen      0

#define maxVector2      1000
#define maxParticles    1000
#define maxProjectiles  1000
#define maxPolygons     100
#define maxBaseObjects  100

#define RGBA_BLACK      (uint8_t[]){0,   0,   0,   0}
#define RGBA_RED        (uint8_t[]){255, 0,   0,   0}
#define RGBA_GREEN      (uint8_t[]){0,   255, 0,   0}
#define RGBA_BLUE       (uint8_t[]){0,   0,   255, 0}
#define RGBA_YELLOW     (uint8_t[]){255, 255, 0,   0}
#define RGBA_PURPLE     (uint8_t[]){255,  0,  255, 0}

#define shipColor       RGBA_GREEN
#define asteroidColor   RGBA_PURPLE
#define fireColor1      RGBA_YELLOW
#define fireColor2      RGBA_RED

#define shipStartPos    center
#define shipScale       1.2
#define shipRadius      8.0 // multiplied by scale
#define turnSpeed       2.0
#define acceleration    0.03
#define maxVelocity     5.0
#define maxVelSquared   maxVelocity * maxVelocity

#define bulletOffset        10.0 * shipScale
#define bulletVelocity      4.0
#define bulletRange         screenWidth
#define bulletDamage        10.0
#define shootDelay          20
#define explosionMagnitude  5

#define exhaustVelocity     100 * shipScale
#define exhaustVelModifier  5
#define exhaustInheritedVel 0.9
#define exhaustDiffusion    0.5
#define exhaustLife         50
#define exhaustLongitudinal -10 * shipScale
#define exhaustLateral      4   * shipScale

#define asteroidCount       7
#define asteroidRadius      1.2 // multiplied by scale
#define asteroidMinRadius   12.0
#define asteroidMinScale    10.0
#define asteroidMaxScale    30.0
#define asteroidMinVel      0.1
#define asteroidMaxVel      1.5
#define asteroidMaxAngVel   2.0
