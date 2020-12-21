#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <random>

#include "ingredient.hpp"
#include "step.hpp"

using namespace std;

static string STANDARD_RECIPE_STRINGS_FILE = "recipe_strings.csv";
static string STANDARD_RECIPE_TITLES_FILE = "recipe_titles.csv";
static string STANDARD_TIME_CONFIG_FILE = "time_config.csv";
static char COMMENT_CHARACTER = '#';

typedef vector<Ingredient> Ingredients;
typedef vector<Step> Steps;
typedef map<string, tuple<int, int>> Times;
typedef vector<string> Titles;

class Recipe{

    Ingredients ingredients;
    Steps steps;
    Steps recipe;
    Times times;
    Titles titles;
    string title;

    bool dependency_satisfied(Step &);

    Recipe();

public:
//ctors
    //copy
    Recipe(Recipe &);
   
    //ingredients
    Recipe(Ingredients);

    //ingredients, recipe strings file path
    Recipe(Ingredients, string);

    //getters
    Ingredients & get_ingredients() {return ingredients;}
    Steps & get_recipe_steps() {return steps;}
    Titles & get_all_recipe_titles(){return titles;}
    string & get_recipe_title(){return title;}
    string to_string();

    //setters
    void set_ingredients(Ingredients &);
    void set_recipe_steps(Steps & steps_){steps = steps_;}
    void set_recipe_title(string & title_){title = title_;}

//public methods
    void load_time_config(string);
    void load_recipe_steps(string);
    void load_recipe_titles(string);

    bool recipe_contains_step(uint32_t);
    void add_recipe_step(Step &);
    void add_recipe_title(string &);
    void build_recipe();
};
