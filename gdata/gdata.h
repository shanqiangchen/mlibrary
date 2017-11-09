#ifndef  GDATA_H
#define  GDATA_H  1

// gdata
#include "observables/gobservables.h"
#include "observables/gdetectorObservables.h"

// c++
#include <vector>
#include <string>
using namespace std;

// mlibrary
#include "ghit.h"
#include "goptions.h"

class GEventData
{
	
public:
	void addDetectorData(GDetectorObservables *detectorData) {
		detectorsData.push_back(detectorData);
	}
	
	int getDetectorDataSize() {
		return (int) detectorsData.size();
	}
	
	// access data
	vector<GDetectorObservables*> getDetectorsData() {return detectorsData;}
	
private:
	// all detectors
	vector<GDetectorObservables*> detectorsData;
	
	// PRAGMA TODO: headers, generators infos
	
	
};

#endif
