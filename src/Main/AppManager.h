/*
 *  AppManager.h
  *  Video Pixels
 *
 *  Created by Imanol Gomez on 30/03/17.
 *
 */

#pragma once

#include "ofMain.h"

#include "Manager.h"

#include "SettingsManager.h"
#include "ResourceManager.h"
#include "ViewManager.h"
#include "VisualEffectsManager.h"
#include "LayoutManager.h"
#include "KeyboardManager.h"
#include "GuiManager.h"
#include "PixelsManager.h"
#include "LedsManager.h"
#include "NoiseManager.h"
#include "ImageManager.h"
#include "VideoManager.h"
#include "AudioVisualsManager.h"
#include "MouseManager.h"


//========================== class AppManager ==============================
//============================================================================
/** \class AppManager AppManager.h
 *	\brief Class managing the whole application
 *	\details it set-ups, updates and renders all the different managers used for the application
 */

class AppManager: public Manager
{
public:

    //! Destructor
    ~AppManager();

    //! Returns the singleton instance.
    static AppManager& getInstance();

    //! Compares two transition objects
    void setup();

    //! updates the logic
    void update();

    //! calls the view manager to draw
    void draw();

    //==========================================================================

    //! Returns the settings manager
    SettingsManager& getSettingsManager() { return m_settingsManager; }
    
    //! Returns the layout manager
    LayoutManager& getLayoutManager() { return m_layoutManager; }
    
    //! Returns the resource manager
    ResourceManager& getResourceManager() { return m_resourceManager; }
    
    //! Returns the view manager
    ViewManager&  getViewManager() { return m_viewManager; }
    
    //! Returns the visual effects manager
    VisualEffectsManager&  getVisualEffectsManager() { return m_visualEffectsManager; }
    
    //! Returns the GUI manager
    GuiManager&   getGuiManager() { return m_guiManager; }
    
    //! Returns the Pixels manager
    PixelsManager&   getPixelsManager() { return m_pixelsManager; }
    
    //! Returns the LEDs manager
    LedsManager&   getLedsManager() { return m_ledsManager; }
    
    //! Returns the Noise manager
    NoiseManager&   getNoiseManager() { return m_noiseManager; }
    
    //! Returns the Image manager
    ImageManager&   getImageManager() { return m_imageManager; }
    
    //! Returns the video manager
    VideoManager&   getVideoManager() { return m_videoManager; }
    
    //! Returns the audio visuals manager
    AudioVisualsManager&   getAudioVisualsManager() { return m_audioVisualsManager; }
    
    //==========================================================================
    
    void toggleDebugMode();
    
    void setDebugMode(bool showDebug);
    

private:

     //! Constructor
     AppManager();

	//! Stop the compiler generating methods of copy the object
	 AppManager(AppManager const& copy);              // Don't Implement

    //! Prevent operator= being generated.
     AppManager& operator=(AppManager const& copy);     // Don't implement

    //==========================================================================

    //! Set-up all the managers
    void setupManagers();

    //! Set-up openFrameworks
    void setupOF();

    //! update all the managers
    void updateManagers();

private:


    SettingsManager          m_settingsManager;          ///< Manages the application's settings
    ResourceManager          m_resourceManager;          ///< Manages the application's resources
    ViewManager              m_viewManager;              ///< Manages visuals
    VisualEffectsManager     m_visualEffectsManager;     ///< Manages visual effects
    LayoutManager            m_layoutManager;            ///< Manages the layout
    KeyboardManager          m_keyboardManager;          ///< Manages the keyboard
    MouseManager             m_mouseManager;             ///< Manages the mouse
    GuiManager               m_guiManager;               ///< Manages the graphical user interface
    PixelsManager            m_pixelsManager;            ///< Manages the pixels' visuals
    LedsManager              m_ledsManager;              ///< Manages the costume leds
    NoiseManager             m_noiseManager;             ///< Manages the noise visuals
    VideoManager             m_videoManager;             ///< Manages the video  visuals
    ImageManager             m_imageManager;             ///< Manages the images to be exported
    AudioVisualsManager      m_audioVisualsManager;      ///< Manages the audio reactive visuals

    bool                     m_debugMode;
};

//==========================================================================


