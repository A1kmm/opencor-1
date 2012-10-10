//==============================================================================
// KINSOLSolver plugin
//==============================================================================

#include "kinsolsolver.h"
#include "kinsolsolverplugin.h"

//==============================================================================

namespace OpenCOR {
namespace KINSOLSolver {

//==============================================================================

PLUGININFO_FUNC KINSOLSolverPluginInfo()
{
    Descriptions descriptions;

    descriptions.insert("en", "A plugin which uses <a href=\"https://computation.llnl.gov/casc/sundials/description/description.html#descr_kinsol\">KINSOL</a> to solve non-linear systems");
    descriptions.insert("fr", "Une extension qui utilise <a href=\"https://computation.llnl.gov/casc/sundials/description/description.html#descr_kinsol\">KINSOL</a> pour r�soudres des syst�mes non-lin�aires");

    return new PluginInfo(PluginInfo::V001,
                          PluginInfo::General,
                          PluginInfo::Simulation,
                          true,
                          QStringList() << "CoreSolver" << "SUNDIALS",
                          descriptions);
}

//==============================================================================

Q_EXPORT_PLUGIN2(KINSOLSolver, KINSOLSolverPlugin)

//==============================================================================

QString KINSOLSolverPlugin::name() const
{
    // Return the name of the solver

    return "KINSOL";
}

//==============================================================================

Solver::Type KINSOLSolverPlugin::type() const
{
    // Return the type of the solver

    return Solver::NonLinearAlgebraic;
}

//==============================================================================

Solver::Properties KINSOLSolverPlugin::properties() const
{
    // Return the properties supported by the solver

    return Solver::Properties();
}

//==============================================================================

void * KINSOLSolverPlugin::instance() const
{
    // Create and return an instance of the solver

    return new KinsolSolver();
}

//==============================================================================

}   // namespace KINSOLSolver
}   // namespace OpenCOR

//==============================================================================
// End of file
//==============================================================================