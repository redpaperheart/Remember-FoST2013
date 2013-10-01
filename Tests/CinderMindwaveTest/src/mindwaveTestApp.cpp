#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/Utilities.h"
#include "cinder/Serial.h"

#include "Mindwave.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class mindwaveTestApp : public AppNative {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
    
    Mindwave* mind;
    
    bool bConnected = false;
    float mAttention = 0.0f;
    float mMeditation = 0.0f;
    float mBlink = 0.0f;
    float mLastBlink = 0.0f;
    float mTimeLastNewData = 0;
    
    // drawing
    int numbars;
    int margin;
    int barWidth;
    int barHeight;
    
    // serial
    Serial serial;

};

void mindwaveTestApp::setup()
{
    // setup mindwave
    mind = new Mindwave("/dev/tty.MindWaveMobile-DevA");
    //mind->enableLowPassFilter();
    //mind->setBaudRate(9600);
    mind->enableBlinkDetection();
    
    // setup serial connection
    // print the devices
	const vector<Serial::Device> &devices( Serial::getDevices() );
	for( vector<Serial::Device>::const_iterator deviceIt = devices.begin(); deviceIt != devices.end(); ++deviceIt ) {
		console() << "Device: " << deviceIt->getName() << endl;
	}
	
	try {
		Serial::Device dev = Serial::findDeviceByNameContains("MindWaveMobile-DevA");
		serial = Serial( dev, 9600);
	}
	catch( ... ) {
		console() << "There was an error initializing the serial device!" << std::endl;
		exit(-1);
    }
    
    // setup graphics
    numbars = 3;
    margin = 10;
    barWidth = getWindowWidth()-margin*2;
    barHeight = 50;
}

void mindwaveTestApp::mouseDown( MouseEvent event )
{

}

void mindwaveTestApp::update()
{
    if(!bConnected){
        if((bConnected = mind->connect())){
            console() << "connected with ID: " << mind->getConnectionID() << endl;
        }
    }
    else{
        bool isNewData = mind->update();
        mAttention = 0.9 * mAttention + 0.1 * (mind->getAttention());
        mMeditation = 0.9 * mMeditation + 0.1 * (mind->getMeditation());

        if(mind->getBlinkStrength() != mLastBlink) mBlink = mind->getBlinkStrength();
        else mBlink = 0.95 * mBlink;
        mLastBlink = mind->getBlinkStrength();
        
        if(isNewData){
            float t = getElapsedSeconds() - mTimeLastNewData;
            mTimeLastNewData = getElapsedSeconds();
            cout << "New data " << t << " after last. Avg datas per second: " << 1.0f/t << endl;
        }
        string message = toString(mAttention) + "," + toString(mMeditation);
        serial.writeString("124\n");
    }
    
    console() << "poor signal: " << mind->getSignalQuality() << endl
    << "attention: " << mind->getAttention() << endl
    << "meditation: " << mind->getMeditation() << endl << endl;
}

void mindwaveTestApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0.7, 0.7, 0.7 ) );
    
    
    Vec2i start, end;
    
    // signal quality
    start = Vec2i(margin, margin);
    end = start + Vec2i(255 - mind->getSignalQuality() * barWidth / 255, barHeight);
    gl::color(Color::gray(0.5f));
    gl::drawSolidRect(Rectf(start, end));
    
    // attention
    start = Vec2i(margin, margin*2 + barHeight);
    end = start + Vec2i(mAttention * barWidth / 100, barHeight);
    gl::color(Color(1.0, 1.0, 0.0));
    gl::drawSolidRect(Rectf(start, end));
    
    // meditation
    start = Vec2i(margin, margin*3 + barHeight*2);
    end = start + Vec2i(mMeditation * barWidth / 100, barHeight);
    gl::color(Color(0.0, 1.0, 1.0));
    gl::drawSolidRect(Rectf(start, end));
    
    // blink
    start = Vec2i(margin, margin*4 + barHeight*3);
    end = start + Vec2i(mBlink * barWidth / 255, barHeight);
    gl::color(Color(1.0, 0.0, 1.0));
    gl::drawSolidRect(Rectf(start, end));
    
    gl::drawString(toString((int)getAverageFps()), Vec2f(10, getWindowHeight()-20));


}

CINDER_APP_NATIVE( mindwaveTestApp, RendererGl )
