//
// Created by twak on 14/10/2019.
//

#ifndef RESPONSIVEWINDOW_H
#define RESPONSIVEWINDOW_H

#include <QWidget>
#include <QScrollArea>

//using namespace std;

class ResponsiveWindow: public QWidget {

public:
    ResponsiveWindow();

protected:
    void createWidgets();
    QScrollArea *createResult();
};


#endif //RESPONSIVEWINDOW_H
