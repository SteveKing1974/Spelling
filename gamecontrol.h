#ifndef GAMECONTROL_H
#define GAMECONTROL_H

#include <QObject>

#include "listmanager.h"
#include "scorecontrol.h"

class QTextToSpeech;

class GameControl : public QObject
{
    Q_OBJECT

    Q_PROPERTY(GameState gameState READ gameState NOTIFY gameStateChanged)

    Q_PROPERTY(QStringList allSets READ allSets CONSTANT)
    Q_PROPERTY(QStringList listsInSet READ listsInSet NOTIFY currentSetChanged)
    Q_PROPERTY(QString currentSet READ currentSet WRITE setCurrentSet NOTIFY currentSetChanged)

    Q_PROPERTY(QString currentWord READ currentWord NOTIFY currentWordChanged)
    Q_PROPERTY(QString currentList READ currentList NOTIFY currentListChanged)

    Q_PROPERTY(QString currentUser READ currentUser NOTIFY currentUserChanged)

    Q_PROPERTY(QStringList completedLists READ completedLists NOTIFY completedListsChanged)

public:

    enum GameState {
        EnterName,
        StartPage,
        Look,
        Say,
        Write,
        Correct,
        Wrong,
        ListComplete,
        Score
    } ;
    Q_ENUM(GameState)


    explicit GameControl(QObject *parent = nullptr);

    GameState gameState() const;
    QStringList allSets() const;
    QStringList listsInSet() const;

    QString currentSet() const;
    void setCurrentSet(const QString& val);

    QString currentWord() const;
    QString currentList() const;
    QString currentUser() const;

    QStringList completedLists() const;

signals:
    void gameStateChanged();
    void currentWordChanged();
    void completedListsChanged();
    void currentSetChanged();
    void currentListChanged();
    void currentUserChanged();

public slots:
    bool isListCompleted(const QString& listName) const;

    void nextState(const QString& typedVal);
    void showScores();
    void sayWord() const;

private:
    QTextToSpeech *m_speech;

    ListManager m_WordLists;
    ScoreControl m_Scorer;
    GameState m_State;
    int m_CurrentIndex;
};

#endif // GAMECONTROL_H
