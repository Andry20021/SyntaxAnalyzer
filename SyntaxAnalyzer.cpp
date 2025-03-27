#include "SyntaxAnalyzer.h"


    bool SyntaxAnalyzer::vdecassign () {         // andry
        if ( tokitr != tokens.end() && (*tokitr == "t_integer" || *tokitr == "t_string")) {
            tokitr++; lexitr++;
            return assignstmt();
        }
    }

    bool SyntaxAnalyzer::stmtlist() {           // charles
        if (stmt() == 1) {
            while (stmt() == 1) {
            }
            return true;
        }
        else {
            if ((tokitr != tokens.end()) && *tokitr == "s_lparent") {
                //Null set
                ++tokitr, ++lexitr;
                return true;
            }
            return false;
        }
    }

    int SyntaxAnalyzer::stmt() {                // ash
        if (tokitr != tokens.end()) {
            if (*tokitr == "t_if") {
                tokitr++;
                lexitr++;
                return ifstmt();
            } else if (*tokitr == "t_while") {
                tokitr++;
                lexitr++;
                return whilestmt();
            } else if (*tokitr == "s_assign") {
                tokitr++;
                lexitr++;
                return assignstmt();
            } else if (*tokitr == "t_input") {
                tokitr++;
                lexitr++;
                return inputstmt();
            } else if (*tokitr == "t_output") {
                tokitr++;
                lexitr++;
                return outputstmt();
            }
        }
        return false;
    }

    bool SyntaxAnalyzer::ifstmt(){              // andry

    }
    bool SyntaxAnalyzer::elsepart(){            // ash

    }
    bool SyntaxAnalyzer::whilestmt(){           // charles

    }
    bool SyntaxAnalyzer::assignstmt(){          // ash

    }
    bool SyntaxAnalyzer::inputstmt(){           // andry

    }
    bool SyntaxAnalyzer::outputstmt(){          // charles

    }
    bool SyntaxAnalyzer::expr(){                // andry

    }
    bool SyntaxAnalyzer::simpleexpr(){          // ash

    }
    bool SyntaxAnalyzer::term(){                // charles

    }
    bool SyntaxAnalyzer::logicop(){             // andry

    }
    bool SyntaxAnalyzer::arithop(){             // charles

    }
    bool SyntaxAnalyzer::relop(){               // ash

    }