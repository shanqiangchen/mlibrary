// gvolume
#include "systemTextFactory.h"


// c++
#include <iostream>
using namespace std;


void GSystemTextFactory::loadMaterial(GOptions* gopt, GSystem *s) {
	if(verbosity > 1) {
		cout << setupLogHeader << " Loading <text> materials for " <<  s->getName() << endl;
	}
}