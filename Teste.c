#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h> 
#include <math.h>
#include <time.h>
#include "ship.h"
#include "phisics.h"


float M = 500000;
float delta = 0.06;
nave *s;
planet *p;

planet *spawPlanet(float x, float y, float mass) {
    planet *p;
    p = mallocc (sizeof(planet));
    p->pos[0] = x, p->pos[1] = y;
    p->mass = mass;
    p->v[0] = 0,  p->v[1] = 0;
    p->a[0] = 0,  p->a[1] = 0;
    return p;
}

void drawPlanet (planet *p) {
    glPushMatrix();
    glTranslatef (p->pos[0], p->pos[1], 0);
    glColor3f(1,0.8,0);
    glutSolidSphere(0.2,40,40);
    glPopMatrix();
    
}

void updatePlanet (planet *p, nave *s, float dt) {
    p->ang = atan2 (s->pos[1] - p->pos[1], s->pos[0] - p->pos[0]);
    float Fgr = gravit (p->pos, s->pos, p->mass, s->mass);
    float Fgx = (Fgr * cos (p->ang));
    float Fgy = (Fgr * sin (p->ang));
    p->a[0] = (-Fgx)/p->mass;
    p->a[1] = (-Fgy)/p->mass;

    p->v[0] += p->a[0] * dt;
    p->v[1] += p->a[1] * dt;

    p->pos[0] += p->v[0] * dt + p->a[0] * pow(dt, 2)/2;
    p->pos[1] += p->v[1] * dt + p->a[1] * pow(dt, 2)/2;
    
    printf(" x = %f, y = %f, vx = %f, vy = %f, ang %f\n", p->pos[0], p->pos[1], p->v[0], p->v[1], to_deg(p->ang));
}

void display() {
    int i;
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        
    glClearColor(0,0,1,0);

    drawShip(s);
    
    drawPlanet(p);
    
    if(s->amno > 1)
	for(i = 1; i < s->amno; i++) {
	    printf("%d\n",s->amno);
	    drawShot(s->missil[i]);
	    updateShot(p, s->missil[i], delta);
	}
    
    updateShip (p, s, delta);
    updatePlanet (p, s, delta);
    
    glutSwapBuffers();

   
}

void keyPressed (int key, int x, int y){

    if(key == GLUT_KEY_UP) 
	s->truster += 0.001;
    
    if(key == GLUT_KEY_DOWN) 
	s->truster -=  0.001;

    if(key == GLUT_KEY_LEFT)
        s->rotate += 5;
        
    if(key == GLUT_KEY_RIGHT)
        s->rotate -= 5;
}

void Teclado(unsigned char key, int x, int y){
    if(key == 27) exit(0); // O Programa Fecha Caso o Esc seja apertado ... 

    if((char)key == ' '){
	if(s->truster > 0) s->truster -= 0.0001;
	else s->truster += 0.0001; 
    }
    
    if((char)key == 'm'){
	if(s->amno <= 4){
	    s->missil[s->amno] = spawShot(s);
	    s->amno++;
	}
    }

}

int main (int argc, char **argv) {

    s = spawShip (0.5, 0, M);

    p = spawPlanet(0, 0, M);

    glutInit (&argc, argv);

    glutInitDisplayMode (GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);

    glutInitWindowSize (700,700);
    
    glutCreateWindow ("Teste");

    glutDisplayFunc (display);

    glutIdleFunc(display);

    glutKeyboardFunc(Teclado);
    
    glutSpecialFunc(keyPressed);

    glutMainLoop();
}
