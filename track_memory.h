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
bool gTrackAllocation = true; /* IMPORTANT: set true when your app starts */
typedef std::map<void *, size_t> AllocationMap;
static AllocationMap gAllocationMapStandard;
static AllocationMap gAllocationMapArray;

/**
 * Allocates using a map to keep track of sizes.
 */
inline void *tracked_new(size_t size, AllocationMap &map) noexcept(false) {
  assert(size != 0);
  void *ptr;

  if (gTrackAllocation) {
    gAllocatedMemory += size;
    ptr = malloc(size);

    gTrackAllocation = false;
    map[ptr] = size;
    gTrackAllocation = true;

#ifdef PRINT_MEMORY_TRACKING
    printf("mem 0x%8.8lx: %8ld (+%ld)\n", (unsigned long) ptr, gAllocatedMemory, size);
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
inline void tracked_delete(void *ptr, AllocationMap &map) noexcept {
  if (gTrackAllocation) {
    size_t size = map[ptr];
    assert(size != 0);
    gAllocatedMemory -= size;

#ifdef PRINT_MEMORY_TRACKING
    printf("mem 0x%8.8lx: %8ld (-%ld)\n", (unsigned long) ptr, gAllocatedMemory, size);
#endif

    gTrackAllocation = false;
    map.erase(ptr);
    gTrackAllocation = true;
  }

  free(ptr);
}

void *operator new(size_t size) noexcept(false) {
  return tracked_new(size, gAllocationMapStandard);
}

void *operator new[](size_t size) noexcept(false) {
  return tracked_new(size, gAllocationMapArray);
}

void operator delete(void *ptr) noexcept {
  tracked_delete(ptr, gAllocationMapStandard);
}

void operator delete[](void *ptr) noexcept {
  tracked_delete(ptr, gAllocationMapArray);
}

#endif /* TRACK_MEMORY */

#endif // TRACK_MEMORY_H_
