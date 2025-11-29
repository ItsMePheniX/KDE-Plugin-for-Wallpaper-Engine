import QtQuick 2.15
import QtMultimedia 6.0
import org.kde.plasma.plasmoid 2.0
import WallpaperEngine 1.0

WallpaperItem {
    id: root
    
    // Debug flag - set to true to enable console logging
    readonly property bool debugMode: false
    
    property string selectedProjectPath: wallpaper.configuration.projectPath || ""
    property string selectedVideo: wallpaper.configuration.videoPath || ""
    property string scaleMode: wallpaper.configuration.scaleMode || "cover"
    
    function debug(message) {
        if (debugMode) console.log("[WE Main]", message)
    }

    Component.onCompleted: {
        debug("Wallpaper loaded - projectPath: " + selectedProjectPath + ", videoPath: " + selectedVideo)
    }
    
    onSelectedVideoChanged: {
        debug("Video changed to: " + selectedVideo)
    }

    // Simple Video Player
    MediaPlayer {
        id: player
        source: selectedVideo ? "file://" + selectedVideo : ""
        loops: MediaPlayer.Infinite
        audioOutput: AudioOutput { muted: true }
        autoPlay: true
        
        onErrorOccurred: function(error, errorString) {
            if (root.debugMode) console.error("[WE Main] Media error:", error, errorString, "Source:", source)
        }
        
        onSourceChanged: {
            debug("MediaPlayer source changed to: " + source)
            if (source) {
                play()
            }
        }
        
        onPlaybackStateChanged: {
            if (playbackState === MediaPlayer.PlayingState) {
                debug("Video is now playing")
            }
        }
    }

    VideoOutput {
        id: videoOut
        anchors.fill: parent
        fillMode: scaleMode === "stretch" ? VideoOutput.Stretch : (scaleMode === "contain" ? VideoOutput.PreserveAspectFit : VideoOutput.PreserveAspectCrop)
        
        Component.onCompleted: {
            player.videoOutput = videoOut
        }
        
        Rectangle {
            anchors.fill: parent
            color: "black"
            visible: !selectedVideo || player.playbackState !== MediaPlayer.PlayingState
            z: -1
        }
    }

    // Fallback overlay when nothing selected
    Rectangle {
        anchors.fill: parent
        color: "#1a1a1a"
        visible: !selectedVideo
        
        Column {
            anchors.centerIn: parent
            spacing: 10
            
            Text {
                text: "No Wallpaper Engine video selected"
                anchors.horizontalCenter: parent.horizontalCenter
                color: "#cccccc"
                font.pixelSize: 16
            }
            
            Text {
                text: "Right-click desktop → Configure Desktop and Wallpaper"
                anchors.horizontalCenter: parent.horizontalCenter
                color: "#888888"
                font.pixelSize: 12
            }
        }
    }
}
