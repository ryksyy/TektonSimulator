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
    void firstRotation(int fiveTick, int fourTick);
    void secondRotation(bool closeLure);
    void lowerDefence(bool usingVuln);
    void defRegen();

    void preCalcAcc(bool usingFang);

    //different hit calcs, todo hit fang
    float hit5t(float maxHit, float accuracy, bool usingScythe, bool usingFang);
    float hit4t(float maxHit, float accuracy);
    float hitHammer(float maxHit, float accuracy);
    float hitVenge(bool isEnraged);
    bool hitVuln(float accuracy);


    float tektonHp = 450;
    float tekDef = 246;
    float currentTekHP;
    float currentTekDef;

    int firstAnvil4t = 3;
    int firstAnvil5t = 4;

    bool closeLure = false;
    bool usingVuln = true;

    float fourTickMax;
    float hammerMax;
    float fiveTickMax;

    //[0][x] will store pre anvil accuracies and [1][x] post anvil, hammer does not need this as
    //hitting with the hammer anywhere but the very start is never done in the game
    //the "column" will have each different possible "defence lowered" case accuracies saved
    //starting with no vuln + hammers 0,1,2 in [0-2] and vuln + hammers 0,1,2 in [3-5]
    //hammer also only needs vuln + hammer 0-1 and no vuln 2-3 as you only hit with it twice at the start of the encounter
    //four and five tick need enrage calcs for post anvil which will be in [2][x]
    float fourTickAcc[3][6];
    float fiveTickAcc[3][6];
    float hammerAcc[4];

    calcs *calc = new calcs;

signals:
    void sendData(QString);
};

#endif // SIMULATE_H
