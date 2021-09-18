#include <Math/Expression.hpp>

FVM::Math::Expression::Expression()
{
    mNumberArgs = 1;
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
    return "";
}
