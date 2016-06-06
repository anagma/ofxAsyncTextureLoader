//
//  ofxAsyncTextureLoader.h
//
//  Created by FURUDATE Ken on 4/17/16.
//
//

#ifndef ofxAsyncTextureLoader_h
#define ofxAsyncTextureLoader_h

#include "ofMain.h"

class ofxAsyncTextureLoader{
public:
	ofEvent<void> loaded;

	ofxAsyncTextureLoader();
	
	void loadData(ofFbo & f, ofPixels & p, int splitH=100);

	
protected:
	
	ofTexture tex;
	
	void onUpdate(ofEventArgs & args);

private:
	struct ofxAsyncTextureLoaderEntry{
		ofxAsyncTextureLoaderEntry(ofFbo & f, ofPixels & p, int splitH=100){
			fbo =& f;
			pix =& p;
			drawIndex = 0;
			splitHeight = splitH;
		}
		
		ofFbo * fbo;
		ofPixels * pix;
		
		int drawIndex;
		int splitHeight;
	};
	queue<ofxAsyncTextureLoaderEntry> entries;
};

#endif /* ofxAsyncTextureLoader_h */
