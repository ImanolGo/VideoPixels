/*
 *  Led.cpp
 *  Video Pixels
 *
 *  Created by Imanol Gomez on 30/03/17.
 *
 */


#include "Led.h"


const int Led::SIZE = 20;

Led::Led(const ofPoint& position, int id): BasicVisual(position, SIZE, SIZE), m_id(id), m_showId(false)
{
    this->setup();
}

Led::~Led()
{
    //Intentionaly left empty
}

void Led::setup()
{
   // this->setupImages();
    this->setupText();
}


void Led::setupImages()
{
    ofVec3f position(0,0);
    string resourceName = "brush";
    m_image = ofPtr<ImageVisual> (new ImageVisual(m_position,resourceName, true));
}

void Led::setupText()
{
    
    ofVec3f position(0,0);
    float fontSize = m_width;
    string text = ofToString(m_id);
    string fontName ="fonts/open-sans/OpenSans-Bold.ttf";
    ofColor textColor = ofColor::white;
    
    m_idText = ofPtr<TextVisual> (new TextVisual(position,2*m_width,m_height, true));
    m_idText->setText(text,fontName,fontSize,textColor);
    
}


void Led::draw()
{
    ofPushMatrix();
    ofPushStyle();
    
    ofTranslate(m_position);
    ofScale(m_scale.x, m_scale.y);
    ofTranslate(-m_width*0.5,-m_height*0.5);
    
    ofRotateX(m_rotation.x);
    ofRotateY(m_rotation.y);
    
    ofSetColor(m_color);
    ofSetCircleResolution(20);
    ofFill();
    
    //ofRect(0, 0, m_width, m_height);
    ofDrawCircle(0, 0, m_width);
    
    ofPopStyle();
    
    if(m_showId){
        m_idText->draw();
    }
    ofPopMatrix();
}

void Led::draw(int width, int height)
{
    
    ofPushMatrix();
    ofTranslate(m_position.x * width, m_position.y * height);
    this->draw();
    ofPopMatrix();
}

void Led::normalize(const ofRectangle& boundingBox)
{
    m_position.x = (m_position.x - boundingBox.getX()) / boundingBox.getWidth();
    m_position.y = (m_position.y - boundingBox.getY()) / boundingBox.getHeight();
}


void Led::setPixelColor(ofPixelsRef pixels)
{
    m_color = pixels.getColor(m_position.x * pixels.getWidth(), m_position.y * pixels.getHeight());
}

