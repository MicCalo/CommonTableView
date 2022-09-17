#ifndef TABLEVIEWMODEL_H
#define TABLEVIEWMODEL_H

#include <QObject>
#include <QAbstractTableModel>

class ColumnType : public QObject {
    Q_OBJECT
public:
    enum class Enum{
        String,
        Number,
        Bool,
        SelectionBool
    };
    Q_ENUM(Enum)
};

class TableViewModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    enum Roles{
        DisplayRole = Qt::DisplayRole,
        TypeRole =  Qt::UserRole + 1,
        SelectedRole
    };
    Q_ENUMS(Roles);



    explicit TableViewModel(QObject *parent = nullptr);

    virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    virtual bool setData(const QModelIndex &index, const QVariant &newValue, int role = Qt::DisplayRole) override;
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual QHash<int, QByteArray> roleNames() const override;

private:
    struct DemoColumn{
        QString header;
        ColumnType::Enum type;
        QList<QVariant> items;
    };

    QList<DemoColumn> data_;
    QList<int> selectedRows_;


};

#endif // TABLEVIEWMODEL_H
