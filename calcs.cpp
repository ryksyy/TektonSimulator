#include "calcs.h"

calcs::calcs()
{

}

float calcs::calcAcc(float weaponAccuracy, float tekDef, bool isAccurate, bool inqBonus, bool isEnraged)
{
    float effAtt = (119)*(1.2);
    effAtt = floor(effAtt);
    effAtt += 8;

    if(isAccurate)
        effAtt += 3;

    float accRoll = effAtt*(baseAcc+weaponAccuracy+64);
    if(inqBonus)
        accRoll = accRoll*1.025;

    accRoll = floor(accRoll);

    float tempDef;

    if(isEnraged){
        tempDef = (tekDef + 9) * (180+64);
    }else{
        tempDef = (tekDef + 9) * (105+64);
    }

    if(accRoll > tempDef){
        tempDef += 2;
        accRoll +=1;
        accRoll = 2*accRoll;
        return 1 - (tempDef/accRoll);
    }else{
        tempDef += 1;
        tempDef = tempDef*2;
        return (accRoll/tempDef);
    }
}

float calcs::calcMax(int weaponStr, bool isAggressive, bool inqBonus)
{
    float effStr = (str+strBoost)*prayerBonus;
    effStr = floor(effStr);
    effStr += 8;

    if(isAggressive)
        effStr += 3;

    float tempMax = (effStr*(baseMeleeStr+weaponStr+64))+320;
    tempMax = tempMax/640;

    if(inqBonus)
        tempMax = tempMax*1.025;

    tempMax = floor(tempMax);

    return tempMax;
}

float calcs::hit(float maxHit, float accuracy)
{
    int tempAcc = (int)(accuracy*100000+1);
    int rngRoll = QRandomGenerator::global()->bounded(100000+1);
    if(rngRoll < tempAcc){
        rngRoll = QRandomGenerator::global()->bounded((int)maxHit+(int)1);
        return (float)rngRoll;
    }else{
        return 0;
    }

}
