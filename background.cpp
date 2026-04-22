#include "platform.h"
#include "globals.h"

void initScene() {
    int i;
    particleCount = 0;
    shockwaveCount = 0;
    bulletCount = 0;
    showCollisionLine = 0;

    ship.x = 130;
    ship.y = 110;
    ship.size = 14;

    for(i=0; i<140; i++) {
        bgStars[i].x = randInt(10, WIDTH-10);
        bgStars[i].y = randInt(10, HEIGHT-10);
        bgStars[i].r = randInt(1,2);
    }

    planets[0].orbitRadius=110; planets[0].angle=0.5f;

planets[0].speed=0.012f;

    planets[0].r=12;
    planets[0].cr=0.75f; planets[0].cg=0.75f; planets[0].cb=0.78f; planets[0].ring=0; planets[0].alive=1;
    planets[1].orbitRadius=165; planets[1].angle=1.7f; planets[1].speed=0.009f; planets[1].r=18;
    planets[1].cr=0.1f; planets[1].cg=0.75f; planets[1].cb=0.85f; planets[1].ring=0; planets[1].alive=1;
    planets[2].orbitRadius=225; planets[2].angle=3.0f; planets[2].speed=0.007f; planets[2].r=16;
    planets[2].cr=1.0f; planets[2].cg=0.35f; planets[2].cb=0.15f; planets[2].ring=0; planets[2].alive=1;
    planets[3].orbitRadius=295; planets[3].angle=5.0f; planets[3].speed=0.005f; planets[3].r=24;
    planets[3].cr=0.92f; planets[3].cg=0.70f; planets[3].cb=0.20f; planets[3].ring=0; planets[3].alive=1;
    planets[4].orbitRadius=350; planets[4].angle=2.4f; planets[4].speed=0.004f; planets[4].r=34;
    planets[4].cr=0.95f; planets[4].cg=0.92f; planets[4].cb=0.75f; planets[4].ring=1; planets[4].alive=1;

    for(i=0; i<5; i++) planets[i].respawnTime = 0;

    for(i=0; i<5; i++) spawnAsteroid(i);
}

void drawBgStars() {
    int i;
    for(i=0; i<140; i++) {
        float twinkle = randFloat(0.4f, 1.0f);
        glColor3f(twinkle, twinkle, twinkle);
        drawPixel(bgStars[i].x, bgStars[i].y);

        if (bgStars[i].r > 1) {
            drawPixel(bgStars[i].x+1, bgStars[i].y);
            drawPixel(bgStars[i].x, bgStars[i].y+1);
            drawPixel(bgStars[i].x+1, bgStars[i].y+1);
        }
    }
}

void drawSun() {

    for (int r = sunR + 40; r > sunR; r-=2) {
        float factor = (sunR + 40 - r) / 40.0f;
        glColor3f(1.0f * factor, 0.4f * factor * factor, 0.0f);
        midpointCircle(sunX, sunY, r);
        midpointCircle(sunX, sunY, r+1); 
    }

    for (int r = sunR; r >= 0; r--) {
        float factor = (float)r / sunR;
        glColor3f(1.0f, 1.0f - factor*0.2f, 1.0f - factor); 
        midpointCircle(sunX, sunY, r);
    }
}

void drawOrbits() {
    int i;
    glColor3f(0.3f,0.3f,0.3f);
    for(i=0; i<5; i++)
        drawEllipse(sunX, sunY, planets[i].orbitRadius, planets[i].orbitRadius*0.55f);
}

