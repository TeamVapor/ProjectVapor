#ifndef EMULATORLAUNCHER_H
#define EMULATORLAUNCHER_H
#include <QObject>
#include <QString>
#include <QHash>
#include <QPair>
#include <QList>
#include "EmulatorCore.h"
#include "EmulatorSettingsReader.h"
/******************************************************************************
* Author: Aaron Lindberg
* Class: EmulatorLauncher
* Created: 10/16/2013           Modified: 11/04/2013
*** OVERVIEW ***
*   The buisness class to expose the c++ functionality of
* launching emulators with games, and managing emulator settings.
******************************************************************************/
class EmulatorLauncher: public QObject
{
    Q_OBJECT
public:
/******************************************************************************
* Default Constructor
******************************************************************************/
    EmulatorLauncher(QObject* parent = nullptr):QObject(parent){}
/******************************************************************************
*	Destructor
*** OVERVIEW **
* 	Stops and deletes the emulator process if it exists, running or not.
******************************************************************************/
    ~EmulatorLauncher()
    {}

/******************************************************************************
*	start
*** OVERVIEW **
* 	Loads a specific emulator with a game.
*** INPUT **
*   Takes a string of the emulator system type, the emulator python name, and
* the path to the game to load.
******************************************************************************/
    Q_INVOKABLE void start(QString system,QString emuFile, QString game)
    {mEmulatorCore.loadEmulator(mEmulatorDir + "/" + system,emuFile, mRomsDir + "/" +game);}
/******************************************************************************
*	start
*** OVERVIEW **
* 	If no process is running start a new python file to load emulator launcher
* configuration, and command line arguments to send to the emulator.
*** INPUT **
*   Takes a emulator systrm and path to the game.
******************************************************************************/
    Q_INVOKABLE void start(const QString & system, const QString & game)
    {mEmulatorCore.start(mEmulatorDir + "/" + system,mRomsDir + "/" +game);}
/******************************************************************************
*	setRomsDir
*** OVERVIEW **
* 	Sets the path to all roms to launch.
*** INPUT **
* 	Take a QString by constant reference to set the executable path to.
******************************************************************************/
    Q_INVOKABLE void setRomsDir(const QString& RomsDir)
    { mRomsDir = RomsDir;}
/******************************************************************************
*	setEmulatorSystemDir
*** OVERVIEW **
* 	Sets the path to the emulator to launch.
*** INPUT **
* 	Take a QString by constant reference to set the executable path to.
******************************************************************************/
    Q_INVOKABLE void setEmulatorSystemDir(const QString& EmuDir)
    {mEmulatorDir = EmuDir;}
/******************************************************************************
*	stop
*** OVERVIEW **
* 	Stops the emulator from running.
******************************************************************************/
    Q_INVOKABLE void stop()
    {
        mEmulatorCore.stop();
    }

    Q_INVOKABLE void readSettings(QString system, QString emuPyFile)
    {
        mSettingsReader.ReadSettings(mEmulatorDir + "/" + system, emuPyFile);
    }
signals:
    void MultipleEmulatorsFound(QStringList emuList);
    void NoEmulatorsFound(QString directory);
    void BadPyDataProcessed(QString ErrMsg);
    void SettingsLoaded(SettingsHash hash);
private:
    QString mEmulatorDir;
    QString mRomsDir;
    EmulatorCore mEmulatorCore;
    EmulatorSettingsReader mSettingsReader;
};
#endif
