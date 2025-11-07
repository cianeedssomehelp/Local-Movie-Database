#include "AdminGUI.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QInputDialog>
#include <BarChartWidget.h>
AdminGUI::AdminGUI(Service& service, QWidget* parent) : QWidget(parent), service(service) {
    this->initGUI();
    this->populateList();
    this->connectSignalsAndSlots();
}

void AdminGUI::initGUI() {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    this->movieslist = new QListWidget(this);
    mainLayout->addWidget(this->movieslist);

    QHBoxLayout* formLayout = new QHBoxLayout();
    this->title = new QLineEdit(this);
    this->title->setPlaceholderText("Title");
    this->genre = new QLineEdit(this);
    this->genre->setPlaceholderText("Genre");
    this->publicationYear = new QLineEdit(this);
    this->publicationYear->setPlaceholderText("Year");
    this->likes = new QLineEdit(this);
    this->likes->setPlaceholderText("Likes");
    this->trailer = new QLineEdit(this);
    this->trailer->setPlaceholderText("Trailer");

    this->showBarChartButton = new QPushButton("Show Bar Chart", this);


    formLayout->addWidget(this->title);
    formLayout->addWidget(this->genre);
    formLayout->addWidget(this->publicationYear);
    formLayout->addWidget(this->likes);
    formLayout->addWidget(this->trailer);

    mainLayout->addLayout(formLayout);

    QHBoxLayout* buttonsLayout = new QHBoxLayout();
    this->addButton = new QPushButton("Add Movie", this);
    this->removeButton = new QPushButton("Remove Movie", this);
    this->updateLikesButton = new QPushButton("Update Likes", this);
    this->updateTrailerButton = new QPushButton("Update Trailer", this);

    buttonsLayout->addWidget(this->addButton);
    buttonsLayout->addWidget(this->removeButton);
    buttonsLayout->addWidget(this->updateLikesButton);
    buttonsLayout->addWidget(this->updateTrailerButton);
    buttonsLayout->addWidget(this->showBarChartButton);
    mainLayout->addLayout(buttonsLayout);
}

void AdminGUI::populateList() {
    this->movieslist->clear();
    for (const auto& movie : this->service.getAllMovies()) {
        QString movieDetails = QString::fromStdString(
            movie.getTitle() + " | " + movie.getGenre() + " | " +
            std::to_string(movie.getYearOfRelease()) + " | " +
            std::to_string(movie.getNumberOfLikes()) + " likes | " +
            movie.getTrailer()
        );
        this->movieslist->addItem(movieDetails);
    }
}

void AdminGUI::connectSignalsAndSlots() {
    connect(this->addButton, &QPushButton::clicked, this, &AdminGUI::addButtonHandler);
    connect(this->removeButton, &QPushButton::clicked, this, &AdminGUI::removeButtonHandler);
    connect(this->updateLikesButton, &QPushButton::clicked, this, &AdminGUI::updateLikesButtonHandler);
    connect(this->updateTrailerButton, &QPushButton::clicked, this, &AdminGUI::updateTrailerButtonHandler);
    connect(this->showBarChartButton, &QPushButton::clicked, this, &AdminGUI::showBarChartHandler);

}

void AdminGUI::addButtonHandler() {
    try {
        std::string title = this->title->text().toStdString();
        std::string genre = this->genre->text().toStdString();
        int year = this->publicationYear->text().toInt();
        int likes = this->likes->text().toInt();
        std::string trailer = this->trailer->text().toStdString();

        this->service.addMovie(title, genre, year, likes, trailer);
        QMessageBox::information(this, "Success", "Movie added successfully!");
        this->populateList();
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Error", QString::fromStdString(e.what()));
    }
}

void AdminGUI::removeButtonHandler() {
    QListWidgetItem* selectedItem = this->movieslist->currentItem();
    if (!selectedItem) {
        QMessageBox::warning(this, "Error", "No movie selected!");
        return;
    }

    QString movieDetails = selectedItem->text();
    std::string title = movieDetails.split(" | ")[0].toStdString();
    std::string genre = movieDetails.split(" | ")[1].toStdString();
    int year = movieDetails.split(" | ")[2].toInt();

    try {
        this->service.removeMovie(title, genre, year);
        QMessageBox::information(this, "Success", "Movie removed successfully!");
        this->populateList();
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Error", QString::fromStdString(e.what()));
    }
}

void AdminGUI::updateLikesButtonHandler() {
    QListWidgetItem* selectedItem = this->movieslist->currentItem();
    if (!selectedItem) {
        QMessageBox::warning(this, "Error", "No movie selected!");
        return;
    }

    QString movieDetails = selectedItem->text();
    std::string title = movieDetails.split(" | ")[0].toStdString();
    std::string genre = movieDetails.split(" | ")[1].toStdString();
    int year = movieDetails.split(" | ")[2].toInt();

    bool ok;
    int newLikes = QInputDialog::getInt(this, "Update Likes", "Enter new number of likes:", 0, 0, 1000000, 1, &ok);
    if (!ok) {
        return;
    }

    try {
        this->service.updateMovieLikes(title, genre, year, newLikes);
        QMessageBox::information(this, "Success", "Movie likes updated successfully!");
        this->populateList();
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Error", QString::fromStdString(e.what()));
    }
}

void AdminGUI::updateTrailerButtonHandler() {
    QListWidgetItem* selectedItem = this->movieslist->currentItem();
    if (!selectedItem) {
        QMessageBox::warning(this, "Error", "No movie selected!");
        return;
    }

    QString movieDetails = selectedItem->text();
    std::string title = movieDetails.split(" | ")[0].toStdString();
    std::string genre = movieDetails.split(" | ")[1].toStdString();
    int year = movieDetails.split(" | ")[2].toInt();

    bool ok;
    QString newTrailer = QInputDialog::getText(this, "Update Trailer", "Enter new trailer URL:", QLineEdit::Normal, "", &ok);
    if (!ok || newTrailer.isEmpty()) {
        return;
    }

    try {
        this->service.updateMovieTrailer(title, genre, year, newTrailer.toStdString());
        QMessageBox::information(this, "Success", "Movie trailer updated successfully!");
        this->populateList();
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Error", QString::fromStdString(e.what()));
    }
}


void AdminGUI::showBarChartHandler() {

    std::map<std::string, int> genreData;
    for (const auto& movie : this->service.getAllMovies()) {
        genreData[movie.getGenre()]++;
    }

    QWidget* chartWindow = new QWidget;
    QVBoxLayout* layout = new QVBoxLayout(chartWindow);
    BarChartWidget* chart = new BarChartWidget(genreData);
    layout->addWidget(chart);
    chartWindow->setWindowTitle("Movies by Genre");
    chartWindow->resize(600, 400);
    chartWindow->show();
}