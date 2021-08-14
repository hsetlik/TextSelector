/*
  ==============================================================================

    DataStructures.cpp
    Created: 13 Aug 2021 4:59:58pm
    Author:  Hayden Setlik

  ==============================================================================
*/

#include "DataStructures.h"

PhrasePair::PhrasePair(std::string n, std::string t) :
nativeFull(n),
targetFull(n)
{
    auto exp = std::regex("\\w+");
    nativeWords = stdu::matchesAsVector(nativeFull, exp);
    targetWords = stdu::matchesAsVector(targetFull, exp);
}
