#ifndef SCORECONTROL_H
#define SCORECONTROL_H

#include <QObject>
#include <QSettings>

class ScoreControl : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString username READ username WRITE setUsername NOTIFY usernameChanged)
    Q_PROPERTY(QStringList completedLists READ completedLists NOTIFY completedListsChanged)


public:
    explicit ScoreControl(QObject *parent = nullptr);

    void setUsername(const QString& name);
    QString username() const;

    void listCompleted(const QString& setName, const QString& listName);

    QStringList completedLists() const;

    bool isListComplete(const QString& setName, const QString& listName) const;

signals:
    void usernameChanged();
    void completedListsChanged();

private:
    void updateSettings();

    QSettings m_Settings;
};

#endif // SCORECONTROL_H
