CXX=g++ -std=c++17
CXXFLAGS=
DEPS=cookr/recipe.cpp cookr/ingredient.cpp cookr/step.cpp
INPUT=cli_handler.cpp
OUTPUT=output/cookr


build:
	$(CXX) $(CXXFLAGS) -o $(OUTPUT) $(INPUT) $(DEPS)

.PHONY: clean

clean:
	rm build/*
