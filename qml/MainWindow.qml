import QtQuick 1.1
//import Qt 4.7
import "content"

Rectangle {
    id: screen
    width: parent.width
    height: 600
    color: "blue"
    signal qmlSignal(int iValue)


    states: [
        State {
            name: "showDetails"
            PropertyChanges {
                target: viewContainer
                x: -screen.width
            }
        }
    ]
    // Somit werden die Details animiert eingeblendet
    transitions: [
        Transition {
            NumberAnimation { target: viewContainer; property: "x"; duration: 700; easing.type: Easing.InOutQuad }
        }
    ]
    Column {
        Row { //Eine Row, damit die Details im Gleichen Screen einfach reingemovet werden können
            id: viewContainer
            CannyGPX2 {
                width: screen.width
                height: screen.height-100
            }
            Text {
                id: detailsPage
                anchors.fill: screen
                text: "Details"
                MouseArea {
                    anchors.fill: parent //Die gesamte Fläche des Delegates ist nun klickbar
                    onClicked: {
                        screen.state=""
                    }
                }
            }
        }
        //
        Row {
            width: screen.width
            height: 100
            spacing: 10
            x: 4
            Rectangle {
                id: gpxButton
                x: 4; y: 4; width: parent.width/2 - x*2-10
                height: parent.height-y*2
                color: "grey"
                border.color: "yellow"
                border.width: 4
                radius: 10
                Text{
                    id: buttonLabelLoadGPX
                    font.bold: true; font.pointSize: 10
                    text: "Load GPX"
                    anchors.centerIn: parent;
                  }
                MouseArea{
                    id: buttonMouseAreaLoadGPX

                    anchors.fill: parent //anchor all sides of the mouse area to the rectangle's anchors
                    //onClicked handles valid mouse button clicks

                    onClicked: {
                        screen.qmlSignal(0)
                        //console.log(buttonLabelLoadGPX.text + " clicked" )
                    }
                  }
            }
            Rectangle {
                    id: closeButton
                    x: gpxButton.x
                    y: gpxButton.y
                    width: gpxButton.width
                    height: gpxButton.height
                    color: "grey"
                    border.color: "yellow"
                    border.width: 4
                    radius: 10
                    Text {
                        id: buttonLabelClose
                        text: "Close"
                        font.bold: true; font.pointSize: 10
                        anchors.centerIn: parent
                    }
                    MouseArea {
                        id: buttonMouseAreaClose
                        anchors.fill: parent

                        onClicked:  {
                            Qt.quit()
                            //screen.qmlSignal(1)
                        }
                    }
        }
        }
    }
}