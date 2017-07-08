#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QFontDatabase>
#include <QDebug>
#include <QFile>

#include "gamecontrol.h"

static QObject *game_control_provider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    GameControl *gc = new GameControl();
    return gc;
}

// Third, register the singleton type provider with QML by calling this function in an initialization function.

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QFontDatabase::addApplicationFont(":/Chunky Felt.otf");

    QQmlApplicationEngine engine;
    qmlRegisterSingletonType<GameControl>("Qt.spellingGame.gameController", 1, 0, "GameControl", game_control_provider);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));


    if (engine.rootObjects().isEmpty())
        return -1;


    return app.exec();
}
