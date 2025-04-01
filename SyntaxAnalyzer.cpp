#include "SyntaxAnalyzer.h"


    bool SyntaxAnalyzer::vdecassign () {         // andry
        if ( tokitr != tokens.end() && (*tokitr == "t_integer" || *tokitr == "t_string")) {
            tokitr++; lexitr++;
        }
        return assignstmt();
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
                tokitr++; lexitr++;
                return ifstmt();
            } else if (*tokitr == "t_while") {
                tokitr++; lexitr++;
                return whilestmt();
            } else if (*tokitr == "t_id") {
                tokitr++; lexitr++;
                return assignstmt();
            } else if (*tokitr == "t_input") {
                tokitr++; lexitr++;
                return inputstmt();
            } else if (*tokitr == "t_output") {
                tokitr++; lexitr++;
                return outputstmt();
            }
        }
        return false;
    }

    bool SyntaxAnalyzer::ifstmt(){              // andry
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
		while (tokitr != tokens.end()) {
			if (*tokitr == "t_else") {
                tokitr++; lexitr++;
			if (*tokitr == "s_lbrace") {
              		tokitr++; lexitr++;
				if (stmtlist()) {
                		tokitr++; lexitr++;
						if (*tokitr == "s_rbrace") {
				    		tokitr++; lexitr++;
							return true;
						}
					}
				}
			}
			tokitr++; lexitr++;
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
		while (tokitr != tokens.end()) {
			if (*tokitr == "t_id") {
				tokitr++; lexitr++;
				if (*tokitr == "s_assign") {
					tokitr++; lexitr++;
					if (expr()) {
						tokitr++; lexitr++;
						return true;
					}
				}
			}
		}
		return false;
	}

    bool SyntaxAnalyzer::inputstmt(){           // andry
      	if (tokitr != tokens.end() && *tokitr == "t_input") {
          	if (tokitr != tokens.end() && *tokitr == "s_lparen") {
        		tokitr++; lexitr++;
        		if (tokitr != tokens.end() && *tokitr == "t_id") {
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

    bool SyntaxAnalyzer::outputstmt(){          // charles
		if (tokitr != tokens.end() && *tokitr == "t_output") {
         	++tokitr, ++lexitr;
         	if (tokitr != tokens.end() && *tokitr == "s_rbrace") {
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
		while (tokitr != tokens.end()) {
			if (term()) {
				tokitr++; lexitr++;
				if (arithop() || relop()) {
					tokitr++; lexitr++;
					if (term()) {
						tokitr++; lexitr++;
						return true;
					}
				}
				tokitr++; lexitr++;
			}
			return true;
		}
		return false;
	}

    bool SyntaxAnalyzer::term(){                // charles
		if (tokitr != tokens.end()) {
         	if (*tokitr == "t_text" || *tokitr == "t_number" || *tokitr == "t_id") {
             	++tokitr, ++lexitr;
             	return true;
         	} else if (expr()) {
             	return true;
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