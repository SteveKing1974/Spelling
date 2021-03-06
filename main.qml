import QtQuick 2.6
import QtQuick.Window 2.2
import "."

import Qt.spellingGame.gameController 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    MainPage {
        anchors.fill: parent
        visible: GameControl.gameState != GameControl.StartPage && GameControl.gameState != GameControl.Score
    }

    StartPage {
        anchors.fill: parent
        visible: GameControl.gameState == GameControl.StartPage
    }

    ScorePage {
        anchors.fill: parent
        visible: GameControl.gameState == GameControl.Score
    }
}
