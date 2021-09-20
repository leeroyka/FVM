import QtQuick 2.10
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4
import QtQuick.Controls.Material 2.12


Rectangle {
    anchors.fill: parent
    color: "#205081"

    Text {
        id: textLabelHeader
        anchors.fill: parent
        anchors.topMargin: 10
        anchors.leftMargin: 15
        text: qsTr("Function Voxel Methods")
        font.pixelSize: 21
        font.bold: true
        color: "White"
     }
    Button{
        id: buttonShowSettings
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.topMargin: (parent.height/2) - (buttonShowSettings.height/2)
        anchors.leftMargin: parent.width - buttonShowSettings.width - 10
        text: qsTr('Настройки')
        onClicked: settingsGateway.open()
    }
}
