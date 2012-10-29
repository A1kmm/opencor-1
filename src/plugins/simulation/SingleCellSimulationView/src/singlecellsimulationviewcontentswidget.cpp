//==============================================================================
// Single cell simulation view contents widget
//==============================================================================

#include "borderedwidget.h"
#include "singlecellsimulationviewcontentswidget.h"
#include "singlecellsimulationviewgraphpanelswidget.h"
#include "singlecellsimulationviewinformationwidget.h"

//==============================================================================

#include <QApplication>
#include <QDesktopWidget>
#include <QSettings>

//==============================================================================

#include "ui_singlecellsimulationviewcontentswidget.h"

//==============================================================================

namespace OpenCOR {
namespace SingleCellSimulationView {

//==============================================================================

SingleCellSimulationViewContentsWidget::SingleCellSimulationViewContentsWidget(QWidget *pParent) :
    QSplitter(pParent),
    CommonWidget(pParent),
    mGui(new Ui::SingleCellSimulationViewContentsWidget)
{
    // Set up the GUI

    mGui->setupUi(this);

    // Create a splitter for our information

    mInformationWidget = new SingleCellSimulationViewInformationWidget(this);

    mInformationWidget->setObjectName("Information");

    // Create a splitter for our graph panels and create a connection to keep
    // track of whether we can remove graph panels

    mGraphPanelsWidget = new SingleCellSimulationViewGraphPanelsWidget(this);

    mGraphPanelsWidget->setObjectName("GraphPanels");

    connect(mGraphPanelsWidget, SIGNAL(removeGraphPanelsEnabled(const bool &)),
            this, SIGNAL(removeGraphPanelsEnabled(const bool &)));

    // Add our information and graph panels widgets to ourselves

    addWidget(new Core::BorderedWidget(mInformationWidget,
                                       false, false, true, true));
    addWidget(new Core::BorderedWidget(mGraphPanelsWidget,
                                       false, true, true, false));
}

//==============================================================================

SingleCellSimulationViewContentsWidget::~SingleCellSimulationViewContentsWidget()
{
    // Delete the GUI

    delete mGui;
}

//==============================================================================

void SingleCellSimulationViewContentsWidget::retranslateUi()
{
    // Retranslate the whole widget

    mGui->retranslateUi(this);

    // Retranslate our information widget

    mInformationWidget->retranslateUi();
}

//==============================================================================

static const QString SettingsContentsCount = "ContentsCount";
static const QString SettingsContentsSize  = "ContentsSize%1";

//==============================================================================

void SingleCellSimulationViewContentsWidget::loadSettings(QSettings *pSettings)
{
    // Retrieve and set our sizes

    int sizesCount = pSettings->value(SettingsContentsCount, 0).toInt();
    QList<int> newSizes = QList<int>();

    if (!sizesCount)
        // There are no previous sizes, so get some default ones

        newSizes << 0.25*qApp->desktop()->screenGeometry().width()
                 << 0.75*qApp->desktop()->screenGeometry().width();
    else
        for (int i = 0; i < sizesCount; ++i)
            newSizes << pSettings->value(SettingsContentsSize.arg(QString::number(i))).toInt();

    setSizes(newSizes);

    // Retrieve the settings of our information and graph panels widgets

    pSettings->beginGroup(mInformationWidget->objectName());
        mInformationWidget->loadSettings(pSettings);
    pSettings->endGroup();

    pSettings->beginGroup(mGraphPanelsWidget->objectName());
        mGraphPanelsWidget->loadSettings(pSettings);
    pSettings->endGroup();
}

//==============================================================================

void SingleCellSimulationViewContentsWidget::saveSettings(QSettings *pSettings) const
{
    // Keep track of our sizes

    pSettings->setValue(SettingsContentsCount, count());

    QList<int> contentsSizes = sizes();

    for (int i = 0, iMax = contentsSizes.count(); i < iMax; ++i)
        pSettings->setValue(SettingsContentsSize.arg(QString::number(i)), contentsSizes[i]);

    // Keep track of the settings of our information and graph panels widgets

    pSettings->beginGroup(mInformationWidget->objectName());
        mInformationWidget->saveSettings(pSettings);
    pSettings->endGroup();

    pSettings->beginGroup(mGraphPanelsWidget->objectName());
        mGraphPanelsWidget->saveSettings(pSettings);
    pSettings->endGroup();
}

//==============================================================================

void SingleCellSimulationViewContentsWidget::addGraphPanel()
{
    // Ask our graph panels widget to add a new graph panel

    mGraphPanelsWidget->addGraphPanel();
}

//==============================================================================

void SingleCellSimulationViewContentsWidget::removeGraphPanel()
{
    // Ask our graph panels widget to remove the current graph panel

    mGraphPanelsWidget->removeGraphPanel();
}

//==============================================================================

SingleCellSimulationViewGraphPanelWidget * SingleCellSimulationViewContentsWidget::activeGraphPanel()
{
    // Ask our graph panels widget to retrieve the active graph panel

    return mGraphPanelsWidget->activeGraphPanel();
}

//==============================================================================

void SingleCellSimulationViewContentsWidget::clearGraphPanels()
{
    // Ask our graph panels widget to clear all the graph panels

    mGraphPanelsWidget->clearGraphPanels();
}

//==============================================================================

void SingleCellSimulationViewContentsWidget::clearActiveGraphPanel()
{
    // Ask our graph panels widget to clear the current graph panel

    mGraphPanelsWidget->clearActiveGraphPanel();
}

//==============================================================================

}   // namespace SingleCellSimulationView
}   // namespace OpenCOR

//==============================================================================
// End of file
//==============================================================================