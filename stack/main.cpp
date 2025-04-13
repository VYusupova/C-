#include <stack>

#include "s21_stack.h"

using namespace s21;
using std::cout;
using std::endl;

struct Point {
  int x;
  int y;
};
// cout << origin; // ERROR так нельзя
// std::stack <int> origin = stack(); // ERROR так нельзя
// std::stack<bool> copyOrigin(origin);  // ERROR так нельзя пихать в стек
// другой стек объектов другого типа  std::stack<int> origin; cout << "top
// element origin stack " <<  origin.top() << std::endl;  // ERROR если берем
// топ элемент из пустого стека
// origin.pop();// ERROR если пытаемлся удалить  из пустого стека

int main() {
  std::stack<int> origin({1, 2, 3, 4, 5, 6, 7});
  s21::stack<int> stack({1, 2, 3, 4, 5, 6, 7});
  // cout << "кол-во элементов origin " << origin.size() << " - stack " <<
  // stack.size() << endl;
  //   cout << "addr origin " << &origin << " - stack " << &stack << endl;
  cout << "addr top() origin " << &origin.top() << " - stack " << &stack.top()
       << endl;

  // std::stack<int> originCP = std::move(origin);
  // s21::stack<int> stackCP = std::move(stack);

  std::stack<int> originCP({8, 9});
  s21::stack<int> stackCP({8, 9});
  cout << "==========================" << endl;
  // cout << "кол-во элементов originCP " << originCP.size() << " stackCP - " <<
  // stackCP.size() << endl;
  //    cout << "addr originCP " << &originCP << " - stackCP " << &stackCP <<
  //    endl;
  cout << "addr top() originCP " << &originCP.top() << " - stackCP "
       << &stackCP.top() << endl;

  originCP.swap(origin);
  stackCP.swap(stack);

  // cout << "кол-во элементов origin " << origin.size()  << " originCP -  " <<
  // originCP.size() << endl; cout << "кол-во элементов stack " << stack.size()
  // << " stackCP -  " << stackCP.size() << endl;
  //    cout << "addr origin " << &origin << " - originCP " << &originCP <<
  //    endl; cout << "addr stack " << &stack  << " - stackCP " << &stackCP <<
  //    endl; cout << "top() origin " << origin.top() << " - stack " <<
  //    stack.top() << endl; cout << "top() originCP " << originCP.top() << " -
  //    stackCP " << stackCP.top() << endl; originCP.pop();
  //   stackCP.pop();
  //     cout << "top() originCP " << originCP.top() << " - stackCP " <<
  //     stackCP.top() << endl;

  cout << "addr top() origin " << &origin.top() << " - stack " << &stack.top()
       << endl;
  cout << "addr top() originCP " << &originCP.top() << " - stackCP "
       << &stackCP.top() << endl;

  // std::stack<int> originCP(std::move(origin));
  // s21::stack<int> stackCP(std::move(stack));

  //////// оператор присваивания
  ////////// конструктор копирования стека

  //  cout << "address copyOrigin " <<  &copyOrigin <<endl;
  // //  s21::stack <int> stack3(origin);

  //   cout << "возвращает кол-во элементов " <<  origin.size() <<  endl;

  // //   cout << "origin.size() элементов " <<  origin.size() <<  endl;

  // cout << "\nadress top element origin stack " <<  &origin.top() << endl;
  // //cout << "adresstop element copy origin stack " <<  &copyOrigin.top() <<
  // endl;

  // s21::stack<int> s1({1, 2, 3});
  // s21::stack<int> s2;

  //    std::cout << "s1.top() address = " << &s1.top() << endl;
  //    std::cout << "s1.size = " << s1.size() << endl;

  //   s21::stack <int> s2(std::move(s1));
  //   //std::cout << "s1.top() = " << s1.top() << endl;
  //   //  // operator =
  //    //s2 = s1;
  //       std::cout << "s1.size = " << s1.size() << endl;
  //  std::cout << "s2.size = " << s2.size() << endl;
  //   std::cout << "s1  address = " << &s1 << endl;
  //   std::cout << "s2  address = " << &s2 << endl;

  //    s1.empty() ?  std::cout << "s1.empty() " << endl : std::cout <<
  //    "s1.top() = " << s1.top() << endl; std::cout << "s2.top() = " <<
  //    s2.top() << endl;

  //    s1.empty() ?  std::cout << "s1.empty() " << endl :   std::cout <<
  //    "s1.top() address = " << &s1.top() << endl;
  //      std::cout << "s2.top() address = " << &s2.top() << endl;

  //    if (!s1.empty())  s1.pop();

  //   std::cout << " top after pop s1" << endl;
  //    s1.empty() ?  std::cout << "s1.empty() " << endl :  std::cout <<
  //    "s1.top() = " << s1.top() << endl; std::cout << "s2.top() = " <<
  //    s2.top() << endl;

  return 0;
}
