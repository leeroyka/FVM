import QtQuick 2.10
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Item{
    function setCurrentTypeRequest(requestType){
        comboSettingsTypeRequest.currentIndex =
                comboSettingsTypeRequest.find(mainWindow.requestType)
    }
    GridLayout{
        id: grid
        columns: 2
        Label{
            text: qsTr("Настройка шлюза")
            Layout.columnSpan: 2
            font.bold: true
            font.pointSize: 14
        }
        Label{
            text: qsTr('Метод')
        }
        ComboBox {
            id: comboSettingsTypeRequest
            editable: false
            model: ListModel{
                id: modelSettingsTypeRequest
                ListElement {text : "POST";}
                ListElement {text : "PUT";}
                ListElement {text : "GET";}
    //                ListElement {text : "REMOVE";}
            }
            onCurrentIndexChanged: mainWindow.requestType =
                                           comboSettingsTypeRequest.currentText}
        Label{
            text: qsTr('IP адрес')
        }
        TextField{
            id: inputIP
            text: mainWindow.requestIp
            onTextChanged: mainWindow.requestIp = text
        }
        Label{
            text: qsTr('Порт')
        }
        TextField{
            id: inputPort
            text: mainWindow.requestPort
            onTextChanged: mainWindow.requestPort = text
        }
        Label{
            text: qsTr('Endpoind')
        }
        TextField{
            id: inputServiceName
            text: mainWindow.requestServiceName
            onTextChanged: mainWindow.requestServiceName = text
        }
    }
}
