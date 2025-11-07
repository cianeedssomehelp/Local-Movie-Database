#include "Service.h"
#include "domain.h"
#include "Ui.h"
#include <limits>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <cstring>

#include "CSVRepository.h"
#include "HTMLRepository.h"
#include "../Exceptions/Exceptions.h"
using namespace std;

void Ui::printMenu() {
    cout<<"========================================================="<<endl;
    cout<<"Welcome to our movie database!"<<endl;
    cout<<"Who are you accessing the application as?"<<endl;
    cout<<"1. Administrator mode."<<endl;
    cout<<"2. User mode."<<endl;
    cout<<"0. Exit."<<endl;
    cout<<"========================================================="<<endl;
    cout<<"> ";
}

void Ui::printAdministratorMenu() {
    cout<<"------------------------------------------------------------"<<endl;
    cout<<"Here's what you can do as an administrator: >"<<endl;
    cout<<"1. See all movies."<<endl;
    cout<<"2. Add a movie."<<endl;
    cout<<"3. Remove a movie."<<endl;
    cout<<"4. Update the number of likes for a movie."<<endl;
    cout<<"5. Update the trailer for a movie."<<endl;
    cout<<"0. Exit."<<endl;
    cout<<"------------------------------------------------------------"<<endl;
    cout<<"> ";

}

void Ui::printUserMenu() {
    cout<<"------------------------------------------------------------"<<endl;
    cout<<"Here's what you can do as a user: "<<endl;
    cout<<"1. See the movies with a given genre."<<endl;
    cout<<"2. Add the movie to your watchlist."<<endl;
    cout<<"3. Delete the movie from your watchlist."<<endl;
    cout<<"4. See the watchlist."<<endl;
    cout<<"5. Save the watchlist to a file."<<endl;
    cout<<"0. Exit."<<endl;
    cout<<"------------------------------------------------------------"<<endl;
    cout<<"> ";
}

void Ui::nextMenu() {
    cout<<"Do you want to add this movie to your watch list or continue to the next trailer?"<<endl;
    cout<<"1. Add the movie."<<endl;
    cout<<"0. Watch the next trailer."<<endl;
    cout<<"> ";
}

void Ui::stringMovie(Movies movie) {
    cout<<"*Title: "<<movie.getTitle()<<" | "<<"Genre: "<<movie.getGenre()<<" | "<<"Year of release: "<<movie.getYearOfRelease()<<" | "<<"Number of likes: "<<movie.getNumberOfLikes()<<" | "<<endl<<"Trailer of the movie: "<<movie.getTrailer()<<endl;
}

void Ui::stringMovieTrailer(Movies movie){
    cout<<"=================================================================="<<endl;
    cout<<"Title: "<<movie.getTitle()<<endl;
    cout<<"Genre: "<<movie.getGenre()<<endl;
    cout<<"Year of release: "<<movie.getYearOfRelease()<<endl;
    cout<<"Number of likes: "<<movie.getNumberOfLikes()<<endl;
    cout<<"Trailer of the movie: "<<movie.getTrailer()<<endl;
    //watchTrailer(movie.getTrailer().c_str());
    cout<<"=================================================================="<<endl;
}

void Ui::addMovieUi() {
    char title[100], genre[100], trailer[250];
    int year_of_release, number_of_likes;
    cout<<"Please enter the title of the movie: > "<<endl;
    cin.ignore();
    cin.getline(title, 100);

    cout<<"Please enter the genre of the movie: > "<<endl;
    cin.getline(genre, 100);

    cout<<"Please enter the year of release of the movie: > "<<endl;
    cin>>year_of_release;
    while (year_of_release > 2025 || year_of_release < 1900) {
        cout<<"The year of release must be between 1900 and 2025. Please enter a valid year of release: > "<<endl;
        cin>>year_of_release;
    }

    cout<<"Please enter the number of likes: > "<<endl;
    cin>>number_of_likes;
    while (number_of_likes < 0) {
        cout<<"The number of likes must be a positive integer. Please enter a valid number of likes: > "<<endl;
        cin.ignore();
        cin>>number_of_likes;
    }

    cout<<"Please enter the trailer link of the movie: > "<<endl;
    cin.ignore();
    cin.getline(trailer, 250);
    try {
        cout << "Adding the movie to the database..." << endl;
        if (this->service.addMovie(title, genre, year_of_release, number_of_likes, trailer)) {
            cout << "The movie was successfully added to the database!" << endl;
        } else {
            cout << "The movie already exists in the database!" << endl;
        }
    }
    catch (MovieException& e) {
        for (auto s : e.getErrors())
            cout << s;
    }
    catch (RepositoryException& e) {
        cout << e.what() << endl;
    }
    catch (DuplicateMovieException& e) {
        cout << e.what() << endl;
    }
    catch (InexistentMovieException& e) {
        cout << e.what() << endl;
    }

}

