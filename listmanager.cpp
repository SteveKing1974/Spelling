#include "listmanager.h"

#include <QDir>
#include <QFile>
#include <QDebug>

enum FileReadState {
    eWaitingForHeader,
    eReadingHeader,
    eWaitingForList,
    eReadingList
} ;

ListManager::ListManager()
{

}

void ListManager::loadLists()
{
    QDir resourceBase(":/Resources");
    QFileInfoList allListFiles = resourceBase.entryInfoList(QStringList() << QString("*.txt"), QDir::Files);

    QFileInfoList::const_iterator i = allListFiles.begin();
    while (i!=allListFiles.end())
    {
        qDebug() << "File is" << i->absoluteFilePath();

        QFile listFile(i->absoluteFilePath().toLatin1());

        if (listFile.open(QIODevice::ReadOnly))
        {
            parseFile(listFile);
        }
        ++i;
    }

    //qDebug() << m_AllLists.keys();

    //qDebug() << m_AllLists;
}

QStringList ListManager::allListsNames() const
{
    return m_AllLists.keys();
}

QStringList ListManager::getList(const QString &name) const
{
    return m_AllLists.value(name);
}

void ListManager::addEntry(const QString &line, QStringList& listEntries)
{
    QList<QString> splitVals = line.split('.', QString::SkipEmptyParts);

    if (splitVals.count()==2)
    {
        listEntries.append(splitVals[1].trimmed());
    }
}

void ListManager::parseFile(QFile &listFile)
{
    FileReadState eState = eWaitingForHeader;

    QString listName;
    QStringList listContent;

    listFile.readLine();

    while (!listFile.atEnd())
    {
        QString l = QString(listFile.readLine());
        l.remove('\r');
        l.remove('\n');

        switch (eState)
        {
        case eWaitingForHeader:
            if (!l.isEmpty())
            {
                eState = eReadingHeader;
            }
            break;

        case eReadingHeader:
            if (!l.isEmpty())
            {
                listName = QString(l);
                eState = eWaitingForList;
            }
            break;

        case eWaitingForList:
            if (!l.isEmpty())
            {
                eState = eReadingList;
                addEntry(l, listContent);
            }
            break;

        case eReadingList:
            if (l.isEmpty())
            {
                eState = eWaitingForHeader;

                if (!listContent.isEmpty())
                {
                    QString nameToAdd = listName;
                    int numberToAdd = 2;
                    while (m_AllLists.contains(nameToAdd))
                    {
                        nameToAdd = listName + QString(" (%1)").arg(numberToAdd);
                        ++numberToAdd;
                    }

                    m_AllLists.insert(nameToAdd, listContent);
                    listContent.clear();
                    listName.clear();
                }
            }
            else
            {
                addEntry(l, listContent);
            }
            break;

        }
    }
}


