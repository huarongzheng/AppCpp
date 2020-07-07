static constexpr int BLOCK = 32; // BLOCK is chosen to be divisible by A, B, C. BLOCK^2 fully leverage all shared memory in a cuda block

template <class T>
struct Matrix
{
    int  width;
    int  height;
    int  stride;
    T   *data;
}

inline int divRoundUp(const int a, const int b)
{
    return (a + b - 1) / b;
}

template <class T>
__forceinline__ __device__ Matrix<T> getSubMatrix(const Matrix<T> mtx, int y, int x)
{
    Matrix<T> sub;
    sub.width  = BLOCK;
    sub.height = BLOCK;
    sub.stride = mtx.stride;
    sub.data   = &mtx.data[y * mtx.stride * BLOCK + x * BLOCK];
}

template <class T>
__forceinline__ __device__ T getData(const Matrix<T> mtx, int y, int x)
{
    return mtx.data[y * mtx.stride + x];
}

template <class T>
__forceinline__ __device__ void setData(const Matrix<T> mtx, int y, int x, T val)
{
    mtx.data[y * mtx.stride + x] = val;
}

template <class T>
__global__ void MatrixMulKernel(Matrix<T> dC, const Matrix<T> dA, const Matrix<T> dB)
{
    assert(dA.width == dB.height);

    Matrix<T> Asub, Bsub, Csub;
    Csub = getSubMatrix(dC, blockIdx.y, blockIdx.x);

    __shared__ T op1[BLOCK][BLOCK];
    __shared__ T op2[BLOCK][BLOCK];
    T sum = 0;

    int nTile = divRoundUp(dA.width, BLOCK);
    // loop over 
    for(int t = 0; t < nTile; t++)
    {
        // load sub matrix to shared memory
        Asub = getSubMatrix(dA, blockIdx.y, t);
        Bsub = getSubMatrix(dB, t, blockIdx.x);

        op1[threadIdx.y][threadIdx.x] = getData(Asub, threadIdx.y, threadIdx.x);
        op2[threadIdx.y][threadIdx.x] = getData(Bsub, threadIdx.y, threadIdx.x);

        __syncthreads();

        // sub sum product
        for(int i = 0; i < BLOCK; i++)
        {
            sum += op1[threadIdx.y][i] * op2[i][threadIdx.x];
        }

        __syncthreads();
    }

    // put sum back to Csub
    setData(Csub, threadIdx.y, threadIdx.x, sum);
}

template <class T>
void MatrixMul(Matrix<T> C, const Matrix<T> A, const Matrix<T> B, cudaStream_t stream = 0)
{
    assert(A.width == B.height);

    size_t size;

    Matrix<T> dA;
    size = A.height * A.width * sizeof(T);
    dA.height = A.height;
    dA.width  = A.width;
    dA.stride = A.stride;
    cudaMalloc(&dA.data, size);
    cudaMemcpy(dA.data, A.data, size, cudaMemcpyHostToDevice, stream);

    Matrix<T> dB;
    size = B.height * B.width * sizeof(T);
    dB.height = B.height;
    dB.width  = B.width;
    dB.stride = B.stride;
    cudaMalloc(&dB.data, size);
    cudaMemcpy(dB.data, B.data, size, cudaMemcpyHostToDevice, stream);

    Matrix<T> dC;
    size = C.height * C.width * sizeof(T);
    dC.height = C.height;
    dC.width  = C.width;
    dC.stride = C.stride;
    cudaMalloc(&dC.data, size);

    dim3 dimBlock(BLOCK, BLOCK);
    dim3 dimGrid(divRoundUp(B.width, BLOCK), divRoundUp(A.height, BLOCK));
    MatrixMulKernel<<<dimGrid, dimBlock, 0, stream>>>(dC, dA, dB);

    // copy back
    cudaMemcpy(C.data, dC.data, size, cudaMemcpyDeviceToHost, stream);
    cudaFree(dA.data);
    cudaFree(dB.data);
    cudaFree(dC.data);
}

