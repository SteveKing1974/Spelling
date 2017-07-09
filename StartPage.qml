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

        text: "Hi " + GameControl.currentUser + " pick the word list you want to try, then press start."
    }

    ComboBox {
        id: fileSelect
        width: parent.width*0.6
        height: parent.height*0.15

        anchors.top: headingText.bottom
        anchors.topMargin: 20

        anchors.horizontalCenter: parent.horizontalCenter

        font.family: "Chunky Felt"
        font.pointSize: 24

        model: GameControl.allSets

        onActivated: {
            GameControl.currentSet = GameControl.allSets[index]
        }
    }

    ComboBox {
        id: wordListSelect
        width: parent.width*0.6
        height: parent.height*0.15

        anchors.top: fileSelect.bottom
        anchors.topMargin: 20

        anchors.horizontalCenter: parent.horizontalCenter

        font.family: "Chunky Felt"
        font.pointSize: 24

        model: GameControl.listsInSet

        delegate: ItemDelegate {
            width: wordListSelect.width
            contentItem: Item {
                Text {
                    text: modelData
                    font.family: wordListSelect.font.family
                    font.pointSize: 14
                    elide: Text.ElideRight
                    verticalAlignment: Text.AlignVCenter
                    anchors.left: parent.left
                }

                Image {
                    anchors.right: parent.right
                    source: "qrc:/Icons/tick.png"
                    height: parent.height
                    width: height
                    visible: GameControl.isListCompleted(modelData)
                }
            }
        }
    }

    Button {
        width: parent.width*0.6
        height: parent.height*0.1

        anchors.bottom: startButton.top
        anchors.bottomMargin: 20

        anchors.horizontalCenter: parent.horizontalCenter

        font.family: "Chunky Felt"
        font.pointSize: 24

        text: "Completed Lists"
        onClicked: GameControl.showScores()
    }

    Button {
        id: startButton
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
