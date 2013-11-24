#ifndef EMULATORSETTINGSREADER_H
#define EMULATORSETTINGSREADER_H

#include <QObject>
#include <QDebug>
#include <QProcess>
#include <QException>
#include <QFile>
#include <QHash>
#include <QPair>
#include <QList>
/******************************************************************************
* TYPE: SettingValuePair
*** OVERVIEW ***
*   A setting value pair is comprised of a setting name and value.
*** INPUT ***
*   Takes QString of the name of the setting, and a QString of the value.
******************************************************************************/
            //guiName, CurrentValue
typedef QPair<QString, QString> SettingValuePair;
/******************************************************************************
* TYPE: FullSettingPair
*** OVERVIEW ***
*   A FullSettingPair is comprised of a SettingsValuePair and a SettingIOPair.
******************************************************************************/
typedef QPair<SettingValuePair , QStringList> FullSettingPair;
/******************************************************************************
* TYPE: SettingsHash
*** OVERVIEW ***
*   A Hash of strings of categories to store settings
******************************************************************************/
            //Category, SettingsForCategory
typedef QHash< QString,  QList<FullSettingPair> > SettingsHash;

class EmulatorSettingsReader : public QObject
{
    Q_OBJECT
public:
    explicit EmulatorSettingsReader(QObject *parent = 0);
    ~EmulatorSettingsReader();
    bool ReadSettings(const QString& system, const QString& emuPyFile);
signals:
    void SettingsLoaded(const SettingsHash& settings);
public slots:
    void RxSettingsData();
private:
    void AddSetting(const QString &category, const QString& rawSetting);
    void ProcessSettingsData(const QString& rawData);
    QProcess* mProcess;
    SettingsHash mSettings;
};

#endif // EMULATORSETTINGSREADER_H
