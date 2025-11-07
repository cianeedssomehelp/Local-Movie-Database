#pragma once

#ifndef TESTS_H
#define TESTS_H

void testServiceAddMovie();
void testServiceRemoveMovie();
void testServiceUpdateMovieLikes();
void testServiceUpdateMovieTrailer();
void testServiceMovieExists();
void testRepositoryAddMovie();
void testRepositoryRemoveMovie();
void testRepositoryUpdateMovieLikes();
void testRepositoryUpdateMovieTrailer();
void testMoviesSetNumberOfLikes();
void testMoviesSetTrailer();
void testMovieDynamicArrayAppend();
void testMovieDynamicArrayRemove();
void testMovieDynamicArrayOperator();
void testMovieDynamicArrayGetLength();
void testMovieDynamicArrayGetCapacity();
void testServiceGetMovies();
void testServiceGetAllMovies();
void testServiceFilterMoviesByGenre();
void testRepositoryGetSize();
void testRepositorySetName();
void testRepositoryGetName();
void source();

#endif //TESTS_H
