//
//  consumer.cpp
//  9815_hw2_q1
//
//  Created by jiang yumin on 12/3/23.
//
//  Reads the integer from shared memory.
//

#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <iostream>

int main() {
    using namespace boost::interprocess;

    try {
        // Open the shared memory object.
        shared_memory_object shm(open_only, "MySharedMemory", read_only);

        // Map the shared memory in this process.
        mapped_region region(shm, read_only);

        // Read the integer from shared memory.
        int* i = static_cast<int*>(region.get_address());
        std::cout << "Consumer read: " << *i << std::endl;
    } catch(const interprocess_exception &ex) {
        std::cerr << ex.what() << std::endl;
        return 1;
    }

    return 0;
}
