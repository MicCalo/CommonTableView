import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import Qt.labs.qmlmodels;

import Lib 1.0

Item{
    HorizontalHeaderView
    {
        id: headerView
        syncView: tableView
        width: parent.width
    }

    TableView{
        id: tableView
        columnSpacing: 4
        rowSpacing: 4
        anchors.top: headerView.bottom
        anchors.bottom: parent.bottom
        width: parent.width
        model: TableViewModel{}
        clip: true

        delegate: DelegateChooser{
            role: "typeRole"
            DelegateChoice{
                 roleValue: ColumnType.SelectionBool
                 Rectangle{
                    implicitWidth: 20
                    implicitHeight: 20

                    CheckBox{
                        checked: model.selectedRole
                        tristate: false;
                        onCheckedChanged: {
                            model.selectedRole = checked
                        }
                    }
                }
            }
            DelegateChoice{
                Rectangle{
                    implicitWidth: Math.max(20, text.implicitWidth)
                    implicitHeight: text.implicitHeight
                    Text{
                        id: text
                        text: model.displayRole
                        width: parent.width
                        font.preferShaping: false
                        color: model.selectedRole ? "red" : "black"
                    }
                }
            }
        }
    }
}
