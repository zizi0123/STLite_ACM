/**
 * implement a container like std::map
 */
#ifndef SJTU_MAP_HPP
#define SJTU_MAP_HPP

// only for std::less<T>
#include <functional>
#include <cstddef>
#include "utility.hpp"
#include "exceptions.hpp"

namespace sjtu {

    template<class Key, class T, class Compare = std::less<Key>>
    class map {

    public:
        /**
         * the internal type of data.
         * it should have a default constructor, a copy constructor.
         * You can use sjtu::map as value_type by typedef.
         */
        typedef pair<const Key, T> value_type;

        struct node {
            value_type data;
            int height;
            node *lson;
            node *rson;
            node *dad;

            //由于没有Key的默认构造函数，node的默认构造函数不应该被使用到。

            node(value_type _data, int _h, node *_l, node *_r, node *_d) : data(_data), height(_h), lson(_l), rson(_r),
                                                                           dad(_d) {};
        };

        /**
         * see BidirectionalIterator at CppReference for help.
         *
         * if there is anything wrong throw invalid_iterator.
         *     like it = map.begin(); --it;
         *       or it = map.end(); ++end();
         */
        class const_iterator;

        class iterator {

        public:
            node *ptr = nullptr;
            map<Key, T, Compare> *this_map;
            bool if_end; //表示是否是end()

            iterator() {
                ptr = nullptr;
                this_map = nullptr;
                if_end = false;
            }

            iterator(node *p, map<Key, T, Compare> *t, bool b) : ptr(p), this_map(t), if_end(b) {}

            iterator(const iterator &other) {
                ptr = other.ptr;
                this_map = other.this_map;
                if_end = other.if_end;
            }

            /**
             * TODO iter++
             */
            iterator operator++(int) {
                iterator iter(*this);
                if (if_end) throw invalid_iterator();
                if (ptr->rson != nullptr) {  //先找右子树中最小的那个
                    ptr = ptr->rson;
                    while (ptr->lson != nullptr) ptr = ptr->lson;
                } else {  //没有右子树
                    if (ptr->dad == nullptr) { //已经是最大的节点了
                        if_end = true;  //变为迭代器end()
                        ptr = nullptr;
                    } else if (ptr == ptr->dad->rson) {  //是父节点的右儿子
                        while (ptr->dad != nullptr && ptr == ptr->dad->rson) {
                            ptr = ptr->dad;
                        }
                        if (ptr->dad == nullptr) { //已经是最大的节点了
                            if_end = true;
                            ptr = nullptr;
                        } else {
                            ptr = ptr->dad;
                        }
                    } else {
                        ptr = ptr->dad;
                    }
                }
                return iter;
            }

            /**
             * TODO ++iter
             */
            iterator &operator++() {
                if (if_end) throw invalid_iterator();
                if (ptr->rson != nullptr) {  //先找右子树中最小的那个
                    ptr = ptr->rson;
                    while (ptr->lson != nullptr) ptr = ptr->lson;
                } else {  //没有右子树
                    if (ptr->dad == nullptr) { //已经是最大的节点了
                        if_end = true;  //变为迭代器end()
                        ptr = nullptr;
                    } else if (ptr == ptr->dad->rson) {  //是父节点的右儿子
                        while (ptr->dad != nullptr && ptr == ptr->dad->rson) {
                            ptr = ptr->dad;
                        }
                        if (ptr->dad == nullptr) { //已经是最大的节点了
                            if_end = true;
                            ptr = nullptr;
                        } else {
                            ptr = ptr->dad;
                        }
                    } else {
                        ptr = ptr->dad;
                    }
                }
                return *this;
            }


            /**
             * TODO iter--
             */

            iterator operator--(int) {
                iterator iter(*this);
                if (if_end) {  //是end 指针
                    ptr = this_map->root;
                    if(ptr == nullptr) throw invalid_iterator();
                    while (ptr->rson != nullptr) ptr = ptr->rson;
                    if_end = false; //不再是end迭代器了
                    return iter;
                }
                if (ptr->lson == nullptr){
                    if(ptr->dad == nullptr) {
                        throw invalid_iterator(); //说明为迭代器begin;
                    }else if(ptr == ptr->dad->lson){
                        node* temp = ptr;
                        while(temp->dad != nullptr && temp == temp->dad->lson){
                            temp = temp->dad;
                        }
                        if(temp->dad == nullptr){
                            throw invalid_iterator(); //说明为迭代器begin;
                        }
                    }
                }
                if(ptr->lson!= nullptr){ //找到左子树中最大的元素
                    ptr = ptr->lson;
                    while (ptr->rson != nullptr) ptr = ptr->rson;
                }else if (ptr == ptr->dad->rson) {  //已经排除了begin迭代器，保证了肯定有父节点
                    ptr = ptr->dad;
                }else{
                    while(ptr == ptr->dad->lson){
                        ptr = ptr->dad;
                    }
                    ptr = ptr-> dad;
                }
                return iter;
            }

