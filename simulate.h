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
    QString runSimulation(int times);
    //for different gear setups can manually insert numbers later from gui
    void setGear(float gearStr, float gearAcc, bool inqBonus);


private:
    void firstRotation();
    void secondRotation();

    //inq setup gear values
    float gearStr = 49;
    float avernicStr = 8;
    float scytheStr = 75;
    float maceStr = 89;
    float hammerStr = 95;

    //inq setup accuracy values
    float gearAcc = 66;
    float scytheAcc = 30;
    float maceAcc = 95;
    float hammerAcc = 95;
    float avernicAcc = 30;

    float tektonHp = 450;
    float tekDef = 246;

signals:
    void sendData(float);
};

#endif // SIMULATE_H
