SET(ROOT_DIR ${CMAKE_SOURCE_DIR})

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})

include_directories(${ROOT_DIR}/include/)

ADD_EXECUTABLE(bomberman main.cpp
    error/error.cpp
    game/gamecore.cpp
    game/gameloop.cpp
    game/map.cpp
    menu/menu.cpp
    menu/help.cpp
    Obj/Player.cpp
    Obj/Bomb.cpp
    Obj/wall.cpp
    pause/pause.cpp
)

TARGET_LINK_LIBRARIES(bomberman raylib ${CMAKE_DL_LIBS})
