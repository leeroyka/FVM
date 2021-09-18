#include <QmlApplication/QmlApplication.hpp>

namespace Gui
{

QmlApplication::QmlApplication(QObject *parent) : QObject(parent)
{
  mExpression = std::make_shared<FVM::Math::Expression>();
  mHttpServer = std::make_shared<HttpServer>(M_ADDED_PORT_JSON.toInt(), QHostAddress::Any);
  connect(mHttpServer.get(), &HttpServer::answerGET,
          this,&QmlApplication::parseRecivedData);
  connect(mHttpServer.get(), &HttpServer::answerPUT,
          this,&QmlApplication::parseRecivedData);
  connect(mHttpServer.get(), &HttpServer::answerPOST,
          this,&QmlApplication::parseRecivedData);
  readHistory();
}

QmlApplication::~QmlApplication()
{
  saveHistory(mHistories, true);
}

void QmlApplication::readHistory()
{
  QVariantList listOfHistories;
  QSettings history(M_FILE_HISTORY_PATH, QSettings::IniFormat);
  for(const auto & key : history.childGroups())
  {
    history.beginGroup(key);
    QVariantMap data;
    for(const auto &gKey : history.allKeys())
    {
        data.insert(gKey, history.value(gKey));
    }
    history.endGroup();
    mHistories.insert({key.toInt(), data});
  }
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
  QSettings history(M_FILE_HISTORY_PATH, QSettings::IniFormat);
  if(allClear)
  {
    history.clear();
  }
  for(const std::pair<int, QVariantMap>& dataHistory : map)
  {
    history.beginGroup(QString::number(dataHistory.first));
    for(const auto  & key : dataHistory.second.keys())
    {
      history.setValue(key, dataHistory.second[key].toString());
    }
     history.endGroup();
  }
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
  QString filePath = path;
  #ifdef Q_OS_WIN
    QFile file(filePath.remove("file:///").remove("\r\n"));
  #endif

  #ifdef Q_OS_UNIX
    QFile file(filePath.remove("file://").remove("\r\n"));
  #endif

  if(!file.open(QFile::ReadOnly))
    return nullptr;

  QByteArray fileData(file.readAll());
  QJsonDocument doc = QJsonDocument::fromJson(fileData);
  if(!doc.isNull())
    return fileData;
}

QString QmlApplication::isCorrectJson(const QString &json)
{
  QJsonDocument doc = QJsonDocument::fromJson(json.toUtf8());
  if(doc.isNull())
    return nullptr;

  QJsonObject jsonObj = doc.object();
  if(!jsonObj.contains("port"))
      jsonObj.insert("port", M_ADDED_PORT_JSON);
  if(!jsonObj.contains("method"))
      jsonObj.insert("method", M_ADDED_METHOD_JSON);
  doc.setObject(jsonObj);
  return doc.toJson();
}

void QmlApplication::parseRecivedData(const QString &json)
{
  QJsonDocument doc = QJsonDocument::fromJson(json.toUtf8());
  if(doc.isNull())
    return;

  QString message;
  QJsonObject jsonObj = doc.object();
  if(jsonObj.contains("logs"))
  {
    QString strLogs = QString("{\"logs\":%1}").arg(
                                    jsonObj.value("logs").toString());
    auto docLogs = QJsonDocument::fromJson(strLogs.toUtf8()).object();
    auto array = docLogs.value("logs").toArray();
    for(int i =0; i < array.size(); i++)
    {
      auto element = array.at(i).toObject();
      message += M_TEMPLATE_LOGS.arg(element["service"].toString().split("-")[1],
                                     element["msg"].toString());
    }
    updateOutputLogs(message);
  }
  else if(jsonObj.contains("error"))
  {
    message = M_TEMPLATE_ERROR.arg(
                jsonObj.value("error").toString());
    updateOutputData(message);
  }
  else
  {
    jsonObj.remove("id");
    if(jsonObj.keys().length() > 1)
    {
      message = M_TEMPLATE_ERROR.arg("больше 2х значений в результате!");
    }
    else
    {
      message = M_TEMPLATE_NORMAL.arg(jsonObj.begin().value().toString());
    }
    updateOutputData(message);
  }
}

}
