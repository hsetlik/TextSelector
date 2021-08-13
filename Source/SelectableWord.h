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
    void linkToWord(Word* link)
    {
        if(link == linkedWord)
            return;
        linkedWord = link;
        linkedWord->linkToWord(this);
        repaint();
    }
    void severLink()
    {
        if(linkedWord == nullptr)
            return;
        auto prevLink = linkedWord;
        linkedWord = nullptr;
        prevLink->severLink();
        repaint();
    }
protected:
    Word* linkedWord;
};

class TargetWord : public Word
{
public:
    TargetWord(std::string content) : Word(content)
    {
        //setInterceptsMouseClicks(true, true);
    }
    void mouseDown(const juce::MouseEvent &e) override
    {
        if(e.mods.isRightButtonDown())
            severLink();
        juce::DragAndDropContainer::findParentDragContainerFor(this)->startDragging(juce::String(text), this);
    }
};

class NativeWord : public Word, public juce::DragAndDropTarget
{
public:
    NativeWord(std::string content) : Word(content)
    {
    }
    void itemDropped(const juce::DragAndDropTarget::SourceDetails &dragSourceDetails) override;
    void itemDragEnter(const juce::DragAndDropTarget::SourceDetails &dragSourceDetails) override{}
    void itemDragExit(const juce::DragAndDropTarget::SourceDetails &dragSourceDetails) override{}
    void itemDragMove(const juce::DragAndDropTarget::SourceDetails &dragSourceDetails) override{}
    bool isInterestedInDragSource(const juce::DragAndDropTarget::SourceDetails &dragSourceDetails) override
    {
        return true;
    }
};
//===================================================================
class Phrase : public juce::Component
{
public:
    Phrase(std::string fullString);
    int getPhraseWidth(int height);
    void resized() override;
    
protected:
    juce::OwnedArray<Word> words;
};

class TargetPhrase : public Phrase
{
public:
    TargetPhrase(std::string content) : Phrase(content)
    {
        words.clear(true);
        auto exp = std::regex("\\w+");
        auto vWords = stdu::matchesAsVector(content, exp);
        for(auto w : vWords)
        {
            addAndMakeVisible(words.add(new TargetWord(w)));
        }
    }
};

class NativePhrase : public Phrase
{
public:
    NativePhrase(std::string content) : Phrase(content)
    {
        words.clear(true);
        auto exp = std::regex("\\w+");
        auto vWords = stdu::matchesAsVector(content, exp);
        for(auto w : vWords)
        {
            addAndMakeVisible(words.add(new NativeWord(w)));
        }
    }
};


//=================================================
class PhraseScreen :
public juce::Component,
public juce::DragAndDropContainer
{
public:
    PhraseScreen(TextEntryScreen* screen);
    TextEntryScreen* const linkedScreen;
    void resized() override;
    void updatePhrases();
    void visibilityChanged() override;
    
    std::unique_ptr<NativePhrase> nativePhrase;
    std::unique_ptr<TargetPhrase> targetPhrase;
    juce::TextButton backButton;
   
};

