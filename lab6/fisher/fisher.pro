TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES = Event.cpp Fish.cpp Simulation.cpp \
    #       main.cpp \
#          test-harness-myprio.cpp \
            test-harness-myvector.cpp

HEADERS = $$files(*.h,true)
