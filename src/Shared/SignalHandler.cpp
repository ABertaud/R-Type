/*
** EPITECH PROJECT, 2020
** client
** File description:
** SignalHandler
*/

#include "SignalHandler.hpp"

bool isInterrupt = false;

SignalHandler::SignalHandler()
{
    signal(SIGINT, signal_callback_handler);
}

bool SignalHandler::isInterrupted(void)
{
    return (isInterrupt);
}

void SignalHandler::signal_callback_handler(int signum)
{
    isInterrupt = true;
}