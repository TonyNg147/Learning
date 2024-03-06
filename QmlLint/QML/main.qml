import QtQuick
Window
{
    visible: true
    width: 1280
    height: 720

    ListModel
    {
        id: entryList
        ListElement{color:"red"}
        ListElement{color:"blue"}
    }

    ListView{
        id: list
        width: 640
        height: 480
        anchors.centerIn: parent
        model: entryList
        delegate: 
        Rectangle
        {
            width: list.width
            height: list.height
            color: model.color
        }
    }
}