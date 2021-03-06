#ifndef MODEL_TERMINAL_H_
#define MODEL_TERMINAL_H_

#include "model/Module.h"

class Terminal : public Module {
public:
    /*
    Create a Pin with zero offset and add it to the Terminal.
    */
    Terminal(std::string name);
    ~Terminal();
    /*
    Set x and y and also update the Pin's position by setting it directly.
    */
    void setPosition(double x, double y);
    double getX();
    double getY();
    /*
    Get the Pin of the Terminal.
    A Terminal is designed to have only one Pin and the Pin
    is created when the Terminal is created.
    */
    Pin *getPin();
    /*
    @Override
    */
    double getPinsOriginX();
    /*
    @Override
    */
    double getPinsOriginY();

private:
    double x;
    double y;
};

#endif