            /**
             * TODO --iter
             */
            iterator &operator--() {
                if (if_end) {  //是end 指针
                    ptr = this_map->root;
                    if(ptr == nullptr) throw invalid_iterator();
                    while (ptr->rson != nullptr) ptr = ptr->rson;
                    if_end = false; //不再是end迭代器了
                    return *this;
                }
                if (ptr->lson == nullptr){
                    if(ptr->dad == nullptr) {
                        throw invalid_iterator(); //说明为迭代器begin;
                    }else if(ptr == ptr->dad->lson){
                        node* temp = ptr;
                        while(temp->dad != nullptr && temp == temp->dad->lson){
                            temp = temp->dad;
                        }
                        if(temp->dad == nullptr){
                            throw invalid_iterator(); //说明为迭代器begin;
                        }
                    }
                }
                if(ptr->lson!= nullptr){ //找到左子树中最大的元素
                    ptr = ptr->lson;
                    while (ptr->rson != nullptr) ptr = ptr->rson;
                }else if (ptr == ptr->dad->rson) {  //已经排除了begin迭代器，保证了肯定有父节点
                    ptr = ptr->dad;
                }else{
                    while(ptr == ptr->dad->lson){
                        ptr = ptr->dad;
                    }
                    ptr = ptr-> dad;
                }
                return *this;
            }

            /**
             * a operator to check whether two iterators are same (pointing to the same memory).
             */
            value_type &operator*() const {
                return ptr->data;
            }

            bool operator==(const iterator &rhs) const {
                if (this_map == rhs.this_map && ptr == rhs.ptr && if_end == rhs.if_end) return true;
                return false;
            }

            bool operator==(const const_iterator &rhs) const {
                if (this_map == rhs.this_map && ptr == rhs.ptr && if_end == rhs.if_end) return true;
                return false;
            }

            /**
             * some other operator for iterator.
             */
            bool operator!=(const iterator &rhs) const {
                if (*this == rhs) return false;
                return true;
            }

            bool operator!=(const const_iterator &rhs) const {
                if (*this == rhs) return false;
                return true;
            }

            /**
             * for the support of it->first.
             * See <http://kelvinh.github.io/blog/2013/11/20/overloading-of-member-access-operator-dash-greater-than-symbol-in-cpp/> for help.
             */
            value_type *operator->() const noexcept {
                return &(ptr->data);
            }
        };

        class const_iterator {
            // it should have similar member method as iterator.
            //  and it should be able to construct from an iterator.

        public:
            node const *ptr;
            map const *this_map;
            bool if_end;

            const_iterator() {
                ptr = nullptr;
                this_map = nullptr;
                if_end = false;
            }

            const_iterator(node const *p, map const *t, bool b) : ptr(p), this_map(t), if_end(b) {}

            const_iterator(const const_iterator &other) : ptr(other.ptr), this_map(other.this_map),
                                                          if_end(other.if_end) {}

            const_iterator(const iterator &other) : ptr(other.ptr), this_map(other.this_map), if_end(other.if_end) {}

            const_iterator operator++(int) {
                if (if_end) throw invalid_iterator();
                const_iterator iter(*this);
                if (ptr->rson != nullptr) {  //先找右子树中最小的那个
                    ptr = ptr->rson;
                    while (ptr->lson != nullptr) ptr = ptr->lson;
                } else {  //没有右子树
                    if (ptr->dad == nullptr) {
                        if_end = true;  //变为迭代器end()
                        ptr = nullptr;
                    } else if (ptr == ptr->dad->rson) {
                        while (ptr->dad != nullptr && ptr == ptr->dad->rson) {
                            ptr = ptr->dad;
                        }
                        if (ptr->dad == nullptr) {
                            if_end = true;
                            ptr = nullptr;
                        } else {
                            ptr = ptr->dad;
                        }
                    } else {
                        ptr = ptr->dad;
                    }
                }
                return iter;
            }

