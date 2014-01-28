#ifndef VAPORARCADE_H
#define VAPORARCADE_H

#include <QObject>
#include "Settings/applicationsettings.h"
class VaporArcade : public QObject
{
    Q_OBJECT
public:
    explicit VaporArcade(QObject *parent = 0);

    // Methods pertaining to application settings
    Q_INVOKABLE QString getUserName(){return AppSettings.getUserName();}
    Q_INVOKABLE QString getEmulatorDirectory(){return AppSettings.getEmulatorDirectory();}
    Q_INVOKABLE QString getRomDirectory(){return AppSettings.getRomDirectory();}
    Q_INVOKABLE QString InterfacesDirectory(){return AppSettings.getInterfacesDirectory();}
    Q_INVOKABLE QString getCoverDirectory(){return AppSettings.getCoverDirectory();}
    Q_INVOKABLE QString getPosterDirectory(){return AppSettings.getPosterDirectory();}
    Q_INVOKABLE QString getVideoDirectory(){return AppSettings.getVideoDirectory();}
    Q_INVOKABLE bool    getUseNSD(){return AppSettings.getUseNSD();}


signals:
    void appSettingsChanged();

public slots:

private:
    ApplicationSettings  AppSettings;
};

#endif // VAPORARCADE_H
