//
// Created by twak on 14/10/2019.
//

#ifndef RESPONSIVELABEL_H
#define RESPONSIVELABEL_H


#include <QLabel>
#include <QString>
#include <map>

//using namespace std;

// Please add to, but DO NOT modify the existing constants in this file.
// label names that are displayed
const QString
        kHomeLink       = "home",
        kShoppingBasket = "basket",
        kSignIn         = "sign-in",
        kNavTabs        = "navigation tabs",
        kAdvert         = "advert",
        kSearchButton   = "search",
        kSearchResult   = "result",
        kSearchText     = "search query",
        kSearchForward  = ">",
        kSearchBackward = "<",
        kSearchOptions  = "search options",
        kDeals          = "deals",
        kImage          = "image",
        kDesc           = "desc",
        kPage           = "page#";

// every label name has a colour
const std::map<QString, QString> kColours = {
        std::make_pair(kHomeLink,       "#ffaaff"),
        std::make_pair(kShoppingBasket, "#ffaaaa"),
        std::make_pair(kSignIn,         "#aaffaa"),
        std::make_pair(kNavTabs,        "#ffa9d3"),
        std::make_pair(kAdvert,         "#ffaa66"),
        std::make_pair(kSearchButton,   "#aaffff"),
        std::make_pair(kSearchResult,   "#99ddff"),
        std::make_pair(kSearchText,     "#aaaaff"),
        std::make_pair(kSearchForward,  "#5caeff"),
        std::make_pair(kSearchBackward, "#5caeff"),
        std::make_pair(kSearchOptions,  "#9dceff"),
        std::make_pair(kDeals, "#ababab"),
        std::make_pair(kImage, "#5555ff"),
        std::make_pair(kDesc, "#1111ff"),
        std::make_pair(kPage, "#acacac")
    };

class ResponsiveLabel : public QLabel {
public:
    ResponsiveLabel(QString name) ;
    ResponsiveLabel(QString name, QString colour) ;
};


#endif // RESPONSIVELABEL_H
