#include "TableViewModel.hpp"

TableViewModel::TableViewModel(QObject *parent)
    : QAbstractTableModel{parent}
{
    data_.append({"Selected", ColumnType::Enum::SelectionBool, {false, true, false, false, true, false, false, false, false, true}});
    data_.append({"State", ColumnType::Enum::Number, {1,1,1,2,4,5,6,1,2,3}});
    data_.append({"Name", ColumnType::Enum::String, {"Einz", "Zwo", "Drü", "Vier", "Füf", "Sächs", "Siba", "Oacht", "Nün", "Zehn"}});
    data_.append({"Description", ColumnType::Enum::String, {"Einz", "Zwo", "Drü", "Vier kommt grad nachem drü", "Füf", "", "Siba", "Oacht", "Nün", "Zehn"}});
    data_.append({"Wert", ColumnType::Enum::Number, {1, 2,3,4,5,6,7,8,9,10}});
    data_.append({"Wert2", ColumnType::Enum::Number, {1.1, 2.2,3.3,4.4,5.5,6.6,7.7,8.8,9.9,10.0}});

    int i{0};
    for(auto & val: data_[0].items){
        if (val.toBool()){
            selectedRows_.append(i);
        }
        i++;
    }
}

QVariant TableViewModel::headerData(int section, Qt::Orientation /*orientation*/, int /*role*/ ) const {
    return data_[section].header;
}

QVariant TableViewModel::data(const QModelIndex &index, int role) const {
    QVariant result;
    if (index.isValid()){
        if (role == DisplayRole){
            result = data_[index.column()].items[index.row() % 10];
        }else if (role == TypeRole){
            result = static_cast<int>(data_[index.column()].type);
        }else if (role == SelectedRole){
            result = selectedRows_.contains(index.row());
        }
    }
    return result;
}

bool TableViewModel::setData(const QModelIndex &index, const QVariant &newValue, int role) {
    bool changed{false};
    if (index.isValid()){
        if (role == SelectedRole){
            bool newIsSelected = newValue.toBool();
            if (newIsSelected != selectedRows_.contains(index.row())){
                if (newIsSelected){
                    selectedRows_.append(index.row());
                }else{
                    qsizetype pos{selectedRows_.indexOf(index.row())};
                    selectedRows_.removeAt(pos);
                }
                changed = true;
                emit dataChanged(createIndex(index.row(), 0), createIndex(index.row(), columnCount()));

                // TODO update underlying data
            }

        }
    }
    return changed;
}


int TableViewModel::rowCount(const QModelIndex &/*parent*/) const {
   return 1000;
}

int TableViewModel::columnCount(const QModelIndex &/*parent*/ ) const {
    return data_.count();
}

QHash<int, QByteArray> TableViewModel::roleNames() const {
    return QHash<int, QByteArray>{
        {DisplayRole, "displayRole"},
        {TypeRole, "typeRole"},
        {SelectedRole, "selectedRole"},
    };
}

