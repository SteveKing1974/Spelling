#include "scorecontrol.h"

#include <QSettings>
#include <QDebug>

static const char* g_Version = "0.2";

ScoreControl::ScoreControl(QObject *parent) :
    QObject(parent),
    m_Settings("Elmsoft", "Spelling")
{
    updateSettings();
}

void ScoreControl::setUsername(const QString &name)
{
    m_Settings.setValue("username", name);
    m_Settings.sync();
    emit usernameChanged();
}

QString ScoreControl::username() const
{
    return m_Settings.value("username").toString();
}

void ScoreControl::listCompleted(const QString &setName, const QString &listName)
{
    const QString doneString = setName + QString::fromLatin1(" - ") + listName;
    QStringList done = completedLists();
    if (!done.contains(doneString))
    {
        done.append(doneString);
        m_Settings.setValue("completed", done);
        emit completedListsChanged();
    }
    m_Settings.sync();
}

QStringList ScoreControl::completedLists() const
{
    return m_Settings.value("completed").toStringList();
}

bool ScoreControl::isListComplete(const QString &setName, const QString &listName) const
{
    const QString doneString = setName + QString::fromLatin1(" - ") + listName;

    return completedLists().contains(doneString);
}

void ScoreControl::updateSettings()
{
    const QVariant currentVersion(g_Version);
    QVariant savedVersion = m_Settings.value("version");

    // To get from no version to 0.1
    if (savedVersion.isNull())
    {
        const QStringList completed = completedLists();
        QStringList newCompleted;
        QStringList::const_iterator i = completed.begin();

        while (i!=completed.end())
        {
            newCompleted.append(QString::fromLatin1("Easy Words 1 - ") + *i);
            ++i;
        }

        m_Settings.setValue("completed", newCompleted);
        savedVersion = QVariant("0.1");
    }

    if (savedVersion == QVariant("0.1"))
    {
        const QStringList completed = completedLists();
        QStringList newCompleted;
        QStringList::const_iterator i = completed.begin();

        while (i!=completed.end())
        {
            QStringList splitVals = (*i).split(" - ");
            newCompleted.append(splitVals[0] + " - " + splitVals[1].trimmed().toLower());
            ++i;
        }

        m_Settings.setValue("completed", newCompleted);
        savedVersion = QVariant("0.2");
    }

    m_Settings.setValue("version", currentVersion);
    m_Settings.sync();
}
