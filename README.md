# Parallel Computation for Cryptography Algorithms

**Description:** 

This project leverages parallel computation using MPI (Message Passing Interface) to accelerate the DES encryption algorithm.

• Encryption tasks are divided and distributed across multiple processes to enable concurrent execution.

• The primary goal is to reduce execution time compared to the sequential approach.

• It also aims to improve scalability to handle larger datasets efficiently.

• Key focus areas include:

• Efficient workload distribution among processes

• Minimizing communication overhead to maintain high performance

• Overall, the project demonstrates how parallelism can enhance the speed and efficiency of cryptographic operations.

**Introduction :**

 This project focuses on accelerating encryption performance using distributed computing techniques.

• At the core of this approach is the Message Passing Interface (MPI), a powerful tool for building parallel applications through inter-process communication.

• MPI enables efficient task distribution and coordination among processes running on different nodes or cores.

• This project applies MPI to implement a parallelized version of the DES (Data Encryption Standard) encryption algorithm.

• Traditional sequential DES suffers from increased latency when processing large volumes of data.

• By parallelizing the DES algorithm, the project aims to improve encryption speed, reduce execution time, and scale better with growing data demands.

• The implementation explores various load balancing and communication strategies to enhance overall efficiency.

• The project began in February 2025 and is currently in progress.

• Tools and technologies used include:
    • MPI (Message Passing Interface)
    • C programming language

**WORKING:**
1. Understood the DES algorithm and built a toy cipher as a starting point.
2. Implemented the full DES encryption code and analyzed it using profiling tools.
3. Learned MPI in C and Python, and applied it to parallelize the DES code.
4. Compared results before and after MPI, and optimized the parallel version for better 

 **RESULTS:**
 Output for des code :
 
    Plaintext : ABCEA123567893F
    Key       : 133457799BBCDFF1
    Ciphertext: B83C9839D83D1BE7
    Time taken for 1000000 iterations: 30.416 seconds

Output for des code with mpi implementation:

    Plaintext : ABCEA123567893F
    Key       : 133457799BBCDFF1
    Ciphertext: B83C9839D83D1BE7
    Time taken for 1000000 iterations: 9.401 seconds

  The time taken speedup is ~ 3x after mpi implementation.

**CONCLUSION:**

1. The MPI implementation of the DES algorithm significantly reduced execution time, achieving up to 3.43× speedup compared to the sequential version.
2. This demonstrates the effectiveness of parallel computing in enhancing cryptographic algorithm performance on large datasets.

**FUTURE WORK:**
1. Function-level MPI Optimization – Apply MPI selectively to the most time-consuming functions to further boost performance.   
2. Explore Other PPLs – Implement DES using CUDA or OpenCL to utilize GPU-based acceleration for even faster encryption.
3. Cryptanalysis Expansion – Extend the work to include parallel cryptanalysis such as brute-force key search and vulnerability analysis.

       



