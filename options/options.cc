#include "options.h"

// initialize general options
goptions::goptions()
{
	optMap["Verbosity"].arg       = 0;
	optMap["Verbosity"].help      = "Controls General Log Verbosity.";
	optMap["Verbosity"].shortHelp = "Log Verbosity";
	optMap["Verbosity"].type      = 0;
	optMap["Verbosity"].category  = "verbosity";
}







