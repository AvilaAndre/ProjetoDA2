//
// Created by asus on 20/05/2022.
//

#include "Stop.h"

Stop::Stop(int id_) : id(id_) {

}

std::string Stop::toString() {
    return "id: " + std::to_string(this->id);
}

int Stop::getId() {
    return this->id;
}
