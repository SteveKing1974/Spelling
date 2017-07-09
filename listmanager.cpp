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

ListManager::ListManager() : QObject(0),
    m_SelectedFile(""),
    m_SelectedList("")
{

}

void ListManager::loadLists()
{
    QDir resourceBase(":/Resources");
    QFileInfoList allListFiles = resourceBase.entryInfoList(QStringList() << QString("*.txt"), QDir::Files);

    QFileInfoList::const_iterator i = allListFiles.begin();
    while (i!=allListFiles.end())
    {
        QFile listFile(i->absoluteFilePath());

        if (listFile.open(QIODevice::ReadOnly))
        {
            QString topLine = QString(listFile.readLine());
            topLine.remove('\r');
            topLine.remove('\n');

            if (topLine.isEmpty() || m_AllFiles.contains(topLine))
            {
                qDebug() << "Invalid file " << listFile.fileName();
            }
            else
            {
                m_AllFiles.insert(topLine, i->absoluteFilePath());
            }
        }
        ++i;
    }

    //qDebug() << m_AllLists.keys();

    //qDebug() << m_AllLists;
}


QStringList ListManager::allFiles() const
{
    return m_AllFiles.keys();
}

QString ListManager::selectedFile() const
{
    return m_SelectedFile;
}

void ListManager::setSelectedFile(const QString &val)
{
    if ((val != m_SelectedFile) && m_AllFiles.contains(val))
    {
        m_SelectedFile = val;
        m_AllLists.clear();
        m_SelectedList.clear();

        QFile listFile(m_AllFiles.value(m_SelectedFile));
        listFile.open(QIODevice::ReadOnly);
        parseFile(listFile);

        emit selectedFileChanged();
        emit selectedListChanged();
    }
}

QStringList ListManager::listsInFile() const
{
    return m_AllLists.keys();
}

QString ListManager::selectedList() const
{
    return m_SelectedList;
}

void ListManager::setSelectedList(const QString &val)
{
    if ((val != m_SelectedList) && m_AllLists.contains(val))
    {
        m_SelectedList = val;
        emit selectedListChanged();
    }
}

QStringList ListManager::wordsInList() const
{
    return m_AllLists.value(m_SelectedList);
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
                listName = QString(l).trimmed().toLower();
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
            if (!l.isEmpty())
            {
                addEntry(l, listContent);
            }

            if (l.isEmpty() || listFile.atEnd())
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

            break;

        }
    }
}


