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

  std::vector<std::vector<std::vector<double>>>
       getVoxelView() const;

  std::string calculate();

  void initVectorArgs();

  void calculateFunction(std::vector<double>& args); /// Хn+1

  std::vector<double> calculateLocalGeomCharacters(std::vector<double> point); /// ЛГХ

  void calculateVoxelView();

private:
  size_t                         mNumberArgs; ///< Количество аргументов
  std::vector<double>            mArgs;       ///< Аргументы выражения
  std::vector<FVM::Math::Range>  mRanges;     ///< Диапазон значений
  std::string                    mExpression; ///< Выражение
  std::shared_ptr<MathEvaluator> mEvaluator;  ///< Подсчет математических выражений
  std::vector<std::vector<std::vector<double>>>
                                 mVoxelViews; ///< Воксельное представление для трехмерного объекта

};
} // namespace Math
} // namespace FVM

#endif // FVM_MATH_EXPRESSION_HPP
