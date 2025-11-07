#include "UserGUI.h"

#include <QDesktopServices>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QInputDialog>
#include <QLabel>
#include <iterator>

UserGUI::UserGUI(Service& service, QWidget* parent) : QWidget(parent), service(service) {
    this->initGUI();
    this->populateList();
    this->populateWatchlist();
    this->connectSignalsAndSlots();
}

void UserGUI::initGUI() {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    this->movieslist = new QListWidget(this);
    this->watchlist = new QListWidget(this);

    mainLayout->addWidget(new QLabel("Movies List", this));
    mainLayout->addWidget(this->movieslist);
    mainLayout->addWidget(new QLabel("Watchlist", this));
    mainLayout->addWidget(this->watchlist);

    QHBoxLayout* buttonsLayout = new QHBoxLayout();
    this->filterButton = new QPushButton("Filter Movies", this);
    this->playButton = new QPushButton("Play Trailer", this);
    this->nextButton = new QPushButton("Next Movie", this);
    this->addToWatchListButton = new QPushButton("Add to Watchlist", this);
    this->deleteMovieFromWatchlistButton = new QPushButton("Remove from Watchlist", this);
    this->saveToFileButton = new QPushButton("Save Watchlist to File", this);

    buttonsLayout->addWidget(this->filterButton);
    buttonsLayout->addWidget(this->playButton);
    buttonsLayout->addWidget(this->nextButton);
    buttonsLayout->addWidget(this->addToWatchListButton);
    buttonsLayout->addWidget(this->deleteMovieFromWatchlistButton);
    buttonsLayout->addWidget(this->saveToFileButton);

    mainLayout->addLayout(buttonsLayout);
}

void UserGUI::populateList() {
    if (this->movieslist->count() > 0)
        this->movieslist->clear();

    vector<Movies> movies = this->service.getAllMovies();
    for (const auto& movie : movies) {
        QString movieDetails = QString::fromStdString(
            movie.getTitle() + " | " + movie.getGenre() + " | " +
            std::to_string(movie.getYearOfRelease()) + " | " +
            std::to_string(movie.getNumberOfLikes()) + " likes | " +
            movie.getTrailer()
        );
        this->movieslist->addItem(movieDetails);
    }
}

void UserGUI::populateWatchlist() {
    if (this->watchlist->count() > 0)
        this->watchlist->clear();
    vector<Movies> movies = this->service.getWatchlist().getMovies();
    for (const auto& movie : movies) {
        QString movieDetails = QString::fromStdString(
            movie.getTitle() + " | " + movie.getGenre() + " | " +
            std::to_string(movie.getYearOfRelease()) + " | " +
            std::to_string(movie.getNumberOfLikes()) + " likes | " +
            movie.getTrailer()
        );
        this->watchlist->addItem(movieDetails);
    }
}

void UserGUI::connectSignalsAndSlots() {
    connect(this->filterButton, &QPushButton::clicked, this, &UserGUI::filterButtonHandler);
    connect(this->playButton, &QPushButton::clicked, this, &UserGUI::playButtonHandler);
    connect(this->nextButton, &QPushButton::clicked, this, &UserGUI::nextButtonHandler);
    connect(this->addToWatchListButton, &QPushButton::clicked, this, &UserGUI::addToWatchListButtonHandler);
    connect(this->deleteMovieFromWatchlistButton, &QPushButton::clicked, this, &UserGUI::deleteMovieFromWatchlistButtonHandler);
    connect(this->saveToFileButton, &QPushButton::clicked, this, &UserGUI::saveToFileButtonHandler);
}

void UserGUI::filterButtonHandler() {
    bool ok;
    QString genre = QInputDialog::getText(this, "Filter Movies", "Enter genre to filter by:", QLineEdit::Normal, "", &ok);
    if (!ok || genre.isEmpty()) {
        return;
    }

    try {
        std::vector<Movies> filteredMovies = this->service.filterMoviesByGenre(genre.toStdString(), "", 0);
        this->movieslist->clear();
        for (const auto& movie : filteredMovies) {
            QString movieDetails = QString::fromStdString(
                movie.getTitle() + " | " + movie.getGenre() + " | " +
                std::to_string(movie.getYearOfRelease()) + " | " +
                std::to_string(movie.getNumberOfLikes()) + " likes | " +
                movie.getTrailer()
            );
            this->movieslist->addItem(movieDetails);
        }
        this->isFiltered = true;
    } catch (std::exception& e) {
        QMessageBox::critical(this, "Error", QString::fromStdString(e.what()));
    }
}

