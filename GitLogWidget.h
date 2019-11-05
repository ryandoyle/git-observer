//
// Created by ryan on 5/11/19.
//

#ifndef GIT_OBSERVER_GITLOGWIDGET_H
#define GIT_OBSERVER_GITLOGWIDGET_H


#include <QtWidgets>

class GitLogWidget: public QListWidget {
Q_OBJECT
public:
    explicit GitLogWidget(QWidget *parent);

    virtual ~GitLogWidget();
};


#endif //GIT_OBSERVER_GITLOGWIDGET_H
