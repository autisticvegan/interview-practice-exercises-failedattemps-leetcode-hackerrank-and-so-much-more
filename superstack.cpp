std::vector<std::string> tokenize(std::string& str) {
    std::vector<std::string> tokens;
    
    std::stringstream c(str);
    std::string temp;
    while(std::getline(c, temp, ' ')) {
        tokens.push_back(temp);
    }
    
    return tokens;
}

/*
 * Complete the function below.
 
 
  3 5 2
  0 0 1
 
 */
void superStack(vector <string> operations) {

    std::vector<long long> theSuperStack;
    std::vector<long long> additionFactors;
    
    for (auto& s : operations) {
        
        //tokenize and parse str
        std::vector<std::string> toks = tokenize(s);
        
        if (toks[0] == "pop") {
            int theSize = (int)theSuperStack.size() - 1;
            
            if (theSize <= 0) {
                
                if (theSize == 0) {
                    additionFactors.pop_back();
                    theSuperStack.pop_back();
                }
                std::cout << "EMPTY\n";
                continue;
            }
            
            if (theSize > 0) {
                additionFactors[theSize - 1] += additionFactors[theSize];
            }
            additionFactors.pop_back();
            theSuperStack.pop_back();
            
            std::cout << additionFactors[theSize - 1] + theSuperStack[theSize - 1] << std::endl;
            
        } else if (toks[0] == "inc") {

            /*
            std::cout << "DEBUG: inc\n";
            std::cout << "before:\n";
            for (int i = 0; i < additionFactors.size(); ++i) {
                std::cout << additionFactors[i] << " ";
            }
            std::cout << std::endl;
            */
            long long size = std::stoll(toks[1]);
            long long amount = std::stoll(toks[2]);
            long long theSize = std::min(size - 1, (long long)theSuperStack.size() - 1);
            if (theSize >= 0) {
                additionFactors[theSize] += amount;
            } else {
                std::cout << "EMPTY\n";
                continue;
            }
            /*
            std::cout << "after:\n";
            for (int i = 0; i < additionFactors.size(); ++i) {
                std::cout << additionFactors[i] << " ";
            }
            std::cout << std::endl;
            */
            std::cout << additionFactors[theSuperStack.size() - 1] + theSuperStack[theSuperStack.size() - 1] << std::endl;
            
        } else if (toks[0] == "push") {
            additionFactors.push_back(0);
            theSuperStack.push_back(std::stoll(toks[1]));
            std::cout << toks[1] << std::endl;
        }
            
    }
    
    
}