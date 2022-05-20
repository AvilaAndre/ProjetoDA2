//
// Created by asus on 20/05/2022.
//

#ifndef PROJETODA2_STOP_H
#define PROJETODA2_STOP_H


#include <string>

class Stop {
private:
    int id;


public:
    Stop(int id_);
    std::string toString();
    int getId();

    bool operator==(Stop stop2) {
        return (this->id == stop2.getId());
    }
};


#endif //PROJETODA2_STOP_H