void Ui::removeMovieUi() {
    char title[100], genre[100];
    int year_of_release;
    cout<<"Please enter the title of the movie: > "<<endl;
    cin.ignore();
    cin.getline(title, 100);

    cout<<"Please enter the genre of the movie: > "<<endl;
    cin.getline(genre, 100);

    cout<<"Please enter the year of release of the movie: > "<<endl;
    cin>>year_of_release;

    while (year_of_release > 2025 || year_of_release < 1900) {
        cout<<"The year of release must be between 1900 and 2025. Please enter a valid year of release: > "<<endl;
        cin>>year_of_release;
    }
    try {
        cout<<"Removing the movie from the database..."<<endl;
        this->service.removeMovie(title, genre, year_of_release);
        cout<<"The movie was successfully removed from the database!"<<endl;
    }
    catch (MovieException& e) {
        for (auto s : e.getErrors())
            cout << s;
    }
    catch (RepositoryException& e) {
        cout << e.what() << endl;
    }
    catch (InexistentMovieException& e) {
        cout << e.what() << endl;
    }
}

void Ui::updateMovieLikesUi() {
    char title[100], genre[100];
    int year_of_release;
    cout<<"Please enter the title of the movie: > "<<endl;
    cin.ignore();
    cin.getline(title, 100);

    cout<<"Please enter the genre of the movie: > "<<endl;
    cin.getline(genre, 100);

    cout<<"Please enter the year of release of the movie: > "<<endl;
    cin>>year_of_release;
    while (year_of_release > 2025 || year_of_release < 1900) {
        cout<<"The year of release must be between 1900 and 2025. Please enter a valid year of release: > "<<endl;
        cin>>year_of_release;
    }

    try {
        cout<<"Enter the new number of likes for the movie: > "<<endl;
        int newLikes;
        cin>>newLikes;
        while (newLikes < 0) {
            cout<<"The number of likes must be a positive integer. Please enter a valid number of likes: > "<<endl;
            cin.ignore();
            cin>>newLikes;
        }
        cout<<"Updating the number of likes for the movie..."<<endl;
        this->service.updateMovieLikes(title, genre, year_of_release, newLikes);
        cout<<"The number of likes for the movie was successfully updated!"<<endl;
    }
    catch (MovieException& e) {
        for (auto s : e.getErrors())
            cout << s;
    }
    catch (RepositoryException& e) {
        cout << e.what() << endl;
    }
    catch (InexistentMovieException& e) {
        cout << e.what() << endl;
    }
}

void Ui::updateMovieTrailerUi() {
    char title[100], genre[100];
    int year_of_release;
    cout<<"Please enter the title of the movie: > "<<endl;
    cin.ignore();
    cin.getline(title, 100);

    cout<<"Please enter the genre of the movie: > "<<endl;
    cin.getline(genre, 100);

    cout<<"Please enter the year of release of the movie: > "<<endl;
    cin>>year_of_release;
    while (year_of_release > 2025 || year_of_release < 1900) {
        cout<<"The year of release must be between 1900 and 2025. Please enter a valid year of release: > "<<endl;
        cin>>year_of_release;
    }

    try {
        cout<<"Enter the new trailer link for the movie: > "<<endl;
        char newTrailer[250];
        cin>>newTrailer;
        cout<<"Updating the trailer link for the movie..."<<endl;
        this->service.updateMovieTrailer(title, genre, year_of_release, newTrailer);
        cout<<"The trailer link for the movie was successfully updated!"<<endl;
    }
    catch (MovieException& e) {
        for (auto s : e.getErrors())
            cout << s;
    }
    catch (RepositoryException& e) {
        cout << e.what() << endl;
    }
    catch (InexistentMovieException& e) {
        cout << e.what() << endl;
    }

}

void Ui::getMovieUi() {
    char title[100], genre[100];
    int year_of_release;
    cout<<"Please enter the title of the movie: > "<<endl;
    cin.ignore();
    cin.getline(title, 100);

    cout<<"Please enter the genre of the movie: > "<<endl;
    cin.getline(genre, 100);

    cout<<"Please enter the year of release of the movie: > "<<endl;
    cin>>year_of_release;
    while (year_of_release > 2025 || year_of_release < 1900) {
        cout<<"The year of release must be between 1900 and 2025. Please enter a valid year of release: > "<<endl;
        cin>>year_of_release;
    }
    if (!this->service.MovieExists(title, genre, year_of_release)) {
        cout<<"The movie does not exist in the database!"<<endl;
    }
    else {
        cout<<"Fetching the movie from the database..."<<endl;
        this->service.getMovies(title, genre, year_of_release);
        cout<<"The movie was successfully fetched from the database!"<<endl;
    }
}


