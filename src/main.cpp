#include <iostream>
#include <chrono>

#include <MT.h>
#include <Solver.h>


int main() {
//    init_genrand(5439UL);
    init_genrand(4539UL);


    for (int i = 0; i < 100; i++){
        Solver solver;

        solver.generateTargetAndTiles();

        solver.displaySetUp();

        auto start = std::chrono::high_resolution_clock::now();

        solver.solve();

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        solver.displayResult();

        std::cout << "Time spent : " << duration.count() << " ms" << std::endl << std::endl;
    }

    return 0;
}
