/*
 *  KeyboardManager.cpp
 *  Video Pixels
 *
 *  Created by Imanol Gomez on 30/03/17.
 *
 */

#include "KeyboardManager.h"
#include "AppManager.h"


KeyboardManager::KeyboardManager(): Manager()
{
    //Intentionally left empty
}

KeyboardManager::~KeyboardManager()
{
   ofLogNotice() << "KeyboardManager::destructor";
}


//--------------------------------------------------------------

void KeyboardManager::setup()
{
    if(m_initialized)
        return;
    
    Manager::setup();
    
    ofLogNotice() <<"KeyboardManager::initialized" ;
    this->addListeners();
}

void KeyboardManager::addListeners()
{
    ofRegisterKeyEvents(this); // this will enable the InteractiveVisual class to listen to the key events.
}

void KeyboardManager::keyPressed(ofKeyEventArgs &e)
{
    int key = e.key;
    
    ofLogNotice() <<"KeyboardManager::keyPressed-> " + ofToString(key);
    
  
    if(key == 'g' || key == 'G') {
        AppManager::getInstance().getGuiManager().toggleGui();
    }
    
    if(key == ' ') {
        AppManager::getInstance().getPixelsManager().toggleShowChannels();
        //AppManager::getInstance().toggleDebugMode();
    }
    
    if(key == OF_KEY_ALT) {
        AppManager::getInstance().getPixelsManager().pressedAlt(true);
    }
    
    if(key == OF_KEY_BACKSPACE) {
        AppManager::getInstance().getPixelsManager().pressedBackSpace();
    }
    
}

void KeyboardManager::keyReleased(ofKeyEventArgs &e)
{
    int key = e.key;
    
    ofLogNotice() <<"KeyboardManager::keyReleased-> " + ofToString(key);
    
    if(key == OF_KEY_ALT) {
        AppManager::getInstance().getPixelsManager().pressedAlt(false);
    }
}










