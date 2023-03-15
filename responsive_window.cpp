//
// Created by twak on 14/10/2019.
//

#include "responsive_window.h"
#include "responsive_layout.h"
#include "screenshot.h"
#include <iostream>
#include <QApplication>


ResponsiveWindow::ResponsiveWindow() {

    setWindowTitle("2811: Coursework 1");
    setMinimumSize(320, 320);
    setMaximumSize(1280, 720);

    createWidgets();
}

void ResponsiveWindow::createWidgets() {

    ResponsiveLayout * rl = new ResponsiveLayout();

    // add all the widgets we need to demonstrate all layouts
    rl->addWidget(new ResponsiveLabel(kNavTabs));
    rl->addWidget(new ResponsiveLabel(kSearchButton));
    rl->addWidget(new ResponsiveLabel(kSearchOptions));
    rl->addWidget(new ResponsiveLabel(kHomeLink));
    rl->addWidget(new ResponsiveLabel(kSignIn));
    rl->addWidget(new ResponsiveLabel(kSearchText));
    rl->addWidget(new ResponsiveLabel(kShoppingBasket));
    rl->addWidget(new ResponsiveLabel(kDeals));
    rl->addWidget(new ResponsiveLabel(kAdvert));
    rl->addWidget(new ResponsiveLabel(kSearchForward));
    rl->addWidget(new ResponsiveLabel(kSearchBackward));
    rl->addWidget(new ResponsiveLabel(kPage));
    rl->addWidget(createResult());
    // we might have more than one search results
//    rl->addWidget(new ResponsiveLabel(kSearchResult));
//    rl->addWidget(new ResponsiveLabel(kSearchResult));
//    constexpr int resultCount = 17;
//    for (int i = 0; i < resultCount; ++i) {
//        rl->addWidget(new ResponsiveLabel(kSearchResult));
//    }
    // note that later widgets are drawn on top of earlier widgets

    setLayout(rl);
}


QScrollArea *ResponsiveWindow::createResult() {
    QScrollArea *a = new QScrollArea();
    a->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    a->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    a->setWidgetResizable(true);

    QWidget *w = new QWidget();
    w->setFixedSize(900, 800);
    ResultLayout *l = new ResultLayout();
    l->setSizeConstraint(QLayout::SetNoConstraint);
    a->setWidget(w);
    w->setLayout(l);
    for (int i = 0; i < 17; ++i) {
        l->addWidget(new ResponsiveLabel(kImage));
        l->addWidget(new ResponsiveLabel(kDesc));
    }
    return a;
}
