#ifndef PMREXPLORERWINDOW_H
#define PMREXPLORERWINDOW_H

#include "commonwidget.h"

#include <QDockWidget>

namespace Ui {
    class PmrExplorerWindow;
}

class PmrExplorerWidget;

class PmrExplorerWindow : public QDockWidget, public CommonWidget
{
    Q_OBJECT

public:
    explicit PmrExplorerWindow(QWidget *pParent = 0);
    ~PmrExplorerWindow();

    virtual void retranslateUi();

    virtual void defaultSettings();

private:
    Ui::PmrExplorerWindow *mUi;

    PmrExplorerWidget *mPmrExplorerWidget;
};

#endif
