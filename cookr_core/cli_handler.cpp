#include "cookr/cookr.hpp"
#include <iostream>

void print_recipe_title(Recipe &);
void print_ingredients(Ingredients &);

using namespace std;

int main(int argc, char * argv[]){
    bool complex_steps = false;
    if(argc > 2){
        cout << "cookr [-x]" << endl;
        cout << "-x\tturn on complex steps" << endl;
        exit(0);
    }

    if(argc == 2){
        string in_flag (argv[1]), complex_steps_flag ("-x");
        if(in_flag == complex_steps_flag){
            complex_steps = true;
        }
    }

    cout << "Cookr (" + COOKR_VERSION + ")" << endl;

    Ingredients ingredients;

    cout << "Please enter a list of ingredients..." << endl;
    cout << "Enter an empty ingredient to finish" << endl;
    
    string line;
    string name;
    uint32_t amount;
    WordType wordtype;

    while(true){
        line.clear();
        cout << "Ingredient: ";
        getline(cin, line);
        if(line.empty()) break;
        name = line;

        if(complex_steps){
            line.clear();
            cout << "How much/many [1]: ";
            getline(cin, line);
            try{
                amount = stoi(line);
            }catch(exception & e){
                cerr << "Not a good numerical value, I'll just use 1!" << endl;
                //cerr << e.what();
                amount = 1;
            }
        }else{
            amount = 1;
        }

        //cout << "Measurement [cup]: ";
        if(complex_steps){   
            line.clear();
            cout << "Countable? [Y/n]: ";
            getline(cin, line);
            
            //if(line == "y" || line == "yes") {wordtype = WordType::CountableNoun;}
            //else if(line == "n" || line == "no") {wordtype = WordType::UncountableNoun;}
            if(line == "n" || line == "no") {wordtype = WordType::UncountableNoun;}
            else{wordtype = WordType::CountableNoun;}
        }else{
            wordtype = WordType::CountableNoun;
        }

        Ingredient ingredient (name, amount, wordtype);
        ingredients.push_back(ingredient);
    }

    if(ingredients.size() > 0){
        Recipe recipe (ingredients);

        recipe.build_recipe();

        print_recipe_title(recipe);

        print_ingredients(ingredients);

        cout << recipe.to_string() << endl;
    }

    cout << "Cya!" << endl;
}

void print_recipe_title(Recipe & recipe){
    int flourish_length = recipe.get_recipe_title().size() + 10;

    cout << endl;
    for(int i = flourish_length; --i;){cout << "~";}
    cout << endl << recipe.get_recipe_title() << endl;
    for(int i = flourish_length; --i;){cout << "~";}
    cout << endl << endl;
}

void print_ingredients(Ingredients & ingredients){
    cout << "-Ingredients";
    for(int i = 38; --i;){cout << "-";}
    cout << endl;

    for(auto ingredient : ingredients){
        cout << ingredient.get_name() << ", " << ingredient.get_amount() << endl;
    }

    for(int i = 50; --i;){cout << "-";}
    cout << endl;
}