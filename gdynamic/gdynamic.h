#ifndef  GDYNAMIC_H
#define  GDYNAMIC_H 1

// mlibrary
#include "gfactory.h"
#include "gtouchable.h"

// c++
#include <vector>
using namespace std;

// geant4
#include "G4Step.hh"

// properties of a sensitive detector, used in GTouchable and GHit.
// they are defined here so that the plugin can return it
class GSensitivePars {
public:
	// default constructor, set by base class
	GSensitivePars() : timeWindow(0), gridStartTime(0), hitStage(0), touchableDynamic(false), useTimeWindow(false) { }
	
	// constructor set by plugins
	GSensitivePars(double tw, double gst, int verbosity) :
	timeWindow(tw),
	gridStartTime(gst),
	hitStage(0),
	touchableDynamic(false),
	useTimeWindow(false) {
		// if(verbosity > )
	}

public:
	void setTouchableDynamic() {touchableDynamic = true;} // will call processTouchable in sensitiveDetector::ProcessHit
	void setUseTimeWindow()    {useTimeWindow = true;}    // will use time window
	bool isTouchableDynamic()  {return touchableDynamic;}
	bool doesUseTimeWindow()   {return useTimeWindow;}

private:
	double timeWindow;         // electronic timewindow of the detector
	double gridStartTime;      // defines the windows grid
	int    hitStage;           // defines what information to be stored in the hit
	bool   touchableDynamic; // decides if the touchable needs to be set with the plugins in sensitiveDetector::processHits
	bool   useTimeWindow;      // decides if the hit definitions needs to use the time window

public:
	inline int timeCell(double time) {
		return (int) (floor((time - gridStartTime)/timeWindow) + 1);
	}
	vector<string> showParameters() {
		vector<string> messages;
		messages.push_back(" Time Window: " + to_string(timeWindow));
		return messages;
	}
};

class GDynamic {

public:

	// change the GTouchable in sensitiveDetector::ProcessHit
	// by default the touchable is not changed
	// this function is loaded by plugin methods
	virtual vector<GTouchable*> processTouchable(GTouchable *gTouchID, G4Step* thisStep) {return { gTouchID } ;}

	// initialize sensitiveDetector parameters in sensitiveDetector::Initialize
	virtual void loadSensitivePars(int runno, string variation) {
	  gSensitiveParameters = new GSensitivePars();
	}

	// loads the calibration constants
	// return false for failure
	virtual bool loadConstants(int runno, string variation) { return false; }
	
	// logs the constants
	virtual vector<string> showConstants() { return  {" Please implement showConstants() in your plugin."}; }
	vector<string> showParameters() {return gSensitiveParameters->showParameters();}
	
	// the implementation should always return true
	// this is used as sanity check that the DL is actually loaded
	virtual bool checkPlugin() { return false; }

	GSensitivePars *gSensitiveParameters;
	
	bool isTouchableDynamic() {
		// gSensitiveParameters will always be there
		return gSensitiveParameters->isTouchableDynamic();
	}
	
	// this method must be present for the dynamic loaded factories
	static GDynamic* instantiate(const dlhandle handle) {
		
		if (handle == nullptr) return nullptr;

		void *maker = dlsym(handle , "GDynamicFactory");

		if (maker == nullptr) return nullptr;

		typedef GDynamic* (*fptr)();

		// static_cast not allowed here
		// see http://stackoverflow.com/questions/573294/when-to-use-reinterpret-cast
		// need to run the DLL GDynamicFactory function that returns the factory
		fptr func = reinterpret_cast<fptr>(reinterpret_cast<void*>(maker));

		return func();
	}

};


#endif
