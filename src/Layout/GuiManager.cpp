/*
 *  GuiManager.cpp
 *  Video Pixels
 *
 *  Created by Imanol Gomez on 30/03/17.
 *
 */

#include "ofMain.h"

#include "AppManager.h"

#include "GuiManager.h"


const string GuiManager::GUI_SETTINGS_FILE_NAME = "xmls/GuiSettings.xml";
const string GuiManager::GUI_SETTINGS_NAME = "HeroDress";
const int GuiManager::GUI_WIDTH = 350;


GuiManager::GuiManager(): Manager(), m_showGui(true)
{
	//Intentionally left empty
}


GuiManager::~GuiManager()
{
    this->saveGuiValues();
    ofLogNotice() <<"GuiManager::Destructor";
}


void GuiManager::setup()
{
	if(m_initialized)
		return;
    
    Manager::setup();


    this->setupGuiParameters();
    this->setupModesGui();
    this->setupLedsGui();
    this->setupLayoutGui();
    this->setupImageGui();
    this->setupVideoGui();
    this->setupAudioGui();
    this->setupNoiseGui();
    this->loadGuiValues();
    
    ofLogNotice() <<"GuiManager::initialized";
    
}

void GuiManager::setupGuiParameters()
{
    m_gui.setDefaultWidth(GUI_WIDTH);
    m_gui.setup(GUI_SETTINGS_NAME, GUI_SETTINGS_FILE_NAME);
    m_gui.setPosition(ofGetWidth() - GUI_WIDTH - 20, 40);
    //m_gui.setPosition(20, 20);
    m_gui.add(m_guiFPS.set("FPS", 0, 0, 60));
    ofxGuiSetFont( "fonts/open-sans/OpenSans-Semibold.ttf", 9 );

}

void GuiManager::setupLedsGui()
{
    auto ledsManager = &AppManager::getInstance().getLedsManager();
    
    m_parametersLeds.setName("Dress");
    
    m_ledsSize.set("Leds Size", 8.0, 2.0, 40);
    m_ledsSize.addListener(ledsManager, &LedsManager::onSetLedsSize);
    m_parametersLeds.add(m_ledsSize);
    
    m_gui.add(m_parametersLeds);
}



void GuiManager::setupModesGui()
{

    m_parametersModes.setName("Modes");
    
    m_videoMode.set("Video",  false );
    m_videoMode.addListener(this, &GuiManager::onSetVideoMode);
    m_parametersModes.add(m_videoMode);
    
    m_noiseMode.set("Noise",  false );
    m_noiseMode.addListener(this, &GuiManager::onSetNoiseMode);
    m_parametersModes.add(m_noiseMode);
    
    m_audioMode.set("Audio",  false );
    m_audioMode.addListener(this, &GuiManager::onSetAudioMode);
    m_parametersModes.add(m_audioMode);
    
    m_gui.add(m_parametersModes);
}

void GuiManager::setupLayoutGui()
{
    auto layoutManager = &AppManager::getInstance().getLayoutManager();
    
    m_parametersLayout.setName("Color");
    
    m_hue.set("Hue", 0.0, 0.0, 255.0);
    m_hue.addListener(layoutManager, &LayoutManager::onHueChange);
    m_parametersLayout.add(m_hue);
    
    m_saturation.set("Saturation", 0.0, 0.0, 255.0);
    m_saturation.addListener(layoutManager, &LayoutManager::onSaturationChange);
    m_parametersLayout.add(m_saturation);
    
    m_brightness.set("Brightness", 0.0, 0.0, 255.0);
    m_brightness.addListener(layoutManager, &LayoutManager::onBrightnessChange);
    m_parametersLayout.add(m_brightness);
    
    m_gui.add(m_parametersLayout);
}


void GuiManager::setupImageGui()
{
    auto imageManager = &AppManager::getInstance().getImageManager();
    
    m_parametersImage.setName("Image Export");
    
    m_imageRecord.set("Record",  false );
    m_imageRecord.addListener(imageManager, &ImageManager::onRecordingChange);
    m_parametersImage.add(m_imageRecord);
    
    m_imageMirror.set("Mirror",  false );
    m_imageMirror.addListener(imageManager, &ImageManager::onMirroringChange);
    m_parametersImage.add(m_imageMirror);

    
    m_gui.add(m_parametersImage);
}

