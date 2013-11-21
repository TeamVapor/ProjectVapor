#include "EmulatorCore.h"
#include <QException>
/******************************************************************************
* Default Constructor
******************************************************************************/
EmulatorCore::EmulatorCore(QObject* parent):QObject(parent),
              mProcess(nullptr){}
/******************************************************************************
* Destructor - cleans up any processes allocated to the Emulator core
******************************************************************************/
EmulatorCore::~EmulatorCore()
{stop();}
/******************************************************************************
*	loadEmulator
*** OVERVIEW **
* 	Loads a specific emulator system python with a game.
*** INPUT **
*   Takes a string of the emulator system type, the emulator python file name,
* and the path to the game to load after system information is gathered.
*** OUTPUT **
*   Returns a boolean value. If the emulator is python file was started with
* python true is returned, however in the event that the python file could not
* be started the return value is false.
******************************************************************************/
bool EmulatorCore::loadEmulator(QString system,QString Emu, QString game)
{
    QString loadEmu(mEmulatorDir+ '/' + system + '/' + Emu);
    bool ret(false);//Return value
    if(mProcess)//Check for a running process
    {
        qDebug() << "already Running";
    }
    else if((ret = QFile(loadEmu).exists()))//check if the python file exists
    {
        //check if the python interpreter is installed
        if((ret = QFile("/usr/bin/python").exists()))
        {
    //update last played system and game to start after launcher configuration
            mLastPlayedGame = game;
            mLastPlayedSystem = system;
            mProcess = new QProcess;
            mProcess->setProcessChannelMode(QProcess::MergedChannels);
            connect(mProcess,SIGNAL(readyRead()),this,SLOT(processLauncherData()));
            try
            {
                qDebug() << "System Loading using /usr/bin/python \"" + loadEmu + "\"";
                mProcess->start("/usr/bin/python \"" + loadEmu + "\"");
                emit EmulatorStarted(mLastPlayedSystem,mLastPlayedGame);
            }catch (const QException& etc)
            {
                qDebug() << etc.what();
            }
        }else
        {
            qDebug() << "Unable to find python interpreter @ /usr/bin/python";
        }
    }else
    {
        qDebug() << "Unable to Locate the python file @\"" + loadEmu + "\"";
    }
    return ret;//indicate if the launcher configuration is started
}
/******************************************************************************
*	start
*** OVERVIEW **
* 	If no process is running start a new python file to load emulator launcher
* configuration, and command line arguments to send to the emulator.
*** INPUT **
*   Takes a string of the emulator system and a string of the path to the game.
*** OUTPUT ***
*   On completion of loading emulator launcher configuration
******************************************************************************/
void EmulatorCore::start(const QString & system, const QString & game)
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
        QDir loadEmu(mEmulatorDir + QDir::separator() + system + QDir::separator());
        //get a list of emulator core script files
        QStringList emuList = loadEmu.entryList(filters);
        //check if there are emulator cores
        if(emuList.isEmpty())
        {
            emit NoEmulatorsFound(loadEmu.path());
            if(!loadEmu.exists())
                qDebug() << "Unable to find python emulator system configuration files @ " << loadEmu.path();
        }
        else if (emuList.count() == 1)
        {//get core information if ther is only one result
            loadEmulator(system,emuList.first(),game);
        }
        else
        {//if there are multiple core scripts give a list of all cores found
            QStringList emus;
            foreach(QString str, emuList)
            {
               emus.append(str.replace(".py",""));
            }
            //emit a signal that multiple emulators were found
            qDebug() << "Multiple emulator system configuration python files found";
            emit MultipleEmulatorsFound(emus);
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
void EmulatorCore::setRomsDir(const QString& RomsDir)
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
void EmulatorCore::setEmulatorSystemDir(const QString& EmuDir)
{
    mEmulatorDir = EmuDir;
}
void EmulatorCore::emuStopped(int status)
{
    emit EmulatorStopped();
    qDebug() << "Emulator " + mLastPlayedSystem + " Stopped Playing " + mLastPlayedGame;
    stop(status);
}

/******************************************************************************
*	stop
*** OVERVIEW **
* 	Stops and deletes the emulator process if it exists, running or not.
*** INPUT **
*   Takes a optional exit code to return.
*** OUTPUT **
*   Return the exit code.
******************************************************************************/
int EmulatorCore::stop(int status)
{
    if(mProcess != nullptr)
    {

        mProcess->disconnect();
        mProcess->close();
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
void EmulatorCore::processLauncherData()
{
    QString str (mProcess->readAll());
    qDebug() << str;
    //check if the python file gave gad data
    if(!str.startsWith("$%$"))
    {
        emit BadPyDataProcessed();
        qDebug() << "Python File is not in the correct format.";
    }
    else
    {//format the data and propigate fields
        QStringList dataIn (str.split('\n'));
        if(dataIn.length() < 3)
        {
            qDebug() << "Error - Python file didn't contain enough data or in a bad format.";
            emit BadPyDataProcessed();
        }
        else
        {
            QString launcher = dataIn[1].split('=').last();
            qDebug() << QFile(launcher).exists();
            QStringList Arg(dataIn[2].split('=').last().split("\""));
            if(Arg.length() <= 1)
            {
                qDebug() << "Arguments are Empty";
                mArguments = "";
            }else
            {
                mArguments = Arg[1];
            }
            QString build (launcher+ " " + (mArguments.length()>0?mArguments + " ":"") + "\"" + mRomsDir + "/" + mLastPlayedGame + "\"");
            qDebug() << "Trying to starting the process with string" << build;
            this->stop(0);

            if(QFile(launcher.split("\"")[1]).exists())
            {
                if(QFile(mRomsDir + "/" + mLastPlayedGame).exists())
                {
                    mProcess = new QProcess;
                    connect(mProcess,SIGNAL(finished(int)),this,SLOT(emuStopped(int)));
                    try
                    {
                        mProcess->start(build);
                        emit EmulatorStarted(mLastPlayedSystem,mLastPlayedGame);
                        qDebug() << "Emulator " + mLastPlayedSystem + " Started Playing " + mLastPlayedGame;
                    }catch(const QException& exc)
                    {
                        qDebug() << exc.what();
                    }
                }
                else
                {
                    qDebug() << "Error - A emulator for " + mLastPlayedSystem
                                + " failed to find the game to launch @ \""
                                + mRomsDir + "/" + mLastPlayedGame + "\"";
                }
            }else
            {
                qDebug() << "Error - Unable to find the emulator core "
                            + launcher + " specified by the python file";
            }

        }
    }
}
