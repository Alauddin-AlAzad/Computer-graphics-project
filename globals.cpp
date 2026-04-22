#include "platform.h"
#include "globals.h"
BgStar bgStars[140];
OrbitPlanet planets[5];
Particle particles[300];
Shockwave shockwaves[20];
Spaceship ship;
Asteroid asteroids[5];
Bullet bullets[20];
int particleCount = 0;
int shockwaveCount = 0;
int bulletCount = 0;
int sunX = WIDTH / 2;
int sunY = HEIGHT / 2 + 40;
int sunR = 60;
int showCollisionLine = 0;
int lineX1=0, lineY1=0, lineX2=0, lineY2=0;
