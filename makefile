CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

# On utilise uniquement pkg-config pour récupérer les flags SFML
SFML_CFLAGS = $(shell pkg-config --cflags sfml-graphics sfml-window sfml-system)
SFML_LIBS   = $(shell pkg-config --libs sfml-graphics sfml-window sfml-system)

CXXFLAGS += $(SFML_CFLAGS)

GTEST_FLAGS = -lgtest -lpthread

SRCDIR = src
OBJDIR = obj
TESTDIR = tests

SRC = main.cpp \
      $(SRCDIR)/Boid.cpp \
      $(SRCDIR)/Rule.cpp \
      $(SRCDIR)/Flock.cpp \
      $(SRCDIR)/Settings.cpp \
	  $(SRCDIR)/Simulation.cpp \
	  $(SRCDIR)/SaveSystem.cpp

OBJ = $(SRC:%.cpp=$(OBJDIR)/%.o)

TARGET = boids

TEST_SRC = $(wildcard $(TESTDIR)/*.cpp)
TEST_OBJ = $(TEST_SRC:%.cpp=$(OBJDIR)/%.o)

SRC_NO_MAIN = $(SRCDIR)/Boid.cpp
OBJ_NO_MAIN = $(SRC_NO_MAIN:%.cpp=$(OBJDIR)/%.o)

all: $(TARGET)

# Compilation du programme principal
$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET) $(SFML_LIBS)

# Compilation des tests unitaires
unit_tests: $(TEST_OBJ) $(OBJ_NO_MAIN)
	$(CXX) $(TEST_OBJ) $(OBJ_NO_MAIN) -o unit_tests $(GTEST_FLAGS)

# Règles de compilation des objets
$(OBJDIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Nettoyage
clean:
	rm -rf $(OBJDIR) *.o

mrproper: clean
	rm -f $(TARGET) unit_tests

re: mrproper all

.PHONY: all clean mrproper re unit_tests
