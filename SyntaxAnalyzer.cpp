#include "SyntaxAnalyzer.h"

	bool SyntaxAnalyzer::tableCheck() {
		//Charles, Ash, Andry
		//Checks to make sure that the resulting id from tokitr is already stored into the table
		if (tokitr != tokens.end() && *tokitr == "t_id") {
			if (lexitr != tokens.end() && symboltable.find(*lexitr) != symboltable.end() ) {
				return true;
			}
		}
		return false;
	}

    bool SyntaxAnalyzer::vdecassign () {         // andry
		string t = *tokitr;
		tokitr++; lexitr++;
		if ( tokitr != tokens.end() && *tokitr == "t_id") {
			if (!tableCheck()) {
				symboltable.insert({*lexitr , t});
			}
			return assignstmt();
		}
		return false;
    }

    bool SyntaxAnalyzer::stmtlist() {           // charles
        if (stmt() == 1) {
			auto prev = tokitr;
        	while (stmt() == 1) {
        		prev = tokitr;
            }
        	if (prev != tokitr) {
        		return false;
        	}
            return true;
        }
        else {
            if ((tokitr != tokens.end()) && *tokitr == "s_rbrace") {
                //Null set
                return true;
            }
            return false;
        }
    }

    int SyntaxAnalyzer::stmt() {                // ash
        if (tokitr != tokens.end()) {
            if (*tokitr == "t_if") {
                tokitr++; lexitr++;
                return ifstmt();
            } else if (*tokitr == "t_while") {
                tokitr++; lexitr++;
                return whilestmt();
            } else if (*tokitr == "t_id") {
                return assignstmt();
            } else if (*tokitr == "t_input") {
                tokitr++; lexitr++;
                return inputstmt();
            } else if (*tokitr == "t_output") {
                tokitr++; lexitr++;
                return outputstmt();
            } else if (*tokitr == "t_integer" || *tokitr == "t_string") {
              	return vdecassign();
            }
        }
        return false;
    }

    bool SyntaxAnalyzer::ifstmt() {              // andry
    	if (tokitr != tokens.end() && *tokitr == "s_lparen") {
        	tokitr++; lexitr++;
        	if (expr()) {
            	if (tokitr != tokens.end() && *tokitr == "s_rparen") {
                	tokitr++; lexitr++;
                	if (tokitr != tokens.end() && *tokitr == "s_lbrace") {
                    	tokitr++; lexitr++;
                    	if (stmtlist()) {
                        	if (tokitr != tokens.end() && *tokitr == "s_rbrace") {
                            	tokitr++; lexitr++;
                            	return elsepart();
                        	}
                    	}
                	}
            	}
        	}
      	}
		return false;
    }

    bool SyntaxAnalyzer::elsepart(){            // ash
		if (tokitr != tokens.end() && *tokitr == "t_else") {
            tokitr++; lexitr++;
			if (tokitr != tokens.end() && *tokitr == "s_lbrace") {
              		tokitr++; lexitr++;
				if (tokitr != tokens.end() && stmtlist()) {
					if (tokitr != tokens.end() && *tokitr == "s_rbrace") {
			    		tokitr++; lexitr++;
						return true;
					}
				}
			}
			return true;
		}
		return false;
	}

    bool SyntaxAnalyzer::whilestmt() {
     // charles
		if (tokitr != tokens.end() && *tokitr == "s_lparen") {
       		++tokitr, ++lexitr;
         	if (expr()) {
             	if (tokitr != tokens.end() && *tokitr == "s_rparen") {
                 	++tokitr, ++lexitr;
                	if (tokitr != tokens.end() && *tokitr == "s_lbrace") {
                     	++tokitr, ++lexitr;
                     	if (stmtlist()) {
                         	if (tokitr != tokens.end() && *tokitr == "s_rbrace") {
                             	++tokitr, ++lexitr;
                             	return true;
                         	}
                     	}
                 	}
             	}
         	}
     	}
     	return false;
 	}

    bool SyntaxAnalyzer::assignstmt(){          // ash
        if (tableCheck()){
			tokitr++; lexitr++;
			if (tokitr != tokens.end() && *tokitr == "s_assign") {
				tokitr++; lexitr++;
				if (tokitr != tokens.end() && expr()) {
                    if (*tokitr == "s_semi") {
                      	tokitr++; lexitr++;
                    	return true;
                    }
                }
			}
		}
		return false;
	}

    bool SyntaxAnalyzer::inputstmt(){           // andry
    	if (tokitr != tokens.end() && *tokitr == "s_lparen") {
        	tokitr++; lexitr++;
        	if (tokitr != tokens.end() && *tokitr == "t_id") {
                if (tableCheck()) {
                	tokitr++; lexitr++;
            		if (tokitr != tokens.end() && *tokitr == "s_rparen") {
                		tokitr++; lexitr++;
                		return true;
            		}
                }
        	}
    	}
    	return false;
    }

	bool SyntaxAnalyzer::outputstmt() {
		// charles
		if (tokitr != tokens.end() && *tokitr == "s_lparen") {
			++tokitr, ++lexitr;
			if (tokitr != tokens.end()) {
				if (*tokitr == "t_text") {
					++tokitr, ++lexitr;
					if (tokitr != tokens.end() && *tokitr == "s_rparen") {
						return true;
					}
				} else if (expr()) {
					if (tokitr != tokens.end() && *tokitr == "s_rparen") {
						return true;
					}
				}
			}
		}
     	return false;
	}

    bool SyntaxAnalyzer::expr(){                // andry
		if (simpleexpr()) {
        	if (logicop()) {
            	if (simpleexpr()) {
                	return true;
            	}
            	return false;
        	}
        	return true;
    	}
    	return false;
    }

    bool SyntaxAnalyzer::simpleexpr(){          // ash
		if (tokitr != tokens.end() && term()) {
			if (tokitr != tokens.end() && (arithop() || relop())) {
				if (tokitr != tokens.end() && term()) {
					return true;
				}
                return false;
			}
			return true;
		}
		return false;
	}

	bool SyntaxAnalyzer::term(){                // charles
		if (tokitr != tokens.end()) {
			if (*tokitr == "t_text" || *tokitr == "t_number") {
				++tokitr, ++lexitr;
				return true;
			}
			if (*tokitr == "t_id") {
				if (tableCheck()) { //variable is defined in symbol table
					++tokitr++; lexitr++;
					return true;
				}
				return false;
			}
			if (*tokitr == "s_lparen") {
				++tokitr; ++lexitr;
				if (expr()) {
					if (tokitr != tokens.end() && *tokitr == "s_rparen") {
						++tokitr; ++lexitr;
						return true;
					}
				}
			}
		}
		return false;
	}

    bool SyntaxAnalyzer::logicop(){             // andry
		if (tokitr != tokens.end()) {
        	if (*tokitr == "t_and" || *tokitr == "t_or") {
            	tokitr++; lexitr++;
            	return true;
        	}
		}
        return false;
    }


    bool SyntaxAnalyzer::arithop(){             // charles
	//Doing +, -, and *.
     	if (tokitr != tokens.end() && (*tokitr == "s_plus" || *tokitr == "s_minus" || *tokitr == "s_mult")) {
         	++tokitr, ++lexitr;
         	return true;
     	}
     	return false;
    }

    bool SyntaxAnalyzer::relop(){               // ash
    // < , >+ , > , >=
		if (tokitr != tokens.end()) {
			if (*tokitr == "s_lt"){
				tokitr++; lexitr++;
				return true;
			}
			else if (*tokitr == "s_le"){
				tokitr++; lexitr++;
				return true;
			}
			else if (*tokitr == "s_gt"){
				tokitr++; lexitr++;
				return true;
			}
			else if (*tokitr == "s_ge"){
				tokitr++; lexitr++;
				return true;
			}
		}
		return false;
	}

