//
//  producer.cpp
//  9815_hw2_q1
//
//  Created by jiang yumin on 12/3/23.
//
//  Creates and writes an integer to shared memory.
//

#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <iostream>

int main() {
    using namespace boost::interprocess;

    try {
        // Create a shared memory object.
        shared_memory_object shm(create_only, "MySharedMemory", read_write);

        // Set size of the shared memory.
        shm.truncate(sizeof(int));

        // Map the shared memory in this process.
        mapped_region region(shm, read_write);

        // Write an integer to the shared memory.
        int* i = static_cast<int*>(region.get_address());
        *i = 42;  // Example integer

        std::cout << "Producer wrote: " << *i << std::endl;
    } catch(const interprocess_exception &ex) {
        std::cerr << ex.what() << std::endl;
        return 1;
    }

    return 0;
}
