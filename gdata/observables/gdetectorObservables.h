#ifndef  GDETECTOR_DATA_H
#define  GDETECTOR_DATA_H  1

// gdata
#include "observables/gobservables.h"

// PRAGMA TODO: decide if we have a pointer object, how to copy it, etc.
// PRAGMA TODO: add "adc", "tcd", "fadc" ?

// detector observales, all hits are accumulated here for one detector
// the quantities stored for both true and digitized vars are:
//
// - hits
// - pulses

class GDetectorObservables
{
public:
	GDetectorObservables(string sdName) : detectorSDName(sdName) {
	}
	
	// when adding an observale we can clear its name and description and add them
	// to the container class: saving memory, we dont need a description for every hit
	void addDetectorObservables(GObservables *observables, bool trueInfo = false) {
		
		if(trueInfo) {
			if(!(observables->isGetDescriptionAssigned())) {
				digiObservableName = observables->getName();
				digiObservableDesc = observables->getDesc();
				observables->clearNamesAndDescriptions();
			}
			digiObservables.push_back(observables);
		} else {
			if(!(observables->isGetDescriptionAssigned())) {
				trueObservableName = observables->getName();
				trueObservableDesc = observables->getDesc();
				observables->clearNamesAndDescriptions();
			}
			trueObservables.push_back(observables);
		}
	}
	

	
	// api to get data
	string getName() {return detectorSDName;}
	vector<string> getDigiObservableName() {return digiObservableName;}
	vector<string> getDigiObservableDesc() {return digiObservableDesc;}
	vector<string> getTrueObservableName() {return trueObservableName;}
	vector<string> getTrueObservableDesc() {return trueObservableDesc;}

	// observables api
	vector<GObservables*> getDigiObservables()  {return digiObservables;}
	vector<GObservables*> getDigiPulses()       {return digiPulses;}

	// true infos api
	vector<GObservables*> getTrueObservables()  {return trueObservables;}
	vector<GObservables*> getTruePulses()       {return truePulses;}

private:
	
	// detector SD name, passed here to it can be published
	string detectorSDName;
	
	vector<string> digiObservableName;
	vector<string> digiObservableDesc;
	
	vector<string> trueObservableName;
	vector<string> trueObservableDesc;

	// observables: accumulating over hits
	vector<GObservables*> digiObservables;   // one instance of a digitized observable / hit
	vector<GObservables*> digiPulses;        // multiple instances of a digitized observable / hit

	// true infos: accumulating over hits
	vector<GObservables*> trueObservables;   // one instance of true infos / hit
	vector<GObservables*> truePulses;        // multiple instances of true infos / hit
	
};
#endif
