/*
  ==============================================================================

    SelectableWord.cpp
    Created: 13 Aug 2021 6:52:48am
    Author:  Hayden Setlik

  ==============================================================================
*/

#include "SelectableWord.h"

Word::Word(std::string content) : text(content), mouseIsOver(false), linkedWord(nullptr)
{
    
}

void Word::resized()
{
    
}

void Word::paint(juce::Graphics &g)
{
    if(mouseIsOver)
    {
        g.fillAll(juce::Colours::lightblue);
    }
    else if (linkedWord != nullptr)
    {
        g.fillAll(juce::Colours::lightgrey);
    }
    g.setColour(juce::Colours::white);
    auto height = (float)getHeight();
    g.setFont(juce::Font(height));
    g.drawFittedText(juce::String(text), getLocalBounds(), juce::Justification::centred, 1);
}

int Word::lengthForFontHeight(int height)
{
    auto font = juce::Font((float)height);
    return font.getStringWidth(juce::String(text));
}

void Word::mouseEnter(const juce::MouseEvent &e)
{
    mouseIsOver = true;
    repaint();
}
void Word::mouseExit(const juce::MouseEvent &e)
{
    mouseIsOver = false;
    repaint();
}
//==============================================================================

Phrase::Phrase(std::string fullPhrase)
{
    auto exp = std::regex("\\w+");
    auto vWords = stdu::matchesAsVector(fullPhrase, exp);
    for(auto w : vWords)
    {
        addAndMakeVisible(words.add(new Word(w)));
    }
    setRepaintsOnMouseActivity(true);
}

void Phrase::resized()
{
    auto height = getHeight();
    int currentX = 0;
    for (auto word : words)
    {
        auto wLength = word->lengthForFontHeight(height);
        word->setBounds(currentX, 0, wLength, height);
        currentX += wLength + SPACE_WIDTH;
    }
}

int Phrase::getPhraseWidth(int height)
{
    int currentX = 0;
    for (auto word : words)
    {
        currentX += word->lengthForFontHeight(height) + SPACE_WIDTH;
    }
    return currentX;
}
//==============================================================================
PhraseScreen::PhraseScreen(TextEntryScreen* screen) :
linkedScreen(screen),
nativePhrase(nullptr),
targetPhrase(nullptr)
{
    updatePhrases();
    backButton.setButtonText("Back");
    addAndMakeVisible(&backButton);
}

void PhraseScreen::updatePhrases()
{
    auto phrases = linkedScreen->getEntry();
    nativePhrase.reset(new Phrase(phrases.first));
    targetPhrase.reset(new Phrase(phrases.second));
    
    addAndMakeVisible(&*nativePhrase);
    addAndMakeVisible(&*targetPhrase);
    
    resized();
}

void PhraseScreen::visibilityChanged()
{
    if(isVisible())
        updatePhrases();
}

void PhraseScreen::resized()
{
    auto dX = getHeight() / 16;
    auto nLength = nativePhrase->getPhraseWidth(dX);
    auto tLength = targetPhrase->getPhraseWidth(dX);
    
    targetPhrase->setBounds(2 * dX, 2 * dX, tLength, dX);
    nativePhrase->setBounds(2 * dX, 6 * dX, nLength, dX);
    backButton.setBounds(2 * dX, 10 * dX, 3 * dX, 2 * dX);
}

