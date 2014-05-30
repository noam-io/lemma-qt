//Copyright (c) 2014, IDEO 

#ifndef CONFIG_FILE_CHECKER_H
#define CONFIG_FILE_CHECKER_H

#include <QtCore/QSet>

class ConfigFileChecker
{
    QString expected;
    QString actual;

public:
    ConfigFileChecker( QString expected, QString actual );

    bool isValid();
    QSet< QString > missingFields();
};

#endif
