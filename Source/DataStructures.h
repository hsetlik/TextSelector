/*
  ==============================================================================

    DataStructures.h
    Created: 13 Aug 2021 4:59:58pm
    Author:  Hayden Setlik

  ==============================================================================
*/

#pragma once
#include "StlUtil.h"
enum class CardTypes
{
    NTA,
    Cloze,
    TypeFromAudio,
    FullPhrase
};


//Class to contain all the info for a pair of phrases and all associated cards
class PhrasePair
{
public:
    PhrasePair(std::string n, std::string t);
    const std::string nativeFull;
    const std::string targetFull;
    std::vector<std::string> nativeWords;
    std::vector<std::string> targetWords;
    std::vector<std::pair<std::string, std::string>> ntaPairs; //again in format {native, target}
   //TODO: functions for saving this info to a file and on constructing this class from that file
};
