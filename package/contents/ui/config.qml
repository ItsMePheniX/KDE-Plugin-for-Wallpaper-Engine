import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import WallpaperEngine 1.0

Item {
    id: configRoot
    width: 800; height: 600

    // Explicit default path (avoid HOME expansion issues in QML binding)
    property string defaultRoot: "/home/AadityaA/.local/share/Steam/steamapps/workshop/content/431960"

    WallpaperEngineModel {
        id: weModel
        Component.onCompleted: useDefaultSteamPath()
    }

    readonly property string defaultRootResolved: defaultRoot

    ColumnLayout {
        anchors.fill: parent
        spacing: 8
        Label { text: "Wallpaper Engine Plugin"; font.bold: true; color: "#ddd" }
        Label { text: "If no projects appear, ensure videos exist under the hardcoded Steam path."; wrapMode: Text.Wrap; color: "#999" }
        Frame {
            Layout.fillWidth: true
            background: Rectangle { color: "#222"; radius: 4 }
            Label { text: "Steam workshop path: " + defaultRootResolved; color: "#ccc"; wrapMode: Text.Wrap; anchors.margins: 6; anchors.fill: parent }
        }
        // Status / error messages
        Loader {
            Layout.fillWidth: true
            sourceComponent: weModel.lastError.length ? errorBox : (weModel.pathExists && weModel.count === 0 ? emptyBox : null)
        }
        Component {
            id: errorBox
            Frame { width: parent.width; background: Rectangle { color: "#552222"; radius: 4 }
                Label { text: "Error: " + weModel.lastError; color: "#ffcccc"; wrapMode: Text.Wrap }
            }
        }
        Component {
            id: emptyBox
            Frame { width: parent.width; background: Rectangle { color: "#333333"; radius: 4 }
                Label { text: "No Wallpaper Engine video projects found here."; color: "#cccccc"; wrapMode: Text.Wrap }
            }
        }
        ScrollView {
            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true
            
            Grid {
                id: grid
                columns: 4
                spacing: 8
                width: parent.width
                
                Repeater {
                    model: weModel
                    delegate: Rectangle {
                        width: 160
                        height: 120
                        color: {
                            if (typeof wallpaper !== 'undefined' && wallpaper.configuration.projectPath === projectPath) {
                                return "#4477aa"
                            }
                            return "#333"
                        }
                        radius: 4
                        border.color: "#555"
                        border.width: 1
                        
                        Column {
                            anchors.fill: parent
                            anchors.margins: 6
                            spacing: 4
                            
                            Image {
                                source: previewPath && previewPath.length > 0 ? "file://" + previewPath : ""
                                fillMode: Image.PreserveAspectFit
                                asynchronous: true
                                width: parent.width
                                height: 70
                                
                                Rectangle {
                                    anchors.fill: parent
                                    color: "#222"
                                    visible: parent.status !== Image.Ready
                                    Text {
                                        anchors.centerIn: parent
                                        text: "No Preview"
                                        color: "#666"
                                        font.pixelSize: 10
                                    }
                                }
                            }
                            
                            Text {
                                text: title || "Untitled"
                                color: "white"
                                elide: Text.ElideRight
                                width: parent.width
                                font.pixelSize: 12
                            }
                            
                            Text {
                                text: author || "Unknown"
                                color: "#bbb"
                                font.pixelSize: 9
                                elide: Text.ElideRight
                                width: parent.width
                            }
                        }
                        
                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                if (typeof wallpaper !== 'undefined') {
                                    wallpaper.configuration.projectPath = projectPath
                                    wallpaper.configuration.videoPath = videoPath
                                }
                            }
                        }
                    }
                }
            }
        }
        RowLayout {
            Layout.fillWidth: true
            ComboBox {
                id: scaleBox
                model: ["cover","contain","stretch"]
                onCurrentTextChanged: wallpaper.configuration.scaleMode = currentText
                Component.onCompleted: currentIndex = model.indexOf(wallpaper.configuration.scaleMode || "cover")
            }
            Button {
                text: "Reload"
                onClicked: weModel.reload()
            }
            Label { text: weModel.count + " projects"; color: weModel.count ? "#aaa" : "#ff8888" }
        }
    }
}
