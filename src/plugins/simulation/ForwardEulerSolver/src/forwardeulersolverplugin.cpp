//==============================================================================
// ForwardEulerSolver plugin
//==============================================================================

#include "forwardeulersolver.h"
#include "forwardeulersolverplugin.h"

//==============================================================================

namespace OpenCOR {
namespace ForwardEulerSolver {

//==============================================================================

PLUGININFO_FUNC ForwardEulerSolverPluginInfo()
{
    Descriptions descriptions;

    descriptions.insert("en", QString::fromUtf8("a plugin which implements the <a href=\"http://en.wikipedia.org/wiki/Euler_method\">Forward Euler method</a> to solve ODEs."));
    descriptions.insert("fr", QString::fromUtf8("une extension qui implémente la <a href=\"http://en.wikipedia.org/wiki/Euler_method\">méthode Forward Euler</a> pour résoudre des EDOs."));

    return new PluginInfo(PluginInfo::InterfaceVersion001,
                          PluginInfo::Simulation,
                          false,
                          true,
                          QStringList() << "CoreSolver",
                          descriptions);
}

//==============================================================================

Solver::Type ForwardEulerSolverPlugin::type() const
{
    // Return the type of the solver

    return Solver::Ode;
}

//==============================================================================

QString ForwardEulerSolverPlugin::name() const
{
    // Return the name of the solver

    return "Euler (forward)";
}

//==============================================================================

Solver::Properties ForwardEulerSolverPlugin::properties() const
{
    // Return the properties supported by the solver

    Solver::Properties res = Solver::Properties();
    Descriptions stepPropertyDescriptions;

    stepPropertyDescriptions.insert("en", QString::fromUtf8("Step"));
    stepPropertyDescriptions.insert("fr", QString::fromUtf8("Pas"));

    res.append(Solver::Property(Solver::Double, StepId, stepPropertyDescriptions, StepDefaultValue, true));

    return res;
}

//==============================================================================

void * ForwardEulerSolverPlugin::instance() const
{
    // Create and return an instance of the solver

    return new ForwardEulerSolver();
}

//==============================================================================

}   // namespace ForwardEulerSolver
}   // namespace OpenCOR

//==============================================================================
// End of file
//==============================================================================
