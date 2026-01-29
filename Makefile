CXX = clang++
CXXFLAGS = -std=c++17 -Wall -Wextra
SFML_INCLUDE = -I/opt/homebrew/opt/sfml/include
SFML_LIB = -L/opt/homebrew/opt/sfml/lib -lsfml-graphics -lsfml-window -lsfml-system

SRC = main.cpp caracter.cpp test.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = jeu

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(TARGET) $(SFML_LIB)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(SFML_INCLUDE) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(TARGET)

re: fclean all

.PHONY: all clean fclean re
