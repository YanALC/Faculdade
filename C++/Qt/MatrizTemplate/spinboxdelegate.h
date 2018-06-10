#ifndef SPINBOXDELEGATE_H
#define SPINBOXDELEGATE_H
#include <QDoubleSpinBox>
#include <QItemDelegate>
#include <QTableWidgetItem>

class SpinBoxDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit SpinBoxDelegate(QObject *parent = nullptr);
protected:
    QWidget *createEditor(QWidget *parent,
                          const QStyleOptionViewItem &,
                          const QModelIndex &) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
    void updateEditorGeometry(QWidget *editor,
                              const QStyleOptionViewItem &option,
                              const QModelIndex &) const override;
};

#endif // SPINBOXDELEGATE_H
