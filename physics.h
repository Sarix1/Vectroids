#define turnSpeed           2.0
#define acceleration        0.03
#define maxVelocity         5.0
#define maxVelocitySquared  maxVelocity * maxVelocity

void calcPlayerPhysics();
void calcParticlePhysics();
void calcProjectilePhysics();
void calcBaseObjectPhysics();
void doPhysics();
