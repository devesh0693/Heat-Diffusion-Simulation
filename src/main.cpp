#include <iostream>
#include <vector>
#include <omp.h> // For OpenMP
#include <iomanip> // For std::fixed and std::setprecision

// Simulation parameters
const int GRID_SIZE = 100;    // Size of the grid (GRID_SIZE x GRID_SIZE)
const int NUM_ITERATIONS = 1000; // Number of time steps
const double ALPHA = 0.1;     // Thermal diffusivity
const double DT = 0.01;       // Time step (ensure stability: DT <= h*h / (4*ALPHA))
const double H = 1.0;         // Spatial step (delta_x = delta_y = H)

// Function to initialize the grid
void initialize_grid(std::vector<std::vector<double>>& grid) {
    // Initialize with some hot spots
    // For example, a hot line in the middle
    for (int i = 0; i < GRID_SIZE; ++i) {
        for (int j = 0; j < GRID_SIZE; ++j) {
            grid[i][j] = 0.0;
        }
    }

    // Set a central hot region
    int center_start = GRID_SIZE / 4;
    int center_end = 3 * GRID_SIZE / 4;
    for (int i = center_start; i < center_end; ++i) {
        for (int j = center_start; j < center_end; ++j) {
            grid[i][j] = 100.0; // Hot temperature
        }
    }

    // Fixed boundary conditions (e.g., edges kept at 0 or another temp)
    // For simplicity, we'll assume Neumann boundary conditions (zero flux)
    // are implicitly handled by how we compute near the boundaries,
    // or you can explicitly set fixed temperatures on boundaries if needed.
}

// Function to print the grid (for visualization or debugging)
void print_grid(const std::vector<std::vector<double>>& grid) {
    std::cout << std::fixed << std::setprecision(2);
    for (int i = 0; i < GRID_SIZE; ++i) {
        for (int j = 0; j < GRID_SIZE; ++j) {
            std::cout << std::setw(6) << grid[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "--------------------------------------------------" << std::endl;
}

int main() {
    std::vector<std::vector<double>> current_grid(GRID_SIZE, std::vector<double>(GRID_SIZE));
    std::vector<std::vector<double>> next_grid(GRID_SIZE, std::vector<double>(GRID_SIZE));

    initialize_grid(current_grid);

    // (Optional) Print initial grid
    // std::cout << "Initial Grid:" << std::endl;
    // print_grid(current_grid);

    double start_time = omp_get_wtime();

    for (int iter = 0; iter < NUM_ITERATIONS; ++iter) {
        // Copy current_grid to next_grid to handle boundary values correctly
        // or use separate logic for boundary cells.
        // For simplicity in this example, boundaries are not explicitly updated,
        // leading to a fixed boundary if not part of the loop below.
        // A more robust solution might involve ghost cells or specific boundary handling.
        #pragma omp parallel for collapse(2)
        for (int i = 0; i < GRID_SIZE; ++i) {
            for (int j = 0; j < GRID_SIZE; ++j) {
                next_grid[i][j] = current_grid[i][j];
            }
        }


        // Parallelize the computation of the next grid state
        // We iterate from 1 to GRID_SIZE-2 to avoid boundary issues in the simplest case.
        // For more complex boundary conditions (Dirichlet, Neumann), handle grid edges separately.
        #pragma omp parallel for collapse(2)
        for (int i = 1; i < GRID_SIZE - 1; ++i) {
            for (int j = 1; j < GRID_SIZE - 1; ++j) {
                double laplacian = (current_grid[i + 1][j] - 2.0 * current_grid[i][j] + current_grid[i - 1][j]) / (H * H) +
                                   (current_grid[i][j + 1] - 2.0 * current_grid[i][j] + current_grid[i][j - 1]) / (H * H);
                next_grid[i][j] = current_grid[i][j] + ALPHA * DT * laplacian;
            }
        }

        // Swap grids for the next iteration
        current_grid.swap(next_grid);

        // (Optional) Print grid at certain intervals
        // if ((iter + 1) % 100 == 0) {
        //     std::cout << "Grid at iteration " << iter + 1 << ":" << std::endl;
        //     print_grid(current_grid);
        // }
    }

    double end_time = omp_get_wtime();

    std::cout << "Simulation finished." << std::endl;
    std::cout << "Time taken: " << std::fixed << std::setprecision(5) << (end_time - start_time) << " seconds." << std::endl;

    // (Optional) Print final grid
    // std::cout << "Final Grid:" << std::endl;
    // print_grid(current_grid);

    // You might want to write the final grid to a file here
    // for visualization with other tools (e.g., gnuplot, Python matplotlib).

    return 0;
}