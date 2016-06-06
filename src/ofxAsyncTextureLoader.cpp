//
//  ofxAsyncTextureLoader.cpp
//  ofxAsyncTextureLoaderExample
//
//  Created by FURUDATE Ken on 6/6/16.
//
//

#include "ofxAsyncTextureLoader.h"

ofxAsyncTextureLoader::ofxAsyncTextureLoader(){
	ofAddListener(ofEvents().update, this, &ofxAsyncTextureLoader::onUpdate, OF_EVENT_ORDER_AFTER_APP);
}

void ofxAsyncTextureLoader::loadData(ofFbo & f, ofPixels & p, int splitH){
	ofLogVerbose("ofxAsyncTextureLoader") << "start loading";
	entries.push(ofxAsyncTextureLoaderEntry(f, p, splitH));
}

void ofxAsyncTextureLoader::onUpdate(ofEventArgs & args){
	if(! entries.empty()){

		ofxAsyncTextureLoaderEntry & entry = entries.front();

		float texWidth = entry.pix->getWidth();
		float texHeight = (entry.splitHeight > 0) ? entry.splitHeight : entry.pix->getHeight();
		
		if(! entry.fbo->isAllocated() || entry.fbo->getWidth() != entry.pix->getWidth() || entry.fbo->getHeight() != entry.pix->getHeight()){
			ofLogVerbose("ofxAsyncTextureLoader") << "allocate fbo: " << entry.pix->getWidth() << ", " << entry.pix->getHeight();
			entry.fbo->allocate(entry.pix->getWidth(), entry.pix->getHeight(), GL_RGB);
		}
		
		int devideY = ceil(entry.pix->getHeight()/texHeight);
		
		float y = texHeight * entry.drawIndex;

		// if it is edge
		bool bEdge = ((entry.drawIndex+1) == devideY-1);

		float h = bEdge ? entry.pix->getHeight() - y	: texHeight;
	
		// load to tex
		tex.loadData(entry.pix->getData()+entry.pix->getPixelIndex(0, y), entry.pix->getWidth(), h, GL_RGB);
	
		// draw to fbo
		entry.fbo->begin();
		ofSetColor(255);
		tex.draw(0, y);
		entry.fbo->end();
		
		if(bEdge){
			ofLogVerbose("ofxAsyncTextureLoader") << "done loading... texture is ready!";
			ofNotifyEvent(loaded);
			entries.pop();
		}else{
			entry.drawIndex++;
		}
	}
}