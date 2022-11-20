#include "simulate.h"

simulate::simulate()
{

}

void simulate::runSimulation(int times)
{
    int tekCompleted = 0;
    int tekFailed = 0;

    for(int i = 0; i < times; i++){
        tekDef = 246;
        tektonHp = 450;

        firstRotation(firstAnvil5t, firstAnvil4t, usingVuln);
        if(tektonHp <= 0)
            tekCompleted++;

        defRegen(tekDef);
        secondRotation(closeLure);
        if(tektonHp <= 0){
            tekCompleted++;
        }else{
            tekFailed++;
        }

    }
    float rate = (float)tekCompleted / ((float)tekCompleted + (float)tekFailed);
    rate = rate*100;


    emit sendData("Sim ran " + QString::number(times)  + " times. " + "1 anvil rate: " + QString::number(rate, 'f', 2));
}

void simulate::setGear(float gearStr, float gearAcc, bool inqBonus)
{
    emit sendData(QString::number(gearStr) + QString::number(gearAcc) +inqBonus);
}

void simulate::firstRotation(int fiveTick, int fourTick, bool usingVuln)
{
    //vuln
    if(usingVuln){
        if(hitVuln(0.62)){
            tekDef *= 0.9;
        }
    }

    //hammers, def reduction is done in hitHammer
    tektonHp -= hitHammer();
    tektonHp -= hitHammer();

    //hits
    for(int i = 0; i<fourTick; i++){
        tektonHp -= hitMace(calc->calcMax(calc->maceMeleestr,true,true),calc->calcAcc(calc->maceMeleeAcc,tekDef,false,true, false));
    }

    for(int i = 0; i<fiveTick; i++){
        tektonHp -= hitScythe(calc->calcMax(calc->scytheMeleeStr,true,true), calc->calcAcc(calc->scytheMeleeAcc,tekDef,false,true,false));
    }
}

void simulate::secondRotation(bool closeLure)
{
    //enraged hits
    //hits
}

float simulate::defRegen(float tekDef)
{

}

//hit methods, returns hit amount (damage)

float simulate::hitScythe(float maxHit, float accuracy)
{

}

float simulate::hitMace(float maxHit, float accuracy)
{

}

float simulate::hitHammer(float maxHit, float accuracy)
{

}

bool simulate::hitVuln(float accuracy)
{

}


