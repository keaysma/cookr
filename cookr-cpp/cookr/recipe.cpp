#include <algorithm>

#include "recipe.hpp"

void find_and_replace(string &, const string, const string);

Recipe::Recipe(Recipe & recipe){
    srand((unsigned) time(0));
    /*set_ingredients(recipe.get_ingredients());

    auto _recipe_steps = recipe.get_recipe_steps();
    set_recipe_steps(_recipe_steps);*/
}

Recipe::Recipe(Ingredients ingredients_){
    srand((unsigned) time(0));
    set_ingredients(ingredients_);
    load_time_config(STANDARD_TIME_CONFIG_FILE);
    load_recipe_titles(STANDARD_RECIPE_TITLES_FILE);
    load_recipe_steps(STANDARD_RECIPE_STRINGS_FILE);
}

Recipe::Recipe(Ingredients ingredients_, string recipe_steps_file_path){
    srand((unsigned) time(0));
    set_ingredients(ingredients_);
    load_time_config(STANDARD_TIME_CONFIG_FILE);
    load_recipe_steps(recipe_steps_file_path);
}

void Recipe::add_recipe_title(string & title){
    titles.push_back(title);
}

void Recipe::set_ingredients(Ingredients & ingredients_){

   ingredients = ingredients_;
}

void Recipe::load_time_config(string filepath){
    //printf("Loading Recipe strings\n");
    ifstream file (filepath, ifstream::in);

    if(file.is_open()){
        //printf("File is open\n");
        string line;
        getline(file, line);
        int line_no = 2;

        while(file.good()){
            try{
                string token, base_text, max_text;
                getline(file, line);
                if(line[0] == COMMENT_CHARACTER || line.length() == 0){
                    continue;
                }
                
                stringstream sline (line);
                getline(sline, token, ',');
                getline(sline, base_text, ',');
                getline(sline, max_text, ',');

                int base = stoi(base_text);
                int max = stoi(max_text);
                
                times[token] = tuple<int, int>{base, max};

                //printf("%s requires %d\n", step.get_step_text().c_str(), step.get_dependency());
                ++line_no;
            }catch(exception & e){
                char * err;
                sprintf(err, "Bad line in %s (line %d): %s", filepath.c_str(), line_no, e.what());
                fprintf(stderr, "%s", err);
                throw string(err);
            }
        }
    }
    
    file.close();
}

void Recipe::load_recipe_steps(string filepath){
    //printf("Loading Recipe strings\n");
    ifstream file (filepath, ifstream::in);

    if(file.is_open()){
        //printf("File is open\n");
        string line;
        getline(file, line);
        int line_no = 2;

        while(file.good()){
            try{
                string id_text, step_text, output_text, dependency_text;
                getline(file, line);
                if(line[0] == COMMENT_CHARACTER || line.length() == 0){
                    continue;
                }
                
                stringstream sline (line);
                getline(sline, id_text, ',');
                getline(sline, step_text, ',');
                getline(sline, output_text, ',');
                getline(sline, dependency_text, ',');

                uint32_t id = stoi(id_text);
                int32_t dependency = stoi(dependency_text);
                
                Step step (id, step_text, output_text, dependency);
                add_recipe_step(step);

                //printf("%s requires %d\n", step.get_step_text().c_str(), step.get_dependency());
                ++line_no;
            }catch(exception & e){
                char * err;
                sprintf(err, "Bad line in %s (line %d): %s", filepath.c_str(), line_no, e.what());
                fprintf(stderr, "%s", err);
                throw string(err);
            }
        }
    }
    
    file.close();
}

void Recipe::load_recipe_titles(string filepath){
    //printf("Loading Recipe strings\n");
    ifstream file (filepath, ifstream::in);

    if(file.is_open()){
        //printf("File is open\n");
        string line;
        getline(file, line);
        int line_no = 2;

        while(file.good()){
            try{
                getline(file, line);
                if(line[0] == COMMENT_CHARACTER || line.length() == 0){
                    continue;
                }

                add_recipe_title(line);

                //printf("%s\n", line.c_str());
                ++line_no;
            }catch(exception & e){
                char * err;
                sprintf(err, "Bad line in %s (line %d): %s", filepath.c_str(), line_no, e.what());
                fprintf(stderr, "%s", err);
                throw string(err);
            }
        }
    }
    
    file.close();
}

