#ifndef SHIP
#define SHIP

typedef struct _shot {
    int active;
    float pos[2];
    float v[2];
    float a[2];
    float ang;
    float mass;
    float power;
} shot;

typedef struct _nave {
    float pos[2];
    float v[2];
    float a[2];
    float ang; //angulo
    float rotate;
    float truster;
    float mass;
    int amno;
    shot *missil[5];
} nave;

typedef struct _planet {
    float ang;
    float mass;
    float pos[2];
    float v[2];
    float a[2];
} planet;


void drawShip (nave *s);

nave *spawShip (float x, float y, float M);

void updateShip (planet *p, nave *s, float dt);

void drawShot (shot *t);

shot *spawShot (nave *ship);

void updateShot (planet *p, shot *t, float dt);

#endif
