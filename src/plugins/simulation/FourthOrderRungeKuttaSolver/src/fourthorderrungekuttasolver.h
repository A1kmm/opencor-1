//==============================================================================
// Fourth-order Runge-Kutta solver class
//==============================================================================

#ifndef FOURTHORDERRUNGEKUTTASOLVER_H
#define FOURTHORDERRUNGEKUTTASOLVER_H

//==============================================================================

#include "coreodesolver.h"

//==============================================================================

namespace OpenCOR {
namespace FourthOrderRungeKuttaSolver {

//==============================================================================

static const QString StepId = "Step";

//==============================================================================

static const double StepDefaultValue = 1.0;

//==============================================================================

class FourthOrderRungeKuttaSolver : public CoreSolver::CoreOdeSolver
{
public:
    explicit FourthOrderRungeKuttaSolver();
    ~FourthOrderRungeKuttaSolver();

    virtual void initialize(const double &pVoiStart,
                            const int &pRatesStatesCount, double *pConstants,
                            double *pRates, double *pStates, double *pAlgebraic,
                            ComputeRatesFunction pComputeRates);

    virtual void solve(double &pVoi, const double &pVoiEnd) const;

private:
    double mStep;

    double *mK1;
    double *mK23;
    double *mYk123;
};

//==============================================================================

}   // namespace FourthOrderRungeKuttaSolver
}   // namespace OpenCOR

//==============================================================================

#endif

//==============================================================================
// End of file
//==============================================================================
