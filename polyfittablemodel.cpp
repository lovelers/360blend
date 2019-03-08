#include "polyfittablemodel.h"

PolyfitTableModel::PolyfitTableModel()
{
    mPrivDataCount      = LayoutPersist::getInstance()->getPolyfitTableSize();
    mpPrivData          = new float[mPrivDataCount];
    for(int i = 0; i < mPrivDataCount; i++)
    {
        mpPrivData[i] = 1.f;
    }
    qDebug("ployfit table size = %d", mPrivDataCount);
}

PolyfitTableModel::~PolyfitTableModel()
{
    if (nullptr != mpPrivData)
    {
        delete mpPrivData;
        mpPrivData = nullptr;
    }
    QAbstractTableModel::~QAbstractTableModel();
}

void PolyfitTableModel::getPolyFitData(float **data, int *size)
{
    if (nullptr != data && nullptr != size)
    {
        *data = mpPrivData;
        *size = mPrivDataCount;
    }
    else
    {
        qDebug("invalid input arguments: data ptr: %p, size ptr: %p", data, size);
    }
}

int PolyfitTableModel::rowCount(const QModelIndex &parent) const
{
    (void)parent;
    return getMaxPolyFitRow();
}

int PolyfitTableModel::columnCount(const QModelIndex &parent) const
{
    (void)parent;
    return getMaxPolyFitCol();
}

QVariant PolyfitTableModel::data(const QModelIndex &index, int role) const
{
    if (index.isValid() == false)
    {
        return QVariant();
    }

    if (Qt::DisplayRole == role)
    {
        int idx = index.row() * getMaxPolyFitCol() + index.column();
        return QVariant(mpPrivData[idx]);
    }

    return QVariant();
}

bool PolyfitTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() == false ||
            Qt::EditRole != role)
    {
        return false;
    }

    int idx = getIdx(index);
    mpPrivData[idx] = value.toFloat();
    return true;
}

Qt::ItemFlags PolyfitTableModel::flags(const QModelIndex &index) const
{
    (void) index;
    return Qt::ItemIsSelectable |
            Qt::ItemIsEditable  |
            Qt::ItemIsEnabled;
}

QVariant PolyfitTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{

    if (Qt::DisplayRole == role &&
            orientation == Qt::Horizontal)
    {
        return QVariant();
    }
    return QAbstractTableModel::headerData(section, orientation, role);
}

int PolyfitTableModel::getIdx(const QModelIndex &index) const
{
    return index.row() * getMaxPolyFitCol() + index.column();
}

int PolyfitTableModel::getMaxPolyFitRow()
{
    return LayoutPersist::getInstance()->getPolyfitTableRow();
}

int PolyfitTableModel::getMaxPolyFitCol()
{
    return LayoutPersist::getInstance()->getPolyfitTableCol();
}
