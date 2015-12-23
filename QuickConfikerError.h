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