#include "platform.h"
#include "globals.h"

void drawBullets() {
    int i;
    for(i=0; i<bulletCount; i++) {
        if(!bullets[i].active) continue;

        for (int dy=-6; dy<=6; dy++) {
            float intensity = 1.0f - abs(dy)/6.0f;
            glColor3f(0.0f, 1.0f * intensity, 1.0f);
            bresenhamLine((int)bullets[i].x-2, (int)bullets[i].y+dy, 
                          (int)bullets[i].x+2, (int)bullets[i].y+dy);
        }
    }
}

void updateBullets() {
    int i;
    for(i=0; i<bulletCount; i++) {
        if(!bullets[i].active) continue;
        bullets[i].y += bullets[i].vy;
        if(bullets[i].y > HEIGHT+10) bullets[i].active = 0;
    }
}

void checkBulletAsteroid() {
    int i,j;
    for(i=0; i<bulletCount; i++) {
        if(!bullets[i].active) continue;
        for(j=0; j<5; j++) {
            if(!asteroids[j].active) continue;
            float d = distance2D(bullets[i].x, bullets[i].y, asteroids[j].x, asteroids[j].y);
            if(d < asteroids[j].r + 4) {
                createBlast((int)bullets[i].x, (int)bullets[i].y, (int)asteroids[j].x, (int)asteroids[j].y);
                bullets[i].active = 0;

spawnAsteroid(j);
            }
        }
    }
}

