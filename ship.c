#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include "ship.h"
#include "phisics.h"

void drawShip (nave *s){
    glPushMatrix ();
    glTranslatef (s->pos[0], s->pos[1], 0);
    glRotatef(s->rotate, 0,  0, 1);
    glBegin (GL_POLYGON);	
    glColor3f (1, 0, 0);
    glVertex3f (0, -0.05, -1);
    glVertex3f (0, 0.05, -1);
    glVertex3f (0.05, 0, -1);
    glEnd ();
    glPopMatrix ();
}

nave *spawShip (float x, float y, float M){
    nave *ship;
    float ov;
    ship = mallocc (sizeof(ship));
    ship->pos[0] = x, ship->pos[1] = y;
    ov = orbtVel (modulo (ship->pos), M);
    ship->ang = atan (y / x);
    ship->v[0] = sin (ship->ang) * ov,  ship->v[1] = cos (ship->ang) * ov;
    ship->amno = 0;
    ship->rotate = 0;
    return ship;
}

void updateShip (planet *p ,nave *s, float dt) { 
    s->ang = atan2 (s->pos[1] - p->pos[1], s->pos[0] - p->pos[0]);
    s->mass = 200;
    float Fgr = gravit (s->pos, p->pos, p->mass, s->mass);
    float Fgx = (Fgr * cos (s->ang));
    float Fgy = (Fgr * sin (s->ang));
    float tx = s->truster * cos (to_rad(s->rotate));
    float ty = s->truster * sin (to_rad(s->rotate));
    s->a[0] = (-Fgx+tx)/s->mass;
    s->a[1] = (-Fgy+ty)/s->mass;

    s->v[0] += s->a[0] * dt;
    s->v[1] += s->a[1] * dt;

    s->pos[0] += s->v[0] * dt + s->a[0] * pow(dt, 2)/2;
    s->pos[1] += s->v[1] * dt + s->a[1] * pow(dt, 2)/2;

    //printf(" ax = %f, ay = %f, vx = %f, vy = %f, rotate %f, ang %f, amno %d \n", s->a[0], s->a[1], s->v[0], s->v[1], s->rotate, to_deg(s->ang), s->amno);    
}

void drawShot (shot *t) {
    glPushMatrix ();
    glTranslatef (t->pos[0], t->pos[1], 0);
    glColor3f(0.5,0,0.5);
    glutSolidSphere(0.02,30,40);
    glPopMatrix();
    glEnd ();
    glPopMatrix ();
    printf(" ax = %f, ay = %f, vx = %f, vy = %f, ang %f\n", t->a[0], t->a[1], t->v[0], t->v[1], to_deg(t->ang));    
}

shot *spawShot (nave *ship) {
    shot *t;
    t = mallocc(sizeof(shot));
    t->pos[0] = ship->pos[0], t->pos[1] = ship->pos[1];
    t->ang = ship->ang;
    t->v[0] = 0.007 * cos (to_rad(ship->rotate)), t->v[1] = 0.007 * sin (to_rad(ship->rotate));
    t->power = 50;
    t->mass = 10;
    t->active = 1;
    return t;
}

void updateShot (planet *p, shot *t, float dt) { 
    t->ang = atan2 (t->pos[1], t->pos[0]);
    
    float Fgr = gravit (t->pos, p->pos, p->mass, t->mass);
    float Fgx = (Fgr * cos (t->ang));
    float Fgy = (Fgr * sin (t->ang));
    t->a[0] = (-Fgx)/t->mass;
    t->a[1] = (-Fgy)/t->mass;

    t->v[0] += t->a[0] * dt;
    t->v[1] += t->a[1] * dt;

    t->pos[0] += t->v[0] * dt + t->a[0] * pow(dt, 2)/2;
    t->pos[1] += t->v[1] * dt + t->a[1] * pow(dt, 2)/2;
}
