#ifndef SJTU_VECTOR_HPP
#define SJTU_VECTOR_HPP

#include "exceptions.hpp"

#include <climits>
#include <cstddef>
#include <iostream>

namespace sjtu {
/**
 * a data container like std::vector
 * store data in a successive memory and support random access.
 */
    template<typename T>
    class vector {

    public:
        /**
         * TODO
         * a type for actions of the elements of a vector, and you should write
         *   a class named const_iterator with same interfaces.
         */
        /**
         * you can see RandomAccessIterator at CppReference for help.
         */
        class const_iterator;

        class iterator {
            // The following code is written for the C++ type_traits library.
            // Type traits is a C++ feature for describing certain properties of a type.
            // For instance, for an iterator, iterator::value_type is the type that the
            // iterator points to.
            // STL algorithms and containers may use these type_traits (e.g. the following
            // typedef) to work properly. In particular, without the following code,
            // @code{std::sort(iter, iter1);} would not compile.
            // See these websites for more information:
            // https://en.cppreference.com/w/cpp/header/type_traits
            // About value_type: https://blog.csdn.net/u014299153/article/details/72419713
            // About iterator_category: https://en.cppreference.com/w/cpp/iterator
        public:
            using difference_type = std::ptrdiff_t;
            using value_type = T;
            using pointer = T *;
            using reference = T &;
            using iterator_category = std::output_iterator_tag;
            pointer ptr;
            vector<value_type> *vec_ptr;

        public:
            /**
             * return a new iterator which pointer n-next elements
             * as well as operator-
             */
            iterator() : ptr(nullptr), vec_ptr(nullptr) {}

            iterator(pointer _ptr, vector<value_type> *_vec_ptr) : ptr(_ptr), vec_ptr(_vec_ptr) {}

            iterator operator+(const int &n) const {  //todo 迭代器越界是否要抛出错误
                iterator new_iter(ptr + n, vec_ptr);
                return new_iter;
            }

            iterator operator-(const int &n) const {
                iterator new_iter(ptr - n, vec_ptr);
                return new_iter;
            }

            // return the distance between two iterators,
            // if these two iterators point to different vectors, throw invalid_iterator.
            int operator-(const iterator &rhs) const {
                if (vec_ptr != rhs.vec_ptr) throw invalid_iterator();
                return ptr - rhs.ptr;
            }

            iterator &operator+=(const int &n) {
                ptr += n;
                return *this;
            }

            iterator &operator-=(const int &n) {
                ptr -= n;
                return *this;
            }

            /**
             * TODO iter++
             */
            iterator operator++(int) {
                iterator new_iter(ptr, vec_ptr);
                ptr++;
                return new_iter;
            }

            /**
             * TODO ++iter
             */
            iterator &operator++() {
                ptr++;
                return *this;
            }

            /**
             * TODO iter--
             */
            iterator operator--(int) {
                iterator new_iter(ptr, vec_ptr);
                ptr--;
                return new_iter;
            }

            /**
             * TODO --iter
             */
            iterator &operator--() {
                ptr--;
                return *this;
            }

            /**
             * TODO *it
             */
            T &operator*() const {
                return *ptr;
            }

            /**
             * a operator to check whether two iterators are same (pointing to the same memory address).
             */
            bool operator==(const iterator &rhs) const {
                return ptr == rhs.ptr;
            }

            bool operator==(const const_iterator &rhs) const {
                return ptr == rhs.ptr;
            }

            /**
             * some other operator for iterator.
             */
            bool operator!=(const iterator &rhs) const {
                return ptr !=rhs.ptr;
            }

            bool operator!=(const const_iterator &rhs) const {
                return ptr != rhs.ptr;
            }
        };

        /**
         * TODO
         * has same function as iterator, just for a const object.
         */
        class const_iterator {
        public:
            using difference_type = std::ptrdiff_t;
            using value_type = T;
            using pointer = T *;
            using reference = T &;
            using iterator_category = std::output_iterator_tag;
            pointer ptr;
            const vector<value_type> *vec_ptr;

        public:
            const_iterator() : ptr(nullptr), vec_ptr(nullptr) {}

            const_iterator(pointer _ptr, const vector<value_type> *_vec_ptr) : ptr(_ptr), vec_ptr(_vec_ptr) {}

            const_iterator operator+(const int &n) const {  //todo 迭代器越界是否要抛出错误
                const_iterator new_iter(ptr + n, vec_ptr);
                return new_iter;
            }

