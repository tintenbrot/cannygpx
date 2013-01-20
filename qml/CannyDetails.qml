import QtQuick 1.1

Rectangle {
    id: detailsScreen
    //Einzelne Eigenschaften von außen sichtbar machen
    property alias sCacheName: txtCacheName.text
    property alias sShortDescription: txtShortDescription.text
    property alias sType: geocacheImage.source
    property alias sLongDescription: txtLongDescription.text
    //
    color: "lightblue"
    width: parent.width
    Column {
        //left: parent.left
        width: parent.width
   //     height: 100
        Row {
            id: topBar
            width: parent.width
            height: 100
            //height: parent.height
//            Rectangle {
//                id: backButton2
//                width: 200
//                height: 60
//                color: "grey"
//                border.color: "yellow"
//                border.width: 4
//                radius: 10
//                opacity: 0
////                Text {
////                    id: backLabelClose
////                    text: "Back"
////                    font.bold: true; font.pointSize: 10
////                    anchors.centerIn: parent
////                }
////                MouseArea {
////                    id: buttonMouseAreaBack
////                    anchors.fill: parent

////                    onClicked:  {
////                        screen.state=""
////                    }
////                }
//            }
            Image {
                id: geocacheImage
                y: 14
                height: parent.height
                width: height;
                smooth: true;
            }
        }

        Text {
            id: txtCacheName
            font.bold: false; font.pointSize: 10
        }

        Flickable {
            id: flickDetails
            //width: detailsScreen.width
            //anchors { top: headerDetails.bottom; bottom: detailsScreen.bottom }
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: txtCacheName.bottom
            anchors.bottom: detailsScreen.bottom
            height: detailsScreen.height
            width: detailsScreen.width
            contentHeight: detailsPage.height
            contentWidth: width
            //boundsBehavior: Flickable.StopAtBounds
            clip: true


            Item {
                id: detailsPage
                width: parent.width
                height: screen.height*12 //Hier hätte ich gern die echte Höhe, aber die ist irgendwie immer null?
                Text {
                    id: headerSummary
                    text: "Summary:"
                    font.pointSize: 12; font.bold: true
                }

                Text {
                    id: txtShortDescription
                    //height:80
                    anchors.top: headerSummary.bottom
                    wrapMode: Text.WordWrap
                    width: detailsScreen.width
                }

                Text {
                    id: headerDetails
                    anchors.top: txtShortDescription.bottom
                    text: "Details:"
                    font.pointSize: 12; font.bold: true
                }

                Text {
                    id: txtLongDescription
                    anchors.top: headerDetails.bottom
                    wrapMode: Text.WordWrap
                    width: detailsScreen.width
                }
            }
        }
    }
}
