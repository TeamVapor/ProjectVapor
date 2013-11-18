#ifndef APPLICATIONSETTINGS_H
#define APPLICATIONSETTINGS_H

#include <QObject>
class QDir;
class ApplicationSettings : public QObject
{
    Q_OBJECT
public:
    explicit ApplicationSettings(QObject *parent = 0);
    QString getUserName(){return mUserName;}
    QString getEmulatorDirectory(){return mEmulatorDirectory;}
    QString getRomDirectory(){return mRomDirectory;}
    QString getCoverDirectory(){return mCoverDirectory;}
    QString getPosterDirectory(){return mPosterDirectory;}
    QString getVideoDirectory(){return mVideoDirectory;}
    QString setUserName(QString username){return mUserName = username;}
    QString setEmulatorDirectory(QString emulator_dir){return mEmulatorDirectory = emulator_dir;}
    QString setRomDirectory(QString rom_dir){return mRomDirectory = rom_dir;}
    QString setCoverDirectory(QString cover_dir){return mCoverDirectory = cover_dir;}
    QString setPosterDirectory(QString poster_dir){return mPosterDirectory = poster_dir;}
    QString setVideoDirectory(QString video_dir){return mVideoDirectory = video_dir;}

signals:

public slots:

private:
    QString mUserName;
    QString mEmulatorDirectory;
    QString mRomDirectory;
    QString mCoverDirectory;
    QString mPosterDirectory;
    QString mVideoDirectory;

    void writeSettingsFile(QDir &dir);
    void loadSettings(QDir &dir);

};

#endif // APPLICATIONSETTINGS_H
