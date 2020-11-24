#pragma once

#include <exception>

#include <iterator>

template < class V, class T >
    class MyIterator: public std::iterator<std::random_access_iterator_tag, T> {
        T * data_;
    public:

        MyIterator(T * data): data_(data) {}

        T & operator * () {
            return *data_;
        }

        MyIterator < V, T > & operator += (size_t add) {
            data_ += add;
            return *this;
        }

        MyIterator < V, T > operator + (size_t add) const {
            return data_ + add;
        }

        MyIterator < V, T > & operator -= (size_t sub) {
            data_ -= sub;
            return *this;
        }

        MyIterator < V, T > operator - (size_t sub) const {
            return data_ - sub;
        }

        bool operator < (const MyIterator < V, T > & other) {
            return data_ < other.data_;
        }
        bool operator > (const MyIterator < V, T > & other) {
            return data_ > other.data_;
        }

        bool operator == (const MyIterator < V, T > & other) {
            return data_ == other.data_;
        }

        bool operator != (const MyIterator < V, T > & other) {
            return !(data_ == other.data_);
        }

        bool operator <= (const MyIterator < V, T > & other) {
            return ( * this == other) || ( * this < other);
        }

        bool operator >= (const MyIterator < V, T > & other) {
            return ( * this == other) || ( * this > other);
        }

        MyIterator < V, T > & operator++() {
            data_++;
            return *this;
        }

        MyIterator < V, T > & operator--() {
            data_--;
            return *this;
        }

        T & operator[](size_t idx) {
            return data_[idx];
        }
    };

template < class V, class T >
    class MyReverseIterator {
        T * data_;
    public:

        MyReverseIterator(T * data): data_(data) {}

        T & operator * () {
            return *data_;
        }

        MyReverseIterator < V, T > & operator += (size_t add) {
            data_ -= add;
            return *this;
        }

        MyReverseIterator < V, T > operator + (size_t add) const {
            return data_ - add;
        }

        MyReverseIterator < V, T > & operator -= (size_t sub) {
            data_ += sub;
            return *this;
        }

        MyReverseIterator < V, T > operator - (size_t sub) const {
            return data_ + sub;
        }

        bool operator < (const MyReverseIterator < V, T > & other) {
            return data_ < other.data_;
        }
        bool operator > (const MyReverseIterator < V, T > & other) {
            return data_ > other.data_;
        }

        bool operator == (const MyReverseIterator < V, T > & other) {
            return data_ == other.data_;
        }

        bool operator != (const MyReverseIterator < V, T > & other) {
            return !(data_ == other.data_);
        }

        bool operator <= (const MyReverseIterator < V, T > & other) {
            return ( * this == other) || ( * this < other);
        }

        bool operator >= (const MyReverseIterator < V, T > & other) {
            return ( * this == other) || ( * this > other);
        }

        MyReverseIterator < V, T > & operator++() {
            data_--;
            return *this;
        }

        MyReverseIterator < V, T > & operator--() {
            data_++;
            return *this;
        }

        T & operator[](size_t idx) {
            return data_[idx];
        }

    };

template < class T >
    class MyAllocator {
        public:
            using value_type = T;
        using pointer = T * ;
        using size_type = size_t;
        pointer allocate(size_type count) {
            return new value_type[count];
        }
        void deallocate(pointer ptr) {
            delete[] ptr;
            return;
        }
    };

