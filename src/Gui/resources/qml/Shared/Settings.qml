import QtQuick 2.10
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Item{

    GridLayout{
        id: grid
        columns: 2
        Label{
            text: qsTr("Настройки отображения")
            Layout.columnSpan: 2
            font.bold: true
            font.pointSize: 14
        }

        Label{
            text: qsTr('Voxel size')
        }
        TextField{
            id: inputVoxelSize
            text: footer.voxelSize
            onTextChanged: footer.voxelSize = parseFloat(text)
        }
        Label{
            text: qsTr('Min')
        }
        TextField{
            id: inputMin
            text: footer.min
            onTextChanged: footer.min = parseFloat(text)
        }
        Label{
            text: qsTr('Max')
        }
        TextField{
            id: inputMax
            text: footer.max
            onTextChanged: footer.max = parseFloat(text)
        }
        Label{
            text: qsTr('Step')
        }
        TextField{
            id: inputStep
            text: footer.step
            onTextChanged: footer.step = parseFloat(text)
        }

    }
}
