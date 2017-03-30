/*
 *  LedsManager.cpp
 *  Video Pixels
 *
 *  Created by Imanol Gomez on 30/03/17.
 *
 */

#include "ofMain.h"

#include "LedsManager.h"
#include "AppManager.h"


const string LedsManager::LEDS_LIST_PATH = "leds/";


LedsManager::LedsManager(): Manager(), m_ledsSize(8.0)
{
	//Intentionally left empty
}


LedsManager::~LedsManager()
{
    this->saveLedsPositions();
    ofLogNotice() <<"LedsManager::Destructor" ;
}


void LedsManager::setup()
{
	if(m_initialized)
		return;


	Manager::setup();
    
    this->setupBoundingBox();
    this->setupLeds();
    
    ofLogNotice() <<"LedsManager::initialized" ;
    
}

void LedsManager::setupBoundingBox()
{
//    m_boundingBox.setX(166.081);
//    m_boundingBox.setY(362.7);
//    m_boundingBox.setWidth(401.301 - m_boundingBox.getX());
//    m_boundingBox.setHeight(706.770 - m_boundingBox.getY());
    
    m_boundingBox.setX(166.081);
    m_boundingBox.setY(362.7);
    m_boundingBox.setWidth(401.301 - m_boundingBox.getX());
    m_boundingBox.setHeight(706.770 - m_boundingBox.getY());
}



void LedsManager::setupLeds()
{
    //this->createLedsPosition();
    this->readLedsPositions();
    //this->normalizeLeds();
}

void LedsManager::createLedsPosition()
{
    float x_offset = 0.05;
    float y_offset = 0.05;
    int num_rows = 20;
    int num_cols = 19;
    
    float w = (1.0 - 2.0*x_offset)/num_cols;
    float h = (1.0 - 2.0*y_offset)/num_rows;
    
    for(int i = 0; i< num_rows; i++){
        for(int j = 0; j< num_cols; j++){
            
            float x = x_offset + j*w;
            float y = y_offset + i*h;
            
            ofPoint ledPosition(x,y,0.0);
            createLed(ledPosition);
        }
    }
    
    
    
}

void LedsManager::addLed(const ofPoint& position)
{
    ofRectangle windowRect = AppManager::getInstance().getPixelsManager().getWindowRect();
    createLed(position);
    
    if (!m_leds.empty()) {
        m_leds.back()->normalize(windowRect);
    }
    
    ofLogNotice() <<"LedsManager::addLed-> id = " <<  m_leds.back()->getId();
}

void LedsManager::deleteLastLed()
{
    if(!m_leds.empty()){
        int id = m_leds.back()->getId();
        m_leds.pop_back();

        ofLogNotice() <<"LedsManager::deleteLastLed-> id = " << id;
    }
}

void LedsManager::readLedsPositions()
{
    
    string led_position_path = LEDS_LIST_PATH + "LedPositions.txt";
    ofBuffer buffer = ofBufferFromFile(led_position_path);
    
    
    if(buffer.size())
    {
        for (ofBuffer::Line it = buffer.getLines().begin(), end = buffer.getLines().end(); it != end; ++it)
        {
            string line = *it;
            ofPoint ledPosition;
            
            if(parseLedLine(line,ledPosition))
            {
                createLed(ledPosition);
            }
            
        }
    }
    
}


void LedsManager::saveLedsPositions()
{
     string led_position_path = LEDS_LIST_PATH + "LedPositions.txt";
     ofFile ledPosFile(led_position_path, ofFile::WriteOnly, true);
    
    for(auto led: m_leds)
    {
        ofPoint pos =led->getPosition();
        ledPosFile << "{" << pos.x << ", " << pos.y << ", 0.0}" <<std::endl;
    }
    
    ledPosFile.close();
    
    ofLogNotice() <<"LedsManager::saveLedsPositions -> saved led positions to file " <<  led_position_path;
    
}


void LedsManager::normalizeLeds()
{
    
    float width = AppManager::getInstance().getPixelsManager().getWidth();
    float height = AppManager::getInstance().getPixelsManager().getHeight();
    
    
    ofLogNotice() <<"LedsManager::normalizeLeds -> width " << width<< ", height = "  << height;
    
    for (auto led: m_leds)
    {
        led->normalize(m_boundingBox);
        ofLogNotice() <<"LedsManager::normalized LED -> id " << led->getId() << ", x = "  << led->getPosition().x << ", y = "  << led->getPosition().y;
    }
    
}


void LedsManager::createLed(const ofPoint& position)
{
    ofPtr<Led> led = ofPtr<Led> (new Led ( position, m_leds.size() + 1) );
    led->setColor(ofColor::black);
    led->setWidth(m_ledsSize);
    m_leds.push_back(led);

    
    ofLogNotice() <<"LedsManager::createLed -> id " << led->getId() << ", x = "  << led->getPosition().x << ", y = "  << led->getPosition().y;
}

bool LedsManager::parseLedLine(string& line, ofPoint& position)
{
    if(line.size() == 0){
        return false;
    }

    char chars[] = "{}";
    removeCharsFromString(line, chars);
    vector <string> strings = ofSplitString(line, ", " );
    
    position.x = ofToFloat(strings[0]);
    position.y = ofToFloat(strings[1]);
    position.z = ofToFloat(strings[2]);
    
    return true;
}

void LedsManager::removeCharsFromString( string &str, char* charsToRemove ) {
    for ( unsigned int i = 0; i < strlen(charsToRemove); ++i ) {
        str.erase( remove(str.begin(), str.end(), charsToRemove[i]), str.end() );
    }
}

void LedsManager::update()
{
    //
}

void LedsManager::setPixels(ofPixelsRef pixels)
{
    this->setLedColors(pixels);
    
    AppManager::getInstance().getImageManager().update();
}

void LedsManager::setLedColors(ofPixelsRef pixels)
{
    for(auto led: m_leds){
        led->setPixelColor(pixels);
    }
}


void LedsManager::draw()
{
    this->drawLeds();
}

void LedsManager::draw(int width, int height)
{
    this->drawLeds(width, height);
}

void LedsManager::drawLeds(int width, int height)
{
    for(auto led: m_leds)
    {
        led->draw(width,height);
    }
}

void LedsManager::onSetLedsSize(float &value)
{
    m_ledsSize = value;
    
    for(auto led: m_leds){
        led->setWidth(m_ledsSize);
    }
}

void LedsManager::showChannels(bool _showChannels)
{
    for(auto led: m_leds)
    {
        led->showId(_showChannels);
    }
}









