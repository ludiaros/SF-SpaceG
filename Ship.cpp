#include "Ship.hpp"

Ship::Ship():
    t_crono(),
    control(false),
    drawable(true),
    alive(true),
    start(false),
    dx(0),
    dy(0),
    vact(0.0),
    vmin(0.0),
    vmax(20.0),
    vjmp(250.0),
    accelup(0.25),
    acceldn(0.05),
    accelin(0.01),
    mangle(45),
    vangle(45),
    turnf(3.50),
    turns(0.50),
    dmgact(0),
    dmgmax(100),
    crashdmg(1.0),
    shieldmax(100),
    shieldreg(0.1),
    time(0)
{

    setTexture(*ResourceManager::getTexture("ship"));

    setOrigin(getLocalBounds().width/2, getLocalBounds().height/2);

    setPosition(MAP_W/2, MAP_H/2);
}

void Ship::update(WorldManager& world, float delta) {

    if (control) {
    }
    else { //Controlada por el jugador (Teclado + Mouse)

        dx = -vact * cos((90 + vangle) * (PI / 180));
        dx = dx * delta;

        dy = -vact * sin((90 + vangle) * (PI / 180));
        dy = dy * delta;

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

void Ship::accelUp(float delta) {

    if (!start) {
        start = true;
        t_crono.restart();
    }

    mangle = vangle;
    if (vact + (accelup * delta) <= vmax) { vact += (accelup * delta); }
    else { vact = vmax; }
}

void Ship::accelDn(float delta) {

    if (vact - (acceldn * delta) >= vmin) { vact -= (acceldn * delta); }
    else { vact = vmin; }
}

void Ship::accelIn(float delta) {

    if (vact - (accelin * delta) >= vmin) { vact -= (accelin * delta); }
    else { vact = vmin; }
}

void Ship::takeDamage(float delta, float damage) {

    if (dmgact + (damage * delta) < dmgmax) {
        if (shieldmax > 0) {
            dmgact += ((damage/100) * delta);
            shieldmax -= ((damage/10) * delta);
        }
        else {
            dmgact += (damage * delta);
        }
    }
    else {
        dmgact = dmgmax;
    }

    accelIn(delta);
}

void Ship::turn(float delta, int dir) {

    vangle += (dir * turnf * delta);

    if (vangle > 359) vangle -= 360;
    if (vangle < 0) vangle += 360;
}

int Ship::getTime() {

    if (start) {
        time = static_cast<int>(t_crono.getElapsedTime().asSeconds());
    }

    return time;
}
