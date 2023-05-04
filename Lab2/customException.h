#ifndef customException_h
#define customException_h

typedef enum {
    Empty,
    Invalid,
} Code;

class IndexOutOfRange {
    Code error;
    const char* text[2] = {"Sequence is empty", "Sequence doesn't have element with that index"};
    
public:
    void printError()
    {
        std::cout << text[(int) error] << std::endl;
    }
    IndexOutOfRange(Code er) : error(er) {};
};

#endif
