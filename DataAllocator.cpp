#include "DataAllocator.h"

DataAllocator::~DataAllocator() {
    //FreeAllocatedMemory();
}

/*
void DataAllocator::operator=(DataAllocator & data) {
    AllocateDataMemory(data.GetAllocatedDataSize());
    std::memcpy(allocated_data.get(), data.GetAllocatedMemory().get(), GetAllocatedDataSize());
}
*/
//void DataAllocator::operator=(Memory & data) {
    //FreeAllocatedMemory();
//	AllocateDataMemory(data.GetAllocatedDataSize());
//    std::memcpy(allocated_data.get(), data.memory.get(), GetAllocatedDataSize());
//}

/*
Memory DataAllocator::GetAllocatedMemory(int offset, int size) {
	if ((offset + size) < GetAllocatedDataSize()) {
        Memory(allocated_data + offset, size);
	} else {
		return Memory(0, 0);
	}
}
*/

void DataAllocator::AllocateDataMemory(int allocated_data_size_) {
    char * new_memory = new char[allocated_data_size_];
    allocated_data = std::shared_ptr<char>(new_memory);
	allocated_data_size = allocated_data_size_;
}

void DataAllocator::FreeAllocatedMemory() {
    if (IsMemoryAllocated()) {
        allocated_data = 0;
        allocated_data_size = 0;
    }
}	
