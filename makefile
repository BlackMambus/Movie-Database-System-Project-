 CXX = g++
CXXFLAGS = -std=c++17 -Iinclude

SRC = src/MovieDatabase.cpp src/main.cpp
OUT = movie_db

all:
    $(CXX) $(CXXFLAGS) $(SRC) -o $(OUT)

clean:
    rm -f $(OUT)
