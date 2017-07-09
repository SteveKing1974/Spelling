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

        text: "Hi, please enter your name:"
    }

    Rectangle {

        anchors.margins: 20
        anchors.left: parent.left
        anchors.right: parent.right

        height: parent.height*0.1

        anchors.top: headingText.bottom

        border.color: 'black'

        TextInput {
            id: typedText
            anchors.fill: parent
            anchors.margins: 10

            font.family: "Chunky Felt"
            font.pointSize: 18

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter

            inputMethodHints: Qt.ImhNoPredictiveText
        }
    }

    Button {
        width: parent.width*0.6
        height: parent.height*0.2

        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20

        anchors.horizontalCenter: parent.horizontalCenter


        contentItem: Label {
            font.family: "Chunky Felt"
            font.pointSize: 14

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter

            wrapMode: Text.WordWrap

            text: "Done"
        }

        enabled: typedText.text.length>0

        onClicked: GameControl.nextState(typedText.text)
    }
}
