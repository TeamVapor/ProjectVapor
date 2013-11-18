#ifndef APPLICATIONSETTINGS_H
#define APPLICATIONSETTINGS_H

#include <QObject>
class QDir;
class ApplicationSettings : public QObject
{
    Q_OBJECT
public:
    explicit ApplicationSettings(QObject *parent = 0);
    Q_INVOKABLE QString getUserName(){return mUserName;}
    Q_INVOKABLE QString getEmulatorDirectory(){return mEmulatorDirectory;}
    Q_INVOKABLE QString getRomDirectory(){return mRomDirectory;}
    Q_INVOKABLE QString getCoverDirectory(){return mCoverDirectory;}
    Q_INVOKABLE QString getPosterDirectory(){return mPosterDirectory;}
    Q_INVOKABLE QString getVideoDirectory(){return mVideoDirectory;}

public slots:
    void setUserName(QString username){mUserName = username;}
    void setEmulatorDirectory(QString emulator_dir){mEmulatorDirectory = emulator_dir;}
    void setRomDirectory(QString rom_dir){mRomDirectory = rom_dir;}
    void setCoverDirectory(QString cover_dir){mCoverDirectory = cover_dir;}
    void setPosterDirectory(QString poster_dir){mPosterDirectory = poster_dir;}
    void setVideoDirectory(QString video_dir){mVideoDirectory = video_dir;}


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
