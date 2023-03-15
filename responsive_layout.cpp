//
// Created by twak on 07/10/2019.
//

#include "responsive_layout.h"
#include "responsive_label.h"
#include <iostream>
#include <QScrollArea>

//using namespace std;

// you should probably make extensive changes to this function
void ResponsiveLayout::setGeometry(const QRect &r /* our layout should always fit inside r */ ) {
    QLayout::setGeometry(r);

//    for (int i = 0; i < list_.size(); ++i) {
//        QLayoutItem *o = list_.at(i);
//        auto p = static_cast<ResponsiveLabel *>(o->widget());
//        if (p) p-> setGeometry( rand() %(r.width()-120)+r.x(),
//                                     rand() %(r.height()-100)+40+r.y(), 60, 60);
//    }
    // for all the Widgets added in ResponsiveWindow.cpp
//    for (int i = 0; i < list_.size(); i++) {

//        QLayoutItem *o = list_.at(i);

//        try {
//            // cast the widget to one of our responsive labels
//            ResponsiveLabel *label = static_cast<ResponsiveLabel *>(o->widget());

//            if (label == NULL) // null: cast failed on pointer
//                std::cout << "warning, unknown widget class in layout" << std::endl;
//            else if (label -> text() == kNavTabs ) // headers go at the top
//                label -> setGeometry(0+r.x(),0+r.y(),r.width(), 40);
//            // only show a search button on small resolution, at the right of the window
//            else if (label -> text() == kSearchButton && r.width() < 500)
//                label -> setGeometry(r.width() - 65+r.x(),45+r.y(),60, 40);
//            // fixme: focus group did not like this behaviour for the search result element.
//            else if (label -> text() == kSearchResult )
//                label -> setGeometry( rand() %(r.width()-120)+r.x(),
//                                     rand() %(r.height()-100)+40+r.y(), 60, 60);
//            else // otherwise: disappear label by moving out of bounds
//                label -> setGeometry (-1,-1,0,0);

//        }
//        catch (std::bad_cast) {
//            // bad_case: cast failed on reference...
//            std::cout << "warning, unknown widget class in layout" << std::endl;
//        }
//    }

    LayOutType type = getLayoutType(r.width(), r.height());
    switch (type) {
    case k_horizon:
        horizonLayout(r);
        break;
    case k_vertical:
        verticalLayout(r);
        break;
    case k_compact:
        compactLayout(r);
        break;
    default:
        break;
    }
}

// following methods provide a trivial list-based implementation of the QLayout class
int ResponsiveLayout::count() const {
    return list_.size();
}

QLayoutItem *ResponsiveLayout::itemAt(int idx) const {
    return list_.value(idx);
}

QLayoutItem *ResponsiveLayout::takeAt(int idx) {
    return idx >= 0 && idx < list_.size() ? list_.takeAt(idx) : 0;
}

void ResponsiveLayout::addItem(QLayoutItem *item) {
    list_.append(item);
}

void ResponsiveLayout::addResult(QLayoutItem *item) {

}

QSize ResponsiveLayout::sizeHint() const {
    return minimumSize();
}

QSize ResponsiveLayout::minimumSize() const {
    return QSize(320,320);
}

ResponsiveLayout::~ResponsiveLayout() {
    QLayoutItem *item;
    while ((item = takeAt(0)))
        delete item;
}

