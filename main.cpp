#include <system_error>
#include <filesystem>
#include <iostream>
#include <fstream>
#include<regex>
namespace fs = std::filesystem;
int main(){

    std::string pattern;
    fs::path dir{};
    std::cout << "please enter the desired file directory" << std::endl;
    std::cin >> dir;
    std::cout << "Plese enter the regex" << std::endl;
    std::cin >> pattern;
    std::regex word_regex(pattern);
    std::cout << fs::exists(dir); // throws: files do not exist
    for (auto const& dir_entry : fs::recursive_directory_iterator(dir)) {
        fs::path test = dir_entry;
        std::string temp = test.string();
        std::ifstream file{temp};
        //if (!file) {
          //  std::cerr << "failed to open file. Exiting with failure" << std::endl;
            //std::exit(EXIT_FAILURE);
        //}

        std::cout << dir_entry << '\n';
        // read file
        std::string s;
        std::vector<std::string> words;
        while(std::getline(file, s)) {
            auto words_begin = std::sregex_iterator(s.begin(), s.end(), word_regex);
            auto words_end = std::sregex_iterator();
            std::cout << "Found "
                      << std::distance(words_begin, words_end)
                      << " words"
                      << std::endl;
            for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
                std::smatch match = *i;
                std::string match_str = match.str();
                words.push_back(match_str);
            }
    }
        std::cout << "matches found in " << temp << std::endl;
        for(auto i : words) {
            std::cout << "   "
            << i
            << std::endl;
        }
        words.erase(words.begin(), words.end());
    }

    return 0;
}
