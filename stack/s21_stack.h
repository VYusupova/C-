#ifndef S21_STACK_H
#define S21_STACK_H

#include <cstring>

#define s21_value_type T
#define s21_reference T &
#define s21_const_reference const T &
#define s21_size_type size_t

namespace s21 {



template <class T>
class node {
 public:
  T data = T{};
	node<T> *tail;
  explicit node() { tail = NULL; }
};

template <class T>
class stack {


 private:
  node<T> *header;
  s21_size_type ssize;
  void copyStack(const stack &s) noexcept;
  void destroyStack() noexcept;

 public:


  stack();  // default constructor, creates empty stack
  stack(std::initializer_list<s21_value_type> const &items);
  stack(const stack &s);  // copy constructor
  stack(stack &&s);       // move constructor
  ~stack();
  stack<T> &operator=(const stack &s);  // без этого это не работает простое равенство
  stack<T> &operator=(stack &&s);

  s21_const_reference top() const;  // accesses the top element

  bool empty() const;
  s21_size_type size() const;

  void push(s21_const_reference value) noexcept;
  void pop() noexcept ;
  void swap(stack &other) noexcept;
  template <typename... Args>
  void insert_many_back(Args &&...args);
};

}  // namespace s21

#include "s21_stack.tpp"
#endif
