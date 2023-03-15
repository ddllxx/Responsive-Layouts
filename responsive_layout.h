//
// Created by twak on 07/10/2019.
//

#ifndef RESPONSIVELAYOUT_H
#define RESPONSIVELAYOUT_H

#include <QtGui>
#include <QList>
#include <QLayout>
#include <QScrollArea>

class ResponsiveLayout : public QLayout {
public:
    enum LayOutType {
        k_horizon, k_vertical, k_compact
    };
    ResponsiveLayout(): QLayout() {
    }
    ~ResponsiveLayout();

    // standard functions for a QLayout
    void setGeometry(const QRect &rect);

    void addItem(QLayoutItem *item);
    void addResult(QLayoutItem *item);
    QSize sizeHint() const;
    QSize minimumSize() const;
    int count() const;
    QLayoutItem *itemAt(int) const;
    QLayoutItem *takeAt(int);

private:
    QList<QLayoutItem*> list_;
    static LayOutType getLayoutType(int width, int height);
    void horizonLayout(const QRect &rect);
    void verticalLayout(const QRect &rect);
    void compactLayout(const QRect &rect);
};

class ResultLayout : public ResponsiveLayout {
public :
    ResultLayout() : ResponsiveLayout() {}
    ~ResultLayout() = default;
    void setGeometry(const QRect &rect);
};

#endif // RESPONSIVELAYOUT_H
