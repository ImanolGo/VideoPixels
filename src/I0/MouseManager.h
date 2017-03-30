/*
 *  MouseManager.h
 *  Video Pixels
 *
 *  Created by Imanol Gomez on 30/03/17.
 *
 */

#pragma once

#include "ofMain.h"
#include "Manager.h"

//========================== class MouseManager =======================================
//==============================================================================
/** \class MouseManager MouseManager.h
 *	\brief class for managing the mouse events
 *	\details It reads all the mouse events and create the proper application events
 */


class MouseManager: public Manager
{

public:
    //! Constructor
    MouseManager();

    //! Destructor
    virtual ~MouseManager();

    //! setups the mouse
    void setup();

    //! Callback functions when mouse is pressed
    virtual void mousePressed(ofMouseEventArgs &e);
    
    //! Callback functions when mouse is released
    virtual void mouseReleased(ofMouseEventArgs &e);
    
    //! Callback functions when mouse is dragged
    virtual void mouseDragged(ofMouseEventArgs &e);
    
    //! Callback functions when mouse is moved
    virtual void mouseMoved(ofMouseEventArgs &e);
    
    //! Callback functions when mouse is moved
    virtual void mouseScrolled(ofMouseEventArgs &e);
    
    //! Callback functions when mouse is entered
    virtual void mouseEntered(ofMouseEventArgs &e);
    
    //! Callback functions when mouse is exited
    virtual void mouseExited(ofMouseEventArgs &e);


protected:
    
    //! Adds the events to be listen to
    virtual void addListeners();

};

