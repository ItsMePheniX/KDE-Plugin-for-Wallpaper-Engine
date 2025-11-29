import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import WallpaperEngine 1.0

Item {
    id: configRoot
    width: 800
    height: 600

    // Debug flag - set to true to enable console logging
    readonly property bool debugMode: false
    
    function debug(message) {
        if (debugMode) console.log("[WE Config]", message)
    }

    property string steamPath: "/home/AadityaA/.local/share/Steam/steamapps/workshop/content/431960"
    
    property string selectedVideoPath: ""
    property string selectedProjectPath: ""

    Component.onCompleted: {
        // Load previously saved configuration
        if (wallpaper && wallpaper.configuration) {
            selectedVideoPath = wallpaper.configuration.videoPath || ""
            selectedProjectPath = wallpaper.configuration.projectPath || ""
            debug("Loaded config - videoPath: " + selectedVideoPath)
        }
    }

    WallpaperEngineModel {
        id: weModel
        Component.onCompleted: {
            useDefaultSteamPath()
            debug("Model loaded - found " + count + " wallpapers, pathExists: " + pathExists)
        }
        onCountChanged: {
            debug("Wallpaper count changed to: " + count)
        }
    }

    Rectangle {
        anchors.fill: parent
        color: "#2a2a2a"

        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 20
            spacing: 15

            Label {
                text: "Wallpaper Engine Plugin"
                font.bold: true
                font.pixelSize: 20
                color: "#ffffff"
            }

            Rectangle {
                Layout.fillWidth: true
                height: 100
                color: "#3a3a3a"
                radius: 8
                border.color: "#555"
                border.width: 2

                ColumnLayout {
                    anchors.fill: parent
                    anchors.margins: 15
                    spacing: 8

                    Label {
                        text: "Steam Workshop Path:"
                        font.bold: true
                        font.pixelSize: 14
                        color: "#cccccc"
                    }

                    Label {
                        text: steamPath
                        font.family: "monospace"
                        font.pixelSize: 13
                        color: "#4fc3f7"
                        Layout.fillWidth: true
                        wrapMode: Text.Wrap
                    }
                }
            }

            Rectangle {
                Layout.fillWidth: true
                height: 80
                color: weModel.pathExists ? "#1b5e20" : "#b71c1c"
                radius: 8

                ColumnLayout {
                    anchors.centerIn: parent
                    spacing: 8

                    Label {
                        text: weModel.pathExists ? "✓ Path Exists" : "✗ Path Not Found"
                        font.bold: true
                        font.pixelSize: 16
                        color: "#ffffff"
                        anchors.horizontalCenter: parent.horizontalCenter
                    }

                    Label {
                        text: "Found " + weModel.count + " video wallpaper(s)"
                        font.pixelSize: 14
                        color: "#ffffff"
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                }
            }

            Label {
                text: "Select a wallpaper:"
                font.bold: true
                font.pixelSize: 14
                color: "#cccccc"
            }

            ScrollView {
                Layout.fillWidth: true
                Layout.fillHeight: true
                clip: true

                Grid {
                    columns: 4
                    spacing: 10
                    width: parent.width - 20

                    Repeater {
                        model: weModel
                        delegate: Rectangle {
                            width: 170
                            height: 130
                            color: selectedVideoPath === videoPath ? "#0d47a1" : "#3a3a3a"
                            radius: 6
                            border.color: "#555"
                            border.width: 2

                            Column {
                                anchors.fill: parent
                                anchors.margins: 8
                                spacing: 6

                                Image {
                                    source: previewPath && previewPath.length > 0 ? "file://" + previewPath : ""
                                    fillMode: Image.PreserveAspectFit
                                    asynchronous: true
                                    width: parent.width
                                    height: 80

                                    Rectangle {
                                        anchors.fill: parent
                                        color: "#222"
                                        visible: parent.status !== Image.Ready
                                        z: -1
                                        
                                        Label {
                                            anchors.centerIn: parent
                                            text: "No Preview"
                                            color: "#666"
                                            font.pixelSize: 10
                                        }
                                    }
                                }

                                Label {
                                    text: title || "Untitled"
                                    color: "white"
                                    elide: Text.ElideRight
                                    width: parent.width
                                    font.pixelSize: 12
                                    font.bold: true
                                }

                                Label {
                                    text: author || "Unknown"
                                    color: "#aaaaaa"
                                    font.pixelSize: 10
                                    elide: Text.ElideRight
                                    width: parent.width
                                }
                            }

                            MouseArea {
                                anchors.fill: parent
                                cursorShape: Qt.PointingHandCursor
                                onClicked: {
                                    debug("Selected wallpaper: " + title + " (" + videoPath + ")")
                                    selectedProjectPath = projectPath
                                    selectedVideoPath = videoPath
                                    
                                    // Save to Plasma configuration
                                    wallpaper.configuration.projectPath = projectPath
                                    wallpaper.configuration.videoPath = videoPath
                                }
                            }
                        }
                    }
                }
            }

            RowLayout {
                Layout.fillWidth: true
                spacing: 10

                Label {
                    text: "Scale mode:"
                    color: "#cccccc"
                }

                ComboBox {
                    id: scaleBox
                    model: ["cover", "contain", "stretch"]
                    currentIndex: 0
                }

                Item { Layout.fillWidth: true }

                Button {
                    text: "Reload"
                    onClicked: weModel.reload()
                }
            }
        }
    }
}
