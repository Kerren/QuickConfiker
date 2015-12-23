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
using std::cerr;
using std::endl;
using std::stringstream;
using std::string;


// All of the error codes will be saved as constants which can be searched for when looking for what errors have occurred.

/**
 * If the file isn't found the error code below will be used.
 */
const string QCERROR_FILE_NOT_FOUND("E#001\n");

/**
 * If the delimiter is not found in the file then this error will be called. Note this will only be thrown when a user tries to set a parameter, before then this error shouldn't exist!
 */
const string QCERROR_DELIMITER_INCORRECT("E#002\n");

/**
 * This error occurs when the user has called a function to retrieve a parameter that doesn't exist and doesn't allow for the option for a boolean to be set when it's not found.
 */
const string QCERROR_PARAMETER_NOT_FOUND("E#003\n");

/**
 * The QuickConfikerError class is the class that will be thrown whenever an error occurs. Error codes are described as global constant strings and when the get() function is called, the error code can be searched for.
 */
class QuickConfikerError
{
public:

    /**
     * The constructor below takes in a number of arguments (of any primitive type and any types supported by the standard stringstream class). It then combines these arguments into a string which is later printed out.
     */
    template< typename... Targs >
    QuickConfikerError( Targs... errorArguments ):
        error( "" )
    {
        stringstream ss;

        generateString( ss, errorArguments... );

        error = ss.str( );

    };

    /**
     * Returns the error in the form of a string, this allows the user to search for the error code.
     * @return The error in the form of a string.
     */
    string get() const { return error; };

    /**
     * Prints out what the error is to the console.
     */
    void what() const { cerr << error << endl; };

    ~QuickConfikerError()
    {

    };

    /**
     * If the delimiter string is set, it'll be added between each argument that's sent into the constructor. This is useful if you'd like it to automatically add spaces between each argument (although I prefer performing that formatting within the actual arguments).
     */
    const string QUICK_CONFIKER_ERROR_DELIMITER = "";


private:
    /**
     * The error string that is generated during the construction of the class.
     */
    string error;


    //===> I modified the example presented in http://en.cppreference.com/w/cpp/language/parameter_pack to create this bit of code. <===//

    /**
     * Generates the error string based on the input parameters.
     * @param ss             The string stream that takes each argument.
     * @param singleArgument The first argument in the "array" of arguments being sent in.
     * @param errorArguments The rest of the "array" of arguments.
     */
    template< typename T, typename... Targs >
    void generateString( stringstream& ss, T singleArgument, Targs... errorArguments )
    {
        ss << singleArgument << QUICK_CONFIKER_ERROR_DELIMITER;

        generateString( ss, errorArguments... );
    }

    /**
     * Once the arguments are finished, this function will be called and we'll just return from the recursive process.
     * @param ss The stringstream that contains the error string.
     */
    void generateString( stringstream& ss )
    {
        return;
    }

};

#endif