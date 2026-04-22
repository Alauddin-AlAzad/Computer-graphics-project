#include "platform.h"
#include "globals.h"

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    drawBgStars();
    drawOrbits();
    drawSun();
    drawPlanets();
    drawAsteroids();
    drawBullets();

    drawShockwaves();
    drawParticles();
    drawSpaceship(ship.x, ship.y);

    drawText(20, HEIGHT-30, "W A S D = Move");
    drawText(20, HEIGHT-55, "SPACE = Fire");
    drawText(20, HEIGHT-80, "R = Reset");

    glutSwapBuffers();
}

void update(int value) {
    updatePlanets();
    updatePlanetRespawn();        
    updateParticles();
    updateShockwaves();
    updateAsteroids();
    updateBullets();

    checkBulletAsteroid();
    checkAsteroidShip();
    checkAsteroidPlanet();
    checkShipPlanet();

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

void keyboard(unsigned char key, int x, int y) {
    int step = 14;
    if(key=='w' || key=='W') ship.y += step;
    if(key=='s' || key=='S') ship.y -= step;
    if(key=='a' || key=='A') ship.x -= step;
    if(key=='d' || key=='D') ship.x += step;
    if(key=='r' || key=='R') initScene();

    if(key==' ') {
        int k;
        for(k=0; k<20; k++) {
            if(!bullets[k].active) {
                bullets[k].x = ship.x;
                bullets[k].y = ship.y + 22;
                bullets[k].vy = 14.0f;
                bullets[k].active = 1;
                if(k >= bulletCount) bulletCount = k+1;
                break;
            }
        }
    }

    if(ship.x < 20) ship.x = 20;
    if(ship.x > WIDTH-20) ship.x = WIDTH-20;
    if(ship.y < 20) ship.y = 20;
    if(ship.y > HEIGHT-20) ship.y = HEIGHT-20;

    glutPostRedisplay();
}

void init() {
    glClearColor(0,0,0,1);
    glPointSize(2.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WIDTH, 0, HEIGHT);
}

int main(int argc, char** argv) {
    srand((unsigned int)time(0));   

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Solar Blast - PRO EDITION");

    init();
    initScene();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(16, update, 0);

    glutMainLoop();
    return 0;

}
