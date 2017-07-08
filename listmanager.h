#ifndef LISTMANAGER_H
#define LISTMANAGER_H

#include <QString>
#include <QList>
#include <QStringList>

class ListManager
{
public:
    ListManager();

    void loadLists();

    QStringList allListsNames() const;

    QStringList getList(const QString& name) const;

private:
    QHash<QString, QStringList> m_AllLists;

    void parseFile(QFile& listFile);
    void addEntry(const QString &line, QStringList &listEntries);
};

#endif // LISTMANAGER_H
