#pragma once

#include <qwidget.h>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include "Service.h"

class GUI : public QWidget {

private:
    Service service;
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
    QPushButton* filterButton;

    QPushButton* moveButton;
    QListWidget* watchlist;
    QPushButton* playButton;
    QPushButton* nextButton;
    QPushButton* deleteMovieFromWatchlistButton;
    QPushButton* saveToFileButton;
    bool isFiltered;

public:
    explicit GUI(const Service& service);
    void initGUI();
    void populateList();
    void populatewatchlist();
    void connectSignalsAndSlots();
    void addButtonHandler();
    void removeButtonHandler();
    void updateLikesButtonHandler();
    void updateTrailerButtonHandler();
    void filterButtonHandler();
    void playButtonHandler();
    void nextButtonHandler();
    void addToWatchListButtonHandler();
    void saveToFileButtonHandler();
    void deleteMovieFromWatchlistButtonHandler();
};