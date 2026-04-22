#include "platform.h"
#include "globals.h"

void spawnAsteroid(int idx) {
    asteroids[idx].x = randInt(50, WIDTH-50);
    asteroids[idx].y = HEIGHT + randInt(20,150);
    asteroids[idx].vx = randFloat(-0.8f, 0.8f);
    asteroids[idx].vy = randFloat(-2.0f, -1.0f);
    asteroids[idx].r = randInt(10,20);
    asteroids[idx].active = 1;
}

void drawAsteroids() {
    int i;
    for(i=0; i<5; i++) {
        if(!asteroids[i].active) continue;
        float ax = asteroids[i].x, ay = asteroids[i].y;
        int r = asteroids[i].r;
        for (int dy = -r; dy <= r; dy++) {
            int w = (int)sqrt(r*r - dy*dy);
            for (int dx = -w; dx <= w; dx++) {
                float nx = (float)dx / r;
                float ny = (float)dy / r;
                float nz = sqrt(1.0f - nx*nx - ny*ny);

                float lFactor = nx*0.3f + ny*0.8f + nz*0.5f;
                if (lFactor < 0) lFactor = 0;

                float noise = sin(dx*1.4f + ax) * cos(dy*1.4f + ay);
                float c = 0.3f * (0.2f + 0.8f * lFactor) + noise * 0.04f;

                glColor3f(c+0.1f, c+0.05f, c);  
                drawPixel(ax + dx, ay + dy);
            }
        }
    }
}

void updateAsteroids() {
    int i;
    for(i=0; i<5; i++) {
        if(!asteroids[i].active) continue;
        asteroids[i].x += asteroids[i].vx;
        asteroids[i].y += asteroids[i].vy;
        if(asteroids[i].y < -30) spawnAsteroid(i);
    }
}

void checkAsteroidShip() {
    int i;
    for(i=0; i<5; i++) {
        if(!asteroids[i].active) continue;
        float d = distance2D(ship.x, ship.y, asteroids[i].x, asteroids[i].y);
        if(d < ship.size + asteroids[i].r) {
            createBlast(ship.x, ship.y, (int)asteroids[i].x, (int)asteroids[i].y);
            ship.x = 130; ship.y = 110;
            spawnAsteroid(i);
        }
    }
}

void checkAsteroidPlanet() {
    int i,j;
    for(i=0; i<5; i++) {
        if(!asteroids[i].active) continue;
        for(j=0; j<5; j++) {
            if(!planets[j].alive) continue;
            float px = sunX + cos(planets[j].angle) * planets[j].orbitRadius;
            float py = sunY + sin(planets[j].angle) * planets[j].orbitRadius * 0.55f;
            float d = distance2D(asteroids[i].x, asteroids[i].y, px, py);
            if(d < asteroids[i].r + planets[j].r) {
                createBlast((int)asteroids[i].x, (int)asteroids[i].y, (int)px, (int)py);
                planets[j].alive = 0;
                planets[j].respawnTime = randInt(180, 420); 
                spawnAsteroid(i);
            }
        }
    }
}

