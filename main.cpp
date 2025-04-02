#include <fstream>
using namespace std;
#include "SyntaxAnalyzer.h"

int main() {
    ifstream source("../example.txt");
    SyntaxAnalyzer syntax_analyzer(source);
    syntax_analyzer.parse();
}
