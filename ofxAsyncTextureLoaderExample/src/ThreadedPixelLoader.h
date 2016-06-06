//
//  ThreadedPixLoader.h
//  ofxAsyncTextureLoaderExample
//
//  Created by FURUDATE Ken on 6/6/16.
//
//

#ifndef ThreadedPixLoader_h
#define ThreadedPixLoader_h

#include "ofMain.h"

class ThreadedPixelLoader : public ofThread{
public:
	ofEvent<ofPixels> loaded;
	
	ThreadedPixelLoader();
	void load(ofPixels & pix_, string filename_);
protected:
	void threadedFunction();
private:
	struct ThreadedPixelLoaderEntry{
		ThreadedPixelLoaderEntry(){
			pix = NULL;
			filename = "";
		}
		ThreadedPixelLoaderEntry(ofPixels & pix_, string filename_){
			pix =& pix_;
			filename = filename_;
		}
		string filename;
		ofPixels * pix;
	};
	ofThreadChannel<ThreadedPixelLoaderEntry> pixAsyncLoading;
};

#endif /* ThreadedPixLoader_h */
