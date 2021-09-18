#ifndef FVM_GUI_QML_APPLICATION_HPP
#define FVM_GUI_QML_APPLICATION_HPP

#include <QVariant>
#include <QString>
#include <QFile>
#include <QSettings>
#include <QObject>
#include <Math/Expression.hpp>

namespace Gui {

class QmlApplication: public QObject

{
  Q_OBJECT
public:

  QmlApplication(QObject * parent = nullptr);
  ~QmlApplication();

  /*!
   * \brief readHistory загрузка истории из QSettings файла
   */
  void readHistory();

signals:
  /*!
   * \brief updateOutputData обновление поля с выводом данных
   * \param data - преобразованный текст для вывода
   */
  void updateOutputData(QString data);

  /*!
   * \brief updateOutputLogs обновление поля с выводом логов
   * \param data - преобразованный текст для вывода
   */
  void updateOutputLogs(QString data);
  /*!
   * \brief updateFieldsHistory сигнал обновления данных в соответствии с
   * выбранной историей
   * \param data - набор данных, для заполнения форм
   */
  void updateFieldsHistory(QVariantMap data);
  /*!
   * \brief addHistoryInList сигнал добавления заголовка истории в GUI
   * \param titleHistory - название истории
   */
  void addHistoryInList(QVariantMap titleHistory);

public slots:
  void addArgInExpression() const;
  void removeArgumentFromExpression() const;
  int getNumberArgsFromExpression() const;
  QString calculate(QString expression);
  //............................................................................
  /*!
   * \brief parseRecivedData преобразование данных в сообщения
   * \param json - json данные в строковом виде
   */
  void parseRecivedData(const QString& json);
  /*!
   * \brief addHistoryItem добавление истории
   * \param map набор параметров, для сохранения
   */
  Q_INVOKABLE void addHistoryItem(QVariantMap map);
  /*!
   * \brief requestToLoadHistory генерация строк для отображения истории
   */
  Q_INVOKABLE void requestToLoadHistory();
  /*!
   * \brief removeHistory удаление истории
   * \param index - индекс выбранной истории (в GUI, индексы совпадают с
   * листом  mHistories)
   */
  Q_INVOKABLE void removeHistory(int hash);
  /*!
   * \brief removeAllHistory -очистка всей истории
   */
  Q_INVOKABLE void removeAllHistory();
  /*!
   * \brief getFieldsHistory получение на клиенте выбранных данных
   * \param index - индекс выбранной истории
   */
  Q_INVOKABLE void getFieldsHistory(int hash);
  /*!
   * \brief saveHistory сохрнение истории в файле
   * \param map - набор данных для сохранения
   * \param allClear - выполнить ли очистку файла перед записью
   */
  Q_INVOKABLE void saveHistory(const std::map<int, QVariantMap>& map,
                               bool allClear = false);
  /*!
   * \brief getUUID получение uuid из http ответа шлюза
   * \param httpAnswer - ответ шлюза
   * \return значение uuid, либо null если в ответе его нет
   */
  Q_INVOKABLE QString getUUID(const QString& httpAnswer);

  /*!
   * \brief loadJsonFromFile загрузка данных из json файла
   * \param path - путь до файла
   * \return возвращает содержимое файла
   */
  Q_INVOKABLE QString loadJsonFromFile(const QString& path);

  /*!
   * \brief isCorrectJson проверка корректности правилам JSON
   * \param json - json данные в строковом виде
   * \return данные в формате JSON (строкой) с поправками на port и method (если их нет)
   */
  Q_INVOKABLE QString isCorrectJson(const QString& json);

private:
  std::shared_ptr<FVM::Math::Expression> mExpression;
  //.....................................................................
  std::map<int, QVariantMap> mHistories; ///< map с хешами и полями истории
  QStringList mListUUID; ///< принятые uuid с запросов, для обновления логов
  const QString M_TEMPLATE_ERROR = "<p style='color: red';>Error: %1</p>";///< Шаблон вывода ошибки
  const QString M_TEMPLATE_NORMAL = "<p style='color: black';>%1</p>";///< Шаблон вывода данных
  const QString M_TEMPLATE_LOGS = "<p style='color: black';>%1: %2</p>";///< Шаблон вывода логов
  const QString M_FILE_HISTORY_PATH = "gui.hsr"; ///< Название файла
  const QString M_ADDED_PORT_JSON = "8008"; ///< port для добавления в JSON
  const QString M_ADDED_METHOD_JSON = "route_services"; ///< method для добавления в JSON
};
} // namespace Gui
#endif// FVM_GUI_QML_APPLICATION_HPP

