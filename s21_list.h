#ifndef S21_LIST_H
#define S21_LIST_H

#include <iostream>
#include <limits>
#include <list>

namespace s21 {
template <typename T>
class list 
{
private :

class Node 
        {
        public:
            Node *pNext;
            Node *pPrev;
            T data;

            Node(T data=T(), Node* pNext=nullptr, Node* pPrev=nullptr) 
            {
                this->data = data;
                this->pNext = pNext;
                this->pPrev = pPrev;
            }
        };



	    Node *sentinel;
            std::size_t length;

protected:

    

    
    template <typename reference>
    class ListIteratorBase
        {
        protected:
            Node* current;
        
        public:

            friend class list<T>;

            ListIteratorBase(Node* node) : current(node) {}

            reference operator*() const { return current->data; }

            ListIteratorBase operator++(){
                current = current->pNext;
                return *this;
            }

            ListIteratorBase operator++(int){
                ListIteratorBase temp = *this;
                ++(*this);
                return temp;
            }

            ListIteratorBase operator--(){
                current = current->pPrev;
                return *this;
            }

            ListIteratorBase operator--(int){
                ListIteratorBase temp = *this;
                --(*this);
                return temp;
            }

            bool operator==(const ListIteratorBase& other) const { return current->data == other.current->data; }
            bool operator!=(const ListIteratorBase& other) const { return current != other.current; }

        };

    class ListIterator : public ListIteratorBase<T&>
        {
            public:
                using ListIteratorBase<T&>::ListIteratorBase;
        };

    class constListIterator : public ListIteratorBase<const T&>
        {
            public:
                using ListIteratorBase<const T&>::ListIteratorBase;

                constListIterator(const ListIterator& iterator) : ListIteratorBase<const T&>(iterator.current) {}
        };

public:

    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using iterator = ListIterator;
    using const_iterator = constListIterator;
    using size_type = std::size_t;

    list();
    list(size_type n);
    list(std::initializer_list<value_type> const &items);
    list(const list &other);
    list(list &&other);
    ~list();
    list operator=(list&& l);

    bool empty();
    size_type size() { return length; };
    size_type max_size() { return std::numeric_limits<size_type>::max() / sizeof(Node) / 2; };

    void clear();
    iterator insert(iterator pos, const_reference value);
    iterator erase(iterator pos);
    void push_back(value_type data);
    void push_front(value_type data);
    void pop_back();
    void pop_front();
    void swap(list& other);
    void merge(list& other);
    void splice(const_iterator pos, list& other);
    void reverse();
    void unique();
    void sort();
    list merge_sort(list l1, list l2);
    Node* midNode(Node* head);
    list<value_type> sortList(Node* head);


    iterator begin() { return iterator(sentinel->pNext); }
    iterator end() { return iterator(sentinel); }

    const_iterator begin() const { return const_iterator(sentinel->pNext); }
    const_iterator end() const { return const_iterator(sentinel); }

    const_reference front() { return this->sentinel->pNext->data; }
    const_reference back() { return this->sentinel->pPrev->data; }

    void init_sentinel();

};

}


#include "s21_list.tpp"
#endif