SyntaxAnalyzer::SyntaxAnalyzer(istream &infile) {
		//Charles
		string data;
		while (getline(infile, data)) {
			int i = 0;
			bool found = false;
			while (i < data.length() && !found) {
				if (data[i] == ':') {
					found = true;
				}
				i++;
			}
			tokens.push_back(data.substr(0, i - 2));
			lexemes.push_back(data.substr(i + 1, data.length()));
		}
		tokitr = tokens.begin();
		lexitr = lexemes.begin();
	}

bool SyntaxAnalyzer::parse() {
		//Charles, Ash
		if (tokitr != tokens.end() && *tokitr == "t_main") {
			++tokitr, ++lexitr;
			if (tokitr != tokens.end() && *tokitr == "s_lbrace") {
				++tokitr, ++lexitr;
				if (stmtlist()) {
					if (tokitr != tokens.end() && *tokitr == "s_rbrace") {
						++tokitr, ++lexitr;
						if (tokitr == tokens.end()) {
							return true;
						}
					}
				}
			}
		}
		auto num = distance(tokens.begin(), tokitr) + 1;
		if (tokitr != tokens.end()) {
			cout << "ERROR: " << *tokitr << " " << *lexitr << " is invalid ";
			cout << "on line " << num << endl;
		}
		else {
			cout << "ERROR: EOF when reading program on line " << num << endl;
		}
		return false;
	}