            /**
             * TODO ++iter
             */
            const_iterator &operator++() {
                if (if_end) throw invalid_iterator();
                if (ptr->rson != nullptr) {  //先找右子树中最小的那个
                    ptr = ptr->rson;
                    while (ptr->lson != nullptr) ptr = ptr->lson;
                } else {  //没有右子树
                    if (ptr->dad == nullptr) { //已经是最大的节点了
                        if_end = true;  //变为迭代器end()
                        ptr = nullptr;
                    } else if (ptr == ptr->dad->rson) {  //是父节点的右儿子
                        while (ptr->dad != nullptr && ptr == ptr->dad->rson) {
                            ptr = ptr->dad;
                        }
                        if (ptr->dad == nullptr) { //已经是最大的节点了
                            if_end = true;
                            ptr = nullptr;
                        } else {
                            ptr = ptr->dad;
                        }
                    } else {
                        ptr = ptr->dad;
                    }
                }
                return *this;
            }


            /**
             * TODO iter--
             */

            const_iterator operator--(int) {
                const_iterator iter(*this);
                if (if_end) {  //是end 指针
                    ptr = this_map->root;
                    if(ptr == nullptr) throw invalid_iterator();
                    while (ptr->rson != nullptr) ptr = ptr->rson;
                    if_end = false; //不再是end迭代器了
                    return iter;
                }
                if (ptr->lson == nullptr){
                    if(ptr->dad == nullptr) {
                        throw invalid_iterator(); //说明为迭代器begin;
                    }else if(ptr == ptr->dad->lson){
                        const node* temp = ptr;
                        while(temp->dad != nullptr && temp == temp->dad->lson){
                            temp = temp->dad;
                        }
                        if(temp->dad == nullptr){
                            throw invalid_iterator(); //说明为迭代器begin;
                        }
                    }
                }
                if(ptr->lson!= nullptr){ //找到左子树中最大的元素
                    ptr = ptr->lson;
                    while (ptr->rson != nullptr) ptr = ptr->rson;
                }else if (ptr == ptr->dad->rson) {  //已经排除了begin迭代器，保证了肯定有父节点
                    ptr = ptr->dad;
                }else{
                    while(ptr == ptr->dad->lson){
                        ptr = ptr->dad;
                    }
                    ptr = ptr-> dad;
                }
                return iter;
            }

            /**
             * TODO --iter
             */
            const_iterator &operator--() {
                if (if_end) {  //是end 指针
                    ptr = this_map->root;
                    if(ptr == nullptr) throw invalid_iterator();
                    while (ptr->rson != nullptr) ptr = ptr->rson;
                    if_end = false; //不再是end迭代器了
                    return *this;
                }
                if (ptr->lson == nullptr){
                    if(ptr->dad == nullptr) {
                        throw invalid_iterator(); //说明为迭代器begin;
                    }else if(ptr == ptr->dad->lson){
                        const node* temp = ptr;
                        while(temp->dad != nullptr && temp == temp->dad->lson){
                            temp = temp->dad;
                        }
                        if(temp->dad == nullptr){
                            throw invalid_iterator(); //说明为迭代器begin;
                        }
                    }
                }
                if(ptr->lson!= nullptr){ //找到左子树中最大的元素
                    ptr = ptr->lson;
                    while (ptr->rson != nullptr) ptr = ptr->rson;
                }else if (ptr == ptr->dad->rson) {  //已经排除了begin迭代器，保证了肯定有父节点
                    ptr = ptr->dad;
                }else{
                    while(ptr == ptr->dad->lson){
                        ptr = ptr->dad;
                    }
                    ptr = ptr-> dad;
                }
                return *this;
            }

            /**
             * a operator to check whether two iterators are same (pointing to the same memory).
             */
            const value_type &operator*() const {
                return ptr->data;
            }

            bool operator==(const const_iterator &rhs) const {
                if (this_map == rhs.this_map && ptr == rhs.ptr && if_end == rhs.if_end) return true;
                return false;
            }

            bool operator==(const iterator &rhs) const {
                if (this_map == rhs.this_map && ptr == rhs.ptr && if_end == rhs.if_end) return true;
                return false;
            }

            /**
             * some other operator for iterator.
             */
            bool operator!=(const const_iterator &rhs) const {
                if (*this == rhs) return false;
                return true;
            }

