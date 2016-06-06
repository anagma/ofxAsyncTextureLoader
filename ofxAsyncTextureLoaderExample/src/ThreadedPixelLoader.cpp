//
//  ThreadedPixLoader.cpp
//  ofxAsyncTextureLoaderExample
//
//  Created by FURUDATE Ken on 6/6/16.
//
//

#include "ThreadedPixelLoader.h"

ThreadedPixelLoader::ThreadedPixelLoader(){
	startThread();
}

void ThreadedPixelLoader::load(ofPixels & pix_, string filename_){
	ThreadedPixelLoaderEntry entry(pix_, filename_);
	pixAsyncLoading.send(entry);
}

void ThreadedPixelLoader::threadedFunction(){
	ThreadedPixelLoaderEntry entry;
	while( pixAsyncLoading.receive(entry) ) {
		ofLogVerbose("ThreadedPixelLoader") << "start loading: \"" << entry.filename << "\" at " << ofGetElapsedTimeMillis();
		if(ofLoadImage(*entry.pix, entry.filename))  {
			ofLogVerbose("ThreadedPixelLoader") << "file loaded: \"" << entry.filename << "\" at " << ofGetElapsedTimeMillis();
			ofNotifyEvent(loaded, *entry.pix, this);
		}else{
			ofLogError("ThreadedPixelLoader") << "couldn't load file: \"" << entry.filename << "\"";
		}
	}
}