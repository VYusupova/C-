#include <stack>

#include "s21_stack.h"

using namespace s21;
using std::cout;
using std::endl;

// cout << origin; // ERROR так нельзя
// std::stack <int> origin = stack(); // ERROR так нельзя
// std::stack<bool> copyOrigin(origin);  // ERROR так нельзя пихать в стек
// другой стек объектов другого типа  std::stack<int> origin; cout << "top
// element origin stack " <<  origin.top() << std::endl;  // ERROR если берем
// топ элемент из пустого стека
// origin.pop();// ERROR если пытаемлся удалить  из пустого стека

int main() {

  std::stack<int> origin({8, 9});
  origin.insert_many_back(1);
  cout << origin.top() << endl;
  return 0;
}
