#include <cassert>
#include "../domain/domain.h"
#include "../repository/Repository.h"
#include "../service/Service.h"
#include <iostream>
// Domain tests
void testMoviesConstructor() {
    Movies movie("Inception", "Sci-Fi", 2010, 1000000, "http://trailer.link");
    assert(movie.getTitle() == "Inception");
    assert(movie.getGenre() == "Sci-Fi");
    assert(movie.getYearOfRelease() == 2010);
    assert(movie.getNumberOfLikes() == 1000000);
    assert(movie.getTrailer() == "http://trailer.link");
}

void testMoviesSetters() {
    Movies movie("Inception", "Sci-Fi", 2010, 1000000, "http://trailer.link");
    movie.setNumberOfLikes(2000000);
    movie.setTrailer("http://newtrailer.link");
    assert(movie.getNumberOfLikes() == 2000000);
    assert(movie.getTrailer() == "http://newtrailer.link");
}

// Repository tests
void testRepositoryAddMovie() {
    Repository repo;
    repo.addMovie("Inception", "Sci-Fi", 2010, 1000000, "http://trailer.link");
    assert(repo.getSize() == 1);
}

void testRepositoryRemoveMovie() {
    Repository repo;
    repo.addMovie("Inception", "Sci-Fi", 2010, 1000000, "http://trailer.link");
    repo.removeMovie("Inception", "Sci-Fi", 2010);
    assert(repo.getSize() == 0);
}

void testRepositoryUpdateMovieLikes() {
    Repository repo;
    repo.addMovie("Inception", "Sci-Fi", 2010, 1000000, "http://trailer.link");
    repo.updateMovieLikes("Inception", "Sci-Fi", 2010, 2000000);
    assert(repo.getMovie("Inception", "Sci-Fi", 2010).getNumberOfLikes() == 2000000);
}

void testRepositoryUpdateMovieTrailer() {
    Repository repo;
    repo.addMovie("Inception", "Sci-Fi", 2010, 1000000, "http://trailer.link");
    repo.updateMovieTrailer("Inception", "Sci-Fi", 2010, "http://newtrailer.link");
    assert(repo.getMovie("Inception", "Sci-Fi", 2010).getTrailer() == "http://newtrailer.link");
}

void testRepositoryGetMovie() {
    Repository repo;
    repo.addMovie("Inception", "Sci-Fi", 2010, 1000000, "http://trailer.link");
    Movies movie = repo.getMovie("Inception", "Sci-Fi", 2010);
    assert(movie.getTitle() == "Inception");
}

void testRepositoryGetAllMovies() {
    Repository repo;
    repo.addMovie("Inception", "Sci-Fi", 2010, 1000000, "http://trailer.link");
    std::vector<Movies> movies = repo.getAllMovies();
    assert(movies.size() == 1);
}

void testRepositoryGetSize() {
    Repository repo;
    repo.addMovie("Inception", "Sci-Fi", 2010, 1000000, "http://trailer.link");
    assert(repo.getSize() == 1);
}


// Service tests
void testServiceAddMovie() {
    Repository repo;
    WatchList watchlist;
    Service service(repo, watchlist);

    assert(service.addMovie("Inception", "Sci-Fi", 2010, 1000000, "http://trailer.link") == true);
    assert(service.addMovie("Inception", "Sci-Fi", 2010, 1000000, "http://trailer.link") == false);
}

void testServiceRemoveMovie() {
    Repository repo;
    WatchList watchlist;
    Service service(repo, watchlist);

    service.addMovie("Inception", "Sci-Fi", 2010, 1000000, "http://trailer.link");
    service.removeMovie("Inception", "Sci-Fi", 2010);
    assert(service.MovieExists("Inception", "Sci-Fi", 2010) == 0);
}

