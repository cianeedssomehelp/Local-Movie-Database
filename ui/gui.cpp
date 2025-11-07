#include "gui.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QFormLayout>
#include <vector>
#include "../Utils.h"
#include <QMessageBox>
#include "../Exceptions/Exceptions.h"
#include <QInputDialog>
#include <QDesktopServices>
using namespace std;

GUI::GUI(const Service& service): service{service} , isFiltered{false}
{
    this->initGUI();
    this->populateList();
    this->populatewatchlist();
    this->connectSignalsAndSlots();
}

void GUI::initGUI() {
    QHBoxLayout* mainLayout = new QHBoxLayout{ this };

    // admin side
    QVBoxLayout* adminLayout = new QVBoxLayout{};
    mainLayout->addLayout(adminLayout);
    QLabel* label = new QLabel{ "All movies" };
    movieslist = new QListWidget{};
    adminLayout->addWidget(label);
    adminLayout->addWidget(movieslist);

    QFormLayout* movieDetails = new QFormLayout{};
    title = new QLineEdit{};
    genre = new QLineEdit{};
    publicationYear = new QLineEdit{};
    likes = new QLineEdit{};
    trailer = new QLineEdit{};
    movieDetails->addRow("Title", title);
    movieDetails->addRow("Genre", genre);
    movieDetails->addRow("Year of release", publicationYear);
    movieDetails->addRow("Number of likes", likes);
    movieDetails->addRow("Trailer", trailer);
    adminLayout->addLayout(movieDetails);

    QGridLayout* adminButtons = new QGridLayout{};
    addButton = new QPushButton{ "Add" };
    removeButton = new QPushButton{ "Delete" };
    updateLikesButton = new QPushButton{ "Update likes" };
    updateTrailerButton = new QPushButton{ "Update trailer" };

    adminButtons->addWidget(addButton, 0, 0);
    adminButtons->addWidget(removeButton, 0, 1);
    adminButtons->addWidget(updateLikesButton, 0, 2);
    adminButtons->addWidget(updateTrailerButton, 1, 0);

    adminLayout->addLayout(adminButtons);

    // user side
    moveButton = new QPushButton{ ">" };
    mainLayout->addWidget(moveButton);

    QVBoxLayout* userLayout = new QVBoxLayout{};
    QLabel* labelPlayList = new QLabel{ "Watchlist" };
    userLayout->addWidget(labelPlayList);
    mainLayout->addLayout(userLayout);

    watchlist = new QListWidget{};
    userLayout->addWidget(watchlist);

    QHBoxLayout* userButtonsLayout = new QHBoxLayout{};
    filterButton = new QPushButton{ "Filter by genre" };
    playButton = new QPushButton{ "Play" };
    nextButton = new QPushButton{ "Next" };
    saveToFileButton = new QPushButton{ "Save to file" };
    deleteMovieFromWatchlistButton = new QPushButton{ "Delete"};
    userButtonsLayout->addWidget(filterButton);
    userButtonsLayout->addWidget(playButton);
    userButtonsLayout->addWidget(nextButton);
    userButtonsLayout->addWidget(deleteMovieFromWatchlistButton);
    userButtonsLayout->addWidget(saveToFileButton);

    userLayout->addLayout(userButtonsLayout);
}