            bool operator!=(const iterator &rhs) const {
                if (*this == rhs) return false;
                return true;
            }

            /**
             * for the support of it->first.
             * See <http://kelvinh.github.io/blog/2013/11/20/overloading-of-member-access-operator-dash-greater-than-symbol-in-cpp/> for help.
             */
            const value_type *operator->() const noexcept {
                return &(ptr->data);
            }
        };


        map() {
            root = nullptr;
            ele_size = 0;
        }

        map(const map &other) {
            root = nullptr;
            creat(root, other.root);
            ele_size = other.ele_size;
        }

        map &operator=(const map &other) {
            if (this == &other) return *this;
            clear(root);
            root = nullptr;
            creat(root, other.root);
            ele_size = other.ele_size;
            return *this;
        }

        ~map() {
            clear(root);
        }

        /**
         * TODO
         * access specified element with bounds checking
         * Returns a reference to the mapped value of the element with key equivalent to key.
         * If no such element exists, an exception of type `index_out_of_bound'
         */
        T &at(const Key &key) {
            node *ptr = find(key, root);
            if (ptr == nullptr) throw index_out_of_bound();
            else return ptr->data.second;
        }

        const T &at(const Key &key) const {
            node *ptr = find(key, root);
            if (ptr == nullptr) throw index_out_of_bound();
            else return ptr->data.second;
        }

        /**
         * TODO
         * access specified element
         * Returns a reference to the value that is mapped to a key equivalent to key,
         *   performing an insertion if such key does not already exist.
         */
        T &operator[](const Key &key) {
            node *ptr = find(key, root);
            if (ptr != nullptr) return ptr->data.second;
            bool flag;
            ++ele_size;
            return (insert(value_type(key, T()), root, flag)->data.second);
        }

        /**
         * behave like at() throw index_out_of_bound if such key does not exist.
         */
        const T &operator[](const Key &key) const {
            node *ptr = find(key, root);
            if (ptr == nullptr) throw index_out_of_bound();
            else return ptr->data.second;
        }

        /**
         * return a iterator to the beginning
         */
        iterator begin() {
            if(ele_size == 0){ // map为空时，begin==end
                return iterator(nullptr,this, true);
            }
            node *ptr = root;
            while (ptr->lson != nullptr) ptr = ptr->lson;
            return iterator(ptr, this, false);
        }

        const_iterator cbegin() const {  //常量成员函数的声明const会导致传出的this指针是一个常量指针
            if(ele_size == 0){ // map为空时，begin==end
                return const_iterator(nullptr,this, true);
            }
            node *ptr = root;
            while (ptr->lson != nullptr) ptr = ptr->lson;
            return const_iterator(ptr, this, false);
        }

        /**
         * return a iterator to the end
         * in fact, it returns past-the-end.
         */
        iterator end() {
            return iterator(nullptr, this, true);
        }

        const_iterator cend() const {
            return const_iterator(nullptr, this, true);
        }

        /**
         * checks whether the container is empty
         * return true if empty, otherwise false.
         */
        bool empty() const {
            return ele_size == 0;
        }

        /**
         * returns the number of elements.
         */
        size_t size() const {
            return ele_size;
        }

        /**
         * clears the contents
         */
        void clear() {
            clear(root);
            ele_size = 0;
            root = nullptr;
        }

        /**
         * insert an element.
         * return a pair, the first of the pair is
         *   the iterator to the new element (or the element that prevented the insertion),
         *   the second one is true if insert successfully, or false.
         */
        pair<iterator, bool> insert(const value_type &value) {
            bool flag;
            node *a = insert(value, root, flag);
            iterator iter(a, this, false);
            if (flag) ++ele_size;  //插入成功，元素数加一
            return pair<iterator, bool>(iter, flag);
        }

        /**
         * erase the element at pos.
         *
         * throw if pos pointed to a bad element (pos == this->end() || pos points an element out of this)
         */
        void erase(iterator pos) {
            if (pos.if_end || pos.this_map != this) throw invalid_iterator();
            erase(root, pos.ptr);
            --ele_size;
        }

        /**
         * Returns the number of elements with key
         *   that compares equivalent to the specified argument,
         *   which is either 1 or 0
         *     since this container does not allow duplicates.
         * The default method of check the equivalence is !(a < b || b > a)
         */
        size_t count(const Key &key) const {
            if (find(key, root) != nullptr) return 1;
            return 0;
        }