void ResponsiveLayout::compactLayout(const QRect &r)
{
    double gap = 5;
    double deltaw = (r.width() - gap * 2) / 9.0;
    double deltah = (r.height() - gap * 3) / 8.0;

    double sx, sy, sw, sh;
    sx = deltaw + gap + r.x(), sy = r.y() + gap * 2 + deltah * 2, sw = deltaw * 7, sh = deltah * 5;
    double bw = fmax(20, (deltaw * 3 - gap * 2) / 3);
    double bh = deltah / 2;
    for (int i = 0; i < list_.size(); ++i) {
        QLayoutItem *item = list_[i];
        ResponsiveLabel *l = dynamic_cast<ResponsiveLabel *>(item->widget());
        if (l == nullptr) {
            QScrollArea *a = dynamic_cast<QScrollArea *>(item->widget());
            if (a == nullptr) {
                std::cerr << "unknow type";
            } else {
                a->setGeometry(sx - deltaw - gap, sy, sw + deltaw, sh);
                a->widget()->setFixedSize(std::min(960, std::max(720, r.width())), 950);
            }
            continue;
        }
        if (l->text() == kHomeLink)
            l->setGeometry(0 + r.x() + deltaw * 8 + gap * 2, deltah * 2 + gap * 2 + r.y(),deltaw, deltah);
        else if (l->text() == kSearchText)
            l->setGeometry(r.x(), r.y(), deltaw * 8, deltah);
        else if (l->text() == kSearchButton)
            l->setGeometry(r.x() + deltaw * 8 + gap * 2, r.y(), deltaw, deltah);
        else if (l->text() == kSignIn)
            l->setGeometry(r.x() + deltaw * 8 + gap * 2, deltah * 3 + gap * 3 + r.y(), deltaw, deltah);
        else if (l->text() == kNavTabs)
            l->setGeometry(r.x(), deltah + gap + r.y(), deltaw * 8, deltah);
        else if (l->text() == kShoppingBasket)
            l->setGeometry(r.x() + deltaw * 8 + gap * 2, deltah + gap + r.y(), deltaw, deltah);
        else if (l->text() == kSearchBackward)
            l->setGeometry(sx + deltaw * 2, sy + gap  * 2 + sh, bw, bh);
        else if (l->text() == kPage)
            l->setGeometry(sx + deltaw * 2 + bw + gap, sy + gap * 2+ sh, bw, bh);
        else if (l->text() == kSearchForward)
            l->setGeometry(sx + deltaw * 2 + bw * 2 + gap * 2, sy + gap * 2+ sh, bw, bh);
        else
            l->setGeometry(-1, -1, 0, 0);
    }
}

