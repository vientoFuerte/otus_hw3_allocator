#include <gtest/gtest.h>
  
#include "allocator.h"
#include "container.h"

// Базовый тест
TEST(LoggingAllocatorTest, BasicAllocation) {
    logging_allocator<int, 10> alloc;
    
    int* p = alloc.allocate(1);
    ASSERT_NE(p, nullptr);
    alloc.construct(p, 42);
    EXPECT_EQ(*p, 42);
    alloc.destroy(p);
    alloc.deallocate(p, 1);
}
