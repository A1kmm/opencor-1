//==============================================================================
// CellML file unit
//==============================================================================

#ifndef CELLMLFILEUNIT_H
#define CELLMLFILEUNIT_H

//==============================================================================

#include "cellmlfileunitelement.h"
#include "cellmlsupportglobal.h"

//==============================================================================

namespace OpenCOR {
namespace CellMLSupport {

//==============================================================================

class CELLMLSUPPORT_EXPORT CellmlFileUnit : public CellmlFileNamedElement
{
public:
    explicit CellmlFileUnit(iface::cellml_api::ImportUnits *pImportUnits);
    explicit CellmlFileUnit(iface::cellml_api::Units *pUnits);
    ~CellmlFileUnit();

    bool isBaseUnit() const;

    CellmlFileUnitElements unitElements() const;

private:
    bool mBaseUnit;

    CellmlFileUnitElements mUnitElements;
};

//==============================================================================

typedef QList<CellmlFileUnit *> CellmlFileUnits;

//==============================================================================

}   // namespace CellMLSupport
}   // namespace OpenCOR

//==============================================================================

#endif

//==============================================================================
// End of file
//==============================================================================