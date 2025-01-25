//
// Created by Paul Quinzi on 06/01/2025.
//

#ifndef COUNT_IS_GOOD_SOLVER_H
#define COUNT_IS_GOOD_SOLVER_H


#include <iostream>
#include <algorithm>
#include <MT.h>
#include <TileSet.h>

/**
 * \class Solver
 * \brief Class to solve a count is good arithmetic puzzle.
 *
 * The Solver class generates a target number and a set of tiles, then attempts to find an arithmetic expression
 * using the tiles that is as close as possible to the target number. The chosen rules are directly inspired by
 * the TV show "Des chiffres et des lettres" and the game "Countdown".
 */
class Solver {
private:
    int target;
    std::vector<int> tiles;
    std::vector<char> operations = {'+', '-', '*', '/'};
    int closestResult;
    std::vector<std::string> bestExpression;


    /**
     * \brief Apply an arithmetic operation to two integers.
     * \param a The first integer.
     * \param b The second integer.
     * \param op The operation to apply.
     * \return The result of the operation if it is valid, -1 otherwise
     *          as negative tiles are not allowed to avoid duplication.
     *          Because if a - b = c, then b - a = -c and you always duplicate
     *          the branch with + c and - (-c)
     */
    int applyOperation(int a, int b, char op) {
        switch (op) {
            case '+': return a + b;
            case '-': return (a > b) ? a - b : -1;
            case '*': return a * b;
            case '/': return (b != 0 && a % b == 0) ? a / b : -1;
            default: return -1;
        }
    }


    /**
     * /brief find the best solution with a recursive approach.
     *
     * /param tileSet The current set of tiles.
     * /param expressions The current path to the best solution
     *
     * The function is recursive and tries all possible combinations of tiles and operations to find the best solution.
     * It stops when the target is reached or when there is no more tile to use.
     * The function is called with the initial tile set and an empty vector of expressions.
     *
     */
    void findSolution(TileSet tileSet, std::vector<std::string> expressions) {
        // If the target is reached, no need to find more solutions
        if (closestResult == target) return;

        // If the target is in the tile set, we have a solution
        // Last tile added is always at the end of the tileSet
        if (tileSet.tiles[tileSet.tiles.size() - 1] == target ){
            closestResult = target;
            bestExpression = expressions;
            return;
        }

        // If there is only one tile left, we can check if it is the closest result
        if (tileSet.tiles.size() == 1) {
            int result = tileSet.tiles[0];
            int difference = abs(target - result);
            if (difference < abs(target - closestResult)) {
                closestResult = result;
                bestExpression = expressions;
            }
            return;
        }

        // Try all possible combinations of tiles and operations
        for (size_t i = 0; i < tileSet.tiles.size(); ++i) {
            for (size_t j = 0; j < tileSet.tiles.size(); ++j) {
                if (i != j) {
                    for (char op : operations) {
                        int a = tileSet.tiles[i];
                        int b = tileSet.tiles[j];

                        // a op b
                        int result = applyOperation(a, b, op);
                        if (result != -1) { // -1 means the operation is invalid
                            TileSet newTileSet(tileSet.tiles);
                            newTileSet.removeTile(std::max(i, j));
                            newTileSet.removeTile(std::min(i, j));
                            newTileSet.addTile(result);

                            std::vector<std::string> newExpressions = expressions;
                            newExpressions.push_back("(" + std::to_string(a) + " " + op + " " + std::to_string(b) + ")");

                            findSolution(newTileSet, newExpressions);
                        }

                        // b op a for non commutative op
                        if (op == '-' || op == '/') {
                            result = applyOperation(b, a, op);
                            if (result != -1) { // -1 means the operation is invalid
                                TileSet newTileSet(tileSet.tiles);
                                newTileSet.removeTile(std::max(i, j));
                                newTileSet.removeTile(std::min(i, j));
                                newTileSet.addTile(result);

                                std::vector<std::string> newExpressions = expressions;
                                newExpressions.push_back("(" + std::to_string(b) + " " + op + " " + std::to_string(a) + ")");

                                findSolution(newTileSet, newExpressions);
                            }
                        }
                    }
                }
            }
        }
    }

public:
    Solver() : closestResult(-1) {}


    /**
     * \brief Generate a target and a set of tiles.
     *
     * The function generates a random target number between 0 and 1000 and a set of 6 random tiles.
     * The tiles are chosen from a list of possible values: 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 25, 50, 100.
     *
     *
     */
    void generateTargetAndTiles() {
        std::vector<int> possibleTiles = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 25, 50, 100};
        random_shuffle(possibleTiles);
        tiles.assign(possibleTiles.begin(), possibleTiles.begin() + 6);
        target = genrand_int32() % 1001 ;
    }

    /**
     * \brief Solve the count is good puzzle.
     *
     * The function solve the puzzle from the current state.
     * It first checks if the target is in the initial tile set.
     */
    void solve() {
        TileSet initialTileSet(tiles);
        if (std::find(initialTileSet.tiles.begin(), initialTileSet.tiles.end(), target) != initialTileSet.tiles.end()) {
            closestResult = target;
            bestExpression.push_back(std::to_string(target));
            return;
        }
        findSolution(initialTileSet, {});
    }

    void displaySetUp() {
        std::cout << "Target: " << target << std::endl;
        std::cout << "Tiles: ";
        for (int tile : tiles) {
            std::cout << tile << " ";
        }
        std::cout << std::endl;
    }

    void displayResult() {
        std::cout << "Closest result: " << closestResult << std::endl;
        if (!bestExpression.empty()) {
            std::cout << "Expression: ";
            for (const std::string& expr : bestExpression) {
                std::cout << expr << " ";
            }
            std::cout << std::endl;
        } else {
            std::cout << "No valid solution found." << std::endl;
        }
    }
};

#endif //COUNT_IS_GOOD_SOLVER_H