            const_iterator operator-(const int &n) const {
                const_iterator new_iter(ptr - n, vec_ptr);
                return new_iter;
            }

            // return the distance between two iterators,
            // if these two iterators point to different vectors, throw invaild_iterator.
            int operator-(const iterator &rhs) const {
                if (vec_ptr != rhs.vec_ptr) throw invalid_iterator();
                return ptr - rhs.ptr;
            }

            const_iterator &operator+=(const int &n) {
                ptr += n;
                return *this;
            }

            const_iterator &operator-=(const int &n) {
                ptr -= n;
                return *this;
            }

            /**
             * TODO iter++
             */
            const_iterator operator++(int) {
                const_iterator new_iter(ptr, vec_ptr);
                ptr++;
                return new_iter;
            }

            /**
             * TODO ++iter
             */
            const_iterator &operator++() {
                ptr++;
                return *this;
            }

            /**
             * TODO iter--
             */
            const_iterator operator--(int) {
                const_iterator new_iter(ptr, vec_ptr);
                ptr--;
                return new_iter;
            }

            /**
             * TODO --iter
             */
            const_iterator &operator--() {
                ptr--;
                return *this;
            }

            /**
             * TODO *it
             */
            T &operator*() const {
                return *ptr;
            }

            /**
             * a operator to check whether two iterators are same (pointing to the same memory address).
             */
            bool operator==(const iterator &rhs) const {
                return ptr == rhs.ptr;
            }

            bool operator==(const const_iterator &rhs) const {
                return ptr == rhs.ptr;
            }

            /**
             * some other operator for iterator.
             */
            bool operator!=(const iterator &rhs) const {
                return ptr != rhs.ptr;
            }

            bool operator!=(const const_iterator &rhs) const {
                return ptr != rhs.ptr;
            }
        };

        /**
         * TODO Constructs
         * At least two: default constructor, copy constructor
         */
        vector() {
            maxsize = 300;
            bbegin = alloc.allocate(300);
            ssize = 0;
        }

        vector(const vector &other) {
            if (other.maxsize > 0) {
                bbegin = alloc.allocate(other.maxsize);
                for (size_t i = 0; i < other.ssize; ++i) {
                    alloc.construct(bbegin+i,*(other.bbegin+i));
                }
            } else {
                bbegin = nullptr;
            }
            maxsize = other.maxsize;
            ssize = other.ssize;
        }

        /**
         * TODO Destructor
         */
        ~vector() {
            for(int i=0;i<ssize;++i) alloc.destroy(bbegin+i);
            alloc.deallocate(bbegin, maxsize);
            maxsize = 0;
            ssize = 0;
            bbegin = nullptr;
        }

        /**
         * TODO Assignment operator
         */
        vector &operator=(const vector &other) {
            if (this == &other) return *this;
            for(int i=0;i<ssize;++i) alloc.destroy(bbegin+i);
            alloc.deallocate(bbegin,maxsize);
            if (other.maxsize > 0) {
                bbegin = alloc.allocate(other.maxsize);
                for (size_t i = 0; i < other.ssize; ++i) {
                   alloc.construct(bbegin+i,*(other.bbegin+i));
                }
            } else {
                bbegin = nullptr;
            }
            maxsize = other.maxsize;
            ssize = other.ssize;
            return *this;
        }

        /**
         * assigns specified element with bounds checking
         * throw index_out_of_bound if pos is not in [0, size)
         */
        T &at(const size_t &pos) {
            if (pos >= 0 && pos < ssize) {
                return *(bbegin + pos);
            } else {
                throw index_out_of_bound();
            }
        }

        const T &at(const size_t &pos) const {
            if (pos >= 0 && pos < ssize) {
                return *(bbegin + pos);
            } else {
                throw index_out_of_bound();
            }
        }

        /**
         * assigns specified element with bounds checking
         * throw index_out_of_bound if pos is not in [0, size)
         * !!! Pay attentions
         *   In STL this operator does not check the boundary but I want you to do.
         */
        T &operator[](const size_t &pos) {
            if (pos >= 0 && pos < ssize) {
                return *(bbegin + pos);
            } else {
                throw index_out_of_bound();
            }
        }

        const T &operator[](const size_t &pos) const {
            if (pos >= 0 && pos < ssize) {
                return *(bbegin + pos);
            } else {
                throw index_out_of_bound();
            }
        }

        /**
         * access the first element.
         * throw container_is_empty if size == 0
         */
        const T &front() const {
            if (ssize>0) {
                return *bbegin;
            } else {
                throw container_is_empty();
            }
        }

