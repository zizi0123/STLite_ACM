#ifndef SJTU_PRIORITY_QUEUE_HPP
#define SJTU_PRIORITY_QUEUE_HPP

#include <cstddef>
#include <functional>
#include "exceptions.hpp"

namespace sjtu {

/**
 * a container like std::priority_queue which is a heap internal.
*/
    template<typename T, class Compare=std::less<T>>  //std::less是一个类，它有成员函数std::less::operator()，；返回一个bool值。left<right时返回true。
    class priority_queue {   //priority_queue的左堆实现
    private:
        struct node {
            int npt;
            T value;
            node *left_son;
            node *right_son;
            node *father;

            node(int _npt, T _value, node *_l, node *_r, node *_f) : npt(_npt), value(_value), left_son(_l),
                                                                     right_son(_r), father(_f) {}

            node() : npt(0), left_son(nullptr), right_son(nullptr), father(nullptr) {}
        };

        node *root;
        size_t ele_num;
        Compare cmp;


        void creat(node *a, node *const b) {
            if (b->left_son == nullptr && b->right_son == nullptr) return;
            if (b->left_son != nullptr) {
                if (a->left_son == nullptr) {
                    a->left_son = new node(b->left_son->npt, b->left_son->value, nullptr, nullptr, a);
                } else {
                    a->left_son->npt = b->left_son->npt;
                    a->left_son->value = b->left_son->value;
                }
                creat(a->left_son, b->left_son);
            }
            if (b->right_son != nullptr) {
                if (a->right_son == nullptr) {
                    a->right_son = new node(b->right_son->npt, b->right_son->value, nullptr, nullptr, a);
                } else {
                    a->right_son->npt = b->right_son->npt;
                    a->right_son->value = b->right_son->value;
                }
                creat(a->right_son, b->right_son);
            }
        }

        void merge_node(node *&a, node *&b) {   //默认两个指针都非空
            if (cmp(a->value, b->value)) {   //保证a是根节点
                node *temp1 = a, *dad = a->father;
                a = b;
                b = temp1;
                a->father = dad;
                b->father = nullptr;
            }

            if (a->right_son != nullptr) {
                merge_node(a->right_son, b);
            } else {
                a->right_son = b;
                b->father = a;
            }
            node *temp = a->right_son;  //维护左堆的性质
            if (a->left_son != nullptr) {   //有可能父亲节点没有左儿子
                a->npt = ((a->right_son->npt < a->left_son->npt) ? a->right_son->npt : a->left_son->npt) + 1;
                if (a->left_son->npt < a->right_son->npt) {  //交换父节点的左右儿子
                    a->right_son = a->left_son;
                    a->left_son = temp;
                }
            } else {
                a->right_son = nullptr;
                a->left_son = temp;
                a->npt = 0;
            }
        }


    public:
        /**
         * TODO constructors
         */
        priority_queue() {
            ele_num = 0;
            root = nullptr;
        }

//        explicit priority_queue(const T &ele) {  //只有一个元素的优先队列
//            ele_num = 1;
//            root = new node(0, ele, nullptr, nullptr, nullptr);
//        }

        priority_queue(const priority_queue &other) {
            ele_num = other.ele_num;
            root = new node(other.root->npt, other.root->value, nullptr, nullptr, nullptr);
            creat(root, other.root);
        }

        /**
         * TODO deconstructor
         */
        ~priority_queue() {
            clear(root);   //clear以后root会变成nullptr!!!!!!!!!
            root = nullptr;
        }

        /**
         * TODO Assignment operator
         */
        priority_queue &operator=(const priority_queue &other) {
            if (this == &other) return *this;
            ele_num = other.ele_num;
            if (root == nullptr) {
                root = new node(other.root->npt, other.root->value, nullptr, nullptr, nullptr);
            } else {
                root->npt = other.root->npt;
                root->value = other.root->value;
            }
            creat(root, other.root);
            return *this;
        }

        /**
         * get the top of the queue.
         * @return a reference of the top element.
         * throw container_is_empty if empty() returns true;
         */
        const T &top() const {
            if (ele_num == 0) throw container_is_empty();
            return root->value;
        }

        /**
         * TODO
         * push new element to the priority queue.
         */
        void push(const T &e) {
            if (ele_num == 0) {
                if (root == nullptr) {
                    root = new node(0, e, nullptr, nullptr, nullptr);
                } else {
                    root->left_son = nullptr;
                    root->right_son = nullptr;
                    root->father = nullptr;
                    root->value = e;
                    root->npt = 0;
                }
                ++ele_num;
            } else {
                node *temp = new node(0, e, nullptr, nullptr, nullptr);
                try {
                    merge_node(root, temp);
                    ++ele_num;
                } catch (...) {
                    delete temp;
                    throw;
                }
            }
        }

        /**
         * TODO
         * delete the top element.
         * throw container_is_empty if empty() returns true;
         */
        void pop() {
            if (ele_num == 0) throw container_is_empty();
            node *temp = root;
            if (root->right_son != nullptr) {
                root->left_son->father = nullptr;
                root->right_son->father = nullptr;
                merge_node(root->left_son, root->right_son);
                root = root->left_son;
            } else if (root->left_son != nullptr) {
                root = root->left_son;
                root->father = nullptr;
            }
            delete temp;   //不把根节点删掉
            --ele_num;
            if (ele_num == 0) root = nullptr;
        }

        /**
         * return the number of the elements.
         */
        size_t size() const {
            return ele_num;
        }

        /**
         * check if the container has at least an element.
         * @return true if it is empty, false if it has at least an element.
         */
        bool empty() const {
            return ele_num == 0;
        }

        void clear(node *a) {    //typename是告诉编译器priority_queue<T>::node是一个类型 保证root不会变成nullptr
            if (a == nullptr) return;
            if (a->left_son != nullptr) clear(a->left_son);
            if (a->right_son != nullptr) clear(a->right_son);
            delete a;
            a = nullptr;
        }

        /**
         * merge two priority_queues with at least O(logn) complexity.
         * clear the other priority_queue.
         */
        void merge(priority_queue &other) {
            merge_node(root, other.root);
            ele_num += other.ele_num;
            other.root = nullptr;
            other.ele_num = 0;
        }


    };


}

#endif
