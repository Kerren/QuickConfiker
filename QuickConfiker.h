#ifndef QUICK_CONFIKER_H
#define QUICK_CONFIKER_H

#include <vector>
#include <sstream>
#include <fstream>
#include <string>

using std::vector;
using std::stringstream;
using std::ifstream;
using std::string;

#include "QuickConfikerError.h"

class QuickConfiker
{
public:

    QuickConfiker( const string& filename );
    ~QuickConfiker();

private:
    vector< stringstream > configurationLines;
};

#endif