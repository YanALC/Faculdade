#include "spinboxdelegate.h"

SpinBoxDelegate::SpinBoxDelegate(QObject *)
{
}

QWidget *SpinBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &, const QModelIndex &) const
{
    auto SpinBox = new QDoubleSpinBox(parent);
    SpinBox->setMinimum(-9999999.99999);
    SpinBox->setMaximum(+9999999.99999);
    SpinBox->setButtonSymbols(QAbstractSpinBox::NoButtons);
    SpinBox->setDecimals(5);
    return SpinBox;
}

void SpinBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    auto SpinBox = static_cast<QDoubleSpinBox *>(editor);
    SpinBox->setValue(index.data().toDouble());
}

void SpinBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    auto SpinBox = static_cast<QDoubleSpinBox *>(editor);
    model->setData(index, SpinBox->value());
}

void SpinBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &) const
{
    editor->setGeometry(option.rect);
}
