#ifndef DATASET_H
#define DATASET_H
#include <QAbstractTableModel>
#include <QVector>
#include <vector>
struct DataPoint
{
    double m_x;
    double m_y;
    DataPoint(double x = 0.0, double y = 0.0)
        :
          m_x(x),
          m_y(y)
    {

    }
};
typedef double(*computeFunc)(double);
class DataSet : public QAbstractTableModel
{


    std::vector<DataPoint> m_data;
    int m_numPts;
public:
    DataSet(double min, double max, double step);
    ~DataSet();
    void compute(double min, double max, double step, computeFunc f);
    // overrides for read only QAbstractItemModel
    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    int columnCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    // bind operations for qcustomplotter
    QVector<double> x() const;
    QVector<double> y() const;
    double minX() const;
    double minY() const;
    double maxX() const;
    double maxY() const;
};

#endif // DATASET_H
