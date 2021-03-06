#include <Math/Expression.hpp>

#include <math.h>

FVM::Math::Expression::Expression()
{
    mNumberArgs = 1;
    mRangeMin   = -3;
    mRangeMax   = 3;
    mRangeStep  = 0.02;
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

void FVM::Math::Expression::setVoxelView(std::vector<std::vector<std::vector<double>>>
                                         voxelView)
{
  mVoxelViews = voxelView;
}

void FVM::Math::Expression::setMatrixValues(std::vector<std::vector<double>> matrixValues)
{
  mMatrixValues = matrixValues;
}

void FVM::Math::Expression::setRange(double min, double max, double step)
{
  mRangeMin  = min;
  mRangeMax  = max;
  mRangeStep = step;
}

std::vector<std::vector<std::vector<double>>>
FVM::Math::Expression::getVoxelView() const
{
  return mVoxelViews;
}

std::vector<std::vector<double> > FVM::Math::Expression::getMatrixValues() const
{
  return mMatrixValues;
}

double FVM::Math::Expression::getMaxValue() const
{
    return mMaxValue;
}

double FVM::Math::Expression::getMinValue() const
{
    return mMinValue;
}

std::string FVM::Math::Expression::calculate()
{
    initVectorArgs();
    std::vector<double> test;
    test.push_back(0);
    test.push_back(1);
    calculateLocalGeomCharacters(test);
    for(size_t i=0;i < mArgs.size(); i++)
    {
        mEvaluator->appendVariable("x_"+std::to_string(i+1),mArgs[i]);
    }

    double result;
    result = mEvaluator->eval(mExpression);

    if(getNumberArgs() == 2)
        calculateVoxelView();

    return std::to_string(result);
}

void FVM::Math::Expression::initVectorArgs()
{
    for(size_t i = 0; i < getNumberArgs(); i++)
    {
        mArgs.push_back(1.);
        mRanges.push_back({mRangeMin,mRangeMax,mRangeStep});
    }
}

void FVM::Math::Expression::calculateFunction(std::vector<double>& args)
{
    for(size_t i=0;i < args.size(); i++)
    {
        mEvaluator->appendVariable("x_"+std::to_string(i+1),args[i]);
    }
    args.push_back(mEvaluator->eval(mExpression));
}

std::vector<double>
FVM::Math::Expression::calculateLocalGeomCharacters(std::vector<double> point)
{
    /*
     * ???????????????????? ?????????????? ?????? ?????????????? ?????????????????? +1
     * ?????????????? ????????????????????????
     * ?????????????????? ????????????????????????
     * ???????????????????? ???????????????? ?????????????????? ?? ???????????????????????? ??????????????
     * ???????????????? ?????????????????? ????????????????, ?????????? ??????????????????
     *
    */
    std::vector<simple_matrix::matrix> matrices;
    size_t numArg = getNumberArgs();
    std::vector<double> firstPoint(point);
    calculateFunction(firstPoint);
    std::vector<std::vector<double>> points;
    firstPoint.push_back(1.);
    points.push_back(firstPoint);
    for(size_t i=0; i<numArg; i++)
    {
        std::vector<double> tempPoint(point);
        tempPoint[i] += mRanges[i].step;
        calculateFunction(tempPoint);
        tempPoint.push_back(1.);
        points.push_back(tempPoint);
    }
    for(size_t i=0; i<numArg+2; i++)
    {
        std::shared_ptr<double[]> components(new double[(numArg+1)*(numArg+1)]);
        size_t pos = 0;
        for(size_t row = 0; row<numArg+1; row++)
        {
            for(size_t column = 0; column<numArg+2; column++)
            {
                if(column == i)
                    continue;
                components[pos] = points[row][column];
                pos++;
            }
        }
        simple_matrix::matrix tempMatrix(numArg+1,
                                         numArg+1,
                                         components.get());
        matrices.push_back(tempMatrix);
    }
    std::vector<double> normal;
    for(auto matrix : matrices)
    {
        normal.push_back(matrix.det());
    }
    double normalFactor=0;
    for(auto n : normal)
    {
        normalFactor+= n*n;
    }
    normalFactor = sqrt(normalFactor);
    for(size_t i = 0; i < normal.size(); i++)
    {
        normal[i] = normal[i]/normalFactor;
    }
    return normal;
}

void FVM::Math::Expression::calculateVoxelView()
{
    //TODO: ????????????????????????????
    std::vector<std::vector<std::vector<double>>> voxelViews;
    std::vector<std::vector<double>> matrixFunction;
    bool isFirst = true;
    for(double row  = mRanges[0].min;
               row <= mRanges[0].max;
               row += mRanges[0].step)
    {
        std::vector<std::vector<double>> voxelRow;
        std::vector<double>              functionRow;
        for(double column  = mRanges[1].min;
                   column <= mRanges[1].max;
                   column += mRanges[1].step)
        {
            std::vector<double> views = calculateLocalGeomCharacters({row, column});
            voxelRow.push_back(views);

            std::vector<double> point = {row,column};
            calculateFunction(point);
            functionRow.push_back(point[point.size()-1]);
            if(isFirst)
            {
              mMaxValue = point[point.size()-1];
              mMinValue = point[point.size()-1];
              isFirst = false;
            }
            else if (point[point.size()-1]> mMaxValue)
            {
              mMaxValue = point[point.size()-1];
            }
            else if (point[point.size()-1]< mMinValue)
            {
                mMinValue = point[point.size()-1];
            }
        }
        matrixFunction.push_back(functionRow);
        voxelViews.push_back(voxelRow);
    }
    setMatrixValues(matrixFunction);
    setVoxelView(voxelViews);

}
