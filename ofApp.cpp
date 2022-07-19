/************************************************************
************************************************************/
#include "ofApp.h"

/************************************************************
************************************************************/

/******************************
******************************/
void ofApp::setup(){
	/********************
	********************/
	ofSetBackgroundAuto(true);
	
	ofSetWindowTitle("Peep:Shutter");
	ofSetVerticalSync(true);
	ofSetFrameRate(30);
	ofSetWindowShape(WINDOW_WIDTH, WINDOW_HEIGHT);
	ofSetEscapeQuitsApp(false);
	
	/********************
	********************/
	ofSeedRandom();
	
	ofEnableAntiAliasing();
	ofEnableBlendMode(OF_BLENDMODE_ALPHA); // OF_BLENDMODE_DISABLED, OF_BLENDMODE_ALPHA, OF_BLENDMODE_ADD
	
	/********************
	********************/
	setup_udp();
	
	/********************
	********************/
	gui.setup();
	
	gui.add(Angle_Open.setup("open", 0, 0, 180));
	gui.add(Angle_Close.setup("close", 180, 0, 180));
}

/******************************
******************************/
void ofApp::setup_udp(){
	/********************
	********************/
	{
		ofxUDPSettings settings;
		// settings.sendTo("127.0.0.1", 12345);
		settings.sendTo("10.0.0.8", 12345);
		settings.blocking = false;
		
		udp_Send.Setup(settings);
	}
	
	/********************
	********************/
	{
		ofxUDPSettings settings;
		settings.receiveOn(12347);
		settings.blocking = false;
		
		udp_Receive.Setup(settings);
	}
}

/******************************
******************************/
void ofApp::update(){
	char udpMessage[UDP_BUF_SIZE];
	udp_Receive.Receive(udpMessage, UDP_BUF_SIZE);
	string message=udpMessage;
	
	if(message!=""){
		int counter = 0;
		do{
			/********************
			********************/
			// printf("%s\n", message.c_str());
			// printf("> %d th message\n", counter);
			counter++;
			
			vector<string> strMessages = ofSplitString(message, "[p]");
			/*
			for(int i = 0; i < strMessages.size(); i++){
				printf("%s\n", strMessages[i].c_str());
			}
			*/
			
			if(strMessages.size() == 2){
				if( (strMessages[0] == "PrjShutter") && (strMessages[1] == "Beat") )	c_Beat++;
			}
			
			/********************
			********************/
			udp_Receive.Receive(udpMessage, UDP_BUF_SIZE);
			message=udpMessage;
		}while(message!="");
	}
}

/******************************
******************************/
void ofApp::draw(){
	ofBackground(40);
	
	gui.draw();
	
	/*
	printf("c_Beats = %d\r", c_Beat);
	fflush(stdout);
	*/
}

/******************************
******************************/
void ofApp::sendUdpTo_PrjShutter__open(){
	char buf[100];
	sprintf(buf, "%d", int(Angle_Open));
	
	string message="";
	message += "oF|set_Angle|";
	message += buf;
	
	udp_Send.Send(message.c_str(),message.length());
}

/******************************
******************************/
void ofApp::sendUdpTo_PrjShutter__close(){
	char buf[100];
	sprintf(buf, "%d", int(Angle_Close));
	
	string message="";
	message += "oF|set_Angle|";
	message += buf;
	
	udp_Send.Send(message.c_str(),message.length());
}

/******************************
******************************/
void ofApp::keyPressed(int key){
	switch(key){
		case '0':
			sendUdpTo_PrjShutter__open();
			break;
		case '1':
			sendUdpTo_PrjShutter__close();
			break;
			
		case 'd':
			printf("c_Beat = %d\n", c_Beat);
			fflush(stdout);
			break;
	}
}

/******************************
******************************/
void ofApp::keyReleased(int key){

}

/******************************
******************************/
void ofApp::mouseMoved(int x, int y ){

}

/******************************
******************************/
void ofApp::mouseDragged(int x, int y, int button){

}

/******************************
******************************/
void ofApp::mousePressed(int x, int y, int button){

}

/******************************
******************************/
void ofApp::mouseReleased(int x, int y, int button){

}

/******************************
******************************/
void ofApp::mouseEntered(int x, int y){

}

/******************************
******************************/
void ofApp::mouseExited(int x, int y){

}

/******************************
******************************/
void ofApp::windowResized(int w, int h){

}

/******************************
******************************/
void ofApp::gotMessage(ofMessage msg){

}

/******************************
******************************/
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
