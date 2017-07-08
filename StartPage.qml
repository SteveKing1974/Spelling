import QtQuick 2.0
import QtQuick.Controls 2.2

import Qt.spellingGame.gameController 1.0


Item {
    ComboBox {
        id: wordListSelect
        width: parent.width*0.6
        height: parent.height*0.3

        anchors.top: parent.top
        anchors.topMargin: 20

        anchors.horizontalCenter: parent.horizontalCenter

        font.family: "Chunky Felt"
        font.pointSize: 24

        model: GameControl.allLists
    }

    Button {
        width: parent.width*0.6
        height: parent.height*0.1

        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20

        anchors.horizontalCenter: parent.horizontalCenter

        font.family: "Chunky Felt"
        font.pointSize: 24

        text: "Start"
        onClicked: GameControl.nextState(wordListSelect.currentText)
    }
}
