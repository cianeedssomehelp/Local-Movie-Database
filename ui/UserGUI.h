#pragma once
#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include "Service.h"
#ifndef USERGUI_H
#define USERGUI_H

class UserGUI : public QWidget {
    Q_OBJECT

private:
    Service& service;
    QListWidget* movieslist;
    QListWidget* watchlist;
    QPushButton* addButton;
    QPushButton* filterButton;
    QPushButton* playButton;
    QPushButton* nextButton;
    QPushButton* addToWatchListButton;
    QPushButton* deleteMovieFromWatchlistButton;
    QPushButton* saveToFileButton;
    bool isFiltered;

public:
    explicit UserGUI(Service& service, QWidget* parent = nullptr);
    void initGUI();
    void populateList();
    void populateWatchlist();
    void connectSignalsAndSlots();
    void filterButtonHandler();
    void addToWatchListButtonHandler();
    void playButtonHandler();
    void nextButtonHandler();
    void deleteMovieFromWatchlistButtonHandler();
    void saveToFileButtonHandler();
};

#endif //USERGUI_H
