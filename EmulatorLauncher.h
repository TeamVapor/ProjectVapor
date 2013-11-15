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
        mProcess(nullptr), mSystemRomsDir(QDir::homePath() + "Games"
         + QDir::separator() + "Roms" + QDir::separator())
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
        QDir loadEmu(QDir::currentPath() + QDir::separator() + "Emulator" + QDir::separator() + system + QDir::separator() + Emu);

        qDebug() << loadEmu.path();
        bool ret(false);
        if(mProcess)
        {
            qDebug() << "already Running";
        }
        else if(ret = loadEmu.exists())
        {
            mLastPlayedGame = game;
            mLastPlayedSystem = system;
            mProcess = new QProcess;
            mProcess->setProcessChannelMode(QProcess::MergedChannels);
            mProcess->disconnect();
            connect(mProcess,SIGNAL(readyRead()),this,SLOT(processLauncherData()));
            ret = QDir("/usr/bin/python").exists();
            mProcess->start("/usr/bin/python " + loadEmu.path());

            qDebug() << loadEmu.path();
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
    Q_INVOKABLE void start()
    {
        start(mLastPlayedSystem, mLastPlayedGame);
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
            QDir loadEmu(QDir::currentPath() + QDir::separator() + "Emulator" + QDir::separator() + system);

            //get a list of emulator core script files

            QStringList foo = loadEmu.entryList(filters);
            //check if there are emulator cores
            if(foo.isEmpty())
            {
                emit NoEmulatorsFound(loadEmu.path());
                if(!loadEmu.exists())
                    qDebug() << "Unable to find python emulator system configuration files @ " << loadEmu.path();
            }
            else if (foo.count() == 1)
            {//get core information if ther is only one result
                mLastPlayedGame = game;
                mLastPlayedSystem = system;
                loadEmulator(mLastPlayedSystem,foo.first(),game);
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
*	setExecutablePath
*** OVERVIEW **
* 	Sets the path to the emulator to launch.
*** INPUT **
* 	Take a QString by constant reference to set the executable path to.
******************************************************************************/
    Q_INVOKABLE void setSystemRomsDir(const QString& RomsDir)
    {
        mSystemRomsDir = RomsDir;
    }

signals:
    Q_INVOKABLE void MultipleEmulatorsFound(QStringList emuList);
    Q_INVOKABLE void NoEmulatorsFound(QString directory);
    Q_INVOKABLE void BadPyDataProcessed();
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
            mEmulatorDir = var[1].split('=').last();
            QString tmp(var[2].split('=').last());
            mArguments = tmp.mid(1,tmp.length()-2);
            QString build = mEmulatorDir.replace("\"","") + " " + mArguments + " " + mLastPlayedGame;
            qDebug() << "PythonFile Output"<< build;
            stop();
            mProcess = new QProcess;
            connect(mProcess,SIGNAL(finished(int)),this,SLOT(stop()));
            mProcess->start(mEmulatorDir+ " " + (mArguments.length()>0?mArguments + " ":"") + mSystemRomsDir+ "/"+ mLastPlayedSystem + "/" + mLastPlayedGame);
        }
    }
private:
    QProcess* mProcess;
    QString mSystemRomsDir;
    QString mLastPlayedGame;
    QString mLastPlayedSystem;
    QString mEmulatorDir;
    QString mArguments;
};
#endif
