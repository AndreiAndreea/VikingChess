#pragma once

class GameRules {
private:
    static GameRules* instance;

    GameRules() {}

public:
    static GameRules* getInstance() {
        if (!instance)
            instance = new GameRules();
        return instance;
    }

    void displayRules(); 
};
