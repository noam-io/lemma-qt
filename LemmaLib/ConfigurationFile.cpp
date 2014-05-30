//Copyright (c) 2014, IDEO 

#include "ConfigurationFile.h"
#include "ConfigFileChecker.h"
#include <QDir>
#include <QSettings>

ConfigurationFile::ConfigurationFile(QString const & applicationDir, QString const & systemDir)
    : applicationDir(applicationDir)
    , systemDir(systemDir)
{
}

QString ConfigurationFile::filename()
{
    QString configFile(  applicationDir + "/config.ini" );
    
    QString configSystemFile ( systemDir );
    QFile systemFile ( configSystemFile );
    if (systemFile.exists())
    {
        configFile = configSystemFile;
    }
    return configFile;

}

bool ConfigurationFile::isValid()
{
    QString exampleConfigFile( applicationDir + "/config-example.ini" );
    return validConfigFile( exampleConfigFile, filename() );
}

QSettings  * ConfigurationFile::readSettings()
{
    return new QSettings( filename(), QSettings::IniFormat );
}

bool ConfigurationFile::validConfigFile( const QString& examplePath, const QString& actualPath )
{
    bool result = false;

    QFile file( actualPath );
    QFile exampleFile( examplePath );

    if( !file.exists() )
    {
       qDebug() << "Missing config.ini file (" << actualPath << ")";
    }
    else if( !exampleFile.exists() )
    {
       qDebug() << "Missing config-example.ini file  (" << examplePath << ")";
    }
    else
    {
        qDebug() << "Using Config: " << actualPath;
        exampleFile.open( QIODevice::Text | QIODevice::ReadOnly );
        file.open( QIODevice::Text | QIODevice::ReadOnly );

        ConfigFileChecker checker( exampleFile.readAll(), file.readAll() );
        if( checker.isValid() )
        {
            result = true;
        }
        else
        {
           qDebug() << "Your config.ini file is missing the following settings:";
           const QSet< QString >& missingFields = checker.missingFields();
           QSet< QString >::const_iterator begin = missingFields.constBegin();
           QSet< QString >::const_iterator end = missingFields.constEnd();
           while( begin != end )
           {
               qDebug() << "--> " << (*begin);
               ++begin;
           }
        }
    }

   file.close();
   exampleFile.close();
   return result;
}
