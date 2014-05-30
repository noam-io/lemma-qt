//Copyright (c) 2014, IDEO 

#ifndef CONFIGURATIONFILE_H
#define CONFIGURATIONFILE_H

#include <QSettings>
#include <QString>

class ConfigurationFile
{
public:
    ConfigurationFile(QString const & applicationDir, QString const & systemDir);
    QSettings * readSettings();
    bool isValid();
    
private:
    QString applicationDir;
    QString systemDir;
    bool validConfigFile( const QString& examplePath, const QString& actualPath );
    QString filename();
};

#endif // CONFIGURATIONFILE_H