void UserGUI::addToWatchListButtonHandler() {
    QListWidgetItem* selectedItem = this->movieslist->currentItem();
    if (!selectedItem) {
        QMessageBox::warning(this, "Error", "No movie selected!");
        return;
    }

    QString movieDetails = selectedItem->text();
    QStringList details = movieDetails.split(" | ");
    if (details.size() < 5) {
        QMessageBox::warning(this, "Error", "Invalid movie details!");
        return;
    }

    std::string title = details[0].toStdString();
    std::string genre = details[1].toStdString();
    int year_of_release = details[2].toInt();
    int number_of_likes = details[3].split(" ")[0].toInt();
    std::string trailer = details[4].toStdString();

    try {
        if (this->service.movieExistsInWatchlist(title, genre, year_of_release)) {
            QMessageBox::warning(this, "Error", "Movie already in watchlist!");
        } else if (this->service.addMovietoWatchlist(title, genre, year_of_release, number_of_likes, trailer)) {
            QMessageBox::information(this, "Success", "Movie added to watchlist successfully!");
            this->populateList();
        } else {
            QMessageBox::warning(this, "Error", "Failed to add movie to watchlist!");
            qDebug() << "Failed to add movie: " << QString::fromStdString(title);
        }
    } catch (std::exception& e) {
        QMessageBox::critical(this, "Error", QString::fromStdString(e.what()));
    }
}

void UserGUI::playButtonHandler() {
    if (!this->isFiltered) {
        QMessageBox::warning(this, "Error", "Please filter the list before playing!");
        return;
    }

    if (this->movieslist->count() == 0) {
        QMessageBox::warning(this, "Error", "No movies available in the filtered list!");
        return;
    }

    try {
        QListWidgetItem* firstItem = this->movieslist->item(0);
        QString movieDetails = firstItem->text();
        std::string trailer = movieDetails.split(" | ")[4].toStdString();
        QDesktopServices::openUrl(QUrl(QString::fromStdString(trailer)));
        QMessageBox::information(this, "Success", "Playing the first movie in the filtered list!");
    } catch (std::exception& e) {
        QMessageBox::critical(this, "Error", QString::fromStdString(e.what()));
    }
}

void UserGUI::nextButtonHandler() {
    if (!this->isFiltered) {
        QMessageBox::warning(this, "Error", "Please filter the list before moving to the next movie!");
        return;
    }

    try {
        this->service.nextMovieFromWatchlist();
        QMessageBox::information(this, "Success", "Moved to the next movie in the watchlist!");
    } catch (std::exception& e) {
        QMessageBox::critical(this, "Error", QString::fromStdString(e.what()));
    }
}

void UserGUI::deleteMovieFromWatchlistButtonHandler() {
    QListWidgetItem* selectedItem = this->watchlist->currentItem();
    if (!selectedItem) {
        QMessageBox::warning(this, "Error", "No movie selected!");
        return;
    }

    QString movieDetails = selectedItem->text();
    std::string title = movieDetails.split(" | ")[0].toStdString();
    std::string genre = movieDetails.split(" | ")[1].toStdString();
    int year_of_release = movieDetails.split(" | ")[2].toInt();

    try {

        QMessageBox::StandardButton reply = QMessageBox::question(
            this, "Like Movie", "Do you want to like this movie before removing it from the watchlist?",
            QMessageBox::Yes | QMessageBox::No
        );

        if (reply == QMessageBox::Yes) {
            int currentLikes = this->service.getMovies(title, genre, year_of_release).getNumberOfLikes();
            this->service.updateMovieLikes(title, genre, year_of_release, currentLikes + 1);
        }

        this->service.removeMovieFromWatchlist(title, genre, year_of_release);
        QMessageBox::information(this, "Success", "Movie removed from watchlist successfully!");
        this->populateList();
        this->populateList();
    } catch (std::exception& e) {
        QMessageBox::critical(this, "Error", QString::fromStdString(e.what()));
    }
}

void UserGUI::saveToFileButtonHandler() {
    bool ok;
    QString filename = QInputDialog::getText(this, "Save Watchlist", "Enter the filename:", QLineEdit::Normal, "", &ok);
    if (!ok || filename.isEmpty()) {
        QMessageBox::warning(this, "Error", "Filename cannot be empty!");
        return;
    }

    try {
        this->service.saveWatchlist(filename.toStdString());
        QMessageBox::information(this, "Success", "Watchlist saved successfully!");
    } catch (std::exception& e) {
        QMessageBox::critical(this, "Error", QString::fromStdString(e.what()));
    }
}
