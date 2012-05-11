//==============================================================================
// CellML annotation view details widget
//==============================================================================

#ifndef CELLMLANNOTATIONVIEWDETAILSWIDGET_H
#define CELLMLANNOTATIONVIEWDETAILSWIDGET_H

//==============================================================================

#include "cellmlfile.h"
#include "widget.h"

//==============================================================================

#include <QStandardItem>
#include <QStyledItemDelegate>

//==============================================================================

namespace Ui {
    class CellmlAnnotationViewDetailsWidget;
}

//==============================================================================

class QLabel;

//==============================================================================

namespace OpenCOR {
namespace CellMLAnnotationView {

//==============================================================================

class CellmlAnnotationViewDetailsWidget : public Core::Widget
{
    Q_OBJECT

public:
    enum Type
    {
        Empty,
        Model,
        Import,
        ImportUnit,
        ImportComponent,
        Unit,
        UnitElement,
        Component,
        Variable,
        Group,
        RelationshipReference,
        ComponentReference,
        Connection,
        ComponentMapping,
        VariableMapping,
        Metadata
    };

    struct Item
    {
        Type type;
        CellMLSupport::CellmlFileElement *element;
    };

    typedef QList<Item> Items;

    explicit CellmlAnnotationViewDetailsWidget(QWidget *pParent);
    ~CellmlAnnotationViewDetailsWidget();

    virtual void retranslateUi();

    static Item item(const Type &pType = Empty,
                     CellMLSupport::CellmlFileElement *pElement = 0);

    void updateGui(const Items &pItems);

private:
    Ui::CellmlAnnotationViewDetailsWidget *mGui;

    Items mItems;

    void addRowToFormLayout(const QString &pLabel, const QString &pValue);
};

//==============================================================================

}   // namespace CellMLAnnotationView
}   // namespace OpenCOR

//==============================================================================

#endif

//==============================================================================
// End of file
//==============================================================================