void GUI::populateList() {
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

void GUI::populatewatchlist() {
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

void GUI::connectSignalsAndSlots() {
    QObject::connect(this->addButton, &QPushButton::clicked, this, &GUI::addButtonHandler);
    QObject::connect(this->removeButton, &QPushButton::clicked, this, &GUI::removeButtonHandler);
    QObject::connect(this->updateLikesButton, &QPushButton::clicked, this, &GUI::updateLikesButtonHandler);
    QObject::connect(this->updateTrailerButton, &QPushButton::clicked, this, &GUI::updateTrailerButtonHandler);
    QObject::connect(this->filterButton, &QPushButton::clicked, this, &GUI::filterButtonHandler);
    QObject::connect(this->playButton, &QPushButton::clicked, this, &GUI::playButtonHandler);
    QObject::connect(this->moveButton, &QPushButton::clicked, this, &GUI::addToWatchListButtonHandler);
    QObject::connect(this->nextButton, &QPushButton::clicked, this, &GUI::nextButtonHandler);
    QObject::connect(this->saveToFileButton, &QPushButton::clicked, this, &GUI::saveToFileButtonHandler);
    QObject::connect(this->deleteMovieFromWatchlistButton, &QPushButton::clicked, this, &GUI::deleteMovieFromWatchlistButtonHandler);
}

void GUI::addButtonHandler() {
    std::string title = this->title->text().toStdString();
    std::string genre = this->genre->text().toStdString();
    int year_of_release = this->publicationYear->text().toInt();
    int number_of_likes = this->likes->text().toInt();
    std::string trailer = this->trailer->text().toStdString();

    try {
        if (this->service.addMovie(title, genre, year_of_release, number_of_likes, trailer)) {
            QMessageBox::information(this, "Success", "Movie added successfully!");
            this->populateList();
        } else {
            QMessageBox::warning(this, "Error", "Movie already exists!");
        }
    } catch (MovieException& e) {
        string allErrors{};
        for (const auto& error : e.getErrors()) {
            allErrors += error;
        }
        auto ret = QMessageBox::critical(this, "Error", QString::fromStdString(allErrors));
    }
    catch (RepositoryException& e) {
        auto ret = QMessageBox::critical(this, "Error", QString::fromStdString(e.what()));
    }
    catch (DuplicateMovieException& e) {
        auto ret = QMessageBox::critical(this, "Error", QString::fromStdString(e.what()));
    }
    catch (InexistentMovieException& e) {
        auto ret = QMessageBox::critical(this, "Error", QString::fromStdString(e.what()));
    }
}

void GUI::removeButtonHandler() {
    QListWidgetItem* selectedItem = this->movieslist->currentItem();
    if (!selectedItem) {
        QMessageBox::warning(this, "Error", "No movie selected!");
        return;
    }

    QString movieDetails = selectedItem->text();
    std::string title = movieDetails.split(" | ")[0].toStdString();
    std::string genre = movieDetails.split(" | ")[1].toStdString();
    int year_of_release = movieDetails.split(" | ")[2].toInt();

    try {
        this->service.removeMovie(title, genre, year_of_release);
        QMessageBox::information(this, "Success", "Movie removed successfully!");
        this->populateList();
    } catch (RepositoryException& e) {
        QMessageBox::critical(this, "Error", QString::fromStdString(e.what()));
    } catch (InexistentMovieException& e) {
        QMessageBox::critical(this, "Error", QString::fromStdString(e.what()));
        QMessageBox::warning(this, "Error", "Movie not found or could not be deleted!");
    }
}

void GUI::updateLikesButtonHandler() {
    QListWidgetItem* selectedItem = this->movieslist->currentItem();
    if (!selectedItem) {
        QMessageBox::warning(this, "Error", "No movie selected!");
        return;
    }

    QString movieDetails = selectedItem->text();
    std::string title = movieDetails.split(" | ")[0].toStdString();
    std::string genre = movieDetails.split(" | ")[1].toStdString();
    int year_of_release = movieDetails.split(" | ")[2].toInt();

    bool ok;
    int newLikes = QInputDialog::getInt(this, "Update Likes", "Enter new number of likes:", 0, 0, INT_MAX, 1, &ok);
    if (!ok) {
        return;
    }

    try {
        this->service.updateMovieLikes(title, genre, year_of_release, newLikes);
        QMessageBox::information(this, "Success", "Movie likes updated successfully!");
        this->populateList();
    } catch (RepositoryException& e) {
        QMessageBox::critical(this, "Error", QString::fromStdString(e.what()));
    } catch (InexistentMovieException& e) {
        QMessageBox::critical(this, "Error", QString::fromStdString(e.what()));
    }
}

void GUI::updateTrailerButtonHandler() {
    QListWidgetItem* selectedItem = this->movieslist->currentItem();
    if (!selectedItem) {
        QMessageBox::warning(this, "Error", "No movie selected!");
        return;
    }

    QString movieDetails = selectedItem->text();
    std::string title = movieDetails.split(" | ")[0].toStdString();
    std::string genre = movieDetails.split(" | ")[1].toStdString();
    int year_of_release = movieDetails.split(" | ")[2].toInt();

    bool ok;
    QString newTrailer = QInputDialog::getText(this, "Update Trailer", "Enter new trailer URL:", QLineEdit::Normal, "", &ok);
    if (!ok || newTrailer.isEmpty()) {
        return;
    }

    try {
        this->service.updateMovieTrailer(title, genre, year_of_release, newTrailer.toStdString());
        QMessageBox::information(this, "Success", "Movie trailer updated successfully!");
        this->populateList();
    } catch (RepositoryException& e) {
        QMessageBox::critical(this, "Error", QString::fromStdString(e.what()));
    } catch (InexistentMovieException& e) {
        QMessageBox::critical(this, "Error", QString::fromStdString(e.what()));
    }
}

void GUI::filterButtonHandler() {
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

void GUI::playButtonHandler() {
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

void GUI::nextButtonHandler() {
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

void GUI::addToWatchListButtonHandler() {
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
            this->populatewatchlist();
        } else {
            QMessageBox::warning(this, "Error", "Failed to add movie to watchlist!");
            qDebug() << "Failed to add movie: " << QString::fromStdString(title);
        }
    } catch (std::exception& e) {
        QMessageBox::critical(this, "Error", QString::fromStdString(e.what()));
    }
}

void GUI::saveToFileButtonHandler() {
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

void GUI::deleteMovieFromWatchlistButtonHandler() {
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
        this->populatewatchlist();
        this->populateList();
    } catch (std::exception& e) {
        QMessageBox::critical(this, "Error", QString::fromStdString(e.what()));
    }
}