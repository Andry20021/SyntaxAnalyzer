//HEADER DOCUMENTATION: TODO

#include <iostream>
#include <vector>
#include <map>
using namespace std;
#ifndef SYNTAXANALYZER_H
#define SYNTAXANALYZER_H
#endif //SYNTAXANALYZER_H

class SyntaxAnalyzer {
private:
    vector<string> lexemes;
    vector<string> tokens;
    vector<string>::iterator lexitr;
    vector<string>::iterator tokitr;
    // map of variables and their datatype
    // i.e. sum t_integer
    map<string, string> symboltable;

    // other private methods
    bool tableCheck();
    bool vdecassign ();          // andry
    bool stmtlist();            // charles
    int stmt();                 // ash
    bool ifstmt();              // andry
    bool elsepart();            // ash
    bool whilestmt();           // charles
    bool assignstmt();          // ash
    bool inputstmt();           // andry
    bool outputstmt();          // charles
    bool expr();                // andry
    bool simpleexpr();          // ash
    bool term();                // charles
    bool logicop();             // andry
    bool arithop();             // charles
    bool relop();               // ash

public:
    SyntaxAnalyzer(istream& infile); //charles
    // pre: 1st parameter consists of an open file containing a source code's
    //	valid scanner/lexical analyzer output.  This data must be in the form: token : lexeme
    // post: the vectors have been populated

    bool parse();
    // pre: none
    // post: The lexemes/tokens have been parsed.
    // If an error occurs, a message prints indicating the token/lexeme pair
    // that caused the error.
    // If no error, vectors contain syntactically correct source code
};
