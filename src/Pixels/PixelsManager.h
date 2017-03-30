/*
 *  PixelsManager.h
 *  Video Pixels
 *
 *  Created by Imanol Gomez on 30/03/17.
 *
 */


#pragma once

#include "Manager.h"
#include "ImageVisual.h"
#include "ofxScrollView.h"

//========================== class DressManager ==============================
//============================================================================
/** \class PixelsManager PixelsManager.h
 *	\brief Class managing the pixels visuals
 *	\details it creates and updates the pixels visuals
 */


class PixelsManager: public Manager
{
    
public:
    
    //! Constructor
    PixelsManager();
    
    //! Destructor
    ~PixelsManager();
    
    //! Setup the Halo Manager
    void setup();
    
    //! Update the Halo Manager
    void update();
    
    //! Draw the Halo Manager
    void draw();
    
    float getWidth() const {return m_costumeImage->getOriginalWidth();}
    
    float getHeight() const {return m_costumeImage->getOriginalHeight();}
    
    const ofRectangle& getWindowRect()  {return m_scrollView.getWindowRect();}
    
    void pressedAlt(bool isAltPressed) {m_isAltPressed = isAltPressed;}
    
    void pressedBackSpace();
    
    void pressedMouse(ofMouseEventArgs &e);
    
    void toggleShowChannels();
    
private:
    
    void setupImages();
    
    void setupBlur();
    
    void setupScrollView();
    
    void drawCostumeLeds();
    
    
    ofPtr<ImageVisual>  m_costumeImage;
    
    ofxScrollView       m_scrollView;
    
    bool                m_isAltPressed;
    bool                m_showChannels;
    
};



