#include <Math/Expression.hpp>

FVM::Math::Expression::Expression()
{
    mNumberArgs = 1;
    mEvaluator = std::make_shared<MathEvaluator>();
}

size_t FVM::Math::Expression::getNumberArgs() const
{
    return mNumberArgs;
}

void FVM::Math::Expression::addArg()
{
    mNumberArgs++;
}

void FVM::Math::Expression::removeArg()
{
    if(mNumberArgs > 0)
         mNumberArgs--;
}

void FVM::Math::Expression::setExpression(std::string expression)
{
    mExpression = expression;
}

std::string FVM::Math::Expression::calculate()
{
    initVectorArgs();
    for(size_t i=0;i < mArgs.size(); i++)
    {
        mEvaluator->appendVariable("x_"+std::to_string(i+1),mArgs[i]);
    }

    double result;
    result = mEvaluator->eval(mExpression);

    return std::to_string(result);
}

void FVM::Math::Expression::initVectorArgs()
{
    for(size_t i = 0; i < getNumberArgs(); i++)
    {
        mArgs.push_back(1.);
        mStep.push_back(0.001);
    }
}

void FVM::Math::Expression::calculateFunction(std::vector<double> &args)
{
    for(size_t i=0;i < args.size(); i++)
    {
        mEvaluator->appendVariable("x_"+std::to_string(i+1),args[i]);
    }
    args.push_back(mEvaluator->eval(mExpression));
}

void FVM::Math::Expression::calculateLocalGeomCharacters()
{
    /*
     * Составляем матрицу для каждого аргумента +1
     * Считаем определители
     * Нормируем определители
     * Составляем конечное уравнение с компонентами нормали
     * Выражаем последний аргумент, через остальные
     *
    */
    std::vector<simple_matrix::matrix> matrices;

}
