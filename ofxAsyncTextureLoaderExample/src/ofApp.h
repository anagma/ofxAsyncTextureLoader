#pragma once

#include "ofMain.h"
#include "ThreadedPixelLoader.h"
#include "ofxAsyncTextureLoader.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
	
	void onPixelLoaded(ofPixels & pix);
	
	ThreadedPixelLoader pixLoader;
	ofxAsyncTextureLoader texLoader;
	ofFbo fbo;
	ofPixels pix;
};
