#ifndef GAMECONTROL_H
#define GAMECONTROL_H

#include <QObject>

#include "listmanager.h"

class GameControl : public QObject
{
    Q_OBJECT

    Q_PROPERTY(GameState gameState READ gameState NOTIFY gameStateChanged)
    Q_PROPERTY(QStringList allLists READ allLists CONSTANT)
    Q_PROPERTY(QString currentWord READ currentWord NOTIFY currentWordChanged)

public:

    enum GameState {
        StartPage,
        Look,
        Say,
        Write,
        Correct,
        Wrong,
        Score
    } ;
    Q_ENUM(GameState)


    explicit GameControl(QObject *parent = nullptr);

    GameState gameState() const;
    QStringList allLists() const;
    QString currentWord() const;

signals:
    void gameStateChanged();
    void currentWordChanged();

public slots:
    void nextState(const QString& typedVal);

private:
    ListManager m_WordLists;
    GameState m_State;
    int m_CurrentIndex;
    QString m_CurrentList;
};

#endif // GAMECONTROL_H
