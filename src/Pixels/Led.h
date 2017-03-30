/*
 *  Led.h
 *  Video Pixels
 *
 *  Created by Imanol Gomez on 30/03/17.
 *
 */


#pragma once

#include "ofMain.h"
#include "BasicVisual.h"
#include "TextVisual.h"
#include "ImageVisual.h"


class Led: public BasicVisual {
    
    static const int SIZE;
    
public:
    
    Led(const ofPoint& position, int id);
    
    virtual ~Led();
    
    void draw();
    
    void draw(int width, int height);
    
    int getId() const {return m_id;}
    
    void normalize(const ofRectangle& boundingBox);
    
    void setPixelColor(ofPixelsRef pixels);
    
    void showId(bool _showId) {m_showId = _showId;}
    
private:
    
    void setup();
    
    void setupImages();
    
    void setupText();
    
private:
    
    int m_id;
    ofPtr<TextVisual>   m_idText;
    ofPtr<ImageVisual>  m_image;
    bool        m_showId;
};




