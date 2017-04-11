#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    mode = EDIT;

    // listen on the given port
    int port = 12345;
    cout << "listening for osc messages on port " << port << "\n";
    receiver.setup(port);
    predictedClass = 0;
    curClassIndex = -1;

    ofTrueTypeFont::setGlobalDpi(72);
    font.load("verdana.ttf", 48, true, true);

    colors.push_back(ofColor::fromHex(0x2D2E41));
    colors.push_back(ofColor::fromHex(0x705A68));
    colors.push_back(ofColor::fromHex(0xECC6A6));
    colors.push_back(ofColor::fromHex(0xE2A58A));
    colors.push_back(ofColor::fromHex(0xCA4B58));

    lastCursorStateTime = 0;
}

//--------------------------------------------------------------
void ofApp::update(){

    // check for waiting messages
    while(receiver.hasWaitingMessages())
    {
        // get the next message
        ofxOscMessage m;
        receiver.getNextMessage(m);
        cout << "received message at " << m.getAddress() << endl;
        // check for mouse moved message
        if(m.getAddress() == "/wek/outputs")
        {
            // both the arguments are int32's
            predictedClass = int(m.getArgAsFloat(0));
            cout << predictedClass << endl;
        }
   }
}

//--------------------------------------------------------------
void ofApp::draw(){

    if (mode == EDIT)
    {
        ofBackground(colors[curClassIndex % colors.size()]);
        font.drawString((curClassIndex > -1 ? classes[curClassIndex] : "") + (cursorState ? "_" : ""), ofGetWidth() * 0.125, ofGetHeight() * 0.5);
    }
    else if (mode == RUN)
    {
        if (predictedClass != 0)
        {
            ofBackground(colors[(predictedClass - 1) % colors.size()]);
            font.drawString(classes[predictedClass - 1], ofGetWidth() * 0.125, ofGetHeight() * 0.5);
        }
    }

    if (ofGetElapsedTimeMillis() - lastCursorStateTime > 500)
    {
        cursorState = !cursorState;
        lastCursorStateTime = ofGetElapsedTimeMillis();
    }

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
//    cout << key << endl;

    // tab key switches modes
    if (key == 9)
    {
        if (mode == EDIT)
        {
            mode = RUN;
        }
        else
        {
            mode = EDIT;
        }
    }

    if (mode == EDIT)
    {
        if (key == 8)
        {
            // delete key
            classes[curClassIndex] = classes[curClassIndex].substr(0, classes[curClassIndex].size() - 1);
        }
        else if (key == 13)
        {
            if (classes[curClassIndex] != "")
            {
                classes.push_back("");
                curClassIndex++;
            }
        }
        else
        {
            // if there are no classes
            if (classes.size() == 0)
            {
               // create first class
               classes.push_back("");
               curClassIndex = 0;
            }

            classes[curClassIndex] += char(key);
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
