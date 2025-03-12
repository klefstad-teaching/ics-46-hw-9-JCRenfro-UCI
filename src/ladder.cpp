#include "ladder.h"

void error(string word1, string word2, string msg)
{
    cerr << "ERROR ON: (" << word1 << ", " << word2 << ") MSG: " << msg << std::endl;
}
bool edit_distance_within(const std::string& str1, const std::string& str2, int d)
{
    /*
        Compares words to see if they are neighbors
        Takes in different sized words & compares
        Let d be distance between str1 & str2 (str1 - str2) usage
    */
    // If Difference greater than 2 return
    if (abs(d) > 1) return false;
    // Get the length of the smallest to loop through
    int size1 = str1.size(); int size2 = str2.size();
    int smallest = (d > 0) ? size2: size1;
    // Count how many differences each string has
    int diff_count = 0, start_pos = 0, offset1 = 0, offset2 = 0;
    if (d != 0){
        // Add 1 to diff_count since size differs by 1
        if (str1[size1-1] != str2[size2-1]) ++diff_count;
        // If difference is the first index, offset one so they add up
        if (str1[start_pos] != str2[start_pos]){
            ++diff_count;
            if (size2 < size1) ++offset1;
            else ++offset2;
        }
    }
        //std::cout << "DiffCount: " << diff_count << " StartPos: " << start_pos << std::endl;
    // Check if each element is the same, start && end differences are accounted for
    for (int i=start_pos; i < smallest && diff_count < 2; ++i){
            //std::cout << "\tCOMPARING: " << str1[i + offset1] << " && " << str2[i + offset2] << std::endl;
        if (str1[i + offset1] != str2[i + offset2]){
            if (size1 < size2) --offset1;
            else if (size2 < size1) --offset2;
            ++diff_count;
        }
    }
    return (diff_count > 1) ? false: true;
}
bool is_adjacent(const string& word1, const string& word2)
{
    /*
        Defines legal hops since can add or remove letters
        Returns true if two words are neighbors (One letter difference only)
    */
    int size1 = word1.size(); int size2 = word2.size();
    return edit_distance_within(word1, word2, size1-size2);
}
vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list)
{
    /*
        Note* when keeping track of used words use a set.
        Since using breadth first search implemented as a queue of stacks
            Queue for BFS traversal
            Stack for keeping track of all current ladders (will return shortest one)
        General procedure:
            1. Initialize variables (Queue of Ladders (strings, used as stack), Set for Visited)
            2. BFS travel so, while ladderqueue not empty
                a. pop front of queue, get last element
                b. Compare to each word in given wordlist, if adjacent (Only one letter changed) && not visited
                    - Add to visited, make a new ladder (copy) with new last element as current word
                    - If valid ladder to endword, return that latter, else push to queue for BFS and continue BFS travel
                c. If at end of BFS travel, then no ladder found
    */
    using ladder = vector<string>;
    // Check Initial Errors
    if (begin_word == end_word) {error(begin_word, end_word, "Same words"); return ladder();}
    // Initialize
    queue<ladder> ladder_queue;
    set<string> visited;
    // Add starting word to visited and ladder_queue
    ladder beg_ladder; beg_ladder.push_back(begin_word);
    ladder_queue.push(beg_ladder);
    visited.insert(begin_word);
    // Start BFS
    while (!ladder_queue.empty()){
        ladder currLadder = ladder_queue.front(); ladder_queue.pop();
            //std::cout << "In Ladder: "; for (auto i: currLadder) std::cout << i << "->"; std::cout << std::endl;
        string endWord = *(currLadder.end()-1);
        for (string word: word_list){
                //std::cout << "\t Comparing Words: " << endWord << " && " << word << ": " << is_adjacent(endWord, word) << std::endl;
            if (is_adjacent(endWord, word) && visited.find(word) == visited.end()){
                    //std::cout << "\tSuccessful word: " << word << std::endl;
                visited.insert(word);
                ladder copy = currLadder;
                copy.push_back(word);
                if (word == end_word) return copy;
                ladder_queue.push(copy);
            }
        }
    }
    return ladder();
}
void load_words(set<string> & word_list, const string& file_name)
{
    /*
        Loads words from file into word_list
    */
    ifstream in(file_name);
    if (!in.is_open()) {error("", "", "Incorrect Filepath"); return;}
    string word;
    while (in >> word){
        word_list.insert(word);
    }
}
void print_word_ladder(const vector<string>& ladder)
{
    for (string word: ladder) std::cout << word << " ";
}

#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}
void verify_word_ladder()
{
    set<string> word_list;

    load_words(word_list, "src/words.txt");

    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);

    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);

    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);

    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);

    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);

    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);

}