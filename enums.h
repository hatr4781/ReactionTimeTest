/**
 * @file enums.h
 * @author Ha Tran
 */

#ifndef ENUMS_H
#define ENUMS_H

enum class State {
    Initial,  //before test has been initiated
    Started,  //after test has been initiated, button set to red
    Reaction, //when button has turned green, waiting on user to react
    End       //test finished
};

#endif // ENUMS_H
