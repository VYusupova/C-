#ifndef S21_STACK_TPP_
#define S21_STACK_TPP_

#include "s21_stack.h"

using namespace s21;

template <typename T>
stack<T>::stack() : header(NULL), ssize(0) {}

template <typename T>
stack<T>::stack(std::initializer_list<s21_value_type> const &items) : stack() {
  for (auto s : items) {
    push(s);
  }
}

template <typename T>
stack<T>::stack(const stack &s) : stack() {
  if (!s.empty()) this->copyStack(s);
}

template <typename T>
stack<T>::stack(stack &&s) : stack() {
  this->header = s.header;
  this->ssize = s.ssize;
  s.header = NULL;
  s.ssize = 0;
}

template <typename T>
stack<T> &s21::stack<T>::operator=(stack &&s) {
  this->destroyStack();
  if (!s.empty() && (this != &s)) {
    this->copyStack(s);
    s.destroyStack();
    //ssize = s.ssize; //исправляет ошибки cppcheck, но ломает тесты
  }
  return *this;
}

template <typename T>
stack<T> &stack<T>::operator=(const stack &s) {
  this->destroyStack();
  if (s.empty()) return *this;
  if (this != &s) {
    this->copyStack(s);
    ssize = s.ssize;
  }
  return *this;
}
template <typename T>
stack<T>::~stack() {
  this->destroyStack();
  ssize = 0;
  header = NULL;
}

template <typename T>
s21_const_reference stack<T>::top() const {
  return header->data;
}
template <typename T>
bool stack<T>::empty() const {
  if (header == NULL)
    return true;
  else
    return false;
}

template <typename T>
s21_size_type stack<T>::size() const {
  return ssize;
}
template <typename T>
void stack<T>::push(s21_const_reference value) {
  node<T> *n = new node<T>();
  n->tail = header;
  n->data = value;
  header = n;
  ssize++;
}
template <typename T>
void stack<T>::pop() {
  node<T> *n = header->tail;
  delete header;
  header = n;
  ssize--;
}
template <typename T>
void s21::stack<T>::swap(stack &other) {
  if (this != &other) {
    node<T> *tmp = other.header;
    other.header = this->header;
    this->header = tmp;

    s21_size_type tmpSize = other.ssize;
    other.ssize = this->ssize;
    this->ssize = tmpSize;
  }
}
template <typename T>
void stack<T>::copyStack(const stack &s) {
  node<T> el = *s.header;
  stack copy;
  while (el.tail != NULL) {
    copy.push(el.data);
    el = *el.tail;
  }
  copy.push(el.data);

  while (!copy.empty()) {
    this->push(copy.top());
    copy.pop();
  }
}
template <typename T>
void stack<T>::destroyStack() {
  while (this->ssize > 0) {
    this->pop();
  }
}

/*template <class value_type, class Container>
template <class... Args>
void Stack<value_type, Container>::insert_many_front(Args &&...args) {
  for (auto item : {args...}) baseClass_.push_back(item);
}*/

#endif
