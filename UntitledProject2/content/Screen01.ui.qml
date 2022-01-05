import QtQuick
import QtQuick.Controls
import UntitledProject2

Rectangle {
    width: Constants.width
    height: Constants.height

    color: Constants.backgroundColor

    Text {
        text: qsTr("Hello UntitledProject2")
        anchors.centerIn: parent
        font.family: Constants.font.family
    }
}
