#ifndef GLOBALS_H
#define GLOBALS_H
#include "platform.h"

#define WIDTH 1200
#define HEIGHT 800
#define PI 3.1415926f   // I don't know why we need this but everyone uses it

typedef struct { int x, y, r; } BgStar;
typedef struct {
    float orbitRadius, angle, speed;
    int r;
    float cr, cg, cb;
    int ring;
    int alive;
    int respawnTime;   // this makes planet come back after some time
} OrbitPlanet;
typedef struct {
    float x, y, vx, vy, life;
    int r;
} Particle;
typedef struct {
    int x, y, radius;
    float life;
} Shockwave;
typedef struct {
    int x, y, size;
} Spaceship;
typedef struct {
    float x, y, vx, vy;
    int r, active;
} Asteroid;
typedef struct {
    float x, y, vy;
    int active;
} Bullet;

extern BgStar bgStars[140];
extern OrbitPlanet planets[5];
extern Particle particles[300];
extern Shockwave shockwaves[20];
extern Spaceship ship;
extern Asteroid asteroids[5];
extern Bullet bullets[20];
extern int particleCount;
extern int shockwaveCount;
extern int bulletCount;
extern int sunX;
extern int sunY;
extern int sunR;
extern int showCollisionLine;
extern int lineX1, lineY1, lineX2, lineY2;

// Function Prototypes
float randFloat(float a, float b);
int randInt(int a, int b);
float distance2D(float x1, float y1, float x2, float y2);
void drawText(float x, float y, const char* t);
void drawPixel(int x, int y);
void plotCirclePoints(int xc, int yc, int x, int y);
void midpointCircle(int xc, int yc, int r);
void drawFilledCircleMidpoint(int xc, int yc, int r);
void bresenhamLine(int x1, int y1, int x2, int y2);
void ddaLine(int x1, int y1, int x2, int y2);
void drawEllipse(float cx, float cy, float rx, float ry);
void spawnAsteroid(int idx);
void initScene();
void createBlast(int sx, int sy, int tx, int ty);
void drawBgStars();
void drawSun();
void drawOrbits();
void drawPlanetBody(float x, float y, int r, float cr, float cg, float cb);
void drawSaturnRing(float x, float y, int r);
void drawPlanets();
void drawSpaceship(float x, float y);
void drawAsteroids();
void drawBullets();
void drawShockwaves();
void drawParticles();
void updatePlanets();
void updatePlanetRespawn();
void updateParticles();
void updateShockwaves();
void updateAsteroids();
void updateBullets();
void checkBulletAsteroid();
void checkAsteroidShip();
void checkAsteroidPlanet();
void checkShipPlanet();
void display();
void update(int value);
void keyboard(unsigned char key, int x, int y);
void init();

#endif
