#ifndef POLYFIT_TABLE_MODEL_H
#define POLYFIT_TABLE_MODEL_H
#include <QAbstractItemModel>
#include <layoutpersist.h>

class PolyfitTableModel : public QAbstractTableModel
{
public:
    PolyfitTableModel();
    ~PolyfitTableModel() override;
    void            getPolyFitData(float **data, int *size);
    // QAbstractItemModel interface
public:

    int             rowCount(const QModelIndex &parent) const override;
    int             columnCount(const QModelIndex &parent) const override;
    QVariant        data(const QModelIndex &index, int role) const override;
    bool            setData(const QModelIndex &index, const QVariant &value, int role) override;
    Qt::ItemFlags   flags(const QModelIndex &index) const override;
    QVariant        headerData(int section, Qt::Orientation orientation, int role) const override;

    inline int      getIdx(const QModelIndex &index) const;
    static int      getMaxPolyFitRow();
    static int      getMaxPolyFitCol();

private:
    float*          mpPrivData;
    int             mPrivDataCount;
};

#endif // POLYFIT_TABLE_MODEL_H
