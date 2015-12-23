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

#ifndef QUICK_CONFIKER_ERROR_H
#define QUICK_CONFIKER_ERROR_H

#include <iostream>
#include <sstream>
#include <string>

using std::cout;
using std::endl;
using std::stringstream;
using std::string;


const string QCERROR_FILE_NOT_FOUND("E#001\n");


class QuickConfikerError
{
public:

    template< typename... Targs >
    QuickConfikerError( Targs... errorArguments ):
        error( "" )
    {
        stringstream ss;

        generateString( ss, errorArguments... );

        error = ss.str( );

    };

    string get() const { return error; };

    void what() const { cout << error << endl; };

    ~QuickConfikerError()
    {

    };

    const string QUICK_CONFIKER_ERROR_DELIMITER = "";


private:
    string error;

    template< typename T, typename... Targs >
    void generateString( stringstream& ss, T singleArgument, Targs... errorArguments )
    {
        ss << singleArgument << QUICK_CONFIKER_ERROR_DELIMITER;

        generateString( ss, errorArguments... );
    }

    void generateString( stringstream& ss )
    {
        return;
    }

};

#endif