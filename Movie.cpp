#ifndef MOVIEDATABASE_HPP
#define MOVIEDATABASE_HPP

#include <string>
#include <vector>

struct Movie {
    int id;
    std::string title;
    std::string director;
    int year;
    std::string genre;
};

class MovieDatabase {
private:
    std::vector<Movie> movies;
    int nextId;

public:
    MovieDatabase();

    void addMovie(const std::string& title, const std::string& director, int year, const std::string& genre);
    bool updateMovie(int id, const std::string& title, const std::string& director, int year, const std::string& genre);
    bool deleteMovie(int id);
    Movie* searchById(int id);
    std::vector<Movie> searchByTitle(const std::string& title);
    void displayAll() const;
};

#endif
#include "MovieDatabase.hpp"
#include <iostream>
#include <iomanip>
#include <algorithm>

MovieDatabase::MovieDatabase() : nextId(1) {}

void MovieDatabase::addMovie(const std::string& title, const std::string& director, int year, const std::string& genre) {
    movies.push_back({nextId++, title, director, year, genre});
}

bool MovieDatabase::updateMovie(int id, const std::string& title, const std::string& director, int year, const std::string& genre) {
    for (auto& movie : movies) {
        if (movie.id == id) {
            movie.title = title;
            movie.director = director;
            movie.year = year;
            movie.genre = genre;
            return true;
        }
    }
    return false;
}

bool MovieDatabase::deleteMovie(int id) {
    auto it = std::remove_if(movies.begin(), movies.end(), [id](const Movie& m) { return m.id == id; });
    if (it != movies.end()) {
        movies.erase(it, movies.end());
        return true;
    }
    return false;
}

Movie* MovieDatabase::searchById(int id) {
    for (auto& movie : movies) {
        if (movie.id == id) return &movie;
    }
    return nullptr;
}

std::vector<Movie> MovieDatabase::searchByTitle(const std::string& title) {
    std::vector<Movie> results;
    for (const auto& movie : movies) {
        if (movie.title.find(title) != std::string::npos) {
            results.push_back(movie);
        }
    }
    return results;
}

void MovieDatabase::displayAll() const {
    std::cout << std::left << std::setw(5) << "ID"
              << std::setw(25) << "Title"
              << std::setw(20) << "Director"
              << std::setw(6) << "Year"
              << std::setw(15) << "Genre" << "\n";

    for (const auto& movie : movies) {
        std::cout << std::left << std::setw(5) << movie.id
                  << std::setw(25) << movie.title
                  << std::setw(20) << movie.director
                  << std::setw(6) << movie.year
                  << std::setw(15) << movie.genre << "\n";
    }
}
#include "MovieDatabase.hpp"
#include <iostream>

int main() {
    MovieDatabase db;
    int choice;

    while (true) {
        std::cout << "\nMovie Database System\n";
        std::cout << "1. Add Movie\n2. Update Movie\n3. Delete Movie\n4. Search by ID\n5. Search by Title\n6. Display All\n7. Exit\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;

        if (choice == 1) {
            std::string title, director, genre;
            int year;
            std::cin.ignore();
            std::cout << "Enter title: "; std::getline(std::cin, title);
            std::cout << "Enter director: "; std::getline(std::cin, director);
            std::cout << "Enter year: "; std::cin >> year;
            std::cin.ignore();
            std::cout << "Enter genre: "; std::getline(std::cin, genre);
            db.addMovie(title, director, year, genre);
        } else if (choice == 2) {
            int id, year;
            std::string title, director, genre;
            std::cout << "Enter movie ID to update: "; std::cin >> id;
            std::cin.ignore();
            std::cout << "Enter new title: "; std::getline(std::cin, title);
            std::cout << "Enter new director: "; std::getline(std::cin, director);
            std::cout << "Enter new year: "; std::cin >> year;
            std::cin.ignore();
            std::cout << "Enter new genre: "; std::getline(std::cin, genre);
            if (!db.updateMovie(id, title, director, year, genre))
                std::cout << "Movie not found.\n";
        } else if (choice == 3) {
            int id;
            std::cout << "Enter movie ID to delete: "; std::cin >> id;
            if (!db.deleteMovie(id))
                std::cout << "Movie not found.\n";
        } else if (choice == 4) {
            int id;
            std::cout << "Enter movie ID to search: "; std::cin >> id;
            Movie* movie = db.searchById(id);
            if (movie) {
                std::cout << "Found: " << movie->title << " (" << movie->year << "), Directed by " << movie->director << ", Genre: " << movie->genre << "\n";
            } else {
                std::cout << "Movie not found.\n";
            }
        } else if (choice == 5) {
            std::string title;
            std::cin.ignore();
            std::cout << "Enter title keyword: "; std::getline(std::cin, title);
            auto results = db.searchByTitle(title);
            if (results.empty()) {
                std::cout << "No movies found.\n";
            } else {
                for (const auto& movie : results) {
                    std::cout << movie.id << ": " << movie.title << " (" << movie.year << "), " << movie.director << ", " << movie.genre << "\n";
                }
            }
        } else if (choice == 6) {
            db.displayAll();
        } else if (choice == 7) {
            break;
        } else {
            std::cout << "Invalid choice.\n";
        }
    }

    return 0;
}

