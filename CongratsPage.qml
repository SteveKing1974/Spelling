import QtQuick 2.0
import QtQuick.Controls 2.2

import Qt.spellingGame.gameController 1.0


Item {
    Text {
        id: congratsText

        font.family: "Chunky Felt"
        font.pointSize: 24

        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter

        height: parent.height*0.2

        anchors.top: parent.top
        anchors.margins: 20
        anchors.left: parent.left
        anchors.right: parent.right

        wrapMode: Text.WordWrap

        text: "Excellent!"
    }

    Text {
        font.family: "Chunky Felt"
        font.pointSize: 24

        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter

        height: parent.height*0.2

        anchors.top: congratsText.bottom
        anchors.margins: 20
        anchors.left: parent.left
        anchors.right: parent.right

        wrapMode: Text.WordWrap

        text: "You completed word list - " + GameControl.currentList
    }

    Button {
        id: nextButton
        width: parent.width*0.6
        height: parent.height*0.1

        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20

        anchors.horizontalCenter: parent.horizontalCenter

        font.family: "Chunky Felt"
        font.pointSize: 24

        text: "Try another list"
        onClicked: GameControl.nextState("")
    }
}
