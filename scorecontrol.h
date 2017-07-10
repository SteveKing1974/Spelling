#ifndef SCORECONTROL_H
#define SCORECONTROL_H

#include <QObject>
#include <QSettings>

class ScoreControl : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString username READ username WRITE setUsername NOTIFY usernameChanged)
    Q_PROPERTY(QStringList completedLists READ completedLists NOTIFY completedListsChanged)
    Q_PROPERTY(QStringList completedSets READ completedSets NOTIFY completedSetsChanged)


public:
    explicit ScoreControl(QObject *parent = nullptr);

    void setUsername(const QString& name);
    QString username() const;

    void listCompleted(const QString& setName, const QString& listName);
    void testCompleted(const QString& setName);

    QStringList completedLists() const;

    QStringList completedSets() const;

    bool isListComplete(const QString& setName, const QString& listName) const;

signals:
    void usernameChanged();
    void completedListsChanged();
    void completedSetsChanged();

private:
    void updateSettings();

    QSettings m_Settings;
};

#endif // SCORECONTROL_H
