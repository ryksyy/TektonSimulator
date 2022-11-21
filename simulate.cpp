#include "simulate.h"

simulate::simulate()
{

}

void simulate::runSimulation(int times)
{
    int tekCompleted = 0;
    int tekFailed = 0;

    preCalcAcc(false);

    for(int i = 0; i < times; i++){
        currentTekDef = tekDef;
        currentTekHP = tektonHp;

        lowerDefence(usingVuln);

        firstRotation(firstAnvil5t, firstAnvil4t);
        if(tektonHp <= 0)
            tekCompleted++;

        defRegen();
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

//------------------------------- ROTATIONS -------------------------------

void simulate::firstRotation(int fiveTick, int fourTick)
{
    //hits
    for(int i = 0; i<fourTick; i++){
        tektonHp -= hit4t(calc->calcMax(calc->fourTickStr,true,true),calc->calcAcc(calc->fourTickAcc,tekDef,false,true, false));
    }

    for(int i = 0; i<fiveTick; i++){
        tektonHp -= hit5t(calc->calcMax(calc->fiveTickStr,true,true), calc->calcAcc(calc->fiveTickAcc,tekDef,false,true,false), true, false);
    }
}

void simulate::secondRotation(bool closeLure)
{
    //enraged hits
    //hits
}

void simulate::lowerDefence(bool usingVuln)
{
    if(usingVuln){
        if(hitVuln(0.62)){
            tekDef *= 0.9;
        }
    }

    //hammers, def reduction is done in hitHammer
}

void simulate::defRegen()
{
    //in game Tekton goes back to the anvil and stays there for a minimum of 3 cycles and a
    //maximum of 6, as the simulation sample size will be very large
    //this does not need to be accurately modeled and instead of modeling the mechanic I can use the
    //average hp and defense tekton regenerates and add that average directly to Tektons stats
    //this simplifies code and slightly improves run time, realizing this now I dont think this really needs
    //its own function but its staying as having it makes the main runSimulation function look a lot nicer
    currentTekHP += 28;
    currentTekDef += 72;

}

//used to calculate the accuracy % before running  the simulation to avoid running the same
//function thousands of times during the actual simulation
void simulate::preCalcAcc(bool usingFang)
{
    currentTekDef = tekDef;
    currentTekHP = tektonHp;
    //----PRE-ANVIL-----
    //no vuln + 0 hammer
    //no vuln + 1 hammer
    //no vuln + 2 hammer
    //vuln + 0 hammer
    //vuln + 1 hammer
    //vuln + 2 hammer
    for(int i = 0; i < 6; i++){
        fourTickAcc[0][i] = calc->calcAcc(calc->fourTickAcc,currentTekDef,false,true,false);
        fiveTickAcc[0][i] = calc->calcAcc(calc->fiveTickAcc, currentTekDef,false,true,false);

        switch (i) {
        case 0: //lower def by one hit and one missed hammer
            currentTekDef = tekDef*0.7*0.95; ceil(currentTekDef);
            break;
        case 1: //lower def by two hit hammers
            currentTekDef = tekDef*0.7*0.7; ceil(currentTekDef);
            break;
        case 2: //lower def by vuln and no h
            currentTekDef = tekDef*0.9*0.95*0.95; ceil(currentTekDef);
            break;
        case 3: //lower def by vuln and 1h
            currentTekDef = tekDef*0.9*0.7*0.95; ceil(currentTekDef);
            break;
        case 4: //lower def by vuln and 2h
            currentTekDef = tekDef*0.9*0.7*0.7; ceil(currentTekDef);
            break;
        }
    }

    currentTekDef = tekDef;
    currentTekHP = tektonHp;

    //----POST-ANVIL----
    //no vuln + 0 hammer
    //no vuln + 1 hammer
    //no vuln + 2 hammer
    //vuln + 0 hammer
    //vuln + 1 hammer
    //vuln + 2 hammer
    for(int i = 0; i < 6; i++){
        fourTickAcc[1][i] = calc->calcAcc(calc->fourTickAcc,currentTekDef,false,true,false);
        fiveTickAcc[1][i] = calc->calcAcc(calc->fiveTickAcc, currentTekDef,false,true,false);

        switch (i) {
        case 0: //lower def by one hit and one missed hammer
            currentTekDef = tekDef*0.7*0.95+72; ceil(currentTekDef);
            break;
        case 1: //lower def by two hit hammers
            currentTekDef = tekDef*0.7*0.7+72; ceil(currentTekDef);
            break;
        case 2: //lower def by vuln and no h
            currentTekDef = tekDef; ceil(currentTekDef); //no math here as if you run tekton with only a vuln hit it will regen to full on average
            break;
        case 3: //lower def by vuln and 1h
            currentTekDef = tekDef*0.9*0.7*0.95+72; ceil(currentTekDef);
            break;
        case 4: //lower def by vuln and 2h
            currentTekDef = tekDef*0.9*0.7*0.7+72; ceil(currentTekDef);
            break;
        }
    }

    currentTekDef = tekDef;
    currentTekHP = tektonHp;

    //----POST-ANVIL ENRAGE----
    //no vuln + 0 hammer
    //no vuln + 1 hammer
    //no vuln + 2 hammer
    //vuln + 0 hammer
    //vuln + 1 hammer
    //vuln + 2 hammer
    for(int i = 0; i < 6; i++){
        fourTickAcc[2][i] = calc->calcAcc(calc->fourTickAcc,currentTekDef,false,true,true);
        fiveTickAcc[2][i] = calc->calcAcc(calc->fiveTickAcc, currentTekDef,false,true,true);

        switch (i) {
        case 0: //lower def by one hit and one missed hammer
            currentTekDef = tekDef*0.7*0.95+72; ceil(currentTekDef);
            break;
        case 1: //lower def by two hit hammers
            currentTekDef = tekDef*0.7*0.7+72; ceil(currentTekDef);
            break;
        case 2: //lower def by vuln and no h
            currentTekDef = tekDef; ceil(currentTekDef); //no math here as if you run tekton with only a vuln hit it will regen to full on average
            break;
        case 3: //lower def by vuln and 1h
            currentTekDef = tekDef*0.9*0.7*0.95+72; ceil(currentTekDef);
            break;
        case 4: //lower def by vuln and 2h
            currentTekDef = tekDef*0.9*0.7*0.7+72; ceil(currentTekDef);
            break;
        }
    }

    currentTekDef = tekDef;
    currentTekHP = tektonHp;

    if(usingFang){
        //fang calcs are a special case and will be added later
    }
}

//------------------------------- HITS -------------------------------

float simulate::hit5t(float maxHit, float accuracy, bool usingScythe, bool usingFang)
{
    if(usingScythe){
        //roll hits 3 times
    }
    if(usingFang){
        //special fang calc
    }
    if(!usingFang && !usingScythe){
        //basic hit (currently pointless as there is not anyother 5tick weapon worth using)
    }
}

float simulate::hit4t(float maxHit, float accuracy)
{

}

float simulate::hitHammer(float maxHit, float accuracy)
{

}

bool simulate::hitVuln(float accuracy)
{

}


