#include "riemann_sum_cuda.h"
#include <cuda_runtime.h>

#include "functions.h"

#define BLOCK_SIZE 16

__device__ double call_function(int func_id, double x, double y) {
    switch (func_id) {
        case 1: return func_1(x, y);
        case 2: return func_2(x, y);
        case 3: return func_3(x, y);
    default: return 0.0;
    }
}


__global__ void riemannSum(double x1, double x2,
                           double y1, double y2,
                           int steps,
                           double *result,
                           int func_id) {

    int i = threadIdx.x + blockIdx.x * blockDim.x;
    int j = threadIdx.y + blockIdx.y * blockDim.y;

    double dx = (x2 - x1) / steps;
    double dy = (y2 - y1) / steps;

    if (i < steps && j < steps) {
        double x = x1 + i * dx;
        double y = y1 + j * dy;
        double f_val = call_function(func_id, x, y) * dx * dy;

        atomicAdd(result, f_val);
    }
}


double riemman_return(double x1, double x2, double y1, double y2, int steps, int func_id) {
    double h_result = 0.0, *d_result;
    cudaMalloc((void**)&d_result, sizeof(double));
    cudaMemcpy(d_result, &h_result, sizeof(double), cudaMemcpyHostToDevice);

    dim3 blockSize(16, 16);
    dim3 gridSize((steps + 15) / 16, (steps + 15) / 16);

    riemannSum<<<gridSize, blockSize>>>(x1, x2, y1, y2, steps, d_result, func_id);
    cudaDeviceSynchronize();

    cudaMemcpy(&h_result, d_result, sizeof(double), cudaMemcpyDeviceToHost);
    cudaFree(d_result);

    return h_result;
}

