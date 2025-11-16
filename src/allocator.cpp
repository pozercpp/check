#include<allocator.h>

Allocator::Allocator(size_t size_) : size(size_) {
    if (size == 0) {
        throw std::invalid_argument("Pool size must be greater than zero");
    }
    buffer = static_cast<char*>(::operator new(size));
    if (!buffer) {
        throw std::bad_alloc();
    }
}

Allocator::~Allocator() noexcept { ::operator delete(buffer); }

void* Allocator::do_allocate(size_t bytes, size_t alignment) {
    if (bytes == 0) { return nullptr; }
    allocated_blocks.sort([](const auto& a, const auto& b) {
        return a.first < b.first;
    });
    char* start = buffer;
    char* end = buffer + size;
    for (auto it = allocated_blocks.begin(); it != allocated_blocks.end(); ++it) {
        char* gap_end = static_cast<char*>(it->first);
        if (gap_end - start >= static_cast<ptrdiff_t>(bytes)) {
            void* aligned_ptr = start;
            size_t space = gap_end - start;
            if (std::align(alignment, bytes, aligned_ptr, space)) {
                allocated_blocks.insert(it, {aligned_ptr, bytes});
                return aligned_ptr;
            }
        }
        start = static_cast<char*>(it->first) + it->second;
    }
    if (end - start >= static_cast<ptrdiff_t>(bytes)) {
        void* aligned_ptr = start;
        size_t space = end - start;
        if (std::align(alignment, bytes, aligned_ptr, space)) {
            allocated_blocks.push_back({aligned_ptr, bytes});
            return aligned_ptr;
        }
    }
    throw std::bad_alloc();
}

void Allocator::do_deallocate(void* p, size_t bytes, size_t alignment) {
    if (p == nullptr) { return; }
    auto it = std::find_if(allocated_blocks.begin(), allocated_blocks.end(),
                           [p, bytes](const auto& block) {
                               return block.first == p && block.second == bytes;
                           });
    if (it != allocated_blocks.end()) {
        allocated_blocks.erase(it);
    }
}

bool Allocator::do_is_equal(const std::pmr::memory_resource& other) const noexcept { return this == &other; }