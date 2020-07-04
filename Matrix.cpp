static constexpr int BLOCK = 32; // BLOCK is chosen to be divisible by A, B, C. BLOCK^2 fully leverage all shared memory in a cuda block

template<T>
struct Matrix
{
    int  width;
    int  height;
    int  stride;
    T   *data;
}

inline int divRoundUp(int a, int b)
{
    return (a + b - 1) / b;
}

__forceinline__ __device__ Matrix<T> getSubMatrix(const Matrix<T> mtx, int y, int, x)
{
    Matrix<T> sub;
    sub.width  = BLOCK;
    sub.height = BLOCK;
    sub.data   = mtx.stride;
    sub.data   = &mtx.data[y * BLOCK * mtx.stride + x * BLOCK];
}

template<T>
__forceinline__ __device__ T getData(const Matrix<T> mtx, int y, int x)
{
    return mtx.data[y * mtx.stride + x];
}

template<T>
__device__ Matrix<T> void setData(const Matrix<T> mtx, int y, int x, T val)
{
    return mtx.data[y * mtx.stride + x] = val;
}

template<T>
__global__ void MatrixMulKernel(const Matrix<T> dC, const Matrix<T> dA, const Matrix<T> dB)
{
    assert(dA.width == dB.height);

    Matrix<T> Asub, Bsub, Csub;
    Csub = getSubMatrix(dC, blockIdx.y, blockIdx.x);
    __shared__ T op1[BLOCK][BLOCK];
    __shared__ T op2[BLOCK][BLOCK];
    T sum = 0;
    int nTile = divRoundUp(dA.width, BLOCK);
    // loop over 
    for (int t = 0; t < nTile; t++)
    {
        // load sub matrix to shared memory
        Asub = getSubMatrix(dA, blockIdx.y, t);
        Bsub = getSubMatrix(dB, t, blockIdx.x);
        op1[threadIdx.y][threadIdx.x]  = getData(Asub, threadIdx.y, threadIdx.x);
        op2[threadIdx.y][threadIdx.x]  = getData(Bsub, threadIdx.y, threadIdx.x);

        __syncthreads();

        // sub sum product
        for (int i = 0; i < BLOCK; i++)
        {
            sum += op1[threadIdx.y][i] * op2[i][threadIdx.x];
        }

        __syncthreads();
    }

    // put sum back to Csub
    setData(Csub, threadIdx.y, threadIdx.x, sum);
}

template<T>
void MatrixMul(const Matrix<T> C, const Matrix<T> A, const Matrix<T> B)
{
    assert(A.width == B.height);

    size_t size;

    Matrix<T> dA;
    size = A.height * A.width * sizeof(T);
    dA.width    = A.width;
    dA.height   = A.height;
    dA.stride   = A.stride;
    cudaMalloc(&dA.data, size);
    cudaMemcpy(dA.data, A.data, size, cudaMemcpyHostToDevice, 0);

    Matrix<T> dB;
    size = B.height * B.width * sizeof(T);
    dB.width    = B.width;
    dB.height   = B.height;
    dB.stride   = B.stride;
    cudaMalloc(&dB.data, size);
    cudaMemcpy(dB.data, B.data, size, cudaMemcpyHostToDevice, 0);

    Matrix<T> dC;
    size = C.height * C.width * sizeof(T);
    dC.width    = C.width;
    dC.height   = C.height;
    dC.stride   = C.stride;
    cudaMalloc(&dC.data, size);

    dim3 dimBlock(BLOCK, BLOCK);
    dim3 dimGrid(divRoundUp(A.height, BLOCK), divRoundUp(B.width, BLOCK));
    MatrixMulKernel<<<dimGrid, dimBlock, 0, 0>>>(dC, dA, dB);

    // copy back
    cudaMemcpy(C.data, dC.data, size, cudaMemcpyDeviceToHost, 0);
    cudaFree(dA.data);
    cudaFree(dB.data);
    cudaFree(dC.data);
}

