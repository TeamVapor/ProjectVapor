#ifndef EMULATORLAUNCHER_H
#define EMULATORLAUNCHER_H
#include <QObject>
#include <QDir>
#include <QString>
#include <QProcess>
#include <QDebug>

/******************************************************************************
* Author: Aaron Lindberg
* Class: EmulatorLauncher
* Created: 10/16/2013           Modified: 11/04/2013
*** OVERVIEW ***
*   Launches a emulator with command line arguments
*** INPUT ***
*   Takes a string to the executable path, and a string to set the arguments.
*** OUTPUT ***
*   Starts a emulator executable with command line argumenst
******************************************************************************/
class EmulatorLauncher: public QObject
{
    Q_OBJECT
public:
/******************************************************************************
* Constructor
******************************************************************************/
    EmulatorLauncher(QObject* parent = nullptr):QObject(parent),
        mProcess(nullptr)
    {}
/******************************************************************************
*	Destructor
*** OVERVIEW **
* 	Stops and deletes the emulator process if it exists, running or not.
******************************************************************************/
    ~EmulatorLauncher()
    {
        stop();
    }

/******************************************************************************
*	loadEmulator
*** OVERVIEW **
* 	Loads a specific emulator with a game.
*** INPUT **
*   Takes a string of the emulator type, the emulator python name, and the
* path to the game to load.
*** OUTPUT **
*   Returns a bool, if the emulator is
******************************************************************************/
    Q_INVOKABLE bool loadEmulator(QString system,QString Emu,
                                  QString game)
    {
        QDir loadEmu(mEmulatorDir+ QDir::separator() + system + QDir::separator() + Emu);
        bool ret(false);
        if(mProcess)
        {
            qDebug() << "already Running";
        }
        else if((ret = loadEmu.exists(loadEmu.path())))
        {
            mLastPlayedGame = game;
            mLastPlayedSystem = system;
            mProcess = new QProcess;
            mProcess->setProcessChannelMode(QProcess::MergedChannels);
            connect(mProcess,SIGNAL(readyRead()),this,SLOT(processLauncherData()));
            //connect(mProcess,SIGNAL(finished(int)),this,SLOT(ProcessFinished(int)));
            ret = QDir("/usr/bin/python").exists();
            qDebug() << "/usr/bin/python \"" + loadEmu.path() + "\"";
            mProcess->start("/usr/bin/python \"" + loadEmu.path()+"\"");

        }
        return ret;
    }
/******************************************************************************
*	start
*** OVERVIEW **
* 	If no process is running start a new python file to load emulator launcher
* configuration, and command line arguments to send to the emulator.
*** INPUT **
*   Takes a emulator systrm and path to the game.
******************************************************************************/
    Q_INVOKABLE void start(const QString & system, const QString & game)
    {
        mLastPlayedGame = game;
        mLastPlayedSystem = system;
        start();
    }

/******************************************************************************
*	start
*** OVERVIEW **
* 	If no process is running start a new python file to load emulator launcher
* configuration, and command line arguments to send to the emulator.
*** INPUT **
*   Takes a emulator systrm and path to the game.
******************************************************************************/
    Q_INVOKABLE void start()
    {
        //check is the process exists
        if(mProcess != nullptr)
        {
            //check if the process is running
            if(mProcess->state() == QProcess::Running)
                qDebug("Process Already Running!");
            else
            {//clean the proess if it is not running
                delete mProcess;
                mProcess = nullptr;
            }
        }//check if there is no process being used
       if(mProcess == nullptr)
        {//create new process
            //filter emulator core scripts
            QStringList filters;
            filters.append("*.py");
            //look for emulator core scripts
            //QDir loadEmu(QDir::homePath() + "/Desktop/fixbuild/Emulator/" + EmuType);
            QDir loadEmu(mEmulatorDir + QDir::separator() + mLastPlayedSystem + QDir::separator());

            //get a list of emulator core script files

            QStringList foo = loadEmu.entryList(filters);
            //check if there are emulator cores
            qDebug() << loadEmu.path();
            if(foo.isEmpty())
            {
                emit NoEmulatorsFound(loadEmu.path());
                if(!loadEmu.exists())
                    qDebug() << "Unable to find python emulator system configuration files @ " << loadEmu.path();
            }
            else if (foo.count() == 1)
            {//get core information if ther is only one result
                loadEmulator(mLastPlayedSystem,foo.first(),mLastPlayedGame);
            }
            else
            {//if there are multiple core scripts give a list of all cores found
                QStringList emu;
                foreach(QString str, loadEmu.entryList(filters))
                {
                   emu.append(str.replace(".py",""));
                }
                //emit a signal that multiple emulators were found
                emit MultipleEmulatorsFound(emu);
            }
        }
    }
/******************************************************************************
*	setRomsDir
*** OVERVIEW **
* 	Sets the path to all roms to launch.
*** INPUT **
* 	Take a QString by constant reference to set the executable path to.
******************************************************************************/
    Q_INVOKABLE void setRomsDir(const QString& RomsDir)
    {
        mRomsDir = RomsDir;
    }
/******************************************************************************
*	setEmulatorSystemDir
*** OVERVIEW **
* 	Sets the path to the emulator to launch.
*** INPUT **
* 	Take a QString by constant reference to set the executable path to.
******************************************************************************/
    Q_INVOKABLE void setEmulatorSystemDir(const QString& EmuDir)
    {
        mEmulatorDir = EmuDir;
    }

signals:
    void MultipleEmulatorsFound(QStringList emuList);
    void NoEmulatorsFound(QString directory);
    void BadPyDataProcessed();
public slots:
/******************************************************************************
*	stop
*** OVERVIEW **
* 	Stops and deletes the emulator process if it exists, running or not.
*** INPUT **
*   Takes a optional exit code to return.
*** OUTPUT **
*   Return the exit code.
******************************************************************************/
    Q_INVOKABLE int stop(int status = 0)
    {
        if(mProcess != nullptr)
        {
            mProcess->disconnect();
            mProcess->kill();
            mProcess->waitForFinished(3000);
            delete mProcess;
            mProcess = nullptr;
        }
        return status;
    }
/******************************************************************************
*	processLauncherData
*** OVERVIEW **
* 	Process the data read from the python script, and starts the emulator with
* the game fed to start or load.
******************************************************************************/
    void processLauncherData()
    {
        QString str (mProcess->readAll());
        qDebug() << str;
        //check if the python file gave gad data
        if(str.length()<3)
            emit BadPyDataProcessed();
        else
        {//format the data and propigate fields
            QStringList var (str.split('\n'));
            QString launcher = var[1].split('=').last();
            QString tmp(var[2].split('=').last());
            mArguments = tmp.mid(1,tmp.length()-2);
            QString build (launcher+ " " + (mArguments.length()>0?mArguments + " ":"") + "\"" + mRomsDir + "/" + mLastPlayedGame + "\"");
            qDebug() << "Starting process with string" << build;
            stop();
            mProcess = new QProcess;
            connect(mProcess,SIGNAL(finished(int)),this,SLOT(stop(int)));
            mProcess->start(build);
        }
    }

private:
    QProcess* mProcess;
    QString mRomsDir;
    QString mLastPlayedGame;
    QString mLastPlayedSystem;
    QString mEmulatorDir;
    QString mArguments;
};
#endif