void Ui::printAllMovies(int command) {
    if (command == 1) {
        std::vector<Movies> allMovies = this->service.getAllMovies();
        for (int i = 0; i < allMovies.size(); i++) {
            stringMovie(allMovies[i]);
        }
    } else {
        std::vector<Movies> watchlist = this->service.getWatchlist().getMovies();
        for (int i = 0; i < watchlist.size(); i++) {
            stringMovie(watchlist[i]);
        }
    }
}

void Ui::watchTrailer(const char *trailer) {
    std::string command = "start msedge \"" + std::string(trailer) + "\"";
    system(command.c_str());
}


//User mode

void Ui::parseThroughMovies() {
    char genretofilter[100];
    cout << "Please enter the genre you want to filter the movies by (leave empty to see all movies): > " << endl;
    cin.ignore();
    cin.getline(genretofilter, 100);

    std::vector<Movies> filteredMovies;
    if (strlen(genretofilter) == 0) {
        filteredMovies = this->service.getAllMovies();
    } else {
        filteredMovies = this->service.filterMoviesByGenre(genretofilter, "", 0);
    }

    for (int i = 0; i < filteredMovies.size(); i++) {
        stringMovieTrailer(filteredMovies[i]);
        nextMenu();
        int option;
        cin >> option;
        if (option == 1) {
            Movies movie = this->service.getMovies(filteredMovies[i].getTitle(), filteredMovies[i].getGenre(), filteredMovies[i].getYearOfRelease());
            if (this->service.getWatchlist().MovieExists(movie)){
                cout << "The movie is already in your watchlist!" << endl;
                continue;
            } else {
                Movies movie = this->service.getMovies(filteredMovies[i].getTitle(), filteredMovies[i].getGenre(), filteredMovies[i].getYearOfRelease());
                this->service.getWatchlist().add(movie);
                cout << "Movie added to your watchlist!" << endl;
                return;
            }
        } else if (option == 0) {
            continue;
        }
    }
}

void Ui::addMovieToWatchlist() {
    char title[100], genre[100];
    int year_of_release;

    cout << "Please enter the title of the movie: > " << endl;
    cin.ignore();
    cin.getline(title, 100);

    cout << "Please enter the genre of the movie: > " << endl;
    cin.getline(genre, 100);

    cout << "Please enter the year of release of the movie: > " << endl;
    cin >> year_of_release;
    while (year_of_release > 2025 || year_of_release < 1900) {
        cout << "The year of release must be between 1900 and 2025. Please enter a valid year of release: > " << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> year_of_release;
    }

    if (this->service.MovieExists(title, genre, year_of_release)) {
        Movies movieToAdd = this->service.getMovies(title, genre, year_of_release);
        if (this->service.getWatchlist().MovieExists(movieToAdd)) {
            cout << "The movie is already in your watchlist!" << endl;
        } else {
            this->service.getWatchlist().add(movieToAdd);
            cout << "Movie added to your watchlist!" << endl;
        }
    } else {
        cout << "The movie does not exist in the database!" << endl;
    }
}

void Ui::removeMovieFromWatchlist() {
    char title[100], genre[100];
    int year_of_release;
    cout << "Please enter the title of the movie: > " << endl;
    cin.ignore();
    cin.getline(title, 100);

    cout << "Please enter the genre of the movie: > " << endl;
    cin.getline(genre, 100);

    cout << "Please enter the year of release of the movie: > " << endl;
    cin >> year_of_release;
    while (year_of_release > 2025 || year_of_release < 1900) {
        cout << "The year of release must be between 1900 and 2025. Please enter a valid year of release: > " << endl;
        cin >> year_of_release;
    }
    Movies movieToRemove = this->service.getMovies(title, genre, year_of_release);
    if (this->service.getWatchlist().MovieExists(movieToRemove)) {
        cout << "Did you like the movie? (yes/no): > " << endl;
        string response;
        cin.ignore();
        getline(cin, response);
        if (response == "yes") {
            this->service.updateMovieLikes(title, genre, year_of_release, this->service.getMovies(title, genre, year_of_release).getNumberOfLikes() + 1);
            cout << "The movie has been liked!" << endl;
        }
        this->service.getWatchlist().deleteMovie(movieToRemove);
        cout << "Movie removed from your watchlist!" << endl;
    } else {
        cout << "The movie does not exist in your watchlist!" << endl;
    }
}

