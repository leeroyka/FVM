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

public slots:
  /*!
   * \brief addArgInExpression Добавление нового аргумента для функции
   */
  Q_INVOKABLE void addArgInExpression() const;

  /*!
   * \brief removeArgumentFromExpression Удалить аргумент из функции
   */
  Q_INVOKABLE void removeArgumentFromExpression() const;

  /*!
   * \brief getNumberArgsFromExpression Получает количество аргументов в функции
   * \return int количество аргументов
   */
  Q_INVOKABLE int getNumberArgsFromExpression() const;

  /*!
   * \brief calculate Вычисляет функцию и строит воксельное представление
   * \param expression Входная строка содержащая функцию
   * \return
   */
  Q_INVOKABLE QString calculate(QString expression);

  /*!
   * \brief getVoxelView Получение воксельного представления функции
   * \return Воксельное представление функции
   */
  Q_INVOKABLE QVariantList getVoxelView();

  /*!
   * \brief getMatrixValues Получение матрицы значений для визуализации функции
   * \return Матрица значений функции
   */
  Q_INVOKABLE QVariantList getMatrixValues() const;

  /*!
   * \brief getMaxValue Получение максимального значения функции
   * \return Максимальное значение функции на промежутке
   */
  Q_INVOKABLE double getMaxValue() const;

  /*!
   * \brief getMinValue Получение минимального значения функции
   * \return Минимальное значение функции
   */
  Q_INVOKABLE double getMinValue() const;

  /*!
   * \brief setRange Установка диапазона значений для расчета функции
   * \param min Минимальное значение аргумента функции
   * \param max Максимальное значение аргумента функции
   * \param step Шаг дискретизации
   */
  Q_INVOKABLE void setRange(double min, double max, double step);


private:
  std::shared_ptr<FVM::Math::Expression> mExpression; ///< Экземпляр функции

  const QString M_TEMPLATE_ERROR = "<p style='color: red';>Error: %1</p>";///< Шаблон вывода ошибки
  const QString M_TEMPLATE_NORMAL = "<p style='color: black';>%1</p>";    ///< Шаблон вывода данных

};
} // namespace Gui

#endif// FVM_GUI_QML_APPLICATION_HPP