template < class T, class Alloc = MyAllocator < T >>
    class Vector {
    public:
        using size_type = size_t;
        using value_type = T;
        using reference = T & ;
        using const_reference =
            const T & ;
    private:
        size_type size_;
        size_type capacity_;
        T * data_ = nullptr;
        Alloc alloc_;
        public:

        Vector(size_type count = 0): size_(count) {
            capacity_ = count ? 1 : 0;
            while (capacity_ < count) {
                capacity_ *= 2;
            }
            if (capacity_) {
                data_ = alloc_.allocate(capacity_);
            } else {
                data_ = nullptr;
            }
        }

        Vector(size_type count,
            const T & value) {
            capacity_ = count ? 1 : 0;
            while (capacity_ < count) {
                capacity_ *= 2;
            }
            size_ = count;
            data_ = alloc_.allocate(capacity_);
            for (size_t i = 0; i < count; i++) {
                data_[i] = value;
            }
        }

        Vector(const Vector & copied) {
            size_ = copied.size_;
            capacity_ = copied.capacity_;
            data_ = alloc_.allocate(capacity_);
            for (size_t i = 0; i < size_; i++) {
                data_[i] = copied.data_[i];
            }
        }

        Vector < T, Alloc > & operator = (const Vector & copied) {
            if (this == & copied) {
                return *this;
            }
            size_ = copied.size_;
            capacity_ = copied.capacity_;
            T * data = alloc_.allocate(capacity_);
            alloc_.deallocate(data_);
            data_ = data;
            for (size_t i = 0; i < size_; i++) {
                data_[i] = copied.data_[i];
            }
            return *this;
        }

        Vector(Vector && moved) {
            size_ = moved.size_;
            capacity_ = moved.capacity_;
            data_ = moved.data_;
            moved.data_ = nullptr;
            moved.size_ = 0;
            moved.capacity_ = 0;
        }

        Vector & operator = (Vector && moved) {
                if (this == & moved) {
                    return *this;
                }
                size_ = std::move(moved.size_);
                capacity_ = std::move(moved.capacity_);
                alloc_.deallocate(data_);
                data_ = moved.data_;
                moved.data_ = nullptr;
                moved.size_ = 0;
                moved.capacity_ = 0;
                return *this;
            }

        ~Vector() {
            if (data_ != nullptr) {
                alloc_.deallocate(data_);
            }
            size_ = 0;
            capacity_ = 0;
        }

        T & operator[](size_type index) {
            if (index >= 0 && index < size_) {
                return data_[index];
            }
            throw std::invalid_argument("Error");
        }

        const T & operator[](size_type index) const {
            if (index >= 0 && index < size_) {
                return data_[index];
            }
            throw std::invalid_argument("Error");
        }

        void push_back(const T & value) {
            if (size_ + 1 > capacity_) {
                size_type capacity = capacity_ ? capacity_ * 2 : 1;
                T * data = alloc_.allocate(capacity);
                for (size_t i = 0; i < size_; i++) {
                    data_[i] = data[i];
                }
                alloc_.deallocate(data_);
                data_ = data;
                capacity_ = capacity;
            }
            data_[size_] = value;
            size_++;
        }
        
        void pop_back() {
            if (!empty()) {
                size_--;
            } else {
                throw std::invalid_argument("Error");
            }
        }
        
        template < class...Args >
            void emplace_back(Args && ...args) {
                return this -> push_back(T(std::forward < Args > (args)...));
            }

        bool empty() const noexcept {
            if (size_) {
                return false;
            }
            return true;
        }

        size_type size() const noexcept {
            return size_;
        }

        void clear() noexcept {
            size_ = 0;
        }

        MyIterator < Vector < T, Alloc > , T > begin() noexcept {
            return MyIterator < Vector < T, Alloc > , T > (data_);
        }

        MyReverseIterator < Vector < T, Alloc > , T > rbegin() noexcept {
            return MyReverseIterator < Vector < T, Alloc > , T > (data_ + size_ - 1);
        }

        MyIterator < Vector < T, Alloc > , T > end() noexcept {
            return MyIterator < Vector < T, Alloc > , T > (data_ + size_);
        }

        MyReverseIterator < Vector < T, Alloc > , T > rend() noexcept {
            return MyReverseIterator < Vector < T, Alloc > , T > (data_);
        }

        void resize(size_type count) {
            size_type capacity = count ? 1 : 0;
            while (capacity < count) {
                capacity *= 2;
            }
            T * data = alloc_.allocate(capacity);
            size_t min_ = count < size_ ? count : size_;
            for (size_t i = 0; i < min_; i++) {
                data[i] = data_[i];
            }
            alloc_.deallocate(data_);
            data_ = data;
            size_ = count;
            capacity_ = capacity;
        }

        void reserve(size_type count) {
            if (count < size_) {
                throw std::invalid_argument("Error");
            }
            T * data = alloc_.allocate(count);
            for (size_t i = 0; i < size_; i++) {
                data[i] = data_[i];
            }
            alloc_.deallocate(data_);
            capacity_ = count;
            data_ = data;
        }

        size_type capacity() const noexcept {
            return capacity_;
        }
    };