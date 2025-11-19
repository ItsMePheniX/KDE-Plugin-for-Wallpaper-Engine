import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtMultimedia 6.0
import WallpaperEngine 1.0

Item {
    id: root
    property string selectedProjectPath: wallpaper.configuration.projectPath || ""
    property string selectedVideo: wallpaper.configuration.videoPath || ""
    property string scaleMode: wallpaper.configuration.scaleMode || "cover"

    // Simple Video Player
    MediaPlayer {
        id: player
        source: selectedVideo
        loops: MediaPlayer.Infinite
        muted: true
        autoPlay: true
        onErrorOccurred: console.warn("Media error", errorString)
        onSourceChanged: { if (source) play() }
    }

    VideoOutput {
        id: videoOut
        anchors.fill: parent
        fillMode: scaleMode === "stretch" ? VideoOutput.Stretch : (scaleMode === "contain" ? VideoOutput.PreserveAspectFit : VideoOutput.PreserveAspectCrop)
        source: player
    }

    // Fallback overlay when nothing selected
    Text {
        visible: !selectedVideo
        text: "Select a Wallpaper Engine project in configuration"
        anchors.centerIn: parent
        color: "#cccccc"
        wrapMode: Text.Wrap
    }
}
