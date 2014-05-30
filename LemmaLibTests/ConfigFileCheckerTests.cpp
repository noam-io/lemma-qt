//Copyright (c) 2014, IDEO 

#include "ConfigFileCheckerTests.h"

#include <QtTest/QTest>
#include "ConfigFileChecker.h"

void ConfigFileCheckerTests::failsWhenMissingFields()
{
    QString expectedContents;
    expectedContents += "a=1\n";
    expectedContents += "b =2\n";
    expectedContents += "c = hi\n";
    expectedContents += "d= abcdefg\n";

    QString actualContents;
    actualContents += "a =1\n";
    actualContents += "c=2\n";

    ConfigFileChecker checker( expectedContents, actualContents );

    QVERIFY( !checker.isValid() );
    QCOMPARE( checker.missingFields().count(), 2 );
    QVERIFY( checker.missingFields().contains( "b" ));
    QVERIFY( checker.missingFields().contains( "d" ));
    QVERIFY( !checker.missingFields().contains( "a" ));
    QVERIFY( !checker.missingFields().contains( "c" ));
}

void ConfigFileCheckerTests::passesWithAllRequiredFields()
{
    QString expectedContents;
    expectedContents += "a=1\n";
    expectedContents += "b =2";

    QString actualContents;
    actualContents += "a =1\n";
    actualContents += "b= 2";

    ConfigFileChecker checker( expectedContents, actualContents );

    QVERIFY( checker.isValid() );
    QCOMPARE( checker.missingFields().count(), 0 );
}

void ConfigFileCheckerTests::ignoresCommentedOutFields()
{
    QString expectedContents;
    expectedContents += "a=1\n";
    expectedContents += "#b=2";

    QString actualContents;
    actualContents += "a=1";

    ConfigFileChecker checker( expectedContents, actualContents );

    QVERIFY( checker.isValid() );
    QCOMPARE( checker.missingFields().count(), 0 );
}
