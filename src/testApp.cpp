#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

	ofBuffer buffer;
	string xmlFile = dragInfo.files[0];
	ofxXmlSettings fcpFile;
	if(fcpFile.loadFile(xmlFile)){
		fcpFile.pushTag("xmeml");
		int numSequences = fcpFile.getNumTags("sequence");
		for(int i = 0; i < numSequences; i++){
			string name = fcpFile.getAttribute("sequence", "id", "", i);
			//            cout << "name is " << name << endl;
			fcpFile.pushTag("sequence", i);
			fcpFile.pushTag("media");
			fcpFile.pushTag("video");
			buffer.append( "Sequence: " + name + "\n");
			int numTracks = fcpFile.getNumTags("track");
			//          cout << "   found " << numTracks << " tracks" << endl;
			for(int t = 0; t < numTracks; t++){
				fcpFile.pushTag("track", t);
				int numClipItems = fcpFile.getNumTags("clipitem");
				//                cout << "   found " << numClipItems << " clips" << endl;
				for(int c = 0; c < numClipItems; c++){
					fcpFile.pushTag("clipitem", c);
					string fileID = fcpFile.getAttribute("file", "id", "");
					string clipFileName = fcpFile.getValue("file:pathurl", "");
					buffer.append("    "+clipFileName + ":\n");

					int numMarkers = fcpFile.getNumTags("marker");
					for(int m = 0; m < numMarkers; m++){
						fcpFile.pushTag("marker", m);
						buffer.append( "        #" + ofToString(m) + " " + fcpFile.getValue("name", "no-name") + " Frame #: " + ofToString(fcpFile.getValue("in", 0)) + "\n");
						fcpFile.popTag(); //marker
					}

                    fcpFile.popTag(); //clipitem
				}
				fcpFile.popTag(); // track;
			}
            fcpFile.popTag(); //video
            fcpFile.popTag(); //media
            fcpFile.popTag(); //sequence
        }
        fcpFile.popTag(); //xmeml
	}
	
	ofBufferToFile(ofFilePath::removeExt( xmlFile ) + "_ExtractedMarkers.txt" , buffer);
	
}

