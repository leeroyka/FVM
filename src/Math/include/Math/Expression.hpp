#ifndef FVM_MATH_EXPRESSION_HPP
#define FVM_MATH_EXPRESSION_HPP

#include <evaluator.hpp>

#include <memory>
#include <vector>
#include <string>

namespace FVM {
namespace Math {

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

  std::string calculate();

  void initVectorArgs();
private:
  size_t                         mNumberArgs; ///< Количество аргументов
  std::vector<double>            mArgs;       ///< Аргументы выражения
  std::string                    mExpression; ///< Выражение
  std::shared_ptr<MathEvaluator> mEvaluator;  ///< Подсчет математических выражений
};
} // namespace Math
} // namespace FVM

#endif // FVM_MATH_EXPRESSION_HPP
