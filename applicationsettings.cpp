#include "applicationsettings.h"
#include <QDir>
#include <QDebug>
ApplicationSettings::ApplicationSettings(QObject *parent) :
    QObject(parent)
{

    //check if file exists
    QString app_data_path(QDir::homePath() + '/' + ".vaporarcade/");
    QDir dir(app_data_path);
    qDebug() << app_data_path;
    if(!dir.exists("user.ini"))
    {
        // if it doesnt write the blank
        writeSettingsFile(dir);
    }
    loadSettings(dir); // load the setting values

}

void ApplicationSettings::writeSettingsFile(QDir&  dir)
{
    dir.cdUp();
    dir.mkdir(".vaporarcade");
    dir.cd(".vaporarcade");
    QFile settings(dir.absolutePath() + "/user.ini",this);
    settings.open(QIODevice::WriteOnly);
    settings.write(QString("Username=\"" + mUserName +
                   "\"\nEmulatorDir=\"" + mEmulatorDirectory +
                   "\"\nRomDir=\"" + mRomDirectory +
                   "\"\nCoverDir=\"" + mCoverDirectory +
                   "\"\nPosterDir=\"" + mPosterDirectory +
                   "\"\nVideoDir=\"" + mVideoDirectory + "\"").toLocal8Bit());
    settings.close();
}

void ApplicationSettings::loadSettings(QDir& dir)
{
    QFile settings(dir.absolutePath() + "/user.ini",this);
    settings.open(QIODevice::ReadOnly); // open and read in data
    QStringList strlst(QString(settings.readAll()).split("\n"));
    settings.close();
    // for each setting value
    // get the whole line, split it on the '=',
    // grab the second half of the string, removing the  ""s
    mUserName = strlst.at(0);
    mUserName = mUserName.split('=')[1].replace("\"","");
    mEmulatorDirectory = strlst.at(1);
    mEmulatorDirectory = mEmulatorDirectory.split('=')[1].replace("\"","");
    mRomDirectory = strlst.at(2);
    mRomDirectory = mRomDirectory.split('=')[1].replace("\"","");
    mCoverDirectory = strlst.at(3);
    mCoverDirectory = mCoverDirectory.split('=')[1].replace("\"","");
    mPosterDirectory = strlst.at(4);
    mPosterDirectory = mPosterDirectory.split('=')[1].replace("\"","");
    mVideoDirectory = strlst.at(5);
    mVideoDirectory = mVideoDirectory.split('=')[1].replace("\"","");
}
