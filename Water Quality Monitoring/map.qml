import QtQuick 2.15
import QtLocation 5.15
import QtPositioning 5.15

Rectangle {
    width: 800
    height: 600

    Map {
        id: map
        anchors.fill: parent
        plugin: Plugin { name: "osm" }
        center: QtPositioning.coordinate(54.0, -2.0) // Centered on UK
        zoomLevel: 6

        // Example marker for London
        MapQuickItem {
            coordinate: QtPositioning.coordinate(51.5074, -0.1278)
            anchorPoint: Qt.point(10, 10)
            sourceItem: Rectangle {
                width: 20; height: 20
                color: "red"
                radius: 10
            }
        }
    }
}
