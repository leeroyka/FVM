import QtQuick 2.10
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import "../Shared" as Shared

Item{
    property string answerText: ""
    property double voxelSize: 1
    property double min: -3
    property double max: 3
    property double step: 0.05
    property int voxelPadding: 20
    property variant arrayVoxelViews
    property variant functionView
    function printAnswer(data)
    {
        //answerText = data;
    }
    function updateVoxelView()
    {
      if(qmlApp.getNumberArgsFromExpression()!=2)
        return;
      for(var i in arrayVoxelViews)
      {
        arrayVoxelViews[i].destroy();
      }
      arrayVoxelViews = []
      for(var i=0; i<4;i++)
      {
        var vv = componentVoxelView.createObject(tabVoxelModel, {});
        arrayVoxelViews[i] = vv;
      }
    }
    function updateFunctionView()
    {
      if(qmlApp.getNumberArgsFromExpression()!=2)
        return;
      functionView = componentFunctionView.createObject(tabExpression, {});
    }
    function drawFunctionView(ctx)
    {
      var matrix = qmlApp.getMatrixValues();
      var max    = qmlApp.getMaxValue();
      for(var row = 0; row < matrix.length; row++)
      {
        var rowList = matrix[row];
        for(var value = 0; value<rowList.length; value++)
        {
          var pointColor = rowList[value]/max;
          ctx.fillStyle = Qt.rgba(pointColor, pointColor, pointColor, 1);
          ctx.fillRect(row*voxelSize+voxelPadding,
                       value*voxelSize+voxelPadding,
                       voxelSize,
                       voxelSize)
        }
      }
    }

    function drawVoxelView(ctx)
    {

      var voxelView = qmlApp.getVoxelView();
      for(var num=0;num<4;num++)
      {
        for(var row=0;row<voxelView.length;row++)
        {
          var rowList = voxelView[row];
          for(var column=0;column<rowList.length;column++)
          {
            var pointColor = rowList[column][num];
            pointColor += 1;
            pointColor /= 2;
            ctx.fillStyle = Qt.rgba(pointColor, pointColor, pointColor, 1);

            ctx.fillRect(row*voxelSize+voxelView.length*voxelSize*num*1.05+voxelPadding,
                         column*voxelSize+voxelPadding,
                         voxelSize,
                         voxelSize);
          }

        }
      }
    }

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
    Component {
      id: componentVoxelView;
      Canvas {
        id: canvasVoxelView

        anchors.leftMargin: 20;
        anchors.topMargin: 20;
        width: parent.width
        height: parent.height
        onPaint: {
          var ctx = getContext("2d");
          drawVoxelView(ctx)
        }
      }
    }
    Component {
      id: componentFunctionView;
      Canvas {
        id: canvasFunctionView

        anchors.leftMargin: 20;
        anchors.topMargin: 20;
        width: parent.width
        height: parent.height
        onPaint: {
          var ctx = getContext("2d");
          drawFunctionView(ctx)
        }
      }
    }
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
        title: "Voxel View"
      }
      Tab {
        id: tab3dModel
        title: "3D"
        enabled: false
        Text {
          leftPadding: 10
          id: nameC
          text: qsTr("c")
        }
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
}
