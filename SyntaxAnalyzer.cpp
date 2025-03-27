#include "SyntaxAnalyzer.h"


    bool SyntaxAnalyzer::vdecassign () {         // andry
        if ( tokitr != tokens.end() && (*tokitr == "t_integer" || *tokitr == "t_string")) {
            tokitr++; lexitr++;
            return assignstmt();
        }
    }

    bool SyntaxAnalyzer::stmtlist() {           // charles

    }
    int SyntaxAnalyzer::stmt() {                // ash

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