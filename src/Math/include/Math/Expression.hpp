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

  void setLocalGeomCharact(std::vector<double> normal);

  std::vector<double> getLocalGeomCharact() const;

  std::string calculate();

  void initVectorArgs();

  void calculateFunction(std::vector<double>& args); /// Хn+1

  void calculateLocalGeomCharacters(std::vector<double> point); /// ЛГХ

private:
  size_t                         mNumberArgs; ///< Количество аргументов
  std::vector<double>            mArgs;       ///< Аргументы выражения
  std::vector<double>            mLocalGeomCh;///< Локальные геометрические характер.
  std::vector<FVM::Math::Range>  mRanges;     ///< Диапазон значений
  std::string                    mExpression; ///< Выражение
  std::shared_ptr<MathEvaluator> mEvaluator;  ///< Подсчет математических выражений

};
} // namespace Math
} // namespace FVM

#endif // FVM_MATH_EXPRESSION_HPP