void Recipe::add_recipe_step(Step & step){
    step.find_and_replace_all("$$", ",");
    steps.push_back(step);
}

bool Recipe::recipe_contains_step(uint32_t step_id){
    for(auto itr : recipe){
        if(itr.get_id() == step_id){
            return true;
        }
    }
    return false;
}

bool Recipe::dependency_satisfied(Step & step){
    int32_t dep = step.get_dependency();
    bool satisfied =    (dep >=  0 && recipe_contains_step(dep)) ||
                        (dep == -1) ||
                        (dep == -2 && steps.size() > 0) ||
                        (dep == -3 && ingredients.size() > 1) ||
                        (dep == -4 && !recipe_contains_step(step.get_id())) ||
                        (dep == -5 && steps.size() > 0 && !recipe_contains_step(step.get_id()));
    return satisfied;
}

void Recipe::build_recipe(){
    recipe.clear();

    int attempts = 5;

    while(ingredients.size() && attempts){
        if(ingredients.size() < 3){
            int title_idx = rand() % titles.size();
            string _title = titles[title_idx];
            find_and_replace(_title, "@i", ingredients.back().get_name());
            title = _title;
            //printf("Recipe title: %s\n", _title.c_str());
        }

        int r = rand();
        int step_idx = r % steps.size();
        Step recipe_step = steps[step_idx];
        
        //Verify that dependency requirement is satisfied
        if(!dependency_satisfied(recipe_step)){
            --attempts;
            continue;
        }

        //Verify that enough ingredients exist to use this step
        int ingredients_needed = recipe_step.count("@i");
        if(ingredients_needed > ingredients.size()){
            --attempts;
            continue;
        }

        //Disallow an ingredient from being consumed by the same step repeatedly
        vector<int> used_in_steps = ingredients.back().get_used_steps();
        int times_used_in_this_step = count(used_in_steps.begin(), used_in_steps.end(), recipe_step.get_id());
        //printf("%s used in this step %d time(s)\n", ingredients.back().get_name().c_str(), times_used_in_this_step);
        if(times_used_in_this_step > 0){
            --attempts;
            continue;
        }

        //Create the output ingredient and put it at the bottom of the stack
        if(recipe_step.get_output_text() != "none"){
            Ingredient new_ingredient (recipe_step.get_output_text(), 1, WordType::CountableNoun);
            new_ingredient.find_and_replace("@i", ingredients.back().get_name());

            auto old_ingredient_used_steps = ingredients.back().get_used_steps();
            new_ingredient.set_used_steps(old_ingredient_used_steps);
            new_ingredient.add_used_steps(recipe_step.get_id());

            ingredients.insert(ingredients.begin(), new_ingredient);
        }

        //fill in ingredients
        for(;ingredients_needed;--ingredients_needed){
            Ingredient ingredient = ingredients.back();
            recipe_step.find_and_replace("@i", ingredient.get_name());
            ingredients.pop_back();
        }

        //fill in time intervals
        for(auto itr = times.begin(); itr != times.end(); ++itr){
            int type_count = recipe_step.count(itr->first);
            for(;type_count--;){
                int base = get<0>(itr->second);
                int max = get<1>(itr->second) - base;
                int num = (rand() % max) + base;

                string token = "@" + itr->first;
                string num_str = std::to_string(num);
                
                recipe_step.find_and_replace(token, num_str);
            }
        }
        //printf("<-%s->\n", recipe_step.get_step_text().c_str());
        recipe.push_back(recipe_step);
    }
}

string Recipe::to_string(){
    stringstream recipe_stream;
    for(auto step : recipe){
        recipe_stream << step.get_step_text() << endl;
    }
    return recipe_stream.str();
}

void find_and_replace(string & str, const string find_str, const string replace_str){
    size_t loc;
    if((loc = str.find(find_str)) != string::npos)
        str.replace(loc, find_str.length(), replace_str);
}