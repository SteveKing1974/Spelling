import QtQuick 2.0
import QtQuick.Controls 2.2

import Qt.spellingGame.gameController 1.0

Item {

    Rectangle {
        id: currentWord
        width: parent.width*0.6
        height: parent.height*0.3

        anchors.top: parent.top
        anchors.topMargin: 20

        border.color: 'black'

        anchors.horizontalCenter: parent.horizontalCenter

        Text {
            font.family: "Chunky Felt"
            font.pointSize: 24
            text: GameControl.currentWord
            anchors.centerIn: parent

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter

            visible: GameControl.gameState != GameControl.Write
        }
    }

    Rectangle {

        width: parent.width*0.6
        height: parent.height*0.3

        anchors.top: currentWord.bottom
        anchors.topMargin: 20

        anchors.horizontalCenter: parent.horizontalCenter

        border.color: 'black'

        TextInput {
            id: typedText
            anchors.fill: parent
            anchors.margins: 10

            font.family: "Chunky Felt"
            font.pointSize: 24

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter

            inputMethodHints: Qt.ImhNoPredictiveText

            enabled: GameControl.gameState == GameControl.Write

            focus: GameControl.gameState == GameControl.Write

            Connections {
                target: GameControl
                onGameStateChanged: {
                    if (GameControl.gameState == GameControl.Look)
                    {
                        typedText.text = ""
                    }
                }

            }
        }
    }

    function buttonText(gameState)
    {
        var textVal = "Next"

        switch (gameState)
        {
        case GameControl.Look:
            textVal = "Look at the word. Click here when you have read it"
            break;
        case GameControl.Say:
            textVal = "Say the word. Click here when you have said it"
            break;
        case GameControl.Write:
            textVal = "Now write the word. Click here when you have finished it"
            break;
        case GameControl.Correct:
            textVal = "Well done you got it right. Click here for the next word"
            break;
        case GameControl.Wrong:
            textVal = "Sorry, that's wrong. Click here to try again"
            break;
        }

        return textVal
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

            text: buttonText(GameControl.gameState)
        }

        enabled: GameControl.gameState != GameControl.Write || typedText.text.length>0

        onClicked: GameControl.nextState(typedText.text)
    }
}
