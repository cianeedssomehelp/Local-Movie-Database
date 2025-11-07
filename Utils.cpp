#include "Utils.h"
#include <sstream>
#include <string>
#include <vector>

using namespace std;

std::vector<std::string> split(std::string s, char del) {
    std::vector<std::string> output;
    std::stringstream data{ s };
    std::string token;

    while (getline(data, token, del)) {
        output.push_back(token);
    }
    return output;
}