void Ui::printWatchlist() {
    std::vector<Movies> watchlist = this->service.getWatchlist().getMovies();
    if (watchlist.size() == 0) {
        cout << "Your watchlist is empty!" << endl;
    } else {
        cout << "Your watchlist:" << endl;
        for (int i = 0; i < watchlist.size(); i++) {
            stringMovie(watchlist[i]);
        }
    }
}

void Ui::inntializeMovieDatabase() {
    this->service.addMovie("Harry Potter and the Philosopher's Stone", "Fantasy", 2001, 2000, "https://www.youtube.com/watch?v=VyHV0BRtdxo");
    this->service.addMovie("Harry Potter and the Chamber of Secrets", "Fantasy", 2002, 3000, "https://www.youtube.com/watch?v=1bq0qff4iF8");
    this->service.addMovie("Harry Potter and the Prisoner of Azkaban", "Fantasy", 2004, 4000, "https://www.youtube.com/watch?v=lAxgztbYDbs");
    this->service.addMovie("Harry Potter and the Goblet of Fire", "Fantasy", 2005, 5000, "https://www.youtube.com/watch?v=3EGojp4Hh6I");
    this->service.addMovie("Harry Potter and the Order of the Phoenix", "Fantasy", 2007, 6000, "https://www.youtube.com/watch?v=y6ZW7KXaXYk");
    this->service.addMovie("Harry Potter and the Half-Blood Prince", "Fantasy", 2009, 7000, "https://www.youtube.com/watch?v=sg81X5k1w3M");
    this->service.addMovie("Harry Potter and the Deathly Hallows: Part 1", "Fantasy", 2010, 8000, "https://www.youtube.com/watch?v=MxqsmsA8y5k");
    this->service.addMovie("Harry Potter and the Deathly Hallows: Part 2", "Fantasy", 2011, 9000, "https://www.youtube.com/watch?v=I_kDb-pRCds");
    this->service.addMovie("The Fellowship of the Ring", "Fantasy", 2001, 1000, "https://www.youtube.com/watch?v=V75dMMIW2B4");
    this->service.addMovie("The Two Towers", "Fantasy", 2002, 2000, "https://www.youtube.com/watch?v=LbfMDwc4azU");
    this->service.addMovie("The Return of the King", "Fantasy", 2003, 3000, "https://www.youtube.com/watch?v=r5X-hFf6Bwo");
    this->service.addMovie("The Hunger Games", "Action", 2012, 4000, "https://www.youtube.com/watch?v=mfmrPu43DF8");
    this->service.addMovie("Catching Fire", "Action", 2013, 5000, "https://www.youtube.com/watch?v=EAzGXqJSDJ8");
    this->service.addMovie("Mockingjay - Part 1", "Action", 2014, 6000, "https://www.youtube.com/watch?v=C_Tsj_wTJkQ");
    this->service.addMovie("Mockingjay - Part 2", "Action", 2015, 7000, "https://www.youtube.com/watch?v=n-7K_OjsDCQ");
    this->service.addMovie("The Maze Runner", "Action", 2014, 8000, "https://www.youtube.com/watch?v=64-iSYVmMVY");
    this->service.addMovie("The Notebook", "Romance", 2004, 9000, "https://www.youtube.com/watch?v=FC6biTjEyZw");
    this->service.addMovie("The Fault in Our Stars", "Romance", 2014, 1000, "https://www.youtube.com/watch?v=9ItBvH5J6ss");
    this->service.addMovie("Pride and Prejudice", "Romance", 2005, 2000, "https://www.youtube.com/watch?v=1dYv5u6v55Y");
    this->service.addMovie("The Great Gatsby", "Romance", 2013, 3000, "https://www.youtube.com/watch?v=rARN6agiW7o");
    this->service.addMovie("Dune", "Sci-Fi", 2021, 4000, "https://www.youtube.com/watch?v=n9xhJrPXop4");
    this->service.addMovie("Interstellar", "Sci-Fi", 2014, 5000, "https://www.youtube.com/watch?v=zSWdZVtXT7E");
    this->service.addMovie("Inception", "Sci-Fi", 2010, 6000, "https://www.youtube.com/watch?v=YoHD9XEInc0");
    this->service.addMovie("PostDecembrist", "Historical", 2024, 7000, "https://youtu.be/OQ2SBN3nk0s?si=geCoD8l-z-f8wGIl");
}
void Ui::innitializeWatchlist() {
    Movies movie1("Harry Potter and the Philosopher's Stone", "Fantasy", 2001, 2000, "https://www.youtube.com/watch?v=VyHV0BRtdxo");
    Movies movie2("The Fellowship of the Ring", "Fantasy", 2001, 1000, "https://www.youtube.com/watch?v=V75dMMIW2B4");
    Movies movie3("The Hunger Games", "Action", 2012, 4000, "https://www.youtube.com/watch?v=mfmrPu43DF8");
    Movies movie4("The Notebook", "Romance", 2004, 9000, "https://www.youtube.com/watch?v=FC6biTjEyZw");
    Movies movie5("Dune", "Sci-Fi", 2021, 4000, "https://www.youtube.com/watch?v=n9xhJrPXop4");

    this->service.getWatchlist().add(movie1);
    this->service.getWatchlist().add(movie2);
    this->service.getWatchlist().add(movie3);
    this->service.getWatchlist().add(movie4);
    this->service.getWatchlist().add(movie5);
}
bool ends_with(const std::string& str, const std::string& suffix) {
    if (suffix.size() > str.size()) return false;
    return std::equal(suffix.rbegin(), suffix.rend(), str.rbegin());
}

