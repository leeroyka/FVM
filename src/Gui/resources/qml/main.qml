import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4
import QtQuick.Controls 2.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls.Material 2.12

import "./MainWindow" as MainWindow
import "./Shared" as Shared

Window {
    property string requestIp: '127.0.0.1'
    property string requestPort: '8000'
    property string requestType: 'POST'
    property string requestServiceName: 'gateway_tasks'
    property string timeToRepeat: '1'
    property alias requestRepeat: updaterLogs.repeat
    property string requestData:
        '{\"port\":\"8008\",
        \"method\":\"route_services\",
        \"service\":\"log_reader_tasks\",
        \"return\":\"logs\",
        \"uuid":\"' + footer.uuid +'\"}'

    id: mainWindow
    visible: true
    width: 520
    height: 500
    minimumWidth: 520
    minimumHeight: 500
    title: qsTr("FVM")
    Material.theme: Material.Dark
    //загрузка формы
    Loader{
        Component.onCompleted: {
          qmlApp.requestToLoadHistory()
        }
    }
    Connections {
        target: qmlApp

        onUpdateOutputData:{
          footer.printData(data)
        }
        onUpdateOutputLogs:{
          footer.printLogs(data)
        }

        onUpdateFieldsHistory:{
            body.updateDataFromHistory(data)
            widgetSettings.setCurrentTypeRequest(data["TYPE"])
        }

        onAddHistoryInList:{
            body.addHistory(titleHistory)
        }

    }
    Timer{
        id: updaterLogs
        repeat: false
        interval: timeToRepeat + '000'
        onTriggered: {
            if(footer.uuid)
                body.sendRequest(requestData, true)
            else
                updaterLogs.stop()
        }
    }

    ////////шапка/////////
  MainWindow.Header {
        id: header
        anchors.fill: parent
        anchors.bottomMargin: parent.height - 45
        width: parent.width
    }

  SplitView{
      anchors.top: header.bottom
      anchors.left: header.left
      width: parent.width
      height: parent.height
      orientation: Qt.Vertical
      Layout.fillHeight: true
      Layout.fillWidth: true
    /////////////Основная часть////////////
    MainWindow.Body {
        id: body
        width: parent.width
        Layout.minimumHeight: 150
    }
    //////////Нижняя полоска////////
    MainWindow.Footer{
        id: footer
        anchors.top: body.bottom
        anchors.left: body.left
        anchors.bottomMargin: 20
        Layout.minimumHeight: 200
    }
  }
    Popup{
        id: settingsGateway
        leftMargin: parent.width - 300
        background: Rectangle {
          color: "#e8e8e8"
        }

        contentItem: Shared.Settings{
            id: widgetSettings
        }
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside
        modal: true
    }
}
