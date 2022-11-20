#ifndef SIMULATE_H
#define SIMULATE_H

#include <math.h>
#include <QRandomGenerator>
#include <QDebug>
#include <QString>
#include "calcs.h"

class simulate : public QObject
{
    Q_OBJECT

public:
    simulate();
    void runSimulation(int times);
    //for different gear setups can manually insert numbers later from gui (TODO)
    void setGear(float gearStr, float gearAcc, bool inqBonus);


private:
    void firstRotation(int fiveTick, int fourTick, bool usingVuln);
    void secondRotation(bool closeLure);
    float defRegen(float tekDef);

    //different hit calcs, todo hit fang
    float hitScythe(float maxHit, float accuracy);
    float hitMace(float maxHit, float accuracy);
    float hitHammer(float maxHit, float accuracy);
    float hitVenge(bool isEnraged);
    bool hitVuln(float accuracy);


    float tektonHp = 450;
    float tekDef = 246;

    int firstAnvil4t = 3;
    int firstAnvil5t = 4;

    bool closeLure = false;
    bool usingVuln = true;

    float maceMax;
    float hammerMax;
    float scytheMax;

    float maceAcc;
    float maceAccEnraged;
    float scytheAcc;
    float hammerAcc;

    calcs *calc = new calcs;

signals:
    void sendData(QString);
};

#endif // SIMULATE_H
