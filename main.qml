import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
//import interface.qml


Window {
    width: 1400
    maximumWidth: 1200
    minimumWidth: 700
    height: 800
    maximumHeight: 800
    minimumHeight: 400
    visible: true
    title: qsTr("LightSheet@IMPB")

    InterfaceUI{
        id: uiGui
        sensor_read: _obj.Value2
        sensor_set: _obj.Value1
        com_channel: _obj.Value3

        l561_on: _obj.Laser561
        l491_on: _obj.Laser491

    }



}
