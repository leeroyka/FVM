import QtQuick 2.10
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import "../Shared" as Shared

Item{
    //..................................................
    property string answerText: ""
    function printAnswer(data)
    {
        answerText = data;
    }

    //..................................................
    function printLogs(data)
    {
        if(data)
            outputLogs.text = data
    }
    function printData(data)
    {
        outputData.text += data
    }

    property alias outText: outputData.text
    property alias uuid: listUUID.currentText
    function setUpDataOutput(data)
    {
        outText += data
    }
    function appendUUID(uuid)
    {
        if(uuid)
            modelListUUID.append({'text':uuid})
            listUUID.currentIndex = listUUID.count - 1
    }
    //.......................................................................
    TabView {
      id: tabViewAnswer
      anchors.fill: parent
      anchors.top: parent.top
      anchors.left: parent.left
      anchors.bottom: parent.bottom
      anchors.topMargin: 10
      anchors.leftMargin: 20
      anchors.rightMargin: 20
      anchors.bottomMargin: 20
      Tab {
        id: tabExpression
        title: "Function"
        Text {
          id: nameA
          leftPadding: 10
          topPadding: 10
          text: answerText
        }
      }
      Tab {
        id: tabVoxelModel
        title: "2D"
        Text {
          leftPadding: 10
          id: nameB
          text: qsTr("b")
        }
      }
      Tab {
        id: tab3dModel
        title: "3D"
        Text {
          leftPadding: 10
          id: nameC
          text: qsTr("c")
        }
      }
    }
    //........................................................................
    Rectangle {

        color: "LightBlue"
        ComboBox{
        id: listUUID
        anchors.top: tabViewAnswer.bottom

        anchors.left: tabViewAnswer.left
        anchors.leftMargin: outputData.width
        anchors.right: buttonStartStop.left
        anchors.rightMargin: 10
        Layout.minimumWidth: 100
        model: ListModel{
            id: modelListUUID
            ListElement {text : "";}

        }
    }
    Text{
        id: textOutputData
        anchors.top: listUUID.bottom
        anchors.topMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 20
        text: qsTr('')
    }

    Text{
        id: textOutputLogs
        anchors.top: textOutputData.top
        anchors.left: textOutputData.right
        anchors.leftMargin: outputData.width
        text: qsTr('')
    }
    Button{
        id: buttonStartStop
        anchors.top: listUUID.top
        anchors.right: checkIsReapeat.left
        anchors.rightMargin: 10
        text: updaterLogs.running ? qsTr('Остановить') : qsTr('Обновить')
        onClicked: updaterLogs.running ? updaterLogs.stop() :
                                         updaterLogs.start()
    }
    CheckBox{
        id: checkIsReapeat
        anchors.top: buttonStartStop.top
        anchors.rightMargin: 10
        anchors.right: parent.right
        text: qsTr('Автообновление (сек)')
        checked: mainWindow.requestRepeat
        onCheckedChanged: mainWindow.requestRepeat = checked
    }
    TextField{
        id: inputTimeToRepeat
        anchors.top: checkIsReapeat.bottom
        anchors.topMargin: 5
        anchors.left: checkIsReapeat.left
        visible: mainWindow.requestRepeat
        width: 40
        text: mainWindow.timeToRepeat
        onTextChanged: mainWindow.timeToRepeat = text
    }

    SplitView{
        orientation: Qt.Horizontal
        anchors.fill: parent
//        anchors.topMargin: 50
        Layout.fillHeight: true
        Layout.fillWidth: true
        TextArea {
            id: outputData
            anchors.top: parent.top
            anchors.topMargin: 60
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 60
            readOnly: true
            text: outText
            Layout.minimumWidth: 100
            textFormat: TextEdit.RichText
        }
        TextArea {
            id: outputLogs
            anchors.top: outputData.top
            anchors.left: outputData.right
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 60
            readOnly: true
            Layout.minimumWidth: 320
            textFormat: TextEdit.RichText
        }
    }
    }
}