void testServiceUpdateMovieLikes() {
    Repository repo;
    WatchList watchlist;
    Service service(repo, watchlist);

    service.addMovie("Inception", "Sci-Fi", 2010, 1000000, "http://trailer.link");
    service.updateMovieLikes("Inception", "Sci-Fi", 2010, 2000000);
    assert(service.getMovies("Inception", "Sci-Fi", 2010).getNumberOfLikes() == 2000000);
}

void testServiceUpdateMovieTrailer() {
    Repository repo;
    WatchList watchlist;
    Service service(repo, watchlist);

    service.addMovie("Inception", "Sci-Fi", 2010, 1000000, "http://trailer.link");
    service.updateMovieTrailer("Inception", "Sci-Fi", 2010, "http://newtrailer.link");
    assert(service.getMovies("Inception", "Sci-Fi", 2010).getTrailer() == "http://newtrailer.link");
}

void testServiceMovieExists() {
    Repository repo;
    WatchList watchlist;
    Service service(repo, watchlist);

    service.addMovie("Inception", "Sci-Fi", 2010, 1000000, "http://trailer.link");
    assert(service.MovieExists("Inception", "Sci-Fi", 2010) == 1);
    assert(service.MovieExists("Nonexistent", "Genre", 2000) == 0);
}

void testServiceAddDuplicateMovie() {
    Repository repo;
    WatchList watchlist;
    Service service(repo, watchlist);
    service.addMovie("Inception", "Sci-Fi", 2010, 1000000, "http://trailer.link");
    bool result = service.addMovie("Inception", "Sci-Fi", 2010, 1000000, "http://trailer.link");
    assert(result == false);
}

void testServiceGetMovies() {
    Repository repo;
    WatchList watchlist;
    Service service(repo, watchlist);
    service.addMovie("Inception", "Sci-Fi", 2010, 1000000, "http://trailer.link");
    Movies movie = service.getMovies("Inception", "Sci-Fi", 2010);
    assert(movie.getTitle() == "Inception");
    assert(movie.getGenre() == "Sci-Fi");
    assert(movie.getYearOfRelease() == 2010);
    assert(movie.getNumberOfLikes() == 1000000);
    assert(movie.getTrailer() == "http://trailer.link");
}

void testServiceGetAllMovies() {
    Repository repo;
    WatchList watchlist;
    Service service(repo, watchlist);
    service.addMovie("Inception", "Sci-Fi", 2010, 1000000, "http://trailer.link");
    std::vector<Movies> movies = service.getAllMovies();
    assert(movies.size() == 1);
    assert(movies[0].getTitle() == "Inception");
}

void testServiceFilterMoviesByGenre() {
    Repository repo;
    WatchList watchlist;
    Service service(repo, watchlist);
    service.addMovie("Inception", "Sci-Fi", 2010, 1000000, "http://trailer.link");
    service.addMovie("Interstellar", "Sci-Fi", 2014, 2000000, "http://trailer.link");
    service.addMovie("The Dark Knight", "Action", 2008, 3000000, "http://trailer.link");

    std::vector<Movies> filteredMovies = service.filterMoviesByGenre("Sci-Fi", "Inception", 2010);
    assert(filteredMovies.size() == 1);
    assert(filteredMovies[0].getTitle() == "Interstellar");
}


void source() {
    // Domain tests
    testMoviesConstructor();
    testMoviesSetters();

    // Repository tests
    testRepositoryAddMovie();
    testRepositoryRemoveMovie();
    testRepositoryUpdateMovieLikes();
    testRepositoryUpdateMovieTrailer();
    testRepositoryGetMovie();
    testRepositoryGetAllMovies();
    testRepositoryGetSize();

    // Service tests
    testServiceAddMovie();
    testServiceRemoveMovie();
    testServiceUpdateMovieLikes();
    testServiceUpdateMovieTrailer();
    testServiceMovieExists();
    testServiceAddDuplicateMovie();
    testServiceGetMovies();
    testServiceGetAllMovies();
    testServiceFilterMoviesByGenre();

    std::cout << "All tests passed!" << std::endl;
}