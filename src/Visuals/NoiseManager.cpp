/*
 *  NoiseManager.cpp
 *  Video Pixels
 *
 *  Created by Imanol Gomez on 30/03/17.
 *
 */


#include "ofMain.h"

#include "NoiseManager.h"
#include "AppManager.h"


NoiseManager::NoiseManager(): Manager(), m_noiseResolution(255), m_playNoise(false)
{
	//Intentionally left empty
}


NoiseManager::~NoiseManager()
{
    ofLogNotice() <<"NoiseManager::Destructor" ;
}


void NoiseManager::setup()
{
	if(m_initialized)
		return;


	Manager::setup();
    
    this->setupBoundingBox();
    this->setupFbo();
    this->setupNoise();
    
    ofLogNotice() <<"NoiseManager::initialized" ;
    
}

void NoiseManager::setupBoundingBox()
{
   
    float ratio = ((float)ofGetWidth())/ofGetHeight();
    
    m_boundingBox.width = AppManager::getInstance().getGuiManager().getWidth();
    m_boundingBox.height = m_boundingBox.width/ratio;

    
    m_boundingBox.y = AppManager::getInstance().getGuiManager().getPosition().y + AppManager::getInstance().getGuiManager().getHeight() + 20;
    m_boundingBox.x = AppManager::getInstance().getGuiManager().getPosition().x;
}

void NoiseManager::setupFbo()
{
    m_fbo.allocate(m_boundingBox.getWidth(), m_boundingBox.getHeight(), GL_RGB);
    m_fbo.begin(); ofClear(0); m_fbo.end();
    
    //m_fboReader.setAsync(true);
    
}

void NoiseManager::setupNoise()
{
   m_noiseImage.allocate( m_noiseResolution, m_noiseResolution, OF_IMAGE_COLOR );
}


void NoiseManager::resetPosition()
{
    setupBoundingBox();
    setupFbo();
}


void NoiseManager::update()
{
    if(!m_playNoise){
        return;
    }
    
    this->updateNoise();
    
    AppManager::getInstance().getLedsManager().setPixels(m_noiseImage.getPixelsRef());
}


void NoiseManager::updateNoise()
{
    float time = ofGetElapsedTimef() * m_noiseSpeed;
    ofPixelsRef pixels = m_noiseImage.getPixelsRef();
    
    int tmpIndex = 0;
    for( int y = 0; y < m_noiseImage.getHeight(); y++ )
    {
        for( int x = 0; x < m_noiseImage.getWidth(); x++ )
        {
            // We're grabbing a single reading from the noise function here, but we can also add together more
            // readings at different frequencies to make more complex patterns
            
            float tmpNoise = ofNoise( x / m_noiseFrequency,  y / m_noiseFrequency, time );
            
            
            ofColor c;
            // the range of each of the arguments here is 0..255 so we map i and j to that range.
    
            c.setHsb( m_color.getHue(), m_color.getSaturation(), m_color.getBrightness()*tmpNoise);
            
            //m_noiseColor.setSaturation(tmpNoise * 255.0f);
            pixels.setColor(x,y, c);
            //pixels.setColor(x,y,ofColor(0,0,tmpNoise * 255.0f));
            
            //pixels[tmpIndex] = tmpNoise * 255.0f;
            //tmpIndex++;
        }
    }

    m_noiseImage.update(); // uploads the new pixels to the gfx card
}

//--------------------------------------------------------------
void NoiseManager::onNoiseResolutionChange( int& value )
{
    m_noiseImage.allocate( value, value, OF_IMAGE_COLOR );
}


void NoiseManager::draw()
{
    if(!m_playNoise){
        return;
    }
    
     m_noiseImage.draw(m_boundingBox);
}




