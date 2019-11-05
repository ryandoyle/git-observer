
#include <QtWidgets>
#include "MainWindow.h"
#include "GitLogWidget.h"

MainWindow::MainWindow() {

    const QRect &currentGeometry = QApplication::desktop()->availableGeometry(this);
    resize(currentGeometry.width() / 3, currentGeometry.height() / 2);


    // Main window
    QSplitter *centralWidget = new QSplitter(this);

    // DiffViewer
    QSplitter *diffViewContainer = new QSplitter(centralWidget);
    QTreeView *diffFileTree = new QTreeView;
    QTextEdit *currentDiffedFile = new QTextEdit;
    diffViewContainer->addWidget(diffFileTree);
    diffViewContainer->addWidget(currentDiffedFile);
    diffViewContainer->setChildrenCollapsible(false);
    QList<int> sizes;
    // FIXME: load from persisted dimensions and scale logarithmically for larger displays.
    //        Also, don't use fixed pixel values
    sizes.push_back(100);
    sizes.push_back(400);
    diffViewContainer->setSizes(sizes);



    GitLogWidget *logWidget = new GitLogWidget(centralWidget);
    centralWidget->setOrientation(Qt::Orientation::Vertical);
    centralWidget->setChildrenCollapsible(false);
    centralWidget->addWidget(diffViewContainer);
    centralWidget->addWidget(logWidget);


    setCentralWidget(centralWidget);

    setUnifiedTitleAndToolBarOnMac(true);
}
