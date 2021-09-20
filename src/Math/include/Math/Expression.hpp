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

  size_t getNumberArgs() const;

  void addArg();

  void removeArg();

  void setExpression(std::string expression);

  void setVoxelView(std::vector<std::vector<std::vector<double>>> voxelView);

  void setMatrixValues(std::vector<std::vector<double>> matrixValues);

  void setRange(double min, double max, double step);

  std::vector<std::vector<std::vector<double>>>
       getVoxelView() const;

  std::vector<std::vector<double>> getMatrixValues() const;

  double getMaxValue() const;

  std::string calculate();

  void initVectorArgs();

  void calculateFunction(std::vector<double>& args); /// Хn+1

  std::vector<double> calculateLocalGeomCharacters(std::vector<double> point); /// ЛГХ

  void calculateVoxelView();

private:
  size_t                         mNumberArgs;   ///< Количество аргументов
  std::vector<double>            mArgs;         ///< Аргументы выражения
  std::vector<FVM::Math::Range>  mRanges;       ///< Диапазон значений
  std::string                    mExpression;   ///< Выражение
  double                         mMaxValue;     ///< Максимальное значение функции
  double                         mRangeMin;     ///< Минимальное значение диапазона
  double                         mRangeMax;     ///<
  double                         mRangeStep;    ///<
  std::shared_ptr<MathEvaluator> mEvaluator;    ///< Подсчет математических выражений
  std::vector<std::vector<std::vector<double>>>
                                 mVoxelViews;   ///< Воксельное представление для трехмерного объекта
  std::vector<std::vector<double>>
                                 mMatrixValues; ///< Матрица значений функции

};
} // namespace Math
} // namespace FVM

#endif // FVM_MATH_EXPRESSION_HPP
