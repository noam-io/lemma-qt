//Copyright (c) 2014, IDEO 

#ifndef CONFIG_FILE_CHECKER_TESTS_H
#define CONFIG_FILE_CHECKER_TESTS_H

#include <QtCore/QObject>

class ConfigFileCheckerTests : public QObject
{
    Q_OBJECT

private slots:
   void failsWhenMissingFields();
   void passesWithAllRequiredFields();
   void ignoresCommentedOutFields();
};

#endif
