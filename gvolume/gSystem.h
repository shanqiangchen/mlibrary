#ifndef  GSYSTEM_H
#define  GSYSTEM_H 1

// c++
#include <string>
using namespace std;

// gvolume
#include "gVolume.h"

// options
#include "goptions.h"


class GModifiers {
private:
	string name;  // volume name
	string shift;
	string tilts;
	bool present; // true by default

};

class GSystem {

public:
	GSystem(string n, string f, string v, int r, int dr) : name(n), factory(f), variation(v), runNumber(r) {
		cout << " System " << name << " loaded with factory " << factory;
		cout << ", variation: " << variation << ", run number: " << runNumber ;
		if(dr != r) cout << " (non default) ";
		cout << endl;
	}

private:
	string      name;    // System name
	string   factory;    // Factory that builds the detector
	string variation;    // Variation of the detector. Default is "default"
	int    runNumber;    // Run Number selected for this detector. Default is 1

	// map containing the volumes
	// the key is system + volume name so the names must be unique in each system
	map<string, GVolume*> systems;

};

class GSetup {
public:
	// constructor from a gcard
	// by default all systems will have the same run number but
	GSetup(GOptions* gopt, int runNo = 1);

private:
	map<string, GSystem*> setup;
	map<string, GModifiers*> setupModifiers;

public:
	// GSetup options
	static map<string, GOption> defineOptions();

};

#endif