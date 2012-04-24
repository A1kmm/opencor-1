//==============================================================================
// CellML file component
//==============================================================================

#ifndef CELLMLFILECOMPONENT_H
#define CELLMLFILECOMPONENT_H

//==============================================================================

#include "cellmlfilenamedelement.h"
#include "cellmlfileunit.h"
#include "cellmlfilevariable.h"
#include "cellmlsupportglobal.h"

//==============================================================================

#include <QList>

//==============================================================================

namespace OpenCOR {
namespace CellMLSupport {

//==============================================================================

class CELLMLSUPPORT_EXPORT CellmlFileComponent : public CellmlFileNamedElement
{
public:
    explicit CellmlFileComponent(iface::cellml_api::ImportComponent *pImportComponent);
    explicit CellmlFileComponent(iface::cellml_api::CellMLComponent *pComponent);
    ~CellmlFileComponent();

    CellmlFileUnits units() const;
    CellmlFileVariables variables() const;

private:
    CellmlFileUnits mUnits;
    CellmlFileVariables mVariables;

    void clearUnits();
    void clearVariables();
};

//==============================================================================

typedef QList<CellmlFileComponent *> CellmlFileComponents;

//==============================================================================

}   // namespace CellMLSupport
}   // namespace OpenCOR

//==============================================================================

#endif

//==============================================================================
// End of file
//==============================================================================