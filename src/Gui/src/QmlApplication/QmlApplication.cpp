#include <QmlApplication/QmlApplication.hpp>

namespace Gui
{

QmlApplication::QmlApplication(QObject *parent) : QObject(parent)
{
  mExpression = std::make_shared<FVM::Math::Expression>();
}

QmlApplication::~QmlApplication()
{}

void QmlApplication::addArgInExpression() const
{
  mExpression->addArg();
}

void QmlApplication::removeArgumentFromExpression() const
{
  mExpression->removeArg();
}

int QmlApplication::getNumberArgsFromExpression() const
{
    return mExpression->getNumberArgs();
}

QString QmlApplication::calculate(QString expression)
{
    mExpression->setExpression(expression.toStdString());
    std::string answer = mExpression->calculate();
    return QString::fromStdString(answer);
}

QVariantList QmlApplication::getVoxelView()
{
  auto voxelView = mExpression->getVoxelView();

  if(voxelView.empty())
    return {};
  QVariantList result;
  for(auto row : voxelView)
  {
    QVariantList tempColumn;
    for(auto column : row)
    {
      QVariantList tempVoxelView;
      for(auto numVoxelView : column)
      {
        tempVoxelView.push_back(numVoxelView);
      }
      tempColumn.push_back(tempVoxelView);
    }
    result.push_back(tempColumn);
  }
  return result;
}

QVariantList QmlApplication::getMatrixValues() const
{
  auto matrixValues = mExpression->getMatrixValues();

  if(matrixValues.empty())
    return {};

  QVariantList result;
  for(auto row : matrixValues)
  {
    QVariantList tempColumn;
    for(auto value : row)
    {
      tempColumn.push_back(value);
    }
    result.push_back(tempColumn);
  }
  return result;
}

double QmlApplication::getMaxValue() const
{
  if(mExpression->getMatrixValues().empty())
    return 0;
  return mExpression->getMaxValue();
}

double QmlApplication::getMinValue() const
{
    if(mExpression->getMatrixValues().empty())
      return 0;
    return mExpression->getMinValue();
}

void QmlApplication::setRange(double min, double max, double step)
{
  mExpression->setRange(min,max,step);
}

//void QmlApplication::requestToLoadHistory()
//{
//  for(std::pair<int, QVariantMap> history : mHistories)
//  {
//    QString titleHistory = QString("%1 %2 %3 %4").arg(
//                           history.second.value("TYPE").toString(),
//                           history.second.value("IP").toString(),
//                           history.second.value("PORT").toString(),
//                           history.second.value("SNAME").toString());
//    addHistoryInList({{"TEXT", titleHistory},
//                      {"HASH", history.first}});
//  }
//}

} // namespace Gui

