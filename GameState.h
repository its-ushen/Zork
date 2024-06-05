// GameState.h
#ifndef GAME_STATE_H
#define GAME_STATE_H

struct GameState {
    unsigned int isRunning: 1;
    unsigned int isEnding: 1;
    unsigned int isReady: 1;
};

#endif // GAME_STATE_H
