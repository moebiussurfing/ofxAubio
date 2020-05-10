#include "ofApp.h"
#include "ofEventUtils.h"

////--------------------------------------------------------------
//void ofApp::setupSoundStream() {
//
//	sampleRate = 44100;
//	bufferSize = 512;
//	numBuffers = 4;
//
//	//input
//
//	soundStream_Input.printDeviceList();
//
//	cout << "INPUT devices" << endl;
//
//	//int myDevice = 6;//wasapi
//	int myDevice = 4;//ds
//	//int myDevice = 0;//asio
//
//	//std::vector<ofSoundDevice> devices = soundStream_Input.getDeviceList(ofSoundDevice::Api::MS_WASAPI);
//	std::vector<ofSoundDevice> devices = soundStream_Input.getDeviceList(ofSoundDevice::Api::MS_DS);
//	//std::vector<ofSoundDevice> devices = soundStream_Input.getDeviceList(ofSoundDevice::Api::MS_ASIO);
//
//	ofSoundStreamSettings settings_Input;
//	settings_Input.setInDevice(devices[myDevice]);
//	settings_Input.setInListener(ofGetAppPtr());
//
//	//settings_Input.setApi(ofSoundDevice::Api::MS_WASAPI);
//	settings_Input.setApi(ofSoundDevice::Api::MS_DS);
//	//settings_Input.setApi(ofSoundDevice::Api::MS_ASIO);
//
//	settings_Input.numInputChannels = 2;
//	settings_Input.numOutputChannels = 0;
//	settings_Input.sampleRate = sampleRate;
//	settings_Input.bufferSize = bufferSize;
//	settings_Input.numBuffers = numBuffers;
//	soundStream_Input.setup(settings_Input);
//
//	//--
//
//	//Output
//
//	soundStream_Output.printDeviceList();
//
//	cout << "OUTPUT devices" << endl;
//
//	//int myDevice = 6;//wasapi
//	int myOutDevice = 0;//ds
//	//int myOutDevice = 0;//asio
//
//	//std::vector<ofSoundDevice> devicesOut = soundStream_Output.getDeviceList(ofSoundDevice::Api::MS_WASAPI);
//	std::vector<ofSoundDevice> devicesOut = soundStream_Output.getDeviceList(ofSoundDevice::Api::MS_DS);
//	//std::vector<ofSoundDevice> devicesOut = soundStream_Output.getDeviceList(ofSoundDevice::Api::MS_ASIO);
//
//	ofSoundStreamSettings settings_Output;
//	settings_Output.setOutDevice(devicesOut[myOutDevice]);
//	settings_Output.setOutListener(ofGetAppPtr());
//	settings_Output.setOutListener(this);
//
//	//settings_Output.setApi(ofSoundDevice::Api::MS_WASAPI);
//	settings_Output.setApi(ofSoundDevice::Api::MS_DS);
//	//settings_Output.setApi(ofSoundDevice::Api::MS_ASIO);
//
//	settings_Output.numInputChannels = 0;
//	settings_Output.numOutputChannels = 2;
//	settings_Output.sampleRate = sampleRate;
//	settings_Output.bufferSize = bufferSize;
//	settings_Output.numBuffers = numBuffers;
//	soundStream_Output.setup(settings_Output);
//}


