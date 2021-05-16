/*
  ==============================================================================

    AR.cpp
    Created: 10 Apr 2021 3:03:12pm
    Author:  Zeno  Loesch

  ==============================================================================
*/

#include "AR.h"
//
//  ADSR.cpp
//
//  Created by Nigel Redmon on 12/18/12.
//  EarLevel Engineering: earlevel.com
//  Copyright 2012 Nigel Redmon
//
//  For a complete explanation of the ADSR envelope generator and code,
//  read the series of articles by the author, starting here:
//  http://www.earlevel.com/main/2013/06/01/envelope-generators/
//
//  License:
//
//  This source code is provided as is, without warranty.
//  You may copy and distribute verbatim copies of this document.
//  You may modify and use this source code to create binary code for your own purposes, free or commercial.
//
//  1.01  2016-01-02  njr   added calcCoef to SetTargetRatio functions that were in the ADSR widget but missing in this code
//  1.02  2017-01-04  njr   in calcCoef, checked for rate 0, to support non-IEEE compliant compilers
//  1.03  2020-04-08  njr   changed float to double; large target ratio and rate resulted in exp returning 1 in calcCoef
//

#include <math.h>


AR::AR(void) {
    reset();
    setAttackRate(0);
    setReleaseRate(0);
    setTargetRatioA(0.5);
    setTargetRatioDR(0.5);
}

AR::~AR(void) {
}

void AR::setAttackRate(double rate) {
    attackRate = rate;
    attackCoef = calcCoef(rate, targetRatioA);
    attackBase = (1.0 + targetRatioA) * (1.0 - attackCoef);
}

void AR::setReleaseRate(double rate) {
    releaseRate = rate;
    releaseCoef = calcCoef(rate, targetRatioA);
    releaseBase = -targetRatioA * (1.0 - releaseCoef);
}

double AR::calcCoef(double rate, double targetRatio) {
    return (rate <= 0) ? 0.0 : exp(-log((1.0 + targetRatio) / targetRatio) / rate);
}



void AR::setTargetRatioA(double targetRatio) {
    if (targetRatio < 0.000000001)
        targetRatio = 0.000000001;  // -180 dB
    targetRatioA = targetRatio;
    attackCoef = calcCoef(attackRate, targetRatioA);
    attackBase = (1.0 + targetRatioA) * (1.0 - attackCoef);
}
/*
void AR::setTargetRatioDR(double targetRatio) {
    if (targetRatio < 0.000000001)
        targetRatio = 0.000000001;  // -180 dB
    targetRatioA = targetRatio;
    releaseCoef = calcCoef(releaseRate, targetRatioA);
    releaseBase = -targetRatioA * (1.0 - releaseCoef);
}
*/
void AR::setTargetRatioDR(double targetRatio) {
    if (targetRatio < 0.000000001)
        targetRatio = 0.000000001;  // -180 dB
    targetRatioDR = targetRatio;
    attackCoef = calcCoef(attackRate, targetRatioDR);
    releaseCoef = calcCoef(releaseRate, targetRatioDR);
    attackBase = (1 - targetRatioDR) * (1.0 - attackCoef);
    releaseBase = -targetRatioDR * (1.0 - releaseCoef);
}
