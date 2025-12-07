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
    
    // Temporary selection (not saved until Apply)
    property string selectedVideoPath: ""
    property string selectedProjectPath: ""
    property string selectedScaleMode: "cover"
    
    // Plasma config properties (trigger Apply button)
    property alias cfg_videoPath: configRoot.tempVideoPath
    property alias cfg_projectPath: configRoot.tempProjectPath
    property alias cfg_scaleMode: configRoot.tempScaleMode
    
    property string tempVideoPath: ""
    property string tempProjectPath: ""
    property string tempScaleMode: "cover"

    Component.onCompleted: {
        // Load previously saved configuration
        if (wallpaper && wallpaper.configuration) {
            selectedVideoPath = wallpaper.configuration.videoPath || ""
            selectedProjectPath = wallpaper.configuration.projectPath || ""
            selectedScaleMode = wallpaper.configuration.scaleMode || "cover"
            
            tempVideoPath = selectedVideoPath
            tempProjectPath = selectedProjectPath
            tempScaleMode = selectedScaleMode
            
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
        color: "#1e1e1e"

        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 16
            spacing: 12

            // Header - Collapsed for more wallpaper viewing space
            /*
            RowLayout {
                Layout.fillWidth: true
                spacing: 12
                
                Rectangle {
                    width: 4
                    height: 32
                    color: "#0078d4"
                    radius: 2
                }
                
                Label {
                    text: "Wallpaper Engine"
                    font.bold: true
                    font.pixelSize: 24
                    color: "#ffffff"
                }
                
                Item { Layout.fillWidth: true }
                
                Label {
                    text: weModel.count + " wallpapers"
                    font.pixelSize: 14
                    color: "#888888"
                }
            }

            // Path Info Card
            Rectangle {
                Layout.fillWidth: true
                height: 90
                color: "#252525"
                radius: 8
                border.color: "#3a3a3a"
                border.width: 1

                ColumnLayout {
                    anchors.fill: parent
                    anchors.margins: 16
                    spacing: 8

                    Label {
                        text: "Steam Workshop Directory"
                        font.bold: true
                        font.pixelSize: 12
                        color: "#aaaaaa"
                        opacity: 0.8
                    }

                    Label {
                        text: steamPath
                        font.family: "monospace"
                        font.pixelSize: 11
                        color: "#4fc3f7"
                        Layout.fillWidth: true
                        wrapMode: Text.Wrap
                    }
                }
            }

            // Status Card
            Rectangle {
                Layout.fillWidth: true
                height: 70
                color: weModel.pathExists ? "#0d3b1a" : "#3d1414"
                radius: 8
                border.color: weModel.pathExists ? "#1b5e20" : "#b71c1c"
                border.width: 2

                RowLayout {
                    anchors.fill: parent
                    anchors.margins: 16
                    spacing: 16
                    
                    Rectangle {
                        width: 38
                        height: 38
                        radius: 19
                        color: weModel.pathExists ? "#2e7d32" : "#c62828"
                        
                        Label {
                            anchors.centerIn: parent
                            text: weModel.pathExists ? "✓" : "✗"
                            font.bold: true
                            font.pixelSize: 20
                            color: "#ffffff"
                        }
                    }

                    ColumnLayout {
                        Layout.fillWidth: true
                        spacing: 4
                        
                        Label {
                            text: weModel.pathExists ? "Connected" : "Path Not Found"
                            font.bold: true
                            font.pixelSize: 14
                            color: "#ffffff"
                        }
                        
                        Label {
                            text: weModel.pathExists ? 
                                  (weModel.count === 0 ? "No wallpapers found" : weModel.count + " wallpapers available") : 
                                  "Check Steam Workshop path"
                            font.pixelSize: 12
                            color: "#cccccc"
                            opacity: 0.9
                        }
                    }
                }
            }
            */

            // Compact header with count
            Label {
                text: "Wallpaper Engine • " + weModel.count + " available"
                font.bold: true
                font.pixelSize: 16
                color: "#ffffff"
                Layout.bottomMargin: 8
            }

            ScrollView {
                Layout.fillWidth: true
                Layout.fillHeight: true
                clip: true
                
                ScrollBar.vertical.policy: ScrollBar.AsNeeded
                ScrollBar.horizontal.policy: ScrollBar.AlwaysOff

                Grid {
                    columns: 4
                    columnSpacing: 12
                    rowSpacing: 12
                    width: parent.width - 20

                    Repeater {
                        model: weModel
                        delegate: Rectangle {
                            width: 170
                            height: 140
                            color: selectedVideoPath === videoPath ? "#1e3a5f" : "#2a2a2a"
                            radius: 8
                            border.color: selectedVideoPath === videoPath ? "#0078d4" : "#3a3a3a"
                            border.width: selectedVideoPath === videoPath ? 2 : 1
                            
                            // Hover effect
                            states: State {
                                name: "hovered"
                                when: mouseArea.containsMouse
                                PropertyChanges {
                                    target: parent
                                    color: selectedVideoPath === videoPath ? "#2a4a7f" : "#353535"
                                    scale: 1.02
                                }
                            }
                            
                            transitions: Transition {
                                PropertyAnimation {
                                    properties: "color,scale"
                                    duration: 150
                                    easing.type: Easing.OutQuad
                                }
                            }

                            Column {
                                anchors.fill: parent
                                anchors.margins: 10
                                spacing: 8

                                // Thumbnail container
                                Rectangle {
                                    width: parent.width
                                    height: 85
                                    color: "#1a1a1a"
                                    radius: 4
                                    clip: true
                                    
                                    Image {
                                        anchors.fill: parent
                                        source: previewPath && previewPath.length > 0 ? "file://" + previewPath : ""
                                        fillMode: Image.PreserveAspectCrop
                                        asynchronous: true

                                        Rectangle {
                                            anchors.fill: parent
                                            color: "#1a1a1a"
                                            visible: parent.status !== Image.Ready
                                            
                                            Label {
                                                anchors.centerIn: parent
                                                text: "No Preview"
                                                color: "#666666"
                                                font.pixelSize: 10
                                            }
                                        }
                                    }
                                }

                                Label {
                                    text: title || "Untitled"
                                    color: "#ffffff"
                                    elide: Text.ElideRight
                                    width: parent.width
                                    font.pixelSize: 11
                                    font.bold: true
                                    maximumLineCount: 2
                                    wrapMode: Text.WordWrap
                                }

                                Label {
                                    text: "by " + (author || "Unknown")
                                    color: "#888888"
                                    font.pixelSize: 9
                                    elide: Text.ElideRight
                                    width: parent.width
                                    opacity: 0.9
                                }
                            }

                            MouseArea {
                                id: mouseArea
                                anchors.fill: parent
                                hoverEnabled: true
                                cursorShape: Qt.PointingHandCursor
                                onClicked: {
                                    debug("Selected wallpaper: " + title + " (" + videoPath + ")")
                                    selectedProjectPath = projectPath
                                    selectedVideoPath = videoPath
                                    selectedScaleMode = scaleBox.currentText
                                    
                                    // Update cfg properties to enable Apply button
                                    tempVideoPath = videoPath
                                    tempProjectPath = projectPath
                                    tempScaleMode = scaleBox.currentText
                                }
                            }
                        }
                    }
                }
            }

            // Bottom controls
            Rectangle {
                Layout.fillWidth: true
                height: 1
                color: "#3a3a3a"
            }
            
            RowLayout {
                Layout.fillWidth: true
                spacing: 12

                Label {
                    text: "Scale Mode:"
                    color: "#aaaaaa"
                    font.pixelSize: 12
                }

                ComboBox {
                    id: scaleBox
                    model: ["Cover (Fill Screen)", "Contain (Fit Screen)", "Stretch"]
                    currentIndex: 0
                    
                    Component.onCompleted: {
                        var modes = ["cover", "contain", "stretch"]
                        var idx = modes.indexOf(selectedScaleMode)
                        if (idx >= 0) currentIndex = idx
                    }
                    
                    onCurrentIndexChanged: {
                        var modes = ["cover", "contain", "stretch"]
                        selectedScaleMode = modes[currentIndex]
                        tempScaleMode = modes[currentIndex]
                    }
                }

                Item { Layout.fillWidth: true }
                
                Label {
                    text: selectedVideoPath ? "Wallpaper selected - click Apply" : "Select a wallpaper above"
                    color: selectedVideoPath ? "#4fc3f7" : "#666666"
                    font.pixelSize: 11
                    font.italic: true
                }

                Button {
                    text: "↻ Refresh"
                    onClicked: weModel.reload()
                }
            }
        }
    }
}
