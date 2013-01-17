import QtQuick 1.1
//import Qt 4.7
import "content"

Rectangle {
    id: mainwindow
    width: 400
    height: 600
    color: "blue"
    signal qmlSignal(int iValue)


    Column {
        CannyGPX {
            width: 400
            height: mainwindow.height-50
        }
        Rectangle {
            id: simpleButton
            width: 400
            height: 50


            Text{
                id: buttonLabel
                text: "Rebuild Database"
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
