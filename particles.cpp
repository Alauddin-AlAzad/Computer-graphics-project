#include "platform.h"
#include "globals.h"

void createBlast(int sx, int sy, int tx, int ty) {
    int i, mx=(sx+tx)/2, my=(sy+ty)/2;
    showCollisionLine = 1;
    lineX1=sx; lineY1=sy; lineX2=tx; lineY2=ty;

    if(shockwaveCount < 20) {
        shockwaves[shockwaveCount].x = mx;
        shockwaves[shockwaveCount].y = my;
        shockwaves[shockwaveCount].radius = 10;
        shockwaves[shockwaveCount].life = 35;
        shockwaveCount++;
    }

    for(i=0; i<40 && particleCount<300; i++) {
        float a = randFloat(0, 2*PI);
        float s = randFloat(1.5f, 4.5f);
        particles[particleCount].x = mx;
        particles[particleCount].y = my;
        particles[particleCount].vx = cos(a)*s;
        particles[particleCount].vy = sin(a)*s;
        particles[particleCount].life = 100;
        particles[particleCount].r = randInt(2,4);
        particleCount++;
    }
}

void drawShockwaves() {
    int i;
    for(i=0; i<shockwaveCount; i++) {
        float fade = shockwaves[i].life / 35.0f; 
        glColor3f(1.0f * fade, 0.7f * fade, 0.2f * fade); 

        for(int w=0; w<4; w++) {
            midpointCircle(shockwaves[i].x, shockwaves[i].y, shockwaves[i].radius + w);
        }
    }
}

void drawParticles() {
    int i;
    for(i=0; i<particleCount; i++) {
        if(particles[i].life > 0) {
            float fade = particles[i].life / 100.0f;

            float r = 1.0f * fade;
            float g = (fade > 0.5f) ? (fade-0.5f)*2.0f : 0.0f;
            float b = (fade > 0.8f) ? (fade-0.8f)*5.0f : 0.0f;
            glColor3f(r, g, b);

            drawFilledCircleMidpoint((int)particles[i].x, (int)particles[i].y, particles[i].r);
        }
    }
}

void updateShockwaves() {
    int i, n=0;
    for(i=0; i<shockwaveCount; i++) {
        shockwaves[i].radius += 3;
        shockwaves[i].life -= 1;
        if(shockwaves[i].life > 0) shockwaves[n++] = shockwaves[i];
    }
    shockwaveCount = n;
    if(shockwaveCount == 0) showCollisionLine = 0;
}

void updateParticles() {
    int i, n=0;
    for(i=0; i<particleCount; i++) {
        if(particles[i].life <= 0) continue;
        particles[i].x += particles[i].vx;
        particles[i].y += particles[i].vy;
        particles[i].vy += 0.08f;
        particles[i].vx *= 0.99f;
        particles[i].life -= 2;
        if(particles[i].life > 0 && particles[i].y <= HEIGHT+50)
            particles[n++] = particles[i];
    }
    particleCount = n;
}

