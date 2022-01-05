import QtQuick 2.12
import QtQuick.Controls 2.12

Item {
    id: interID
    width: 800
    height: 800
    property int sensor_set: 140
    property int sensor_read: 0
    Rectangle {
        id: rectangle
        color: Constants.backgroundColor
        anchors.fill: parent

        Dial {
            id: dial
            width: 400
            height: 400
            anchors.verticalCenter: parent.verticalCenter
            stepSize: 5
            value: sensor_set
            wheelEnabled: true
            to: 255
            from: 1
            anchors.horizontalCenter: parent.horizontalCenter

            SpinBox {
                id: spinBox
                y: 217
                anchors.horizontalCenterOffset: 0
                to: dial.to
                from: dial.from
                value: dial.value
                anchors.horizontalCenter: parent.horizontalCenter
            }

            ProgressBar {
                id: progressBar
                x: 100
                y: 197
                anchors.verticalCenter: parent.verticalCenter
                to: 50
                from: 20
                anchors.horizontalCenter: parent.horizontalCenter
                value: 0.5
            }

            SpinBox {
                id: cali_temp
                x: 131
                y: 144
                width: 138
                height: 40
                value: 35
            }

            SpinBox {
                id: cali_sensor
                x: 131
                y: 98
                width: 138
                height: 40
                to: 255
                value: 140
            }

            SpinBox {
                id: settemp
                x: 131
                y: 264
                value: cali_temp.value/(cali_sensor.value)*dial.value
            }
        }

        Dial {
            id: dial1
            width: 697
            height: 684
            opacity: 0.5
            anchors.verticalCenter: parent.verticalCenter
            stepSize: 1
            to: 255
            from: 1
            value: sensor_read
            anchors.horizontalCenter: parent.horizontalCenter

            ProgressBar {
                id: progressBar1
                y: 596
                anchors.horizontalCenter: parent.horizontalCenter
                value: 0.5
            }

            SpinBox {
                id: spinBox1
                x: 279
                y: 616
                to: dial1.to
                from: 1
                value: dial1.value
            }
        }
    }

}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.66}D{i:3}D{i:4}D{i:5}D{i:6}D{i:7}D{i:2}D{i:9}D{i:10}D{i:8}
D{i:1}
}
##^##*/
