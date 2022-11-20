#ifndef CALCS_H
#define CALCS_H

#include <math.h>
#include <QRandomGenerator>

class calcs
{
public:
    calcs();

    float calcAcc(float weaponAccuracy, float tekDef, bool isAccurate, bool inqBonus, bool isEnraged);
    float calcMax(int weaponStr, bool isAggressive, bool inqBonus);
    float hit(float max, float acc);

    //defender is included in base so scythe stats need to be lowered accordingly
    float baseMeleeStr = 57;
    float scytheMeleeStr = 67;
    float maceMeleestr = 89;
    float hammerMeleestr = 85;

    float baseAcc = 96;
    float scytheMeleeAcc = 2;
    float maceMeleeAcc = 95;
    float hammerMeleeAcc = 95;

private:
    float str = 99;
    float strBoost = 19;
    float prayerBonus = 1.23;
};

#endif // CALCS_H
