#pragma once
#include <QWidget>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include "Service.h"

#ifndef ADMINGUI_H
#define ADMINGUI_H

class AdminGUI : public QWidget {
    Q_OBJECT

private:
    Service& service;
    QListWidget* movieslist;
    QLineEdit* title;
    QLineEdit* genre;
    QLineEdit* publicationYear;
    QLineEdit* likes;
    QLineEdit* trailer;
    QPushButton* addButton;
    QPushButton* removeButton;
    QPushButton* updateLikesButton;
    QPushButton* updateTrailerButton;
    QPushButton* showBarChartButton;

public:
    explicit AdminGUI(Service& service, QWidget* parent = nullptr);
    void initGUI();
    void populateList();
    void connectSignalsAndSlots();
    void addButtonHandler();
    void removeButtonHandler();
    void updateLikesButtonHandler();
    void updateTrailerButtonHandler();

    void showBarChartHandler();
};

#endif //ADMINGUI_H
