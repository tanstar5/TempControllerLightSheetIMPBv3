import QtQuick 2.12
import QtQuick.Controls 2.12
//import QtQml 2.15

Item {
    id: uiID
    width: 1200
    height: 800
    property int sensor_set: _val1
    property int sensor_read: _val2
    //property bool sensor_warming: false
    property string com_channel: "com6"

    //property string aotfcom_channel: _obj.


    property bool l561_on: false
    property bool l491_on: false

    //signal qmlSignal1()

    Rectangle {
        id: rectangle
        color: "#ffffff"
        anchors.fill: parent
        anchors.rightMargin: 0

        //property int sensor_set: 140
        //property int sensor_read: 0
        //color: cyan

        Dial {
            id: dial
            width: 400
            height: 400
            anchors.verticalCenter: parent.verticalCenter
            z: 1
            anchors.horizontalCenter: dial1.horizontalCenter
            live: true
            stepSize: 5
            value: sensor_set
            wheelEnabled: true
            to: 255
            from: 1
            onValueChanged: _obj.dial1Set(value)
            palette.dark: "orange"

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
                value: settemp.value
                to: 50
                from: 20
                anchors.horizontalCenter: parent.horizontalCenter
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
                font.pointSize: 20
                value: cali_temp.value/(cali_sensor.value)*dial.value
            }


        }

        Dial {
            id: dial1
            x: 1
            width: 697
            height: 684
            opacity: 1
            anchors.verticalCenter: parent.verticalCenter
            layer.mipmap: false
            z: 0
            anchors.verticalCenterOffset: 0
            enabled: true
            wheelEnabled: true
            live: true
            stepSize: 1
            to: 255
            from: 1
            value: sensor_read
            palette.dark: "red"


            ProgressBar {
                id: progressBar1
                y: 550
                to: 50
                from: 20
                value: spinBox2.value
                anchors.horizontalCenterOffset: 0
                anchors.horizontalCenter: parent.horizontalCenter
            }

            SpinBox {
                id: spinBox1
                x: 279
                y: 564
                z: 0
                layer.enabled: false
                font.pointSize: 9
                font.kerning: false
                to: dial1.to
                from: 1
                value: dial1.value
            }

            SpinBox {
                id: spinBox2
                x: 279
                y: 608
                font.pointSize: 20
                value: cali_temp.value/(cali_sensor.value)*dial1.value
            }

            Text {
                id: text1
                x: 338
                y: 469
                text: qsTr("Set")
                font.pixelSize: 12
            }

            Text {
                id: text2
                x: 339
                y: 662
                text: qsTr("Read")
                font.pixelSize: 12
            }

            SwitchDelegate {
                id: switchDelegate
                y: 8
                text: qsTr("Warming")
                anchors.horizontalCenterOffset: 0
                anchors.horizontalCenter: parent.horizontalCenter
                checked:  (sensor_read<sensor_set)

            }
        }

        ComboBox {
            id: comboBox
            y: 35
            anchors.left: parent.left
            anchors.leftMargin: 8
            currentIndex: 5
            model: ["COM1","COM2","COM3","COM4","COM5","COM6","COM7","COM8","COM9","COM10","COM11","COM12","COM13"]
            //currentIndex: com_channel
            onCurrentTextChanged: _obj.setValue3(currentText);
        }

        Button {
            id: button
            x: 300
            text: qsTr("Connect")
            anchors.top: dial1.bottom
            anchors.topMargin: -588
            checkable: true
            onClicked:  _obj.readSerial()
            //autoRepeat: true
            onPressed: _obj.contiSerial(checked)
            //palette.dark: "green"

        }

        GroupBox {
            id: groupBox
            x: 747
            y: 90
            width: 398
            height: 119
            title: qsTr("L561")

            Button {
                id: button1
                x: -12
                y: 9
                width: 112
                height: 40
                text: qsTr("L561")
                anchors.left: parent.left
                anchors.leftMargin: -12
                checkable: true
                palette.dark: "green"
                onClicked:   _obj.onL561(checked)
                checked:  l561_on
                //autoRepeat: true
                //onPressed: _obj.contiSerial(checked)
            }

            SpinBox {
                id: spinBox3
                x: 192
                y: 9
                width: 137
                height: 40
                anchors.right: parent.right
                anchors.top: parent.top
                stepSize: 100
                to: 60000
                from: 1000
                value: 5000
                anchors.rightMargin: -12
                anchors.topMargin: 9
                onValueChanged: _obj.update_L561activetime(value);
            }

            Slider {
                id: slider
                x: 96
                y: 55
                width: 182
                height: 40
                value: 0.5
                palette.dark: "green"
            }

            Label {
                id: label1
                text: qsTr("ms")
                anchors.top: spinBox3.bottom
                anchors.horizontalCenter: spinBox3.horizontalCenter
                anchors.topMargin: 6
            }

            Label {
                id: label7
                x: 155
                y: 9
                text: qsTr("Expose time")
            }
        }

        GroupBox {
            id: groupBox1
            x: 747
            y: 261
            width: 398
            height: 119
            title: qsTr("L491")

            Slider {
                id: slider1
                x: 96
                y: 55
                width: 182
                height: 40
                value: 0.5
                palette.dark: "purple"
            }

            Button {
                id: button2
                x: 197
                y: 17
                text: qsTr("L491")
                anchors.left: parent.left
                checkable: true
                anchors.leftMargin: -12
                palette.dark: "purple"
                //checkable: true
                onClicked:   _obj.onL491(checked)
                checked:  l491_on

            }

            SpinBox {
                id: spinBox4
                x: 189
                y: 136
                anchors.right: parent.right
                anchors.top: parent.top
                value: 5000
                stepSize: 100
                to: 60000
                from: 1000
                anchors.rightMargin: -12
                anchors.topMargin: 17
                onValueChanged: _obj.update_L491activetime(value);
            }

            Label {
                id: label2
                text: qsTr("ms")
                anchors.top: spinBox4.bottom
                anchors.horizontalCenter: spinBox4.horizontalCenter
                anchors.topMargin: 6
            }

            Label {
                id: label8
                x: 155
                y: 17
                text: qsTr("Expose time")
            }
        }

        Button {
            id: button4
            x: 896
            y: 24
            text: qsTr("protocol")
            anchors.right: parent.right
            anchors.top: parent.top
            checkable: true
            anchors.topMargin: 35
            anchors.rightMargin: 204
            onClicked: _obj.startProtocol(checked)
        }

        ComboBox {
            id: comboBox1
            x: 1039
            y: 24
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.leftMargin: 747
            anchors.topMargin: 35
            currentIndex: 0;
            model: ["COM1","COM2","COM3","COM4","COM5","COM6","COM7","COM8","COM9","COM10","COM11","COM12","COM13"]
            onCurrentTextChanged: _obj.setAotfCom(currentText)
        }

        Text {
            id: text3
            x: 926
            y: 718
            width: 162
            height: 16
            text: qsTr("By TS using Qt (LGPL licence)")
            font.pixelSize: 12
        }

        SpinBox {
            id: spinBox5
            x: 876
            y: 215
            editable: true
            value: 5
            stepSize: 10
            to: 7200
            from: spinBox3.value/1000
            onValueChanged: _obj.setIntervaltimeProtocol(value);
        }

        SpinBox {
            id: spinBox6
            x: 1005
            y: 35
            editable: true
            value: 30
            stepSize: 10
            to: spinBox3.to/1000 + spinBox4.to/1000 + (spinBox5.to)
            from: spinBox3.value/1000 + spinBox4.value/1000 + spinBox5.value
            onValueChanged: _obj.setGlobaltimeProtocol(value);
        }

        Label {
            id: label3
            x: 1022
            y: 227
            text: qsTr("secs")
        }

        Label {
            id: label
            x: 1151
            y: 47
            text: qsTr("secs")
        }

        Label {
            id: label4
            x: 784
            y: 13
            width: 67
            height: 16
            text: qsTr("Aotf comm")
        }

        Label {
            id: label5
            x: 929
            y: 13
            width: 67
            height: 16
            text: qsTr("Start")
        }

        Label {
            id: label6
            x: 1055
            y: 13
            width: 67
            height: 16
            text: qsTr("Loop interval")
        }

        Label {
            id: label9
            x: 792
            y: 227
            width: 67
            height: 16
            text: qsTr(" interval")
        }

        Image {
            id: image
            x: 747
            y: 406
            width: 400
            height: 300
            source: "PNG/Asset 1@4x.png"
            antialiasing: true
            smooth: false
            fillMode: Image.PreserveAspectFit
        }






    }
}





/*##^##
Designer {
    D{i:0;formeditorZoom:0.5}D{i:3}D{i:4}D{i:5}D{i:6}D{i:7}D{i:2}D{i:9}D{i:10}D{i:11}
D{i:12}D{i:13}D{i:14}D{i:8}D{i:15}D{i:16}D{i:18}D{i:19}D{i:20}D{i:21}D{i:22}D{i:17}
D{i:24}D{i:25}D{i:26}D{i:27}D{i:28}D{i:23}D{i:29}D{i:30}D{i:31}D{i:32}D{i:33}D{i:34}
D{i:35}D{i:36}D{i:37}D{i:38}D{i:39}D{i:40}D{i:1}
}
##^##*/
