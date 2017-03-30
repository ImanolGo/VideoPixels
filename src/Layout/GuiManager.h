/*
 *  GuiManager.h
 *  Video Pixels
 *
 *  Created by Imanol Gomez on 30/03/17.
 *
 */

#pragma once

#include "Manager.h"
#include "ofxGui.h"
//========================== class GuiManager ==============================
//============================================================================
/** \class GuiManager GuiManager.h
 *	\brief Class managing the application´s grapical user interface (GUI)
 *	\details It creates the gui and the callback functions that will be affected
 *    by the gui
 */

class GuiManager: public Manager
{
    static const string GUI_SETTINGS_FILE_NAME;
    static const string GUI_SETTINGS_NAME;
    static const int GUI_WIDTH;
    
public:

    //! Constructor
    GuiManager();

    //! Destructor
    ~GuiManager();

    //! Set-up the gui
    void setup();
    
    //! Draw the gui
    void draw();
    
    void saveGuiValues();
    
    void loadGuiValues();
    
    void toggleGui();
    
    void showGui(bool show){m_showGui=show;}
    
    void onSetVideoMode(bool& value);
    
    void onSetNoiseMode(bool& value);
    
    void onSetAudioMode(bool& value);
    
    int getWidth() {return GUI_WIDTH;}
    
    int getHeight() {return m_gui.getHeight();}
    
    ofPoint  getPosition() {return m_gui.getPosition();}
    
private:
    
    void setupGuiParameters();
    
    void setupModesGui();
    
    void setupLedsGui();
    
    void setupNoiseGui();
    
    void setupImageGui();
    
    void setupVideoGui();
    
    void setupAudioGui();
    
    void setupLayoutGui();
    
    void drawRectangle();

private:
    
    // Fluid GUI
    ofxPanel			m_gui;
    
    ofParameter<float>	m_guiFPS;
    
    
    ofParameterGroup    m_parametersNoise;
    ofParameterGroup    m_parametersLeds;
    ofParameterGroup    m_parametersModes;
    ofParameterGroup    m_parametersImage;
    ofParameterGroup    m_parametersVideo;
    ofParameterGroup    m_parametersAudio;
    ofParameterGroup    m_parametersLayout;
    
    ofxButton           m_nextVideo;
    ofParameter<bool>   m_recordVideoLoops;
    ofParameter<bool>   m_videoTrail;
    
    ofParameter<float>    m_ledsSize;
    
    ofParameter<float>    m_audioLevel;
    ofxButton             m_nextAudio;
    
    ofParameter<bool>     m_imageRecord;
    ofParameter<bool>     m_imageMirror;
    
    ofParameter<bool>     m_videoMode;
    ofParameter<bool>     m_noiseMode;
    ofParameter<bool>     m_audioMode;
    
    ofParameter<int>      m_noiseResolution;
    ofParameter<float>    m_noiseFrequency;
    ofParameter<float>    m_noiseSpeed;
    
    ofParameter<float>      m_hue;
    ofParameter<float>      m_brightness;
    ofParameter<float>      m_saturation;
    
   
    bool        m_showGui;  //It defines the whether the gui should be shown or not
};

//==========================================================================


