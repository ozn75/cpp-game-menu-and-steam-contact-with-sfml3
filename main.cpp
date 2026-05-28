#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "game.hpp"

int main(int argc, char* argv[]) {
    try {
        Game oyun;
        oyun.calistir();
    }
    catch (const std::exception& e) {
        std::cerr << "Hata: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
