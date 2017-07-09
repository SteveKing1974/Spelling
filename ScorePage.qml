import QtQuick 2.0
import QtQuick.Controls 2.2

import Qt.spellingGame.gameController 1.0


Item {
    Text {
        id: headingText

        font.family: "Chunky Felt"
        font.pointSize: 18

        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter

        height: parent.height*0.2

        anchors.top: parent.top
        anchors.margins: 20
        anchors.left: parent.left
        anchors.right: parent.right

        wrapMode: Text.WordWrap

        text: "You've completed all of these lists:"
    }

    Rectangle {
        anchors.top: headingText.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: nextButton.top

        anchors.margins: 20

        border.color: "black"

        ListView {
            anchors.fill: parent
            anchors.margins: 10

            model: GameControl.completedLists

            delegate: Text {
                font.family: "Chunky Felt"
                font.pointSize: 14

                text: modelData
            }
        }
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

        text: "Back"
        onClicked: GameControl.nextState("")
    }
}
