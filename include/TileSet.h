//
// Created by paulo on 06/01/2025.
//

#ifndef COUNT_IS_GOOD_TILESET_H
#define COUNT_IS_GOOD_TILESET_H

#include <iostream>
#include <vector>
#include "../include/MT.h"


/**
 * \class TileSet
 * \brief Class to represent a set of tiles.
 *
 * Used to store the tiles and manipulate them.
 */
class TileSet {
public:
    std::vector<int> tiles;

    TileSet(const std::vector<int>& initialTiles) : tiles(initialTiles) {}

    void removeTile(int index) {
        tiles.erase(tiles.begin() + index);
    }

    void addTile(int value) {
        tiles.push_back(value);
    }
};

#endif //COUNT_IS_GOOD_TILESET_H