        /**
         * Finds an element with key equivalent to key.
         * key value of the element to search for.
         * Iterator to an element with key equivalent to key.
         *   If no such element is found, past-the-end (see end()) iterator is returned.
         */
        iterator find(const Key &key) {
            node *result = find(key, root);
            if (result == nullptr) return end();
            return iterator(result, this, false);
        }

        const_iterator find(const Key &key) const {
            node *result = find(key, root);
            if (result == nullptr) return cend();
            return const_iterator(result, this, false);
        }

    private:
        node *root = nullptr;
        size_t ele_size = 0;

        void creat(node *&_root, node *o_root) {   //递归私有成员函数：将o_root的内容复制到root中。在调用create时，保证_root为空指针。
            if (o_root == nullptr) return;
            _root = new node(o_root->data, o_root->height, nullptr, nullptr, nullptr);
            if (o_root->lson != nullptr) {
                creat(_root->lson, o_root->lson);
                _root->lson->dad = _root;
            }
            if (o_root->rson != nullptr) {
                creat(_root->rson, o_root->rson);
                _root->rson->dad = _root;
            }
        }

        void clear(node *_root) {    //递归私有成员函数：清空root的内容
            if (_root == nullptr) return;
            node *l = _root->lson;
            node *r = _root->rson;
            delete _root;
            clear(l);
            clear(r);
        }

        node *find(const Key key, node *r) const {  //从节点r开始寻找键值key,没找到就返回空指针
            if (r == nullptr || (!Compare()(key, r->data.first) && !Compare()(r->data.first, key))) return r; //为空节点或相等
            if (Compare()(key, r->data.first)) return find(key, r->lson);
            return find(key, r->rson);
        }

        int height(node *ptr) {  //返回节点的高度
            if (ptr == nullptr) return 0;
            return ptr->height;
        }

        int max(const int &a, const int &b) {
            return a > b ? a : b;
        }

        void LL(node *&a) {
            node *b = a->lson;
            a->lson = b->rson;
            if (b->rson != nullptr) b->rson->dad = a;
            a->height = max(height(a->lson), height(a->rson)) + 1;
            b->rson = a;
            b->dad = a->dad;
            a->dad = b;
            b->height = max(height(b->lson), height(b->rson)) + 1;
            a = b;
        }

        void RR(node *&a) {
            node *b = a->rson;
            a->rson = b->lson;
            if (b->lson != nullptr) b->lson->dad = a;
            a->height = max(height(a->lson), height(a->rson)) + 1;
            b->lson = a;
            b->dad = a->dad;
            a->dad = b;
            b->height = max(height(b->lson), height(b->rson)) + 1;
            a = b;
        }

        void LR(node *&a) {
            RR(a->lson);
            LL(a);
        }

        void RL(node *&a) {
            LL(a->rson);
            RR(a);
        }

        node *insert(const value_type &data, node *&_root,
                     bool &flag) {    //insert 作用与一个节点，表示将这个节点的插入全部完成（包括height的调整。）返回插入的节点指针(或者
            node *ret;
            if (_root == nullptr) {
                _root = new node(data, 1, nullptr, nullptr, nullptr);
                flag = true;
                return _root;
            } else if (!Compare()(_root->data.first, data.first) &&
                       !Compare()(data.first, _root->data.first)) {  //出现重复元素
                flag = false;
                return _root;
            } else if (Compare()(data.first, _root->data.first)) {  //插在左边
                ret = insert(data, _root->lson, flag);
                _root->lson->dad = _root;
                if (height(_root->lson) - height(_root->rson) >= 2) { // 如果插入后左右子树高度差达到了2，那么肯定成功插入了，并且至少是插入在左（右）子树的儿子节点。
                    if (Compare()(_root->lson->data.first, data.first)) {  //此为第一个失衡节点，它的子节点一定都是平衡的。
                        LR(_root);
                    } else {
                        LL(_root);
                    }
                }
            } else {
                ret = insert(data, _root->rson, flag); //插在右边
                _root->rson->dad = _root;
                if (height(_root->rson) - height(_root->lson) >= 2) {
                    if (Compare()(_root->rson->data.first, data.first)) {
                        RR(_root);
                    } else {
                        RL(_root);
                    }
                }
            }
            _root->height = max(height(_root->lson), height(_root->rson)) + 1;
            return ret;
        }