        /**
         * access the last element.
         * throw container_is_empty if size == 0
         */
        const T &back() const {
            if (ssize>0) {
                return *(bbegin + ssize - 1);
            } else {
                throw container_is_empty();
            }
        }

        /**
         * returns an iterator to the beginning.
         */
        iterator begin() {
            return iterator(bbegin, this);
        }

        const_iterator cbegin() const {
            return const_iterator(bbegin, this);
        }

        /**
         * returns an iterator to the end.
         */
        iterator end() {
            return iterator(bbegin + ssize , this);
        }

        const_iterator cend() const {
            return const_iterator(bbegin + ssize , this);
        }

        /**
         * checks whether the container is empty
         */
        bool empty() const {
            return ssize == 0;
        }

        /**
         * returns the number of elements
         */
        size_t size() const {
            return ssize;
        }

        /**
         * clears the contents
         */
        void clear() {
            if (ssize > 0) {
                ssize = 0;
            }
        }

        /**
         * inserts value before pos
         * returns an iterator pointing to the inserted value.
         */
        iterator insert(iterator pos, const T &value) {   //注意：在doublespace以后，begin()与pos不再是指向同一个空间的迭代器，pos没有意义。
            size_t ind=pos-begin();
            if(ind>ssize) throw index_out_of_bound();
            if(ssize==maxsize) double_space();
            alloc.construct(bbegin+ssize,*(bbegin+ssize-1));
            for(int i=ssize-1;i>=ind+1;--i) *(bbegin+i)=*(bbegin+i-1);
            *(bbegin+ind)=value;
            ssize++;
            iterator iter(bbegin+ind,this);
            return iter;
        }

        /**
         * inserts value at index ind.
         * after inserting, this->at(ind) == value
         * returns an iterator pointing to the inserted value.
         * throw index_out_of_bound if ind > size (in this situation ind can be size because after inserting the size will increase 1.)
         */
        iterator insert(const size_t &ind, const T &value) {
            if(ind>ssize) throw index_out_of_bound();
            if(ssize==maxsize) double_space();
            alloc.construct(bbegin+ssize,*(bbegin+ssize-1));
            for(int i=ssize-1;i>=ind+1;--i) *(bbegin+i)=*(bbegin+i-1);
            *(bbegin+ind)=value;
            ssize++;
            iterator iter(bbegin+ind,this);
            return iter;
        }

        /**
         * removes the element at pos.
         * return an iterator pointing to the following element.
         * If the iterator pos refers the last element, the end() iterator is returned.
         */
        iterator erase(iterator pos) {
            for(int i=pos-begin();i<ssize-1;++i) *(bbegin+i)=*(bbegin+i+1);
            alloc.destroy(bbegin+ssize-1);
            ssize--;
            if(pos-begin()==ssize) return end();
            return pos;
        }

        /**
         * removes the element with index ind.
         * return an iterator pointing to the following element.
         * throw index_out_of_bound if ind >= size
         */
        iterator erase(const size_t &ind) {
            if(ind>=ssize) throw index_out_of_bound();
            for(int i=ind;i<ssize-1;++i) *(bbegin+i)=*(bbegin+i+1);
            alloc.destroy(bbegin+ssize-1);
            ssize--;
            if(ind==ssize) return end();
            return iterator(bbegin+ind,this);
        }

        /**
         * adds an element to the end.
         */
        void push_back(const T &value) {
            if (ssize == maxsize) {
                double_space();
            }
            ++ssize;
            alloc.construct(bbegin + ssize - 1,value) ;
        }

        /**
         * remove the last element from the end.
         * throw container_is_empty if size() == 0
         */
        void pop_back() {
            if (ssize == 0) throw container_is_empty();
            alloc.destroy(bbegin+ssize-1);
            ssize--;
        }

    private:
        T *bbegin;
        size_t ssize;
        size_t maxsize;
        std::allocator<T> alloc;   //一个属于vector的分配器对象
        void double_space() {
//            static int cnt=0;
            T *temp = bbegin;
            bbegin = alloc.allocate(2 * maxsize);
            for (int i = 0; i < ssize; ++i) alloc.construct(bbegin+i,*(temp+i));
            for (int i = 0; i < ssize; ++i) alloc.destroy(temp+i);
            alloc.deallocate(temp, maxsize);
            maxsize *= 2;
//            cnt++;
//            std::cout<<"cnt:"<<cnt<<'\n';
        }
    };
    template class vector<int>;


}

#endif
