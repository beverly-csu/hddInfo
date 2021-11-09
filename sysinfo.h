#ifndef SYSINFO_H
#define SYSINFO_H

#include <QObject>
#include <QStorageInfo>
#include <QSysInfo>
#include <QDebug>
#include <QString>
#include <QList>
#include <QMap>

class PartitionData
{
public:
    PartitionData(QString name, qreal total, qreal occupied, qreal free, QString type);
    QString partitionName;
    qreal totalSize;
    qreal occupiedSize;
    qreal freeSize;
    QString filesystemType;
};

class SysInfo : public QObject
{
    Q_OBJECT
public:
    explicit SysInfo(QObject *parent = nullptr);
    QList<QString> getPartitionList();
    PartitionData* getPartitionData(QString path);

private:
    void scanPartitions();

private:
    QStorageInfo *storage;
    QList<QString> partitionsList;
    QMap<QString, PartitionData*> storages;

signals:

};

#endif // SYSINFO_H
