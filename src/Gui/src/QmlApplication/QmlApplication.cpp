#include <QmlApplication/QmlApplication.hpp>

namespace Gui
{

QmlApplication::QmlApplication(QObject *parent) : QObject(parent)
{
  mExpression = std::make_shared<FVM::Math::Expression>();

}

QmlApplication::~QmlApplication()
{
  saveHistory(mHistories, true);
}

void QmlApplication::readHistory()
{

}

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

void QmlApplication::addHistoryItem(QVariantMap map)
{
    QString titleHistory = QString("%1 %2 %3 %4").arg(
                            map.value("TYPE").toString(),
                            map.value("IP").toString(),
                            map.value("PORT").toString(),
                            map.value("SNAME").toString());
    std::hash<std::string> hash_fn;
    auto sourceHash = (titleHistory + map.value("JSON").toString()).toStdString();
    auto hashValue = (int)hash_fn(sourceHash);
    if(mHistories.insert({hashValue,map}).second)
    {
      addHistoryInList({{"TEXT", titleHistory},
                        {"HASH", hashValue}});
      saveHistory({std::pair<int, QVariantMap>(hashValue,map)});
    }
}

void QmlApplication::requestToLoadHistory()
{
  for(std::pair<int, QVariantMap> history : mHistories)
  {
    QString titleHistory = QString("%1 %2 %3 %4").arg(
                           history.second.value("TYPE").toString(),
                           history.second.value("IP").toString(),
                           history.second.value("PORT").toString(),
                           history.second.value("SNAME").toString());
    addHistoryInList({{"TEXT", titleHistory},
                      {"HASH", history.first}});
  }
}

void QmlApplication::removeHistory(int hash)
{
  mHistories.erase(hash);
}

void QmlApplication::removeAllHistory()
{
    mHistories.clear();
    mListUUID.clear();
}

void QmlApplication::getFieldsHistory(int hash)
{
  if(mHistories.find(hash) != mHistories.end())
    updateFieldsHistory(mHistories[hash]);
}

void QmlApplication::saveHistory(const std::map<int, QVariantMap>& map,
                                 bool allClear)
{

}

QString QmlApplication::getUUID(const QString &httpAnswer)
{
  QStringList keys = httpAnswer.split(' ');
  QRegExp reg(".+-.+-.+-.+-.+");
  for(const auto & key : keys)
  {
    if(reg.indexIn(key) > -1 && mListUUID.indexOf(key) < 0)
    {
      mListUUID.append(key);
      return key;
    }
  }
  return nullptr;
}

QString QmlApplication::loadJsonFromFile(const QString &path)
{
    return "";
}

QString QmlApplication::isCorrectJson(const QString &json)
{
    return "";
}

void QmlApplication::parseRecivedData(const QString &json)
{

}

}
