#ifndef FVM_MATH_EXPRESSION_HPP
#define FVM_MATH_EXPRESSION_HPP

#include <evaluator.hpp>
#include <matrix.hpp>

#include <memory>
#include <vector>
#include <string>

namespace FVM {
namespace Math {

struct Range {
    double min;
    double max;
    double step;
};

class Expression
{
public:
  /*!
   * \brief Expression
   */
  Expression();

  /*!
   * \brief getNumberArgs Получение количества аргументов функции
   * \return количество аргументов функции
   */
  size_t getNumberArgs() const;

  /*!
   * \brief addArg Добавить аргумент в функцию
   */
  void addArg();

  /*!
   * \brief removeArg Удалить аргумент из функции
   */
  void removeArg();

  /*!
   * \brief setExpression Установить строку содержащую функцию
   * \param expression функция для расчета
   */
  void setExpression(std::string expression);

  /*!
   * \brief setVoxelView Установить воксельное представление
   * \param voxelView Воксельное представление
   */
  void setVoxelView(std::vector<std::vector<std::vector<double>>> voxelView);

  /*!
   * \brief setMatrixValues Установить матрицу знаечений функции
   * \param matrixValues Матрица значений функции
   */
  void setMatrixValues(std::vector<std::vector<double>> matrixValues);

  /*!
   * \brief setRange Установить диапазон аргументов функции
   * \param min Минимальное значение
   * \param max Максимальное значение
   * \param step Шаг дискретизации
   */
  void setRange(double min, double max, double step);

  /*!
   * \brief getVoxelView Получить воксельное представление
   * \return Воксельное представление
   */
  std::vector<std::vector<std::vector<double>>>
       getVoxelView() const;

  /*!
   * \brief getMatrixValues Получить матрицу значений функции
   * \return Матрица значений функции
   */
  std::vector<std::vector<double>> getMatrixValues() const;

  /*!
   * \brief getMaxValue Получить макисмальное значение функции
   * \return Максимальное значение функции
   */
  double getMaxValue() const;

  /*!
   * \brief getMinValue Получить минимальное значение функции
   * \return Минимальное значение функции
   */
  double getMinValue() const;

  /*!
   * \brief calculate Вычислить функцию
   * \return
   */
  std::string calculate();

  /*!
   * \brief initVectorArgs Инициализация вектора аргументов
   */
  void initVectorArgs();

  /*!
   * \brief calculateFunction Подсчет функции из аргументов
   * \param args Аргументы
   */
  void calculateFunction(std::vector<double>& args); /// Хn+1

  /*!
   * \brief calculateLocalGeomCharacters Вычисление локальных геометрических характеристик
   * \param point Аргументы для конкретной точки
   * \return Локальные геометрические характеристики
   */
  std::vector<double> calculateLocalGeomCharacters(std::vector<double> point); /// ЛГХ

  /*!
   * \brief calculateVoxelView Вычислить воксельную модель
   */
  void calculateVoxelView();

private:
  size_t                         mNumberArgs;   ///< Количество аргументов
  std::vector<double>            mArgs;         ///< Аргументы выражения
  std::vector<FVM::Math::Range>  mRanges;       ///< Диапазон значений
  std::string                    mExpression;   ///< Выражение
  double                         mMaxValue;     ///< Максимальное значение функции
  double                         mMinValue;     ///< Минимальное значение функции
  double                         mRangeMin;     ///< Минимальное значение диапазона
  double                         mRangeMax;     ///< Максимальное значение диапазона
  double                         mRangeStep;    ///< Шаг дискредитации
  std::shared_ptr<MathEvaluator> mEvaluator;    ///< Подсчет математических выражений
  std::vector<std::vector<std::vector<double>>>
                                 mVoxelViews;   ///< Воксельное представление для трехмерного объекта
  std::vector<std::vector<double>>
                                 mMatrixValues; ///< Матрица значений функции

};
} // namespace Math
} // namespace FVM

#endif // FVM_MATH_EXPRESSION_HPP
