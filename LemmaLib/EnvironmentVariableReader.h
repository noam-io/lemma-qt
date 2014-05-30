//Copyright (c) 2014, IDEO 

#ifndef ENVIRONMENTVARIABLEREADER_H
#define ENVIRONMENTVARIABLEREADER_H

class QString;

class EnvironmentVariableReader
{
private:
    char const * const * variables;

public:
    EnvironmentVariableReader( char const * const * variables );

    QString read( QString name ) const;
};

#endif