void GuiManager::setupVideoGui()
{
    auto videoManager = &AppManager::getInstance().getVideoManager();
    
    m_parametersVideo.setName("Video");
    
    m_nextVideo.setup("Next Video");
    m_nextVideo.addListener(videoManager, &VideoManager::onNextVideoChange);
    
    
    m_recordVideoLoops.set("Record Video Loops", false);
    m_recordVideoLoops.addListener(videoManager, &VideoManager::onRecordVideoLoopsChange);
    m_parametersVideo.add(m_recordVideoLoops);
    
    
    m_videoTrail.set("Video Trail", false);
    m_videoTrail.addListener(videoManager, &VideoManager::onVideoTrailChange);
    m_parametersVideo.add(m_videoTrail);

    
    m_gui.add(m_parametersVideo);
    m_gui.add(&m_nextVideo);
    
}

void GuiManager::setupAudioGui()
{
    auto audioManager = &AppManager::getInstance().getAudioVisualsManager();
    
    m_parametersAudio.setName("Audio");
    
    m_audioLevel.set("Audio Level",  0.5, 0.0, 1.0 );
    m_audioLevel.addListener(audioManager, &AudioVisualsManager::onInputLevelChange);
    m_parametersAudio.add(m_audioLevel);
    
    m_nextAudio.setup("Next Visual");
    m_nextAudio.addListener(audioManager, &AudioVisualsManager::onNextAudiohange);
    
    m_gui.add(m_parametersAudio);
    m_gui.add(&m_nextAudio);
}

void GuiManager::setupNoiseGui()
{
    auto noiseManager = &AppManager::getInstance().getNoiseManager();
    
    m_parametersNoise.setName("Noise");

    m_noiseResolution.set("Noise Resolution",  64, 2, 256 );
    m_noiseResolution.addListener(noiseManager, &NoiseManager::onNoiseResolutionChange);
    m_parametersNoise.add(m_noiseResolution);
        
    m_noiseFrequency.set("Noise Frequency",  0.4, 0.0, 4.0);
    m_noiseFrequency.addListener(noiseManager, &NoiseManager::onNoiseFrequencyChange);
    m_parametersNoise.add(m_noiseFrequency);
    
    m_noiseSpeed.set("Noise Speed",  1.0, 0.001, 3);
    m_noiseSpeed.addListener(noiseManager, &NoiseManager::onNoiseSpeedChange);
    m_parametersNoise.add(m_noiseSpeed);

    
    m_gui.add(m_parametersNoise);
}


void GuiManager::draw()
{
    if(!m_showGui)
        return;
    
    this->drawRectangle();
    
    m_guiFPS = ofGetFrameRate();
    m_gui.draw();
    
}


void GuiManager::saveGuiValues()
{
    m_gui.saveToFile(GUI_SETTINGS_FILE_NAME);
}

void GuiManager::loadGuiValues()
{
    m_gui.loadFromFile(GUI_SETTINGS_FILE_NAME);
}


void GuiManager::toggleGui()
{
    m_showGui = !m_showGui;
}

void GuiManager::drawRectangle()
{
    ofPushStyle();
    ofSetColor(ofColor::black);
    ofRect( m_gui.getPosition().x - 20, 0, GUI_WIDTH + 60, ofGetHeight());
    ofPopStyle();
}



void GuiManager::onSetVideoMode(bool& value)
{
    if(value == true){
        m_noiseMode = false;
        m_audioMode = false;
        AppManager::getInstance().getVideoManager().onPlayVideoChange(true);
        AppManager::getInstance().getNoiseManager().onPlayNoiseChange(false);
        AppManager::getInstance().getAudioVisualsManager().onPlayAudioVisualsChange(false);
    }

}

void GuiManager::onSetNoiseMode(bool& value)
{
    if(value == true){
        m_videoMode = false;
        m_audioMode = false;
        AppManager::getInstance().getVideoManager().onPlayVideoChange(false);
        AppManager::getInstance().getNoiseManager().onPlayNoiseChange(true);
        AppManager::getInstance().getAudioVisualsManager().onPlayAudioVisualsChange(false);
    }
}

void GuiManager::onSetAudioMode(bool& value)
{
    if(value == true){
        m_videoMode = false;
        m_noiseMode = false;
        AppManager::getInstance().getVideoManager().onPlayVideoChange(false);
        AppManager::getInstance().getNoiseManager().onPlayNoiseChange(false);
        AppManager::getInstance().getAudioVisualsManager().onPlayAudioVisualsChange(true);
    }
    
}
