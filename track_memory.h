#ifndef TRACK_MEMORY_H_
#define TRACK_MEMORY_H_

/**
 * Implements simple memory tracking for use in C++ applications.
 * Define: TRACK_MEMORY to enable during debug and unit testing, and undef for production.
 * Define: PRINT_MEMORY_TRACKING to print memory tracking
 */

#include <cassert>
#include <cstdio>
#include <cstdlib>

#ifdef TRACK_MEMORY
#include <map>

size_t gAllocatedMemory = 0;
bool gTrackAllocation = true;
typedef std::map<void *, size_t> AllocationMap;
static AllocationMap gAllocationMapStandard;
static AllocationMap gAllocationMapArray;

/**
 * Allocates using a map to keep track of sizes.
 */
inline void *wrap_malloc(size_t size,
                         const char *file,
                         int line,
                         const char *func,
                         AllocationMap &map = gAllocationMapStandard) {

  assert(size != 0);
  void *ptr;

  if (gTrackAllocation) {
    gAllocatedMemory += size;
    ptr = malloc(size);

    gTrackAllocation = false;
    map[ptr] = size;
    gTrackAllocation = true;

#ifdef PRINT_MEMORY_TRACKING
    printf("[Malloc %s:%d:%s] Allocated mem 0x%8.8lx: %8ld (%ld)\n",
           file, line, func, (unsigned long) ptr, gAllocatedMemory, size);
#endif
  } else {
    ptr = malloc(size);
  }

  if (ptr == nullptr)
    throw std::bad_alloc();
  else
    return ptr;
}

/**
 * Deletes stuff allocated with tracked_new.
 */
inline void wrap_free(void *ptr,
                      const char *file,
                      int line,
                      const char *func,
                      AllocationMap &map = gAllocationMapStandard) {

  if (gTrackAllocation) {
    size_t size = map[ptr];
    assert(size != 0);
    gAllocatedMemory -= size;

#ifdef PRINT_MEMORY_TRACKING
    printf("[Delete %s:%d:%s] Deallocated mem 0x%8.8lx: %8ld (-%ld)\n",
           file, line, func, (unsigned long) ptr,
           gAllocatedMemory,
           size);
#endif

    gTrackAllocation = false;
    map.erase(ptr);
    gTrackAllocation = true;
  }

  free(ptr);
}

#define malloc(X) wrap_malloc(X, __FILE__, __LINE__, __FUNCTION__)
#define free(X) wrap_free(X, __FILE__, __LINE__, __FUNCTION__)

void *operator new(size_t size) noexcept(false) {
  return wrap_malloc(size, __FILE__, __LINE__, __FUNCTION__, gAllocationMapStandard);
}

void *operator new[](size_t size) noexcept(false) {
  return wrap_malloc(size, __FILE__, __LINE__, __FUNCTION__, gAllocationMapArray);
}

void operator delete(void *ptr) noexcept {
  wrap_free(ptr, __FILE__, __LINE__, __FUNCTION__, gAllocationMapStandard);
}

void operator delete[](void *ptr) noexcept {
  wrap_free(ptr, __FILE__, __LINE__, __FUNCTION__, gAllocationMapArray);
}

#endif /* TRACK_MEMORY */

#endif // TRACK_MEMORY_H_
