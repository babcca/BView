#ifndef _BDATA_ALLOCATOR_H__
#define _BDATA_ALLOCATOR_H__
#include <string>
#include <memory>

/* jak ochranit pamet proti zapisu????? */
struct Memory {
public:
    Memory(std::shared_ptr<char> memory_, int size_) : memory(memory_), size(size_) { }
	Memory() : memory(0), size(0) {}
	const int GetAllocatedDataSize() const { return size; }
    std::shared_ptr<char> memory;
private:
	int size;

};


struct DataAllocator {
	DataAllocator() : allocated_data(0), allocated_data_size(0) {} 
	virtual ~DataAllocator();
	/** Copy constructor */
	void operator=(DataAllocator & data);
    //void operator=(Memory & data);
    ///** Return part of allocated data */
    //std::shared_ptr<char *> GetAllocatedMemory(int offset, int size);
	/** Return writeable pointer to allocated data */
    std::shared_ptr<char> GetAllocatedMemory() { return allocated_data; }
	/** Return size of allocated memory */
	const int GetAllocatedDataSize() const { return allocated_data_size; }
	/** Return true if memmory is allocated */
    const bool IsMemoryAllocated() const { return allocated_data.get() != 0; }
	/** Allocate memmory for data */ 
	void AllocateDataMemory(int allocated_data_size_);
	/** Free allocated memory */
	void FreeAllocatedMemory();

private:
    std::shared_ptr<char> allocated_data; /**< Pointer to allocated memory */
	int allocated_data_size; /**< Size of allocated memory */
};

#endif
