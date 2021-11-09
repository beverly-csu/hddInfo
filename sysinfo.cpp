#include "sysinfo.h"

SysInfo::SysInfo(QObject *parent) : QObject(parent)
{
    scanPartitions();
}

QList<QString> SysInfo::getPartitionList()
{
    return partitionsList;
}

PartitionData* SysInfo::getPartitionData(QString path)
{
    return storages[path];
}

void SysInfo::scanPartitions()
{
    if (storages.size() != 0)
    {
        storages.clear();
        partitionsList.clear();
    }
    QString alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (auto symbol : alphabet) {
        auto path = symbol + ':';
        storage = new QStorageInfo(path);
        if (storage->bytesTotal() != -1) {
            partitionsList.append(path);
            storages[path] = new PartitionData(
                        storage->displayName(),
                        qRound(storage->bytesTotal() * 1.0 / (1024 * 1024 * 1024) * 100) * 1.0 / 100,
                        qRound(((storage->bytesTotal() * 1.0 / (1024 * 1024 * 1024)) - (storage->bytesFree() / (1024 * 1024 * 1024))) * 100)  * 1.0 / 100,
                        qRound(storage->bytesFree() * 1.0 / (1024 * 1024 * 1024) * 100) * 1.0 / 100,
                        QString::fromUtf8(storage->fileSystemType())
                        );
            //qDebug() << storages[path]->filesystemType << " " << storages[path]->partitionName << " " << storages[path]->totalSize << " " <<
            //            storages[path]->occupiedSize << " " << storages[path]->freeSize;
        }
    }
    delete storage;
}

PartitionData::PartitionData(QString name, qreal total, qreal occupied, qreal free, QString type) :
    partitionName(name),
    totalSize(total),
    occupiedSize(occupied),
    freeSize(free),
    filesystemType(type)
{

}
