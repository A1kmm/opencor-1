//==============================================================================
// Core NLA solver class
//==============================================================================

#include "corenlasolver.h"
#include "plugin.h"

//==============================================================================

#include <QSettings>

//==============================================================================

namespace OpenCOR {
namespace CoreSolver {

//==============================================================================

CoreNlaSolver::CoreNlaSolver() :
    mComputeSystem(0),
    mParameters(0),
    mSize(0),
    mUserData(0)
{
}

//==============================================================================

void CoreNlaSolver::initialize(ComputeSystemFunction pComputeSystem,
                               double *pParameters, int pSize, void *pUserData)
{
    // Initialise ourselves

    mComputeSystem = pComputeSystem;

    mParameters = pParameters;
    mSize = pSize;
    mUserData = pUserData;
}

//==============================================================================

static const QString SettingsGlobal = "Global";

//==============================================================================

CoreNlaSolver * nlaSolver(const QString &pRuntime)
{
    // Return the runtime's NLA solver

    QSettings settings(SettingsOrganization, SettingsApplication);
    qulonglong res;

    settings.beginGroup(SettingsGlobal);
        res = settings.value(pRuntime, 0).toULongLong();
    settings.endGroup();

    // Return the NLA solver

    return static_cast<CoreNlaSolver *>((void *) res);
}

//==============================================================================

void setNlaSolver(const QString &pRuntime, CoreNlaSolver *pGlobalNlaSolver)
{
    // Keep track of the runtime's NLA solver

    QSettings settings(SettingsOrganization, SettingsApplication);

    settings.beginGroup(SettingsGlobal);
        settings.setValue(pRuntime, QString::number(qulonglong(pGlobalNlaSolver)));
        // Note: for some reasons, on Windows and OS X, QSettings doesn't handle
        //       qulonglong values properly, so we do it through a QString value
        //       instead...
        //       (See https://bugreports.qt-project.org/browse/QTBUG-29681)
    settings.endGroup();
}

//==============================================================================

void unsetNlaSolver(const QString &pRuntime)
{
    // Stop tracking the runtime's NLA solver

    QSettings settings(SettingsOrganization, SettingsApplication);

    settings.beginGroup(SettingsGlobal);
        settings.remove(pRuntime);
    settings.endGroup();
}

//==============================================================================

}   // namespace CoreSolver
}   // namespace OpenCOR

//==============================================================================
// End of file
//==============================================================================