void ResponsiveLayout::horizonLayout(const QRect &r)
{
    double gap = 5;
    double deltaw = (r.width() - gap * 3) / 10.0;
    double deltah = (r.height() - gap * 3) / 16.0;

    double sx, sy, sw, sh;
    sx = r.x() + deltaw * 4, sy = r.y() + gap * 2 + deltah * 15, sw = (deltaw * 2 - gap * 2) / 3, sh = deltah / 1.5;
    sw = fmax(20.0, sw);
    for (int i = 0; i < list_.size(); ++i) {
        QLayoutItem *item = list_[i];
        ResponsiveLabel *l = dynamic_cast<ResponsiveLabel *>(item->widget());
        if (l == nullptr) {
            QScrollArea *a = dynamic_cast<QScrollArea *>(item->widget());
            if (a == nullptr) {
                std::cerr << "unknow type";
            } else {
                a->setGeometry(r.x() + gap * 3 + deltaw * 2, r.y() + deltah * 2 + gap * 2, deltaw * 8, deltah * 13);
                a->widget()->setFixedSize(std::min(960, std::max(720, r.width())), 950);
            }
            continue;
        }
        if (l->text() == kHomeLink)
            l->setGeometry(0 + r.x() + gap, deltah * 2 + gap * 2 + r.y(), deltaw, deltah);
        else if (l->text() == kSearchText)
            l->setGeometry(r.x() + gap, r.y(), deltaw * 8, deltah);
        else if (l->text() == kSearchButton)
            l->setGeometry(r.x() + deltaw * 8 + gap * 2, r.y(), deltaw, deltah);
        else if (l->text() == kSearchOptions)
            l->setGeometry(r.x() + deltaw * 9 + gap * 3, r.y(), deltaw, deltah);
        else if (l->text() == kSignIn)
            l->setGeometry(r.x() + gap + deltaw + gap, deltah + gap + r.y() + deltah + gap, deltaw, deltah);
        else if (l->text() == kNavTabs)
            l->setGeometry(r.x() + gap, deltah + gap + r.y(), deltaw * 8, deltah);
        else if (l->text() == kShoppingBasket)
            l->setGeometry(r.x() + deltaw * 8 + gap * 2, deltah + gap + r.y(), deltaw, deltah);
        else if (l->text() == kDeals)
            l->setGeometry(r.x() + deltaw * 9 + gap * 3, deltah + gap + r.y(), deltaw, deltah);
        else if (l->text() == kSearchBackward)
            l->setGeometry(sx, sy + gap * 2, sw, sh);
        else if (l->text() == kPage)
            l->setGeometry(sx + sw + gap, sy + gap * 2, sw, sh);
        else if (l->text() == kSearchForward)
            l->setGeometry(sx + sw * 2 + gap * 2, sy + gap * 2, sw, sh);
        else if (l->text() == kAdvert)
            l->setGeometry(r.x() + gap, r.y() + deltah * 3 + gap * 3, deltaw * 2 + gap, deltah * 12 - gap);
        else
            l->setGeometry(-1, -1, 0, 0);
    }
}
void ResponsiveLayout::verticalLayout(const QRect &r)
{
    double gap = 5;
    double deltaw = (r.width() - gap * 3) / 10.0;
    double deltah = (r.height() - gap * 3) / 16.0;

    double sx, sy, sw, sh;
    sx = r.x() + deltaw * 4, sy = r.y() + gap * 2 + deltah * 15, sw = (deltaw * 2 - gap * 2) / 3, sh = deltah / 1.5;
    sw = fmax(20.0, sw);
    for (int i = 0; i < list_.size(); ++i) {
        QLayoutItem *item = list_[i];
        ResponsiveLabel *l = dynamic_cast<ResponsiveLabel *>(item->widget());
        if (l == nullptr) {
            QScrollArea *a = dynamic_cast<QScrollArea *>(item->widget());
            if (a == nullptr) {
                std::cerr << "unknow type";
            } else {
                a->setGeometry(r.x() + gap, r.y() + deltah * 2 + gap * 2, deltaw * 8, deltah * 13);
                a->widget()->setFixedSize(std::min(960, std::max(720, r.width())), 950);
            }
            continue;
        }
        if (l->text() == kHomeLink)
            l->setGeometry(0 + r.x() + deltaw * 8 + gap * 2, deltah * 2 + gap * 2 + r.y(), deltaw, deltah);
        else if (l->text() == kSearchText)
            l->setGeometry(r.x() + gap, r.y(), deltaw * 8, deltah);
        else if (l->text() == kSearchButton)
            l->setGeometry(r.x() + deltaw * 8 + gap * 2, r.y(), deltaw, deltah);
        else if (l->text() == kSearchOptions)
            l->setGeometry(r.x() + deltaw * 9 + gap * 3, r.y(), deltaw, deltah);
        else if (l->text() == kSignIn)
            l->setGeometry(r.x() + deltaw * 9 + gap * 3, deltah + gap + r.y() + deltah + gap, deltaw, deltah);
        else if (l->text() == kNavTabs)
            l->setGeometry(r.x() + gap, deltah + gap + r.y(), deltaw * 8, deltah);
        else if (l->text() == kShoppingBasket)
            l->setGeometry(r.x() + deltaw * 8 + gap * 2, deltah + gap + r.y(), deltaw, deltah);
        else if (l->text() == kDeals)
            l->setGeometry(r.x() + deltaw * 9 + gap * 3, deltah + gap + r.y(), deltaw, deltah);
        else if (l->text() == kSearchBackward)
            l->setGeometry(sx, sy + gap * 2, sw, sh);
        else if (l->text() == kPage)
            l->setGeometry(sx + sw + gap, sy + gap * 2, sw, sh);
        else if (l->text() == kSearchForward)
            l->setGeometry(sx + sw * 2 + gap * 2, sy + gap * 2, sw, sh);
        else
            l->setGeometry(-1, -1, 0, 0);
    }
}

ResponsiveLayout::LayOutType ResponsiveLayout::getLayoutType(int width, int height)
{
    if ((width / height > 1.5) || (width > 900 && height > 600)) {
        return k_horizon;
    } else if (height > 500) {
        return k_vertical;
    } else {
        return k_compact;
    }
}

void ResultLayout::setGeometry(const QRect &rect) {
    double gap = 5;
    double w = 180, h = 180 / 4 * 3, dh = 180 / 4;
    int rn = std::max((rect.width() + gap) / (w + gap) , 1.5);
    int ci = 0;
    int ri = 0;
    int dci = 0;
    int dri = 0;
    for (int i = 0; i < count(); ++i) {
        ResponsiveLabel *l = dynamic_cast<ResponsiveLabel *>(itemAt(i)->widget());
        if (l == nullptr) {
            std::cerr << "unknow type\n";
            continue;
        }
        if (l->text() == kImage) {
            double y = ri * dh * 4 + gap * ri, x = ci * w + gap * ci;
            l->setGeometry(x, y, w, h);
            ri += (ci + 1) / rn;
            ci = (ci + 1) % rn;
        } else if (l->text() == kDesc) {
            double y = dri * dh * 4 + gap * dri + dh * 3, x = dci * w + gap * dci;
            l->setGeometry(x, y, w, dh);
            dri += (dci + 1) / rn;
            dci = (dci + 1) % rn;
        } else
            l->setGeometry(-1, -1, 0, 0);
    }
    return;
}
