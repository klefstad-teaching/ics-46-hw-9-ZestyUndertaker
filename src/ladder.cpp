#include "ladder.h"
#include "algorithm"

void error(string word1, string word2, string msg){
    cerr << "Error: " << msg << endl;
    cerr << "Caused by words " << word1 << " and " << word2 << endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d){
    int m = str1.length();
    int n = str2.length();

    vector<vector<int>> ed_table(m+1, vector<int>(n+1, 0));

    for (int i = 0; i <= m; ++i) {
        ed_table[i][0] = i;
    }
    for (int j = 0; j <= n; ++j) {
        ed_table[0][j] = j;
    }

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            int substitution_cost = (str1[i-1] == str2[j-1]) ? 0 : 1;

            ed_table[i][j] = min({ed_table[i-1][j] + 1,
                           ed_table[i][j-1] + 1,
                           ed_table[i-1][j-1] + substitution_cost});
        }
    }

    return ed_table[m][n] <= d;
}

bool is_adjacent(const string& word1, const string& word2){
    // if words differ by more than one character it is safe to assume their 
    // edit distance would be greater than 1
    if (abs(int(word1.length()) - int(word2.length())) > 1) {
        return false;
    }
    if (word1 == word2) {
        return true;
    }

    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    if (begin_word == end_word) {
        error(begin_word, end_word, "Both words are the same.");
        return {};
    }

    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});
    set<string> visited;
    visited.insert(begin_word);
    
    while (!ladder_queue.empty()) {
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = ladder.back();

        for (string word : word_list) {
            if (is_adjacent(last_word, word)) {
                if (visited.find(word) == visited.end()) {
                    visited.insert(word);
                    vector<string> new_ladder = ladder;
                    new_ladder.push_back(word);

                    if (word == end_word) {
                        return new_ladder;
                    }
                    ladder_queue.push(new_ladder);
                }
            }
        }
    }
    return {};
}

void load_words(set<string> & word_list, const string& file_name){
    ifstream in(file_name);
    if (!in) {
        throw runtime_error("Can't open input file");
    }

    for (string word; in >> word;) {
        word_list.insert(word);
    }
    in.close();
}

void print_word_ladder(const vector<string>& ladder){
    if (ladder.empty()) {
        cout << "No word ladder found." << endl;
    }

    cout << "Word ladder found: ";
    for (const string& word : ladder) {
        cout << word << " ";
    }
    cout << endl;
}

#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}
void verify_word_ladder(){
    set<string> word_list;

    load_words(word_list, "src/words.txt");
    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}