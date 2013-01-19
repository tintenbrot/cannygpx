import QtQuick 1.1

Rectangle {
    id: gpxview
    //width: 400; height: 240
    width: 400; height: 400
    color: "blue"

    // The delegate for each Cache in the model:
    Component {
        id: listDelegate

        Item {
            id: geocache

            width: listView.width
            height: width / 6

            // A simple rounded rectangle for the background of one Geocache
            Rectangle {
                id: background
                x: 4; y: 4; width: parent.width - x*2; height: parent.height - y*2
                color: "ivory"
                border.color: "white"
                radius: 10
                MouseArea {
                    anchors.fill: parent //Die gesamte Fläche des Delegates ist nun klickbar
                    onClicked: {
                        screen.state = "showDetails"
                        detailsPage.sType = sType
                        detailsPage.sCacheName = sName
                        detailsPage.sShortDescription = sShortDescription
                        detailsPage.sLongDescription = sLongDescription
                    }
                }
            }

            Row {
                id: rowOneCache
                x: 10; y: 0; height: geocacheImage.height; width: parent.width
                spacing: 5

                Image {
                    id: geocacheImage
                    y: 14
                    width: geocache.height*.9; height: width
                    smooth: true;
                    source: sType
                    //asynchronous: true
                }

                Column {
                    width: background.width - geocacheImage.width - 20; height: rowOneCache.height
                    spacing: 0

                    Text {
                        y: 0
                        text: sCode
                        font.bold: true; font.pointSize: 12
                    }
                    Text {
                        y: 0
                        text: sName
                        font.bold: false; font.pointSize: 8
                    }
//                    Text {
//                        opacity: 1
//                        text: sShortDescription
//                    }
                }
            }


        }


    }

//    Row {
//        id: viewContainer
        // The actual list
        ListView {
            id: listView
            anchors.fill: gpxview
            model: GpxModel
            delegate: listDelegate
            clip: true
            //delegate: smartviewDelegate
        }
        // Details of the Cache
//        Rectangle {
//            id: viewDetails
//            width: screen.width

//        }
//    }




//    Component {
//        id: smartviewDelegate

//        Item {
//            id: smartview

//            width: listView.width
//            height: width / 6

//            // A simple rounded rectangle for the background
//            Rectangle {
//                id: background
//                x: 4; y: 4; width: parent.width - x*2; height: parent.height - y*2
//                color: "ivory"
//                border.color: "white"
//                radius: 10
//            }

//            // Lay out the page: picture, title and ingredients at the top, and method at the
//            // bottom.  Note that elements that should not be visible in the list
//            // mode have their opacity set to recipe.detailsOpacity.
//            Row {
//                id: topLayout
//                x: 10; y: 10; height: smartviewImage.height; width: parent.width
//                spacing: 10

//                Image {
//                    id: smartviewImage
//                    width: smartview.height*.9; height: width
//                    smooth: true;
//                    source: sType
//                }

//                Column {
//                    width: background.width - recipeImage.width - 20; height: recipeImage.height
//                    spacing: 5

//                    Text {
//                        text: sCode
//                        font.bold: true; font.pointSize: 16

//                    }
//                    Text {
//                        text: sName
//                        font.bold: false; font.pointSize: 12
//                    }


//                }

//            }

//        }
//    }
}
