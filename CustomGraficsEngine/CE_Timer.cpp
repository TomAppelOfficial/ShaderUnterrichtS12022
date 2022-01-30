#include "CE_Timer.h"

void CE_Timer::Init()
{
    lastTimestamp = timeGetTime() / 1000.0f;
}

void CE_Timer::Update()
{
    //Berechnet die Deltatime und timeGetTime() noch mal nachschauen
    float actualTimestamp = timeGetTime() / 1000.0f;
    deltaTime = actualTimestamp - lastTimestamp;
    lastTimestamp = actualTimestamp;
}
