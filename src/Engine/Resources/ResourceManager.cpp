/*
 *  ResourceManager.cpp
 *
 *  Created by Imanol G�mez on 16/02/15.
 *
 */

#include "../Main/AppManager.h"
#include "../Main/SettingsManager.h"

#include "ResourceManager.h"

const int ResourceManager::DEFAULT_IMAGE_SIZE = 256;


ResourceManager::ResourceManager() : Manager()
{
    //Intentionally left empty
}

ResourceManager::~ResourceManager()
{
    ofLogNotice() <<"ResourceManager::destructor" ;
}


void ResourceManager::setup()
{
    if(m_initialized)
		return;

    ofLogNotice() <<"ResourceManager::initialized" ;

	Manager::setup();

    this->createDefaultResource();
    this->loadResources();
}

void ResourceManager::loadResources()
{
    this->loadTextures();
    this->loadSVGs();
}

void ResourceManager::loadTextures()
{
    ResourcesPathMap texturePathMap = AppManager::getInstance().getSettingsManager().getTextureResourcesPath();

    for(ResourcesPathMap::iterator it = texturePathMap.begin(); it!= texturePathMap.end(); it++)
    {
        string textureName = it->first;
        string texturePath = it->second;

        ofPtr<ofTexture> texture = ofPtr<ofTexture>(new ofTexture());

        if(ofLoadImage(*texture,texturePath)){
            m_textures[textureName] = texture;
            ofLogNotice() <<"ResourceManager::loadTextures-> allocated texture " << textureName ;

        }
        else{
            ofLogNotice() <<"ResourceManager::loadTextures-> unable to load texture " << textureName
            << " from path " << texturePath ;
        }
    }
}

void ResourceManager::loadSVGs()
{
    ResourcesPathMap svgPathMap = AppManager::getInstance().getSettingsManager().getSvgResourcesPath();

    for(ResourcesPathMap::iterator it = svgPathMap.begin(); it!= svgPathMap.end(); it++)
    {
        string svgName = it->first;
        string svgPath = it->second;

        ofPtr<ofxSVG> svg = ofPtr<ofxSVG>(new ofxSVG);
        svg->load(svgPath);
        m_SVGs[svgName] = svg;
        ofLogNotice() <<"ResourceManager::loadSVGs-> allocated svg " << svgName ;
    }
}


ofPtr<ofTexture> ResourceManager::getTexture(const string& name) const
{
    if(this->containsTexture(name)) {
		return m_textures.at(name);
	}

	return m_defaultTexture;
}
void ResourceManager::createDefaultResource()
{
    int resourceSize = 256;
    m_defaultTexture = ofPtr<ofTexture>(new ofTexture());
    m_defaultTexture->allocate(DEFAULT_IMAGE_SIZE,DEFAULT_IMAGE_SIZE,GL_RGB);
}

bool ResourceManager::containsTexture(const string& name) const
{
	if(m_textures.find(name) == m_textures.end()) {
        ofLogNotice() <<"ResourceManager::containsTexture-> no resource with name " << name ;
		return false; // no entries for the specified name
	}

	return true;
}


ofPtr<ofxSVG> ResourceManager::getSVG(const string& name)
{
    if(this->containsSvg(name)) {
		return m_SVGs.at(name);
	}

    ofPtr<ofxSVG> svg = ofPtr<ofxSVG> (new ofxSVG);
	return svg;
}

bool ResourceManager::containsSvg(const string& name) const
{
	if(m_SVGs.find(name) == m_SVGs.end()) {
        ofLogNotice() <<"ResourceManager::containsSvg-> no resource with name " << name ;
		return false; // no entries for the specified name
	}

	return true;
}






