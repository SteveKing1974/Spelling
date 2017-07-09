#ifndef LISTMANAGER_H
#define LISTMANAGER_H

#include <QString>
#include <QList>
#include <QStringList>
#include <QObject>

class ListManager : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QStringList allFiles READ allFiles() CONSTANT)
    Q_PROPERTY(QString selectedFile READ selectedFile WRITE setSelectedFile NOTIFY selectedFileChanged)
    Q_PROPERTY(QStringList listsInFile READ listsInFile NOTIFY selectedFileChanged)
    Q_PROPERTY(QString selectedList READ selectedList WRITE setSelectedList NOTIFY selectedListChanged)
    Q_PROPERTY(QStringList wordsInList READ wordsInList NOTIFY selectedListChanged)


public:
    ListManager();

    void loadLists();

    QStringList allFiles() const;

    QString selectedFile() const;
    void setSelectedFile(const QString& val);

    QStringList listsInFile() const;

    QString selectedList() const;
    void setSelectedList(const QString& val);

    QStringList wordsInList() const;

signals:
    void selectedFileChanged();
    void selectedListChanged();

//    QStringList allListsNames(const QString& fileName) const;
//    QStringList getList(const QString& fileName, const QString& name) const;

private:
    QHash<QString, QStringList> m_AllLists;
    QHash<QString, QString> m_AllFiles;

    QString m_SelectedFile;
    QString m_SelectedList;

    void parseFile(QFile& listFile);
    void addEntry(const QString &line, QStringList &listEntries);
};

#endif // LISTMANAGER_H