void Ui::setWatchlistFilename(const std::string& filename) {
    this->service.setWatchlistFilename(filename);
}

void Ui::saveWatchlistToFile() {
    try {
        if (this->service.getWatchlist().getMovies().empty()) {
            cout << "Watchlist is empty! Nothing to save." << endl;
            return;
        }

        std::string watchlistFileName = this->service.getWatchlistFilename();
        if (watchlistFileName.empty()) {
            throw std::runtime_error("Watchlist filename is not set!");
        }

        this->service.saveWatchlist(watchlistFileName);

        if (ends_with(watchlistFileName, ".csv")) {
            CVSRepository repo(watchlistFileName.c_str());
            repo.displayWatchlist();
        } else if (ends_with(watchlistFileName, ".html")) {
            HTMLRepository repo(watchlistFileName.c_str());
            repo.displayWatchlist();
        }

        cout << "Watchlist saved successfully to: " << watchlistFileName << endl;

        // Exit the function after saving
        return;
    } catch (const FileException& e) {
        cout << "File error: " << e.what() << endl;
    } catch (const std::exception& e) {
        cout << "Error: " << e.what() << endl;
    }
}



void Ui::source() {
    while (true) {
        printMenu();
        int option;
        cin>>option;
        if (option == 0) {
            cout<<"Thank you for using our movie database! Hope to see you soon!"<<endl;
            break;
        }
        switch (option) {
            case 1:{
                char password[100];
                cout<<"Please enter the password to access the administrator mode: > "<<endl;
                cin.ignore();
                cin.getline(password, 100);
                if (strcmp(password, "admin") != 0) {
                    cout<<"Invalid password! Please try again."<<endl;
                    break;
                }

                while (true) {
                    printAdministratorMenu();
                    int choice;
                    cin>>choice;
                    if (choice == 1) {
                        this->printAllMovies(1);
                    }
                    else if (choice == 2) {
                        this->addMovieUi();
                    }
                    else if (choice == 3) {
                        this->removeMovieUi();
                    }
                    else if (choice == 4) {
                        this->updateMovieLikesUi();
                    }
                    else if (choice == 5) {
                        this->updateMovieTrailerUi();
                    }
                    else if(choice == 0) {
                        cout<<"Hope to see you soon for our next database update! Heard there's many more movies out there to discover :D."<<endl;
                        break;
                    }
                }

                break;

            }
            case 2:{
                while (true) {
                    printUserMenu();
                    int choice;
                    cin>>choice;
                    if (choice == 1) {
                        this->parseThroughMovies();
                    }
                    else if (choice == 2) {
                        this->addMovieToWatchlist();
                    }
                    else if (choice == 3) {
                        this->removeMovieFromWatchlist();
                    }
                    else if (choice == 4) {
                        this->printWatchlist();

                    }
                    else if (choice == 5) {
                        this->saveWatchlistToFile();
                    }
                    else if (choice == 0) {
                        cout<<"Thank you so much for making a most magical watchlist with us! Hope to see you soon!"<<endl;
                        break;
                    }
                    if (choice < 0 || choice > 5) {
                        cout<<"Invalid command! Please try again!"<<endl;
                    }
                }

                break;

            }
            default: {
                cout<<"Invalid command, do try again."<<endl;
                break;
            }

        }
    }
}