//--------------------------------------------------------------
void ofApp::setup(){
    // set the size of the window
    ofSetWindowShape(750, 250);

    int nOutputs = 2;
    int nInputs = 2;
    //int sampleRate = 44100;
    //int bufferSize = 256;
    //int nBuffers = 4;

    // setup onset object
    onset.setup();
    //onset.setup("mkl", 2 * bufferSize, bufferSize, sampleRate);
    // listen to onset event
    ofAddListener(onset.gotOnset, this, &ofApp::onsetEvent);

    // setup pitch object
    pitch.setup();
    //pitch.setup("yinfft", 8 * bufferSize, bufferSize, sampleRate);

    // setup beat object
    beat.setup();
    //beat.setup("default", 2 * bufferSize, bufferSize, samplerate);
    // listen to beat event
    ofAddListener(beat.gotBeat, this, &ofApp::beatEvent);

    // setup mel bands object
    bands.setup();

	//---

	//SOUND INPUTS

	//setupSoundStream();

	//

	//ofSoundStreamSettings settings;

	//// if you want to set the device id to be different than the default
	// auto devices = soundStream.getDeviceList();
	// //settings.setInDevice = devices[4];

	//// you can also get devices for an specific api
	//// auto devices = soundStream.getDevicesByApi(ofSoundDevice::Api::PULSE);
	//// settings.device = devices[0];

	//// or get the default device for an specific api:
	//// settings.api = ofSoundDevice::Api::PULSE;

	////// or by name
	////auto devices = soundStream.getMatchingDevices("default");
	////if (!devices.empty()) {
	////	settings.setInDevice(devices[0]);
	////}

	//settings.setInListener(this);
	//settings.sampleRate = 44100;
	//settings.numOutputChannels = 0;
	//settings.numInputChannels = 2;
	//settings.bufferSize = bufferSize;
	//soundStream.setup(settings);

	//---

    ofSoundStreamSetup(nOutputs, nInputs, this);
    ////ofSoundStreamSetup(nOutputs, nInputs, sampleRate, bufferSize, nBuffers);
    ofSoundStreamListDevices();


	//--

    // setup the gui objects
    int start = 0;
    beatGui.setup("ofxAubioBeat", "settings.xml", start + 10, 10);
    beatGui.add(bpm.setup( "bpm", 0, 0, 250));

    start += 250;
    onsetGui.setup("ofxAubioOnset", "settings.xml", start + 10, 10);
    onsetGui.add(onsetThreshold.setup( "threshold", 0, 0, 2));
    onsetGui.add(onsetNovelty.setup( "onset novelty", 0, 0, 10000));
    onsetGui.add(onsetThresholdedNovelty.setup( "thr. novelty", 0, -1000, 1000));
    // set default value
    onsetThreshold = onset.threshold;

    start += 250;
    pitchGui.setup("ofxAubioPitch", "settings.xml", start + 10, 10);
    pitchGui.add(midiPitch.setup( "midi pitch", 0, 0, 128));
    pitchGui.add(pitchConfidence.setup( "confidence", 0, 0, 1));

    bandsGui.setup("ofxAubioMelBands", "settings.xml", start + 10, 115);
    for (int i = 0; i < 40; i++) {
        bandPlot.addVertex( 50 + i * 650 / 40., 240 - 100 * bands.energies[i]);
    }
}

void ofApp::exit(){
    ofSoundStreamStop();
    ofSoundStreamClose();
}

void ofApp::audioIn(float * input, int bufferSize, int nChannels){
    // compute onset detection
    onset.audioIn(input, bufferSize, nChannels);
    // compute pitch detection
    pitch.audioIn(input, bufferSize, nChannels);
    // compute beat location
    beat.audioIn(input, bufferSize, nChannels);
    // compute bands
    bands.audioIn(input, bufferSize, nChannels);
}

void audioOut(){
}

//--------------------------------------------------------------
void ofApp::update(){
    onset.setThreshold(onsetThreshold);
}

//--------------------------------------------------------------
void ofApp::draw(){
    // update beat info
    if (gotBeat) {
        ofSetColor(ofColor::green);
        ofRect(90,150,50,50);
        gotBeat = false;
    }

    // update onset info
    if (gotOnset) {
        ofSetColor(ofColor::red);
        ofRect(250 + 90,150,50,50);
        gotOnset = false;
    }
    onsetNovelty = onset.novelty;
    onsetThresholdedNovelty = onset.thresholdedNovelty;

    // update pitch info
    pitchConfidence = pitch.pitchConfidence;
    if (pitch.latestPitch) midiPitch = pitch.latestPitch;
    bpm = beat.bpm;

    // draw
    pitchGui.draw();
    beatGui.draw();
    onsetGui.draw();

    ofSetColor(ofColor::orange);
    ofSetLineWidth(3.);
    bandsGui.draw();
    //bandPlot.clear();
    for (int i = 0; i < bandPlot.size(); i++) {
        bandPlot[i].y = 240 - 100 * bands.energies[i];
    }
    bandPlot.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}

//----
void ofApp::onsetEvent(float & time) {
    //ofLog() << "got onset at " << time << " s";
    gotOnset = true;
}

//----
void ofApp::beatEvent(float & time) {
    //ofLog() << "got beat at " << time << " s";
    gotBeat = true;
}
