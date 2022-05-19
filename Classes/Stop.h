//
// Created by asus on 20/05/2022.
//

#ifndef PROJETODA2_STOP_H
#define PROJETODA2_STOP_H


class Stop {
private:
    int origin;
    int destination;
    int capacity;
    int duration;
    
public:
    Stop(int origin_, int destination_, int capacity_, int duration_);
};


#endif //PROJETODA2_STOP_H
