TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11
LIBS += -L"/usr/local/lib"
CONFIG(release, debug|release): LIBS += -lsfml-graphics -lsfml-system -lsfml-network -lsfml-window -lthor-d
CONFIG(debug, debug|release): LIBS +=  -lsfml-graphics-d -lsfml-system-d -lsfml-network-d -lsfml-window-d -lthor-d

INCLUDEPATH += "/usr/local/include"
DEPENDPATH += "/usr/local/include"
SOURCES += \
    Source/Application.cpp \
    Source/Command.cpp \
    Source/CommandQueue.cpp \
    Source/Entity.cpp \
    Source/Main.cpp \
    Source/ParallelTask.cpp \
    Source/Player.cpp \
    Source/SceneNode.cpp \
    Source/SpriteNode.cpp \
    Source/State.cpp \
    Source/StateStack.cpp \
    Source/Utility.cpp \
    Source/World.cpp \
    States/Source/GameState.cpp \
    Ball.cpp \
    Include/Book/ResourceHolder.inl \
    Paddle.cpp \
    States/Source/MenuState.cpp \
    States/Source/PauseState.cpp \
    States/Source/NewLevel.cpp \
    Level.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    Include/Book/Application.hpp \
    Include/Book/Category.hpp \
    Include/Book/Command.hpp \
    Include/Book/CommandQueue.hpp \
    Include/Book/Entity.hpp \
    Include/Book/Foreach.hpp \
    Include/Book/ParallelTask.hpp \
    Include/Book/Player.hpp \
    Include/Book/ResourceHolder.hpp \
    Include/Book/ResourceIdentifiers.hpp \
    Include/Book/SceneNode.hpp \
    Include/Book/SpriteNode.hpp \
    Include/Book/State.hpp \
    Include/Book/StateIdentifiers.hpp \
    Include/Book/StateStack.hpp \
    Include/Book/Utility.hpp \
    Include/Book/World.hpp \
    States/Include/GameState.hpp \
    Ball.hpp \
    Paddle.hpp \
    States/Include/MenuState.hpp \
    States/Include/PauseState.hpp \
    Level.hpp

