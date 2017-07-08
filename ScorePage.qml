import QtQuick 2.0
import QtQuick.Controls 2.2

import Qt.spellingGame.gameController 1.0


Item {
    Rectangle {
        width: parent.width*0.6
        height: parent.height*0.3

        anchors.top: parent.top
        anchors.topMargin: 20

        border.color: 'black'

        anchors.horizontalCenter: parent.horizontalCenter

        Text {
            font.family: "Chunky Felt"
            font.pointSize: 24
            anchors.centerIn: parent

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter

            text: "Well done, you finished that level"
        }
    }

    Button {
        width: parent.width*0.6
        height: parent.height*0.1

        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20

        anchors.horizontalCenter: parent.horizontalCenter

        font.family: "Chunky Felt"
        font.pointSize: 24

        text: "Another go"
        onClicked: GameControl.nextState(wordListSelect.currentText)
    }
}
