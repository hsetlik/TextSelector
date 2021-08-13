/*
  ==============================================================================

    SelectableWord.h
    Created: 13 Aug 2021 6:52:48am
    Author:  Hayden Setlik

  ==============================================================================
*/

#pragma once
#include "TextEntryComponent.h"
#define SPACE_WIDTH 11

class Word : public juce::Component
{
public:
    Word(std::string content);
    const std::string text;
    void resized() override;
    void paint(juce::Graphics& g) override;
    int lengthForFontHeight(int height);
    void mouseEnter(const juce::MouseEvent& e) override;
    void mouseExit(const juce::MouseEvent& e) override;
    bool mouseIsOver;
protected:
    Word* linkedWord;
};

class Phrase : public juce::Component
{
public:
    Phrase(std::string fullString);
    int getPhraseWidth(int height);
    void resized() override;
    
private:
    juce::OwnedArray<Word> words;
};

class PhraseScreen : public juce::Component
{
public:
    PhraseScreen(TextEntryScreen* screen);
    TextEntryScreen* const linkedScreen;
    void resized() override;
    void updatePhrases();
    void visibilityChanged() override;
    
    std::unique_ptr<Phrase> nativePhrase;
    std::unique_ptr<Phrase> targetPhrase;
    juce::TextButton backButton;
   
};

