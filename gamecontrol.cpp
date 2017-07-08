#include "gamecontrol.h"

#include <QDebug>

GameControl::GameControl(QObject *parent) :
    QObject(parent),
    m_State(GameControl::StartPage),
    m_CurrentIndex(0),
    m_CurrentList("")
{
    m_WordLists.loadLists();
}

GameControl::GameState GameControl::gameState() const
{
    return m_State;
}

QStringList GameControl::allLists() const
{
    QStringList allNames = m_WordLists.allListsNames();
    std::sort(allNames.begin(), allNames.end());
    return allNames;
}

QString GameControl::currentWord() const
{
    if (m_WordLists.allListsNames().contains(m_CurrentList))
    {
        return m_WordLists.getList(m_CurrentList).at(m_CurrentIndex);
    }

    return QString("-");
}

void GameControl::nextState(const QString &typedVal)
{
    bool wordValChanged = false;
    bool stateValChanged = true;

    switch (m_State)
    {
    case StartPage:
        if (m_WordLists.allListsNames().contains(typedVal))
        {
            m_CurrentList = typedVal;
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
        if (m_CurrentIndex>=m_WordLists.getList(m_CurrentList).count())
        {
            m_CurrentIndex = 0;
            m_State = Score;
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
