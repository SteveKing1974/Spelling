#include "gamecontrol.h"

#include <QDebug>
#include <QTextToSpeech>

GameControl::GameControl(QObject *parent) :
    QObject(parent),
    m_State(GameControl::StartPage),
    m_CurrentIndex(0)
{
    m_speech = new QTextToSpeech(this);

    if (m_Scorer.username().isEmpty())
    {
        m_State = EnterName;
    }

    m_WordLists.loadLists();
    m_WordLists.setSelectedFile(allSets().at(0));

    connect(&m_Scorer, SIGNAL(completedListsChanged()), this, SIGNAL(completedListsChanged()));
    connect(&m_Scorer, SIGNAL(usernameChanged()), this, SIGNAL(currentUserChanged()));

    connect(&m_WordLists, SIGNAL(selectedFileChanged()), this, SIGNAL(currentSetChanged()));

    connect(&m_WordLists, SIGNAL(selectedListChanged()), this, SIGNAL(currentSetChanged()));
}

GameControl::GameState GameControl::gameState() const
{
    return m_State;
}

QStringList GameControl::allSets() const
{
    QStringList sets = m_WordLists.allFiles();
    std::sort(sets.begin(), sets.end());
    return sets;
}

QStringList GameControl::listsInSet() const
{
    QStringList allNames = m_WordLists.listsInFile();
    std::sort(allNames.begin(), allNames.end());
    return allNames;
}

QString GameControl::currentSet() const
{
    return m_WordLists.selectedFile();
}

void GameControl::setCurrentSet(const QString& val)
{
    m_WordLists.setSelectedFile(val);
}


QString GameControl::currentWord() const
{
    const QStringList list = m_WordLists.wordsInList();

    if (list.length()>m_CurrentIndex)
    {
        return list.at(m_CurrentIndex);
    }

    return QString("-");
}

QString GameControl::currentList() const
{
    return m_WordLists.selectedList();
}

QString GameControl::currentUser() const
{
    return m_Scorer.username();
}

QStringList GameControl::completedLists() const
{
    return m_Scorer.completedLists();
}

bool GameControl::isListCompleted(const QString &listName) const
{
    return m_Scorer.isListComplete(m_WordLists.selectedFile(), listName);
}

void GameControl::nextState(const QString &typedVal)
{
    bool wordValChanged = false;
    bool stateValChanged = true;

    switch (m_State)
    {
    case EnterName:
        if (!typedVal.isEmpty())
        {
            m_Scorer.setUsername(typedVal);
            m_State = StartPage;
        }
        break;
    case StartPage:
        if (m_WordLists.listsInFile().contains(typedVal))
        {
            m_WordLists.setSelectedList(typedVal);
            m_CurrentIndex = 0;
            m_State = Look;
            wordValChanged = true;
        }
        else
        {
            stateValChanged = false;
        }
        break;

    case Look:
        m_State = Say;
        m_speech->say(currentWord());
        break;

    case Say:
        m_State = Write;
        break;

    case Write:
        if (currentWord().compare(typedVal, Qt::CaseInsensitive) == 0)
        {
            m_State = Correct;
        }
        else
        {
            m_State = Wrong;
        }
        break;

    case Correct:
        ++m_CurrentIndex;
        if (m_CurrentIndex>=m_WordLists.selectedList().count())
        {
            m_Scorer.listCompleted(m_WordLists.selectedFile(), m_WordLists.selectedList());
            m_CurrentIndex = 0;
            m_State = ListComplete;
        }
        else
        {
            m_State = Look;
            wordValChanged = true;
        }
        break;

    case Wrong:
        m_State = Look;
        break;

    case ListComplete:
        m_State = StartPage;
        break;

    case Score:
        m_State = StartPage;
        break;
    }

    if (wordValChanged)
    {
        emit currentWordChanged();
    }

    if (stateValChanged)
    {
        emit gameStateChanged();
    }
}

void GameControl::showScores()
{
    m_State = Score;
    emit gameStateChanged();
}

void GameControl::sayWord() const
{
    m_speech->say(currentWord());
}
