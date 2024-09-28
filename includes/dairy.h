#ifndef _DIARY_H_
#define _DIARY_H_

#include <string>
#include <fstream>

class Dairy {
    public:
        std::string get_breakfast_total();
        std::string get_lunch_total();
        std::string get_dinner_total();

    private:
        std::string return_total(std::ifstream& file);
};

#endif
