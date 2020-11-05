/*
** EPITECH PROJECT, 2020
** client
** File description:
** SignalHandler
*/

#ifndef SIGNALHANDLER_HPP_
#define SIGNALHANDLER_HPP_

#include <signal.h>
#include <iostream>

extern bool isInterrupt;

class SignalHandler {
    public:
        SignalHandler();
        ~SignalHandler()=default;
        bool isInterrupted(void);
    private:
        static void signal_callback_handler(int signum);
};

#endif /* !SIGNALHANDLER_HPP_ */