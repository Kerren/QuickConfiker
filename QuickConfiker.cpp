#include "QuickConfiker.h"

QuickConfiker::QuickConfiker( const string& filename )
{
    ifstream input( filename );

    if ( !input )
    {
        throw QuickConfikerError( QCERROR_FILE_NOT_FOUND, "There was an error opening the file named ==> ", filename, " <== please ensure that it's in the right folder an the path to this file was specified correctly!" );
    }
}

QuickConfiker::~QuickConfiker()
{

}
