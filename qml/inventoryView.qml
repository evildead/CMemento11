/*************************************************
 *                                               *
 *   Author: Danilo Carrabino                    *
 *                                               *
 *************************************************/

import QtQuick 2.2
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.1

Item {
    // green
    property var normalColor: String("#ff21be2b")
    property var selectedColor: String("#FF17a81a")

    id: mainContent

    anchors.fill: parent

    Timer {
        id: timer
    }

    function delay(delayTime, cb) {
        timer.interval = delayTime;
        timer.repeat = false;
        timer.triggered.connect(cb);
        timer.start();
    }

    function execClearAll() {
        if(inventoryModel.rowCount() > 0) {
            inventoryModel.clearAll();
        }
    }

    function execDeleteListable() {
        if((inventoryList.currentIndex >= 0) && (inventoryList.currentIndex < inventoryModel.rowCount())) {
            inventoryModel.removeListable(inventoryList.currentIndex)
        }
    }

    function execUndo() {
        if(inventoryModel.isUndoable()) {
            inventoryModel.undo();
        }
    }

    function execRedo() {
        if(inventoryModel.isRedoable()) {
            inventoryModel.redo();
        }
    }

    function execAddListable() {
        var listableType = listableTypeComboBox.currentIndex + 1;
        var listableName = listableNameTextField.text;
        inventoryModel.addListable(listableType, listableName);
        inventoryList.positionViewAtEnd();
    }

    function execInsertListable() {
        if((inventoryList.currentIndex >= 0) && (inventoryList.currentIndex < inventoryModel.rowCount())) {
            var listableType = listableTypeComboBox.currentIndex + 1;
            var listableName = listableNameTextField.text;
            inventoryModel.insertListable(listableType, listableName, inventoryList.currentIndex);
        }
    }

    ComboBox {
        x: 10
        y: 10
        id: listableTypeComboBox
        model: [ "Book", "CD-Rom", "DVD" ]
    }

    TextField {
        x: 10
        y: 35
        id: listableNameTextField
        placeholderText: qsTr("Enter item name")
    }

    Button {
        x: 10
        y: 100
        id: cmdButtonAdd
        Layout.alignment: Qt.AlignLeft
        anchors.topMargin: 10

        text: qsTr("Add Item")

        style: ButtonStyle {
            background: Rectangle {
                implicitWidth: 120
                implicitHeight: 40
                opacity: enabled ? 1 : 0.3
                border.color: cmdButtonAdd.down ? selectedColor : normalColor
                border.width: 1
                radius: 2
            }

            label: Text {
                text: cmdButtonAdd.text
                opacity: enabled ? 1.0 : 0.3
                color: cmdButtonAdd.down ? selectedColor : normalColor
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
            }
        }

        action: Action {
            enabled: true

            onTriggered: {
                execAddListable();
                console.log("Add detected!")
            }
        }
    }

    Button {
        x: 10
        y: 150
        id: cmdButtonInsert
        Layout.alignment: Qt.AlignLeft
        anchors.topMargin: 10

        text: qsTr("Insert Item")

        style: ButtonStyle {
            background: Rectangle {
                implicitWidth: 120
                implicitHeight: 40
                opacity: enabled ? 1 : 0.3
                border.color: cmdButtonInsert.down ? selectedColor : normalColor
                border.width: 1
                radius: 2
            }

            label: Text {
                text: cmdButtonInsert.text
                opacity: enabled ? 1.0 : 0.3
                color: cmdButtonInsert.down ? selectedColor : normalColor
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
            }
        }

        action: Action {
            enabled: ((inventoryList.currentIndex >= 0) && (inventoryList.currentIndex < inventoryList.count)) ? 1 : 0

            onTriggered: {
                execInsertListable();
                console.log("Insert detected!")
            }
        }
    }

    Button {
        x: 10
        y: 200
        id: cmdButtonClearAll
        Layout.alignment: Qt.AlignLeft
        anchors.topMargin: 10
        text: qsTr("Clear All")

        style: ButtonStyle {
            background: Rectangle {
                implicitWidth: 120
                implicitHeight: 40
                opacity: enabled ? 1 : 0.3
                border.color: cmdButtonClearAll.down ? selectedColor : normalColor
                border.width: 1
                radius: 2
            }

            label: Text {
                text: cmdButtonClearAll.text
                opacity: enabled ? 1.0 : 0.3
                color: cmdButtonClearAll.down ? selectedColor : normalColor
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
            }
        }

        action: Action {
            enabled: (inventoryList.count > 0) ? 1 : 0

            onTriggered: {
                execClearAll();
                console.log("Clear all detected!")
            }
        }
    }

    Button {
        x: 10
        y: 250
        id: cmdButtonDelete
        Layout.alignment: Qt.AlignLeft
        anchors.topMargin: 10

        text: qsTr("Delete Item")

        style: ButtonStyle {
            background: Rectangle {
                implicitWidth: 120
                implicitHeight: 40
                opacity: enabled ? 1 : 0.3
                border.color: cmdButtonDelete.down ? selectedColor : normalColor
                border.width: 1
                radius: 2
            }

            label: Text {
                text: cmdButtonDelete.text
                opacity: enabled ? 1.0 : 0.3
                color: cmdButtonDelete.down ? selectedColor : normalColor
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
            }
        }

        action: Action {
            enabled: ((inventoryList.currentIndex >= 0) && (inventoryList.currentIndex < inventoryList.count)) ? 1 : 0

            onTriggered: {
                execDeleteListable();
                console.log("Delete detected!")
            }
        }
    }

    Button {
        x: 10
        y: 300
        id: cmdButtonUndo
        Layout.alignment: Qt.AlignLeft
        anchors.topMargin: 10

        text: qsTr("Undo")

        style: ButtonStyle {
            background: Rectangle {
                implicitWidth: 120
                implicitHeight: 40
                opacity: enabled ? 1 : 0.3
                border.color: cmdButtonUndo.down ? selectedColor : normalColor
                border.width: 1
                radius: 2
            }

            label: Text {
                text: cmdButtonUndo.text
                opacity: enabled ? 1.0 : 0.3
                color: cmdButtonUndo.down ? selectedColor : normalColor
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
            }
        }

        action: Action {
            enabled: (inventoryList.isModelUndoable) ? 1 : 0

            onTriggered: {
                execUndo()
                console.log("Undo detected!");
            }
        }
    }

    Button {
        x: 10
        y: 350
        id: cmdButtonRedo
        Layout.alignment: Qt.AlignLeft
        anchors.topMargin: 10

        text: qsTr("Redo")

        style: ButtonStyle {
            background: Rectangle {
                implicitWidth: 120
                implicitHeight: 40
                opacity: enabled ? 1 : 0.3
                border.color: cmdButtonRedo.down ? selectedColor : normalColor
                border.width: 1
                radius: 2
            }

            label: Text {
                text: cmdButtonRedo.text
                opacity: enabled ? 1.0 : 0.3
                color: cmdButtonRedo.down ? selectedColor : normalColor
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
            }
        }

        action: Action {
            enabled: (inventoryList.isModelRedoable) ? 1 : 0

            onTriggered: {
                execRedo();
                console.log("Redo detected!");
            }
        }
    }

    Rectangle {
        id: rectListView
        y: 10
        x: 150
        width: 300
        height: 530

        ScrollView {
            anchors.fill: parent;

            ListView {
                id: inventoryList
                anchors.fill: rectListView;
                width: rectListView.width
                height: rectListView.height
                model: inventoryModel
                property bool isModelUndoable: inventoryModel.isUndoable()
                property bool isModelRedoable: inventoryModel.isRedoable()

                delegate: Item {
                    id: container
                    height: listableRect.height

                    Rectangle {
                        id: listableRect
                        height: textLabel.height * 2
                        width: inventoryList.width
                        color: (inventoryList.currentIndex == index) ? "#E6FFE6" : "white"    // green
                        opacity: (inventoryList.currentIndex == index) ? 0.8 : 1
                        radius: (inventoryList.currentIndex == index) ? 20 : 0
                        ColorAnimation on color { duration: 1000 }

                        MouseArea {
                            id: dragArea
                            anchors.fill: parent
                            hoverEnabled: true         //this line will enable mouseArea.containsMouse

                            onClicked: {
                                inventoryList.currentIndex = index
                                console.log("MouseArea onClicked: index = " + index);
                            }

                            onDoubleClicked: {
                                inventoryList.currentIndex = index
                                console.log("MouseArea onDoubleClicked: index = " + index);
                            }
                        }

                        Text {
                            id: textLabel
                            anchors.centerIn: parent
                            text: title
                            color: selectedColor
                        }

                        // Bottom line border
                        Rectangle {
                            anchors {
                                left: parent.left
                                right: parent.right
                                bottom: parent.bottom
                            }
                            height: 2
                            color: selectedColor
                        }
                    }
                }

                Connections {
                    target: inventoryModel
                    onDataChanged: {
                        inventoryList.isModelUndoable = inventoryModel.isUndoable()
                        inventoryList.isModelRedoable = inventoryModel.isRedoable()
                    }

                    onModelAboutToBeReset: {

                    }

                    onModelReset: {
                        inventoryList.isModelUndoable = inventoryModel.isUndoable()
                        inventoryList.isModelRedoable = inventoryModel.isRedoable()
                        console.log("Model rows: " + inventoryModel.rowCount());

                        delay(100, function() {
                            inventoryList.width = rectListView.width - 1;
                            inventoryList.height = rectListView.height - 1;
                            inventoryList.width = rectListView.width;
                            inventoryList.height = rectListView.height;

                            if((inventoryList.currentIndex >= 0) && (inventoryList.currentIndex < inventoryModel.rowCount())) {
                                console.log("onModelReset inside if");
                                inventoryList.positionViewAtIndex(inventoryList.currentIndex, ListView.Visible);
                            }
                        });
                    }

                    onRowsMoved: {
                        inventoryList.isModelUndoable = inventoryModel.isUndoable()
                        inventoryList.isModelRedoable = inventoryModel.isRedoable()
                    }

                    onRowsRemoved: {
                        inventoryList.isModelUndoable = inventoryModel.isUndoable()
                        inventoryList.isModelRedoable = inventoryModel.isRedoable()
                    }

                    onRowsInserted: {
                        inventoryList.isModelUndoable = inventoryModel.isUndoable()
                        inventoryList.isModelRedoable = inventoryModel.isRedoable()
                    }
                }

                populate: Transition {
                    NumberAnimation { properties: "y"; from: 30; duration: 10; easing.type: Easing.InOutBounce; }
                }

                add: Transition {
                    NumberAnimation { property: "opacity"; from: 0; to: 1.0; duration: 500 }
                    NumberAnimation { property: "scale"; from: 0; to: 1.0; duration: 500 }
                }

                remove: Transition {
                    ParallelAnimation {
                        NumberAnimation { properties: "x,y"; duration: 500; easing.type: Easing.OutBounce }
                    }
                }
            }
        }

        Component.onCompleted: {

        }
    }
}
