# QuickConfiker
A simple C++ class that allows you to load options from a configuration file.


## Library Usage
It is very simple to use this library. Just include the `QuickConfiker.h` file and don't forget to include the `QuickConfiker.cpp` file in your `g++` build!

The configuration can be used in many ways, let's assume that your delimiter is a space `' '`, then we don't need to change in settings in the constructor. So an example would be as follows:

```c++
try
{
    QuickConfiker configuration( "settings.ini" );

    // We can set the type before we try to find the parameters like this:
    double var1;
    int var2;
    configuration.setParameter( "firstVariable", var1 );
    configuration.setParameter( "secondVariable",var2 );

    // Or we can specify the type in the call like this:
    double var3 = configuration.getParameter<double>( "thirdVariable" );
    char var4 = configuration.getParameter<char>( "FirstLetter" );
    string var5 = configuration.getParameter<string>( "Surname" );

    //This method of specifying the type in the call means that these functions can be called during the construction of a class!
}
```

## Error Handling
This library contains its own error class known as `QuickConfikerError`. This error class is thrown when there are problems during the configuration. The `what()` function can be called to print out the error to console and the `get()` function can be called to get the error in the form of a string. This is useful because the error codes are set as constants in the library and can be searched for in each `QuickConfikerError` error that's returned. Example usage would include:

```c++
try
{
    // ...
    // Enter your code here where you use the QuickConfiker class
    // ...
}
catch ( QuickConfikerError error )
{
    error.what();

    string e = error.get();

    if ( e.find( QCERROR_FILE_NOT_FOUND ) != string::npos )
    {
        // Retry with a different filename or something.
    }
}
```

The error codes that currently exist are as follows:
```c++
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
```