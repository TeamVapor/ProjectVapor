#ifndef EMULATORLAUNCHER_H
#define EMULATORLAUNCHER_H
#include "QObject"
#include "QString"
#include "QProcess"
/******************************************************************************
* Author: Aaron Lindberg
* Class: EmulatorLauncher
* Created: 10/16/2013           Modified: 10/16/2013
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
    EmulatorLauncher(QString executablePath = "zsnes", QString arguments = 
    "-m -v 14 /home/jack/ROMS/SuperMetroid.smc", QObject* parent = nullptr):
	mExecutablePath(executablePath), mArguments(arguments), 
	mProcess(nullptr), QObject(parent)
	{}
/******************************************************************************
*	
******************************************************************************/
    ~EmulatorLauncher()
    {
        delete mProcess;
        mProcess = nullptr;
    }

    Q_INVOKABLE void start()
    {

        if(mProcess != nullptr)
        {
            if(mProcess->state() == QProcess::Running)
                qDebug("Process Already Running!");
            else
            {
                mProcess->close();
                delete mProcess;
                mProcess = nullptr;
            }
        }
       if(mProcess == nullptr)
        {
            mProcess = new QProcess;
            mProcess->start(mExecutablePath + " " + mArguments);

        }
    }

    Q_INVOKABLE void stop()
    {
        if(mProcess != nullptr)
        {
            mProcess->kill();
            delete mProcess;
            mProcess = nullptr;
        }
    }

    Q_INVOKABLE void setExecuteablePath(const QString& exePath)
    {
        mExecutablePath = exePath;
    }

    Q_INVOKABLE void setArguments(const QString& args)
    {
        mArguments = args;
    }

   /* Q_INVOKABLE bool setSetting(QString settingName, QString value)
    {

    }*/

    Q_INVOKABLE const QString& getArguments()
    {
        return mArguments;
    }

    Q_INVOKABLE const QString& getExecutablePath()
    {
        return mExecutablePath;
    }

private:
    QProcess* mProcess;
    QString mExecutablePath;
    QString mArguments;
};
#endif
