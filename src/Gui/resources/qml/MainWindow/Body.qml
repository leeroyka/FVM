import QtQuick 2.10
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls.Material 2.12
import QtQuick.Dialogs 1.2
import "../Shared" as Shared

Item{
    property variant arrayButtonArgs
    function updateArgs()
    {
      var count = qmlApp.getNumberArgsFromExpression()
      for(var i in arrayButtonArgs)
      {
        arrayButtonArgs[i].destroy();
      }
      arrayButtonArgs = []
      for(var i=0; i<count;i++)
      {
        var btn = buttonArg.createObject(layoutArgs, {
                                         "text"     : "X<font size=\"1\">"+(i+1)+"</font>",
                                         "buttonId" : (i+1)});
        arrayButtonArgs[i] = btn;
      }
    }

    function calculate(func)
    {
      //isCorrectExpression(func)
      if(!func)
      {
        dialogError.setText("Ошибка! Не введена функция")
        dialogError.open()
          return
      }
      qmlApp.setRange(footer.min, footer.max, footer.step)
      var answer = qmlApp.calculate(func)
      footer.printAnswer(answer)
      footer.updateVoxelView()
      footer.updateFunctionView()
    }

    function clickedArgButton(buttonId)
    {
      inputFunction.insert(inputFunction.cursorPosition,"x_"+buttonId);
    }
    function addArg()
    {
      qmlApp.addArgInExpression();
      updateArgs();
    }
    function removeArg()
    {
      qmlApp.removeArgumentFromExpression();
      updateArgs();
    }

    function updateDataFromHistory(data){
        mainWindow.requestIp = data["IP"]
        inputJsonData.text = data["JSON"]
        mainWindow.requestPort = data["PORT"]
        mainWindow.requestServiceName = data["SNAME"]
        mainWindow.requestType = data["TYPE"]
    }

    DropArea{
        anchors.fill: parent
        onDropped: {
            if(drop.hasText){
                var dataFromFile = qmlApp.loadJsonFromFile(drop.text)
                if(dataFromFile)
                    inputJsonData.text = dataFromFile;
                else{
                    dialogError.setText('Ошибка! Json файл не корректен!')
                    dialogError.open()
                }
            }
            drop.accepted = true
        }
    }
    Component.onCompleted: {
      updateArgs();
    }

    Component {
      id: buttonArg;
      Button {
        property string buttonId;
        Layout.preferredWidth: 30
        Layout.preferredHeight: 30
        MouseArea {
          anchors.fill: parent
          acceptedButtons: Qt.RightButton
          onClicked: {
              removeArg()
          }
        }
        onClicked: {
            clickedArgButton(buttonId)
        }
      }
    }

    RowLayout {
      id: layoutArgs
      anchors.top: parent.top
      anchors.left: parent.left
      anchors.leftMargin: 20
      anchors.topMargin: 30
      Button {
          id: buttonAddArgument
          Text {
            anchors.centerIn: parent
            font.pixelSize: 15
            text: qsTr("<b>+</b>")
          }

          Layout.preferredWidth: 35
          Layout.preferredHeight: 35
          onClicked: {
            addArg()
          }
      }
    }
    Text {
      id: labelFunction
      text: qsTr("f(x)=")
      font.pixelSize: 14
      anchors.top: layoutArgs.bottom
      anchors.left: parent.left
      anchors.leftMargin: 20
      anchors.topMargin: 10
    }

    Item {
      id: func
      anchors.top: labelFunction.top
      anchors.left: labelFunction.right
      anchors.leftMargin: 10
      anchors.bottomMargin: 40
      width: parent.width - func.x - 20
      height: 21
      property alias text: inputFunction.text
      Rectangle{
                  radius: 2
                  anchors.fill: parent
                  border.color: "#000000"
                  border.width: 1
              }
      TextInput {
          id: inputFunction
          anchors.centerIn: parent
          width: parent.width - 16
          focus: true
          autoScroll: false
          selectByMouse: true
          onTextChanged: {
          }
      }
    }
    Button {
        id: buttonCalculate
        anchors.top: labelFunction.bottom
        anchors.topMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: (parent.width / 2) - (buttonCalculate.width / 2)
        text: qsTr("Посчитать")
        onClicked: {
              calculate(inputFunction.text)
        }
    }

            Shortcut{
                sequence: "Ctrl+Return"
                onActivated: {
                    footer.outText = ''
                }
            }
            Dialog{
                id: dialogError
                title: "Error"
                standardButtons: Dialog.Ok
                Label{
                    id:labelError
                    text: qsTr('Ошибка! Функция не корректна!')
                }
                function setText(errorText){
                    labelError.text = errorText
                }
            }
}
