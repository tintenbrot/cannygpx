import QtQuick 1.1
import "content"

// This example illustrates expanding a list item to show a more detailed view.

Rectangle {
    id: gpxview
    //width: 400; height: 240
    width: 400; height: 400
    color: "black"

    // Delegate for the recipes.  This delegate has two modes:
    // 1. List mode (default), which just shows the picture and title of the recipe.
    // 2. Details mode, which also shows the ingredients and method.
    Component {
        id: recipeDelegate

        Item {
            id: recipe

            // Create a property to contain the visibility of the details.
            // We can bind multiple element's opacity to this one property,
            // rather than having a "PropertyChanges" line for each element we
            // want to fade.
            property real detailsOpacity : 0

            width: listView.width
            height: width / 6

            // A simple rounded rectangle for the background
            Rectangle {
                id: background
                x: 2; y: 2; width: parent.width - x*2; height: parent.height - y*2
                color: "ivory"
                border.color: "white"
                radius: 5
            }

            // This mouse region covers the entire delegate.
            // When clicked it changes mode to 'Details'.  If we are already
            // in Details mode, then no change will happen.
            MouseArea {
                anchors.fill: parent
                onClicked: recipe.state = 'Details';
            }

            // Lay out the page: picture, title and ingredients at the top, and method at the
            // bottom.  Note that elements that should not be visible in the list
            // mode have their opacity set to recipe.detailsOpacity.
            Row {
                id: topLayout
                x: 10; y: 10; height: recipeImage.height; width: parent.width
                spacing: 10

                Image {
                    id: recipeImage
                    width: recipe.height*.9; height: width
                    smooth: true;
                    //source: picture
                    source: sType
                }

                Column {
                    width: background.width - recipeImage.width - 20; height: recipeImage.height
                    spacing: 5

                    Text { 
                        text: sCode
                        font.bold: true; font.pointSize: 16

                    }
                    Text {
                        text: sName
                        font.bold: false; font.pointSize: 12
                    }

                    Text {
                        text: "Summary"
                        font.pointSize: 12; font.bold: true
                        opacity: recipe.detailsOpacity
                    }

                    Text {
                        //text: shortDescription
                        text: sShortDescription
                        wrapMode: Text.WordWrap
                        width: parent.width
                        opacity: recipe.detailsOpacity
                    }
                }
            }

            Item {
                id: details
                x: 10; width: parent.width - 20
                anchors { top: topLayout.bottom; topMargin: 10; bottom: parent.bottom; bottomMargin: 10 }
                opacity: recipe.detailsOpacity

                Text {
                    id: methodTitle
                    anchors.top: parent.top
                    text: "Details"
                    font.pointSize: 12; font.bold: true
                }

                Flickable {
                    id: flick
                    width: parent.width
                    anchors { top: methodTitle.bottom; bottom: parent.bottom }
                    contentHeight: methodText.height
                    clip: true

                    Text { id: methodText; text: sLongDescription; wrapMode: Text.WordWrap; width: details.width }
                    //Text { id: methodText; text: Name; wrapMode: Text.WordWrap; width: details.width }
                }

                Image {
                    anchors { right: flick.right; top: flick.top }
                    source: "content/pics/moreUp.png"
                    opacity: flick.atYBeginning ? 0 : 1
                }

                Image {
                    anchors { right: flick.right; bottom: flick.bottom }
                    source: "content/pics/moreDown.png"
                    opacity: flick.atYEnd ? 0 : 1
                }
            }

            // A button to close the detailed view, i.e. set the state back to default ('').
            TextButton {
                y: 10
                anchors { right: background.right; rightMargin: 10 }
                opacity: recipe.detailsOpacity
                text: "Close"

                onClicked: recipe.state = '';
            }

            states: State {
                name: "Details"

                PropertyChanges { target: background; color: "lightblue" }
                PropertyChanges { target: recipeImage; width: listView.width*.3; height: width; smooth: true } // Make picture bigger
                PropertyChanges { target: recipe; detailsOpacity: 1; x: 0 } // Make details visible
                PropertyChanges { target: recipe; height: listView.height } // Fill the entire list area with the detailed view

                // Move the list so that this item is at the top.
                PropertyChanges { target: recipe.ListView.view; explicit: true; contentY: recipe.y }

                // Disallow flicking while we're in detailed view
                PropertyChanges { target: recipe.ListView.view; interactive: false }
            }

            transitions: Transition {
                // Make the state changes smooth
                ParallelAnimation {
                    ColorAnimation { property: "color"; duration: 500 }
                    NumberAnimation { duration: 300; properties: "detailsOpacity,x,contentY,height,width" }
                }
            }
        }
    }

    // The actual list
    ListView {
        id: listView
        anchors.fill: parent
        //model: RecipesModel {}
        model: GpxModel
        delegate: recipeDelegate
    }
}