        //在以结点r为根的树中删除节点target。返回值表示执行完毕以后，以r为根的树高度是否不变。
        //必须要引用传递，否则调用adjust时，由于会用到LL()和RR()，都会失效
        bool erase(node *&r, node *&target) {
            if (r == nullptr) throw invalid_iterator();  //表示要删除的结点不存在，抛出异常
            if (r == target) {
                if (r->lson == nullptr || r->rson == nullptr) { // 被删除的节点是叶子节点或仅有一个儿子
                    node *temp = (r->lson == nullptr) ? r->rson : r->lson;
                    if (temp != nullptr) temp->dad = r->dad;
                    node *tool = r; //为了删除r中元素而赋值的删除工具节点。由于r是引用传递的，所以不能把r直接删除掉。
                    r = temp;
                    delete tool; //必须把这个节点整个删掉,而不能仅仅是把值给替换了。因为指向这个结点的迭代器应该失效。
                    return false; //删除完毕，树的高度发生了变化
                } else {
                    node *temp = r->rson;
                    while (temp->lson != nullptr) temp = temp->lson;
//                    if(r->dad != nullptr){  //必须把结点整个替换成temp，
//                        if(r == r->dad->lson){
//                            r->dad->lson = temp;
//                        }else{
//                            r->dad->rson = temp;
//                        }
//                    }else{
//                        root = temp;
//                    }
                    node *temp_dad = temp->dad, *temp_rson = temp->rson;
                    int temp_height = temp->height;
                    //为了防止出现指针循环无穷指的情况，应该将r和temp交换，而不是直接让temp指针取代r的位置。
                    //注意分类讨论，用于替换的节点temp是否就是r的右儿子。如果是的话，直接交换两个节点即可。
                    if (r->rson == temp) {
                        temp->dad = r->dad;
                        temp->lson = r->lson;
                        r->lson->dad = temp;
                        temp->rson = r;
                        temp->height = r->height;
                        r->dad = temp;
                        r->lson = nullptr;
                        r->rson = temp_rson;
                        if (temp_rson != nullptr) temp_rson->dad = r;
                        r->height = temp_height;
                    } else {
                        temp->dad = r->dad;
                        r->lson->dad = temp;
                        r->rson->dad = temp;
                        temp->rson = r->rson;
                        temp->lson = r->lson;
                        temp->height = r->height;
                        r->lson = nullptr;
                        r->rson = temp_rson;
                        if (temp_rson != nullptr) temp_rson->dad = r;
                        temp_dad->lson = r;
                        r->dad = temp_dad;
                        r->height = temp_height;
                    }
                    node *tmp = r; //tmp用于删除
                    r = temp;
                    if (erase(r->rson, tmp)) return true; //删除以后，右子树的高度未变
                    return adjust(r, true);
                }
            } else if (Compare()(r->data.first, target->data.first)) { //在右子树上删除
                if (erase(r->rson, target)) return true; //在右子树上删完后，右子树高度不变
                return adjust(r, true); //尝试对结点r进行调整
            } else {
                if (erase(r->lson, target)) return true;
                return adjust(r, false);
            }
        }

        bool adjust(node *&r, bool flag) {  //r节点的flag ? 右 ： 左子树高度减一，需要对r节点进行调整。返回调整后高度是否回到了本来的值。
            if (flag) {
                if (height(r->lson) == height(r->rson)) {
                    --r->height;
                    return false;
                } else if (height(r->lson) - height(r->rson) == 1) {
                    return true;
                }
                if (r->lson != nullptr && height(r->lson->lson) == height(r->lson->rson) + 1) {
                    LL(r);  //LL函数也完成了修改结点高度
                    return false; //树的高度-1
                }
                if (r->lson != nullptr && height(r->lson->lson) == height(r->lson->rson) - 1) {
                    LR(r);
                    return false; //树的高度-1
                }
                LL(r);
                return true;
            } else {
                if (height(r->lson) == height(r->rson)) {
                    --r->height;
                    return false;
                } else if (height(r->rson) - height(r->lson) == 1) {
                    return true;
                }
                if (r->rson != nullptr && height(r->rson->rson) == height(r->rson->lson) + 1) {
                    RR(r);
                    return false;
                }
                if (r->rson != nullptr && height(r->rson->rson) == height(r->rson->lson) - 1) {
                    RL(r);
                    return false;
                }
                RR(r);
                return true;
            }
        }
    };



}

#endif
