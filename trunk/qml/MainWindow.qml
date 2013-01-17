import QtQuick 1.1
//import Qt 4.7
import "content"

Rectangle {
    id: mainwindow
    width: parent.width
    height: 600
    color: "blue"
    signal qmlSignal(int iValue)


    Column {
        CannyGPX {
            width: mainwindow.width
            height: mainwindow.height-100
        }
        Rectangle {
            id: simpleButton
            width: mainwindow.width
            height: 100


            Text{
                id: buttonLabel
                text: "Load GPX"
               anchors.centerIn: parent;
               //anchors.verticalCenterOffset: -1
              }
            MouseArea{
                id: buttonMouseArea

                anchors.fill: parent //anchor all sides of the mouse area to the rectangle's anchors
                //onClicked handles valid mouse button clicks

                onClicked: {
                    mainwindow.qmlSignal(0)
                    //console.log(buttonLabel.text + " clicked" )
                }
              }
        }
    }
}
