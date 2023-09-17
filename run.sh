#!/bin/bash

#Compile
g++ -c main.cpp
#Link
g++ main.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system
#execute
./sfml-app

#if you get permission error run: chmod 755 run.sh