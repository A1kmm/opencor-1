//==============================================================================
// CellML Model Repository window
//==============================================================================

#include "cellmlmodelrepositorywindow.h"
#include "cellmlmodelrepositorywidget.h"
#include "coreutils.h"

//==============================================================================

#include "ui_cellmlmodelrepositorywindow.h"

//==============================================================================

#include <QClipboard>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMenu>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QRegularExpression>

//==============================================================================

namespace OpenCOR {
namespace CellMLModelRepository {

//==============================================================================

CellMLModelRepositoryWindow::CellMLModelRepositoryWindow(QWidget *pParent) :
    OrganisationWidget(pParent),
    mGui(new Ui::CellMLModelRepositoryWindow),
    mModelListRequested(false)
{
    // Set up the GUI

    mGui->setupUi(this);

    // Make the name value our focus proxy

    setFocusProxy(mGui->filterValue);

    // Create and add the CellML Model Repository widget

    mCellMLModelRepositoryWidget = new CellMLModelRepositoryWidget(this);

    mGui->dockWidgetContents->layout()->addWidget(mCellMLModelRepositoryWidget);

    // We want our own context menu for the help widget (indeed, we don't want
    // the default one which has the reload menu item and not the other actions
    // that we have in our tool bar widget, so...)

    mCellMLModelRepositoryWidget->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(mCellMLModelRepositoryWidget, SIGNAL(customContextMenuRequested(const QPoint &)),
            this, SLOT(showCustomContextMenu(const QPoint &)));

    // Keep track of the window's visibility, so that we can request the list of
    // models, if necessary

    connect(this, SIGNAL(visibilityChanged(bool)),
            this, SLOT(retrieveModelList(const bool &)));

    // Create a network access manager so that we can then retrieve a list of
    // CellML models from the CellML Model Repository

    mNetworkAccessManager = new QNetworkAccessManager(this);

    // Make sure that we get told when the download of our Internet file is
    // complete

    connect(mNetworkAccessManager, SIGNAL(finished(QNetworkReply *)),
            this, SLOT(finished(QNetworkReply *)) );
}

//==============================================================================

CellMLModelRepositoryWindow::~CellMLModelRepositoryWindow()
{
    // Delete the GUI

    delete mGui;
}

//==============================================================================

void CellMLModelRepositoryWindow::retranslateUi()
{
    // Retranslate the whole window

    mGui->retranslateUi(this);

    // Retranslate our list of models

    outputModelList(mModelList);
}

//==============================================================================

void CellMLModelRepositoryWindow::outputModelList(const QStringList &pModelList)
{
    // Output a given list of models

    mModelList = pModelList;

    QString contents = "";
    const QString leadingSpaces = "        ";

    if (mModelList.count()) {
        // We have models to list, so...

        if (mModelList.count() == 1)
            contents = tr("<strong>1</strong> CellML model was found:")+"\n";
        else
            contents = tr("<strong>%1</strong> CellML models were found:").arg(mModelList.count())+"\n";

        contents += leadingSpaces+"<ul>\n";

        foreach (const QString &model, mModelList)
            contents += leadingSpaces+"<li><a href=\""+mModelUrls[mModelNames.indexOf(model)]+"\">"+model+"</a></li>\n";

        contents += leadingSpaces+"</ul>";
    } else if (mModelNames.empty()) {
        if (mErrorMsg.count()) {
            // Something went wrong while trying to retrieve the list of models,
            // so...

            QString errorMsg = mErrorMsg[0].toLower()+mErrorMsg.right(mErrorMsg.size()-1);
            QString dots = (errorMsg[errorMsg.size()-1] == '.')?"..":"...";

            contents = leadingSpaces+tr("<strong>Error:</strong> ")+errorMsg+dots;
        } else if (mModelListRequested) {
            // The list is still being loaded, so...

            contents = leadingSpaces+tr("Please wait while the list of CellML models is being loaded...");
        } else {
            // We have yet to request the list of models, so...

            contents = QString();
        }
    } else {
        // No model could be found, so...

        contents = leadingSpaces+tr("No CellML model matches your criteria");
    }

    // Output the list matching the search criteria, or a message telling the
    // user what went wrong, if anything

    mCellMLModelRepositoryWidget->output(contents);
}

//==============================================================================

void CellMLModelRepositoryWindow::on_filterValue_textChanged(const QString &text)
{
    // Generate a Web page that contains all the models which match our search
    // criteria

    outputModelList(mModelNames.filter(QRegularExpression(text, QRegularExpression::CaseInsensitiveOption)));
}

//==============================================================================

void CellMLModelRepositoryWindow::on_actionCopy_triggered()
{
    // Copy the current slection to the clipboard

    QApplication::clipboard()->setText(mCellMLModelRepositoryWidget->selectedText());
}

//==============================================================================

void CellMLModelRepositoryWindow::on_refreshButton_clicked()
{
    // Output the message telling the user that the list is being downloaded
    // Note: to clear mModelNames ensures that we get the correct message from
    //       outputModelList...

    mModelListRequested = true;

    mModelNames.clear();

    outputModelList(QStringList());

    // Disable the GUI side, so that the user doesn't get confused and ask to
    // refresh over and over again while he should just be patient

    setEnabled(false);

    // Get the list of CellML models

    mNetworkAccessManager->get(QNetworkRequest(QUrl("http://models.cellml.org/workspace/rest/contents.json")));
}

//==============================================================================

void CellMLModelRepositoryWindow::finished(QNetworkReply *pNetworkReply)
{
    // Clear some properties

    mModelNames.clear();
    mModelUrls.clear();

    // Output the list of models, should we have retrieved it without any
    // problem

    if (pNetworkReply->error() == QNetworkReply::NoError) {
        // Parse the JSON code

        QJsonParseError jsonParseError;
        QJsonDocument jsonDocument = QJsonDocument::fromJson(pNetworkReply->readAll(), &jsonParseError);

        if (jsonParseError.error == QJsonParseError::NoError) {
            // Retrieve the list of CellML models

            QVariantMap resultMap = jsonDocument.object().toVariantMap();

            foreach (const QVariant &modelVariant, resultMap["values"].toList()) {
                QVariantList modelDetailsVariant = modelVariant.toList();

                mModelNames << modelDetailsVariant[0].toString();
                mModelUrls << modelDetailsVariant[1].toString();
            }

            // Everything went fine, so...

            mErrorMsg = QString();
        } else {
            // Something went wrong, so...

            mErrorMsg = jsonParseError.errorString();
        }
    } else {
        // Something went wrong, so...

        mErrorMsg = pNetworkReply->errorString();
    }

    // Initialise the output using whatever search criteria is present

    on_filterValue_textChanged(mGui->filterValue->text());

    // Re-enable the GUI side

    setEnabled(true);

    // Give, within the current window, the focus to mGui->filterValue, but
    // only if the current window already has the focus

    Core::setFocusTo(mGui->filterValue);

    // Delete (later) the network reply

    pNetworkReply->deleteLater();
}

//==============================================================================

void CellMLModelRepositoryWindow::showCustomContextMenu(const QPoint &pPosition) const
{
    Q_UNUSED(pPosition);

    // Create a custom context menu for our CellML Models Repository widget

    QMenu menu;

    menu.addAction(mGui->actionCopy);

    menu.exec(QCursor::pos());
}

//==============================================================================

void CellMLModelRepositoryWindow::retrieveModelList(const bool &pVisible)
{
    // Retrieve the list of models, if we are becoming visible and the list of
    // models has never been requested before

    if (pVisible && !mModelListRequested)
        on_refreshButton_clicked();
}

//==============================================================================

}   // namespace CellMLModelRepository
}   // namespace OpenCOR

//==============================================================================
// End of file
//==============================================================================
