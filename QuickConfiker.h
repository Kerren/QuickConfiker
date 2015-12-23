/*====================================================================================
    The MIT License (MIT)

    Copyright (c) 2015 Kerren

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
====================================================================================*/

#ifndef QUICK_CONFIKER_H
#define QUICK_CONFIKER_H

#include <vector>
#include <sstream>
#include <fstream>
#include <string>
#include <algorithm>

using std::vector;
using std::stringstream;
using std::ifstream;
using std::string;
using std::transform;
using std::getline;


#include "QuickConfikerError.h"

class QuickConfiker
{
public:
    /**
     * This is currently the only constructor available, I might change this in the future but for now I'm this'll have to do.
     * @parameter filename      The name of the configuration file.
     * @parameter fileDelimiter The delimiter used in the file to separate the parameter name and the value of that parameter.
     * @parameter caseSensitive Set this to false if you don't want your configuration file to be case sensitive. In other words, "FILENAME" and "filename" would be the same parameter.
     */
    QuickConfiker( const string& filename, const string fileDelimiter = " ", const bool caseSensitive = true );


    template< typename Tret >
    Tret getParameter( const string& parameter )
    {
        Tret result;

        if ( setParameter( parameter, result ) )
        {
            return result;
        }
        else
        {
            throw QuickConfikerError(QCERROR_PARAMETER_NOT_FOUND,"The parameter ==> ", parameter, " <== was not found! This error was thrown due to the fact that you're using a function that is unable to return 'false' when the parameter is not found. It might be better to use\n\ntemplate< typename Tret >\nTret getParameter( const string& parameter, bool& found )\n\nBecause this one will just set the 'found' parameter to 'false' if it doesn't find the variable." );
        }
    }

    template< typename Tret >
    Tret getParameter( const string& parameter, bool& found )
    {
        Tret result;

        if ( setParameter( parameter, result ) )
        {
            found = true;
        }
        else
        {
            found = false;
        }
    }

    /**
     * Sets a parameter to the value stored in the configuration file.
     * @param  parameter      The parameter name that needs to be set.
     * @param  parameterValue The variable that should be set with the value linked to the parameter name.
     * @return                A boolean value of whether or not this value was found.
     *
     * Unfortunately due to the templating, this needs to be defined in the header not the cpp file.
     */
    template< typename T >
    bool setParameter( const string& parameter, T& parameterValue )
    {

        for ( const stringstream& line : configurationLines )
        {
            string linestr( line.str() );
            bool found = false;
            if ( isCaseSensitive )
            {
                if ( linestr.find( parameter ) != string::npos )
                {
                    found = true;
                }
            }
            else
            {
                string lineUpper( linestr );
                string parameterUpper( parameter );
                std::transform( lineUpper.begin(), lineUpper.end(), lineUpper.begin(), ::toupper );
                std::transform( parameterUpper.begin(), parameterUpper.end(), parameterUpper.begin(), ::toupper );

                if ( lineUpper.find( parameterUpper ) != string::npos )
                {
                    found = true;
                }
            }

            if ( found )
            {
                auto pos = linestr.find( delimiter );
                if ( pos == string::npos )
                {
                    throw QuickConfikerError( QCERROR_DELIMITER_INCORRECT, "The parameter ==> ", parameter, " <== was found, but the delimiter ==> '", delimiter, "' <== was not found on the same line??\nThe line that I'm referring to is as follows:\n\n", linestr );
                }

                stringstream value( linestr.substr( pos + 1 ) );
                value >> parameterValue;
                return true;
            }
        }

        return false;
    };

    ~QuickConfiker();

private:
    /**
     * The delimiter used in the configuration file to separate parameter names and values.
     */
    const string delimiter;

    /**
     * A boolean of whether or not the user wants the parameter names to be case sensitive.
     */
    const bool isCaseSensitive;

    /**
     * A vector of all of the lines in the configuration file. This is used so that the file doesn't need to be reopened every time the user searches for a new parameter.
     */
    vector< stringstream > configurationLines;


};

#endif