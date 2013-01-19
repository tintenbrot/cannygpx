import QtQuick 1.1

Rectangle {
    id: detailsScreen
    //Einzelne Eigenschaften von außen sichtbar machen
    property alias sCacheName: txtCacheName.text
    property alias sShortDescription: txtShortDescription.text
    property alias sType: geocacheImage.source
    property alias sLongDescription: txtLongDescription.text
    //
    Column {

        Row {
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
                width: 100; height: width
                smooth: true;
                MouseArea {
                    anchors.fill: parent
                    onClicked: screen.state = ""
                }
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
            height: detailsScreen.height
            width: detailsScreen.width
            contentHeight: detailsPage.height*2
            clip: true

            Item {
                id: detailsPage
                width: parent.width
                Text {
                    text: "Summary"
                    font.pointSize: 12; font.bold: true
                }

                Text {
                    id: txtShortDescription
                    wrapMode: Text.WordWrap
                    width: detailsScreen.width
                }

                Text {
                    id: headerDetails
                    text: "Details"
                    font.pointSize: 12; font.bold: true
                }

                Text {
                    id: txtLongDescription
                    wrapMode: Text.WordWrap
                    width: detailsScreen.width
                }
            }
        }
    }
}
