#include "dataset.h"
#include <cmath>


#include <iostream>


DataSet::DataSet(double min, double max, double step)
{
    m_numPts = 0;
    double x = min;
    while(x < max)
    {
        m_data.push_back(DataPoint(x, sin(x) / x));

        x += step;
        m_numPts++;
    }
}

DataSet::~DataSet()
{
    //delete []m_data;
}
void DataSet::compute(double min, double max, double step, computeFunc f)
{
    m_data.clear();
    m_numPts = 0;
    double x = min;
    while(x < max)
    {
        m_data.push_back(DataPoint(x, f(x)));
        x += step;
        ++m_numPts;
    }
}

// overrides for read only QAbstractTableModel

int DataSet::rowCount(const QModelIndex & ) const
{
    return m_numPts;
}
int DataSet::columnCount(const QModelIndex & ) const
{
    return 2;
}
QVariant DataSet::data(const QModelIndex & index, int role) const
{
    if(Qt::DisplayRole == role)
    {
        if(index.column() == 0)
        {
            return QVariant(m_data[index.row()].m_x);
        }
        else if(index.column() == 1)
        {
            return QVariant(m_data[index.row()].m_y);
        }
    }
    // removes unwanted checkbox
    return QVariant();
}

// interface for binding to qcustom plot
QVector<double> DataSet::x() const
{
    QVector<double> data(m_numPts);
    for(int t = 0; t < m_numPts; t++) data[t] = m_data[t].m_x;
    return data;
}
QVector<double> DataSet::y() const
{
    QVector<double> data(m_numPts);
    for(int t = 0; t < m_numPts; t++) data[t] = m_data[t].m_y;
    return data;
}
double DataSet::minX() const
{
    double min = std::numeric_limits<double>::max();
    for(int t = 0; t < m_numPts; t++)
    {
        min = std::min<double>(min, m_data[t].m_x);
    }
    return min;
}
double DataSet::minY() const
{
    double min = std::numeric_limits<double>::max();
    for(int t = 0; t < m_numPts; t++)
    {
        if(!std::isinf(m_data[t].m_y))
        {
            min = std::min<double>(min, m_data[t].m_y);
        }
    }
    return min;
}
double DataSet::maxX() const
{
    double max = std::numeric_limits<double>::min();
    for(int t = 0; t < m_numPts; t++)
    {

        max = std::max<double>(max, m_data[t].m_x);
    }
    return max;
}
double DataSet::maxY() const
{
    double max = std::numeric_limits<double>::min();
    for(int t = 0; t < m_numPts; t++)
    {
         if(!std::isinf(m_data[t].m_y))
         {
            max = std::max<double>(max, m_data[t].m_y);
         }
    }
    return max;
}
