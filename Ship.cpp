#include "Ship.hpp"

const double Ship::PI = 4.0*atan(1);

Ship::Ship():
    t_crono(),
    control(false),
    drawable(true),
    alive(true),
    start(false),
    dx(0),
    dy(0),
    vact(0.00),
    vmin(0.00),
    vmax(25.00),
    vjmp(250.00),
    accelup(0.25),
    acceldn(0.05),
    accelin(0.01),
    mangle(45),
    vangle(45),
    turnf(2.50),
    turns(0.50),
    dmgact(0),
    dmgmax(100),
    crashdmg(1),
    shieldmax(100),
    shieldreg(0.1),
    time(0)
{

    setTexture(*TextureManager::getTexture(1));

    setOrigin(getLocalBounds().width/2, getLocalBounds().height/2);

    setPosition(MAP_W/2, MAP_H/2);
}

void Ship::update(WorldManager& world) {

    if (control) {
    }
    else { //Controlada por el jugador (Teclado + Mouse)

        dx = -vact * cos((90 + vangle) * (PI / 180));
        dy = -vact * sin((90 + vangle) * (PI / 180));

        if (
            (getPosition().x + dx < 0) ||
            (getPosition().x + dx > MAP_W) ||
            (getPosition().y + dy < 0) ||
            (getPosition().y + dy > MAP_H)
        ) {
            //Al chocar con los limites del mapa rebota regresando a este
            if ((getPosition().x + dx < 0) || (getPosition().x + dx > MAP_W)) {
                mangle = -mangle;
            }
            if ((getPosition().y + dy < 0) || (getPosition().y + dy > MAP_H)) {
                mangle = 180-mangle;
            }

            vangle = mangle;
            dx = -vact * cos((90 + mangle) * (PI / 180));
            dy = -vact * sin((90 + mangle) * (PI / 180));
        }

        move(dx, dy);//Mover la nave
        setRotation(vangle);//Rotar la imagen alineandola al movimiento

        if (shieldmax > 25 && shieldmax < 100) { shieldmax += shieldreg; }

        if (shieldmax < 0) { shieldmax = 0; }
        if (shieldmax > 99) { shieldmax = 100; }
    }
}

void Ship::setControl(bool ctrl) {
    control = ctrl;
}

void Ship::accelUp() {

    if (!start) {
        start = true;
        t_crono.restart();
    }

    mangle = vangle;
    if (vact + accelup <= vmax) { vact += accelup; }
    else { vact = vmax; }
}

void Ship::accelDn() {

    if (vact - acceldn >= vmin) { vact -= acceldn; }
    else { vact = vmin; }
}

void Ship::accelIn() {

    if (vact - accelin >= vmin) { vact -= accelin; }
    else { vact = vmin; }
}

void Ship::takeDamage(float damage) {

    if (dmgact + damage < dmgmax) {
        if (shieldmax > 0) {
            dmgact += damage/100;
            shieldmax -= damage/10;
        }
        else {
            dmgact += damage;
        }
    }
    else {
        dmgact = dmgmax;
    }

    accelIn();
}

/*void Ship::reset() {
    if (start) {
        start = false;
        time = (int) (t_crono.getElapsedTime().asMilliseconds()) / 1000.f;
        t_crono.restart();
    }
}*/

void Ship::turn(int dir, bool maxi) {

    if (maxi) vangle += (dir * turnf);
    else vangle += (dir * turns);

    if (vangle > 359) vangle -= 360;
    if (vangle < 0) vangle += 360;
}

float Ship::getTime() {

    if (!start) { return time; }
    return time = (int) (t_crono.getElapsedTime().asMilliseconds()) / 1000.f;
}
