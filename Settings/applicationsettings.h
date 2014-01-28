#ifndef APPLICATIONSETTINGS_H
#define APPLICATIONSETTINGS_H

#include <QObject>
class QDir;
class ApplicationSettings : public QObject
{
    Q_OBJECT
public:
    explicit ApplicationSettings(QObject *parent = 0);
    ApplicationSettings(const ApplicationSettings& right);
    Q_INVOKABLE QString getUserName(){return mUserName;}
    Q_INVOKABLE QString getEmulatorDirectory(){return mEmulatorDirectory;}
    Q_INVOKABLE QString getRomDirectory(){return mRomDirectory;}
    Q_INVOKABLE QString getInterfacesDirectory(){return mInterfacesDirectory;}
    Q_INVOKABLE QString getCoverDirectory(){return mCoverDirectory;}
    Q_INVOKABLE QString getPosterDirectory(){return mPosterDirectory;}
    Q_INVOKABLE QString getVideoDirectory(){return mVideoDirectory;}
    Q_INVOKABLE bool    getUseNSD(){return mUseNetworkDiscovery;}
    ApplicationSettings& operator= (const ApplicationSettings& right);
public slots:
    void setUserName(QString username){mUserName = username;}
    void setEmulatorDirectory(QString emulator_dir){mEmulatorDirectory = emulator_dir;}
    void setRomDirectory(QString rom_dir){mRomDirectory = rom_dir;}
    void setCoverDirectory(QString cover_dir){mCoverDirectory = cover_dir;}
    void setInterfacesDirectory(QString interfaces_dir){mInterfacesDirectory = interfaces_dir;}
    void setPosterDirectory(QString poster_dir){mPosterDirectory = poster_dir;}
    void setVideoDirectory(QString video_dir){mVideoDirectory = video_dir;}
    void setUseNSD(bool use_nsd){mUseNetworkDiscovery = use_nsd;}

signals:
    void InterfacesDirectoryChanged(QString interface_dir);

private:
    QString mUserName;
    QString mEmulatorDirectory;
    QString mRomDirectory;
    QString mCoverDirectory;
    QString mInterfacesDirectory;
    QString mPosterDirectory;
    QString mVideoDirectory;
    bool    mUseNetworkDiscovery;
    void writeSettingsFile(QDir &dir);
    void loadSettings(QDir &dir);

};

#endif // APPLICATIONSETTINGS_H
