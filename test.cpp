#ifndef S21_TEST_STL_CPP
#define S21_TEST_STL_CPP

#include <gtest/gtest.h>

#include <list>

#include "s21_list.h"

using namespace s21;

using namespace std;



/*1 - CONSTRUCTOR TEST*/
TEST(simpleTests, listConstructor0) {
  std::list<int> origin;
  s21::list<int> list;
 
  EXPECT_EQ(origin.empty(), true);
  EXPECT_EQ(list.empty(), true);
}
TEST(simpleTests, listConstructor1) {
  std::list<bool> origin;
  s21::list<bool> list;
 
  EXPECT_EQ(origin.empty(), true);
  EXPECT_EQ(list.empty(), true);
}

TEST(simpleTests, listConstructor3) {
  std::list<int> origin(5);
  s21::list<int> list(5);
 
    EXPECT_EQ(origin.empty(), false);
    EXPECT_EQ(list.empty(), false);
}

TEST(simpleTests, listConstructor4) {
  std::list<int> origin(5,2);
  s21::list<int> list(5,2);
 
    EXPECT_EQ(origin.empty(), false);
    EXPECT_EQ(list.empty(), false);
}

TEST(simpleTests, listConstructor5) {
  std::list<int> origin({9, 2, 4, 6, 2});
  s21::list<int> list({9, 2, 4, 6, 2});
  //std::list<int> origin{9, 2, 4, 6, 2};
  //s21::list<int> list{9, 2, 4, 6, 2};
 
    EXPECT_EQ(origin.empty(), false);
    EXPECT_EQ(list.empty(), false);
}

TEST(simpleTests, listConstructor6) {
  std::list<int> origin = {9, 2, 4, 6, 2};
  s21::list<int> list = {9, 2, 4, 6, 2};
 
    EXPECT_EQ(origin.empty(), false);
    EXPECT_EQ(list.empty(), false);
}

TEST(hardTest, constuctorCopyTest) {
  std::list<bool> origin(
      {true, false, true, true, true, 0, 1, 1, true, false, 0, 0, 0});
  s21::list<bool> list(
      {true, false, true, true, true, 0, true, 1, 1, 0, false, 0, false});
  EXPECT_EQ(origin.empty(), false);
  EXPECT_EQ(list.empty(), false);
  std::list<bool> originCP(origin);
  s21::list<bool> listCP(list);
  EXPECT_EQ(originCP.empty(), false);
  EXPECT_EQ(listCP.empty(), false);
  
  EXPECT_NE(&origin, &originCP);
  EXPECT_NE(&list, &listCP);
  //int count = 13;
  //while (count > 0) {
  /*  count--;

    EXPECT_NE(&origin.top(), &originCP.top());
    EXPECT_NE(&stack1.top(), &stack1CP.top());
    EXPECT_EQ(origin.top(), originCP.top());
    EXPECT_EQ(stack1.top(), stack1CP.top());
    EXPECT_EQ(origin.size(), originCP.size());
    EXPECT_EQ(stack1.size(), stack1CP.size());
    origin.pop();
    originCP.pop();
    stack1.pop();
    stack1CP.pop();
    */
  }
/*  
TEST(hardTest, constuctorMoveTest) {
  std::list<int> origin;
  s21::list<int> list;

 // int count = 1300;
 // while (count > 0) {
 //   count--;
 //   origin.push(count);
 //   stack1.push(count);
 // }
 // const void *p1 = &origin.top();
//  const void *p2 = &stack1.top();

  std::list<int> originCP(std::move(origin));
  s21::list<int> listCP(std::move(list));
  
  EXPECT_EQ(origin.empty(), true);
  EXPECT_EQ(list.empty(), true);
  EXPECT_EQ(originCP.empty(), false);
  EXPECT_EQ(listCP.empty(), false);
  //EXPECT_EQ(origin.size(), 0);
  //EXPECT_EQ(stack1.size(), 0);

  //EXPECT_EQ(&originCP.top(), p1);
  //EXPECT_EQ(&stack1CP.top(), p2);
}
*/
/*TEST(hardTest, constuctorMoveTest2) {
  std::list<bool> origin(
      {true, false, true, true, true, 0, 1, 1, true, false, 0, 0, 0});
  s21::list<bool> list(
      {true, false, true, true, true, 0, true, 1, 1, 0, false, 0, false});

  //const void *p1 = &origin.top();
  //const void *p2 = &stack1.top();

  std::list<bool> originCP(std::move(origin));
  s21::list<bool> listCP(std::move(list));
  EXPECT_EQ(origin.empty(), true);
  EXPECT_EQ(list.empty(), true);
    EXPECT_EQ(originCP.empty(), false);
  EXPECT_EQ(listCP.empty(), false);
  //EXPECT_EQ(origin.size(), 0);
  //EXPECT_EQ(stack1.size(), 0);

  //EXPECT_EQ(&originCP.top(), p1);
  //EXPECT_EQ(&stack1CP.top(), p2);
}*/

TEST(hardTest, operatorEqTest) {
  std::stack<bool> origin(
      {true, false, true, true, true, 0, 1, 1, true, false, 0, 0, 0});
  s21::list<bool> list(
      {true, false, true, true, true, 0, true, 1, 1, 0, false, 0, false});

  std::list<bool> originCP = origin;
  s21::stack<bool> listCP = list;
  EXPECT_NE(&origin, &originCP);
  EXPECT_NE(&list, &listCP);
  int count = 13;
  while (count > 0) {
    count--;
    EXPECT_NE(&origin.top(), &originCP.top());
    EXPECT_NE(&list.top(), &listCP.top());
    EXPECT_EQ(origin.top(), originCP.top());
    EXPECT_EQ(list.top(), listCP.top());
    EXPECT_EQ(origin.size(), originCP.size());
    EXPECT_EQ(list.size(), listCP.size());
    origin.pop();
    originCP.pop();
    list.pop();
    listCP.pop();
  }
}

TEST(hardTest, operatorEqTest1) {
  // проверить что будет если  копировать пустой список в непустой список
  std::list<int> origin;
  std::list<int> originCP({1, 2, 3});
  originCP = origin;

  s21::list<int> list;
  s21::list<int> listCP({1, 2, 3});
  listCP = list;
  
// ожидаение оба списка стали пустые и размеры их нулевые 
  EXPECT_EQ(origin.empty(), true);
  EXPECT_EQ(originCP.empty(), true);
  EXPECT_EQ(list.empty(), true);
  EXPECT_EQ(listCP.empty(), true);

  //EXPECT_EQ(origin.size(), 0);
 // EXPECT_EQ(originCP.size(), 0);
 // EXPECT_EQ(list.size(), 0);
 // EXPECT_EQ(listCP.size(), 0);
// адреса списков разные
  EXPECT_NE(&origin, &originCP);
  EXPECT_NE(&list, &listCP);
}
//оператор перемещения
TEST(simpleTest, operatorEqMoveTest) {
  std::list<int> origin;
  s21::list<int> list;
  std::list<int> originCP;
  originCP = std::move(origin);
  s21::list<int> listCP;
  listCP = std::move(list);

  EXPECT_NE(&origin, &originCP);
  EXPECT_NE(&list, &listCP);
}
TEST(mediumTest, operatorEqMoveTest) {
  std::list<int> origin({1, 2, 3, 4, 5, 6, 7});
  s21::list<int> list({1, 2, 3, 4, 5, 6, 7});
  //int size = origin.size();

  std::list<int> originCP;
  s21::list<int> listCP;

  originCP = std::move(origin);
  listCP = std::move(list);

  EXPECT_NE(&origin, &originCP);
  EXPECT_NE(&list, &listCP);

  EXPECT_EQ(origin.empty(), true);
  EXPECT_EQ(originCP.empty(), false);
  EXPECT_EQ(list.empty(), true);
  EXPECT_EQ(listCP.empty(), false);

 // EXPECT_EQ(origin.size(), 0);
 // EXPECT_EQ(originCP.size(), size);
 // EXPECT_EQ(list.size(), 0);
//  EXPECT_EQ(listCP.size(), size);

 // while (size > 1) {
  //  EXPECT_EQ(listCP.top(), originCP.top());
 //   EXPECT_EQ(listCP.size(), originCP.size());
 //   originCP.pop();
//    listCP.pop();
//    size--;
//  }
}
TEST(hardTest, operatorEqMoveTest) {
  std::list<int> origin;
  s21::list<int> list;

  std::list<int> originCP({1, 2, 3, 4, 5, 6, 7});
  s21::list<int> listCP({1, 2, 3, 4, 5, 6, 7});

  originCP = std::move(origin);
  listCP = std::move(list);

  EXPECT_NE(&origin, &originCP);
  EXPECT_NE(&list, &listCP);

  EXPECT_EQ(origin.empty(), true);
  EXPECT_EQ(originCP.empty(), true);
  EXPECT_EQ(list.empty(), true);
  EXPECT_EQ(listCP.empty(), true);

  //EXPECT_EQ(origin.size(), 0);
 // EXPECT_EQ(originCP.size(), 0);
//  EXPECT_EQ(list.size(), 0);
//  EXPECT_EQ(listCP.size(), 0);
}
/*2*/
TEST(simpleTests, listPushTest) {
    std::list<int> origin;
    s21::list<int> list;
    origin.push_back(3);
    list.push_back(3);
    origin.push_back(4);
    list.push_back(4);
    EXPECT_EQ(origin.empty(), false);
    EXPECT_EQ(list.empty(), false);
}
/*
TEST(mediumTests, pushPopTest) {
  std::stack<int> origin;
  s21::stack<int> list;
  int a = 2;
  list.push(a);
  origin.push(a);
  list.push(3);
  origin.push(3);
  EXPECT_EQ(origin.top(), list.top());
  list.pop();
  origin.pop();
  EXPECT_EQ(origin.top(), list.top());
}
TEST(simpleTests, pushTest1) {
  std::stack<int> origin;
  s21::stack<int> list;
  list.push(5);
  origin.push(5);
  EXPECT_EQ(origin.top(), list.top());
}
TEST(simpleTests, pushTest2) {
  std::stack<int> origin;
  s21::stack<int> stack1;
  stack1.push(5);
  origin.push(5.5);
  EXPECT_EQ(origin.top(), stack1.top());
  // cout <<"\n data in stack : %d & %d" <<  origin.top() <<  stack1.top());
}
TEST(simpleTests, pushTest3) {
  std::stack<std::string> origin;
  s21::stack<std::string> stack1;
  std::string str = "HELLO";
  stack1.push(str);
  origin.push(str);
  EXPECT_EQ(origin.top(), stack1.top());
}
TEST(simpleTests, pushTest4) {
  std::stack<bool> origin;
  s21::stack<bool> stack1;
  bool b = 0;
  stack1.push(b);
  origin.push(b);
  EXPECT_EQ(origin.top(), stack1.top());
}
// проверка дефолтного конструктора и работы функции size()
TEST(simpleTests, sizeTest1) {
  std::stack<int> origin;
  s21::stack<int> stack1;
  EXPECT_EQ(origin.size(), stack1.size());
  // cout << "size origin - " << origin.size() << " \nsize my stack - " <<
  // stack1.size();
}
TEST(simpleTests, sizeTest2) {
  std::stack<std::string> origin;
  s21::stack<std::string> stack1;
  EXPECT_EQ(origin.size(), stack1.size());
  // cout << "size origin - " << origin.size() << " \nsize my stack - " <<
  // stack1.size();
}
TEST(simpleTests, sizeTest3) {
struct Point {
  int x =0;
  int y= 0;
};
  std::stack<Point> origin;
  s21::stack<Point> stack1;
  EXPECT_EQ(origin.size(), stack1.size());

  Point p;
  p.x = 4;
  p.y = 8;
  
  origin.push(p);
  stack1.push(p);
  
  

}
TEST(simpleTests, sizeTest4) {
  std::stack<std::string> origin;
  s21::stack<std::string> stack1;
  origin.push("HELLO");
  stack1.push("WORLD");
  EXPECT_EQ(origin.size(), stack1.size());
  // cout << "size origin - " << origin.size() << " \nsize my stack - " <<
  // stack1.size();
}
TEST(mediumTests, sizePopTest) {
  std::stack<std::string> origin({"first", "string", "Second"});
  s21::stack<std::string> stack1({"string", "size", "equal"});
  EXPECT_EQ(origin.size(), stack1.size());
  while (origin.size() > 1) {
    EXPECT_EQ(origin.size(), stack1.size());
    origin.pop();
    stack1.pop();
  }
}

TEST(simpleTests, emptyTest3) {
  std::stack<int> origin({1});
  s21::stack<int> stack1({2});
  origin.pop();
  stack1.pop();
  EXPECT_EQ(origin.empty(), true);
  EXPECT_EQ(stack1.empty(), true);
  // cout << "size origin - " << origin.size() << " \nsize my stack - " <<
  // stack1.size();
}
TEST(mediumTests, emptyTest) {
  std::stack<bool> origin(
      {true, false, true, true, true, 0, 1, 1, true, false, 0, 0, 0});
  s21::stack<bool> stack1(
      {true, false, true, true, true, 0, true, 1, 1, 0, false, 0, false});
  EXPECT_EQ(origin.empty(), false);
  EXPECT_EQ(stack1.empty(), false);
}
TEST(mediumTests, emptyPopTest) {
  std::stack<std::string> origin;
  s21::stack<std::string> stack1;
  origin.push("HELLO");
  origin.push("HELLO");
  stack1.push("WORLD");
  stack1.push("HELLO");
  origin.pop();
  stack1.pop();
  EXPECT_EQ(origin.empty(), false);
  EXPECT_EQ(stack1.empty(), false);
}
TEST(simpleTests, constuctorDefTest1) {
  std::stack<bool> origin;
  s21::stack<bool> stack1;
  EXPECT_EQ(origin.empty(), true);
  EXPECT_EQ(stack1.empty(), true);
}
TEST(mediumTests, pushTest1) {
struct Point {
  int x =0;
  int y= 0;
};
  std::stack<Point> origin;
  s21::stack<Point> stack1;
  Point p;
  p.x = 6;
  p.y = 3;
  stack1.push(p);
  origin.push(p);
  EXPECT_EQ(origin.top().x, stack1.top().x);
  EXPECT_EQ(origin.top().y, stack1.top().y);
  EXPECT_NE(&origin.top(), &p);
  EXPECT_NE(&stack1.top(), &p);
  EXPECT_NE(&stack1.top(), &origin.top());

  // printf("address top element stack : %p & %p &%p" <<  &origin.top() <<
  // &stack1.top() << &p; p.x = 7; cout << "stack : %d & %d &%d" <<
  // origin.top().x <<  stack1.top().x, p.x; completedTO DO  разобраться :
  // оригинал делает копию структуры, моя версия пихает адрес структуры
}
TEST(mediumTests, pushTest2) {
  std::stack<int *> origin;
  s21::stack<int *> stack1;
  int a = 2;
  int *p = &a;
  stack1.push(p);
  origin.push(p);
  EXPECT_EQ(origin.top(), stack1.top());
  EXPECT_EQ(origin.top(), p);
  EXPECT_EQ(stack1.top(), p);
  EXPECT_EQ(stack1.top(), origin.top());
  // printf("address top element stack : %p & %p &%p",  origin.top(),
  // stack1.top(), p);
  //  a = 7;
  // printf("\n data in stack : %d & %d & %d",  *origin.top(),  *stack1.top(),
  // *p);
}

TEST(hardTest, sizeTest) {
  std::stack<int> origin;
  s21::stack<int> stack1;
  int count = 1300;
  while (count > 0) {
    count--;
    origin.push(count);
    stack1.push(count);
  }
  EXPECT_EQ(origin.size(), stack1.size());
  // cout << "size origin - " << origin.size() << " \nsize my stack - " <<
  // stack1.size();
}

//проверяем конструктор со списком инициализации
TEST(hardTest, constuctorIniListTest) {
  std::stack<int> origin({1, 2, 3, 4, 5, 6, 7});
  s21::stack<int> stack1({1, 2, 3, 4, 5, 6, 7});
  EXPECT_EQ(origin.size(), stack1.size());
  while (origin.size() > 1) {
    EXPECT_EQ(origin.top(), stack1.top());
    origin.pop();
    stack1.pop();
  }
  // origin.pop();  //stack1.pop();
  // cout << ".top() origin - " << origin.top() << " \n.top() my stack - " <<
  // stack1.top(); cout << "size origin - " << origin.size() << " \nsize my
  // stack - " << stack1.size();
}
TEST(hardTest, constuctorIniListSizePopTest) {
  std::stack<bool> origin(
      {true, false, true, true, true, 0, 1, 1, true, false, 0, 0, 0});
  s21::stack<bool> stack1(
      {true, false, true, true, true, 0, true, 1, 1, 0, false, 0, false});
  EXPECT_EQ(origin.top(), stack1.top());
  EXPECT_EQ(origin.size(), stack1.size());
  while (origin.size() > 0) {
    EXPECT_EQ(origin.top(), stack1.top());
    origin.pop();
    stack1.pop();
  }
}

TEST(hardTest, constuctorCopyTest2) {
  std::stack<int> origin;
  s21::stack<int> stack1;

  int count = 1300;
  while (count > 0) {
    count--;
    origin.push(count);
    stack1.push(count);
  }

  std::stack<int> originCP(origin);
  s21::stack<int> stack1CP(stack1);
  count = 1300;
  while (count > 0) {
    count--;
    EXPECT_NE(&origin, &originCP);
    EXPECT_NE(&stack1, &stack1CP);
    EXPECT_NE(&origin.top(), &originCP.top());
    EXPECT_NE(&stack1.top(), &stack1CP.top());
    EXPECT_EQ(origin.top(), originCP.top());
    EXPECT_EQ(stack1.top(), stack1CP.top());
    EXPECT_EQ(origin.size(), originCP.size());
    EXPECT_EQ(stack1.size(), stack1CP.size());
    origin.pop();
    originCP.pop();
    stack1.pop();
    stack1CP.pop();
  }

  EXPECT_EQ(origin.empty(), true);
  EXPECT_EQ(stack1.empty(), true);
}
TEST(simpleTest, operatorEqTest) {
  std::stack<int> origin;
  s21::stack<int> stack1;

  std::stack<int> originCP = origin;
  s21::stack<int> stack1CP = stack1;
  EXPECT_NE(&origin, &originCP);
  EXPECT_NE(&stack1, &stack1CP);
  EXPECT_EQ(origin.empty(), true);
  EXPECT_EQ(stack1.empty(), true);
  EXPECT_EQ(originCP.empty(), true);
  EXPECT_EQ(stack1CP.empty(), true);
  EXPECT_EQ(origin.size(), originCP.size());
  EXPECT_EQ(stack1.size(), stack1CP.size());
}

//оперетор обмена swap(stack &other) 

TEST(simpleTest, swapTest) {
  std::stack<int> origin;
  s21::stack<int> stack;
  std::stack<int> originCP;
  s21::stack<int> stackCP;

  const void *porigin = &origin;
  const void *pstack = &stack;
  const void *poriginCP = &originCP;
  const void *pstackCP = &stackCP;

  originCP.swap(origin);
  stackCP.swap(stack);

  EXPECT_EQ(&origin, porigin);
  EXPECT_EQ(&originCP, poriginCP);
  EXPECT_EQ(&stack, pstack);
  EXPECT_EQ(&stackCP, pstackCP);
}
TEST(mediumTest, swapTest) {
  std::stack<int> origin({1, 2, 3, 4, 5, 6, 7});
  s21::stack<int> stack({1, 2, 3, 4, 5, 6, 7});
  std::stack<int> originCP;
  s21::stack<int> stackCP;

  const void *porigin = &origin;
  const void *pstack = &stack;
  const void *poriginCP = &originCP;
  const void *pstackCP = &stackCP;

  originCP.swap(origin);
  stackCP.swap(stack);

  EXPECT_EQ(&origin, porigin);
  EXPECT_EQ(&originCP, poriginCP);
  EXPECT_EQ(&stack, pstack);
  EXPECT_EQ(&stackCP, pstackCP);

  EXPECT_EQ(origin.size(), 0);
  EXPECT_EQ(originCP.size(), 7);
  EXPECT_EQ(stack.size(), 0);
  EXPECT_EQ(stackCP.size(), 7);

  EXPECT_EQ(origin.empty(), true);
  EXPECT_EQ(originCP.empty(), false);
  EXPECT_EQ(stack.empty(), true);
  EXPECT_EQ(stackCP.empty(), false);

  EXPECT_EQ(originCP.top(), 7);
  EXPECT_EQ(stackCP.top(), 7);

  originCP.pop();
  stackCP.pop();

  EXPECT_EQ(originCP.top(), 6);
  EXPECT_EQ(stackCP.top(), 6);
}

TEST(mediumTest, swapTest2) {
  std::stack<int> origin;
  s21::stack<int> stack;
  std::stack<int> originCP({1, 2, 3, 4, 5, 6, 7});
  s21::stack<int> stackCP({1, 2, 3, 4, 5, 6, 7});

  const void *porigin = &origin;
  const void *pstack = &stack;
  const void *poriginCP = &originCP;
  const void *pstackCP = &stackCP;

  originCP.swap(origin);
  stackCP.swap(stack);

  EXPECT_EQ(&origin, porigin);
  EXPECT_EQ(&originCP, poriginCP);
  EXPECT_EQ(&stack, pstack);
  EXPECT_EQ(&stackCP, pstackCP);

  EXPECT_EQ(origin.size(), 7);
  EXPECT_EQ(originCP.size(), 0);
  EXPECT_EQ(stack.size(), 7);
  EXPECT_EQ(stackCP.size(), 0);

  EXPECT_EQ(origin.empty(), false);
  EXPECT_EQ(originCP.empty(), true);
  EXPECT_EQ(stack.empty(), false);
  EXPECT_EQ(stackCP.empty(), true);

  EXPECT_EQ(origin.top(), 7);
  EXPECT_EQ(stack.top(), 7);

  origin.pop();
  stack.pop();
  origin.pop();
  stack.pop();

  EXPECT_EQ(origin.top(), 5);
  EXPECT_EQ(stack.top(), 5);
}

TEST(hardTest, swapTest1) {
  std::stack<int> origin({8, 9});
  s21::stack<int> stack({8, 9});
  std::stack<int> originCP({1, 2, 3, 4, 5, 6, 7});
  s21::stack<int> stackCP({1, 2, 3, 4, 5, 6, 7});

  const void *porigin = &origin;
  const void *pstack = &stack;
  const void *poriginCP = &originCP;
  const void *pstackCP = &stackCP;

  const void *poriginTOP = &origin.top();
  const void *pstackTOP = &stack.top();
  const void *poriginCPtop = &originCP.top();
  const void *pstackCPtop = &stackCP.top();

  originCP.swap(origin);
  stackCP.swap(stack);

  EXPECT_EQ(&origin, porigin);
  EXPECT_EQ(&originCP, poriginCP);
  EXPECT_EQ(&stack, pstack);
  EXPECT_EQ(&stackCP, pstackCP);

  EXPECT_EQ(&origin.top(), poriginCPtop);
  EXPECT_EQ(&originCP.top(), poriginTOP);
  EXPECT_EQ(&stack.top(), pstackCPtop);
  EXPECT_EQ(&stackCP.top(), pstackTOP);

  EXPECT_EQ(origin.size(), 7);
  EXPECT_EQ(originCP.size(), 2);
  EXPECT_EQ(stack.size(), 7);
  EXPECT_EQ(stackCP.size(), 2);

  EXPECT_EQ(origin.empty(), false);
  EXPECT_EQ(originCP.empty(), false);
  EXPECT_EQ(stack.empty(), false);
  EXPECT_EQ(stackCP.empty(), false);

  EXPECT_EQ(origin.top(), 7);
  EXPECT_EQ(stack.top(), 7);
  EXPECT_EQ(originCP.top(), 9);
  EXPECT_EQ(stackCP.top(), 9);

  origin.pop();
  stack.pop();
  origin.pop();
  stack.pop();

  EXPECT_EQ(origin.top(), 5);
  EXPECT_EQ(stack.top(), 5);

  originCP.pop();
  stackCP.pop();

  EXPECT_EQ(originCP.top(), 8);
  EXPECT_EQ(stackCP.top(), 8);
}

TEST(hardTest, swapTest2) {
  std::stack<int> origin({8, 9});
  s21::stack<int> stack({8, 9});
  std::stack<int> originCP({1});
  s21::stack<int> stackCP{1};

  const void *porigin = &origin;
  const void *pstack = &stack;
  const void *poriginCP = &originCP;
  const void *pstackCP = &stackCP;

  const void *poriginTOP = &origin.top();
  const void *pstackTOP = &stack.top();
  const void *poriginCPtop = &originCP.top();
  const void *pstackCPtop = &stackCP.top();

  originCP.swap(origin);
  stackCP.swap(stack);

  EXPECT_EQ(&origin, porigin);
  EXPECT_EQ(&originCP, poriginCP);
  EXPECT_EQ(&stack, pstack);
  EXPECT_EQ(&stackCP, pstackCP);

  EXPECT_EQ(&origin.top(), poriginCPtop);
  EXPECT_EQ(&originCP.top(), poriginTOP);
  EXPECT_EQ(&stack.top(), pstackCPtop);
  EXPECT_EQ(&stackCP.top(), pstackTOP);

  EXPECT_EQ(origin.size(), 1);
  EXPECT_EQ(originCP.size(), 2);
  EXPECT_EQ(stack.size(), 1);
  EXPECT_EQ(stackCP.size(), 2);

  EXPECT_EQ(origin.empty(), false);
  EXPECT_EQ(originCP.empty(), false);
  EXPECT_EQ(stack.empty(), false);
  EXPECT_EQ(stackCP.empty(), false);

  EXPECT_EQ(origin.top(), 1);
  EXPECT_EQ(stack.top(), 1);
  EXPECT_EQ(originCP.top(), 9);
  EXPECT_EQ(stackCP.top(), 9);

  origin.pop();
  stack.pop();
  EXPECT_EQ(origin.size(), 0);
  EXPECT_EQ(stack.size(), 0);

  EXPECT_EQ(origin.empty(), true);
  EXPECT_EQ(stack.empty(), true);

  originCP.pop();
  stackCP.pop();

  EXPECT_EQ(originCP.top(), 8);
  EXPECT_EQ(stackCP.top(), 8);

  originCP.pop();
  stackCP.pop();

  EXPECT_EQ(originCP.size(), 0);
  EXPECT_EQ(stackCP.size(), 0);

  EXPECT_EQ(originCP.empty(), true);
  EXPECT_EQ(stackCP.empty(), true);
}

TEST(simpleTests, insertManyTest) {

  s21::stack<int> stack({8, 9});
  stack.insert_many_back(1);
  EXPECT_EQ(stack.top(), 1);
}

TEST(mediumTests, insertManyTest) {
  s21::stack<int> stack({8, 9});
  stack.insert_many_back(1,4,18);
  EXPECT_EQ(stack.top(), 18);
  EXPECT_EQ(stack.size(), 5);
}

TEST(mediumTests, insertManyTest1) {
  s21::stack<int> stack({8, 9});
  stack.insert_many_back();
  EXPECT_EQ(stack.top(), 9);
  EXPECT_EQ(stack.size(), 2);
}

TEST(mediumTests, insertManyTest2) {
  s21::stack<int> stack({8, 9});
  stack.insert_many_back(4,3.6); // static_cast()
  EXPECT_EQ(stack.top(), 3);
  EXPECT_EQ(stack.size(), 4);
}

TEST(hardTests, insertManyTest) {
  s21::stack<int> stack({8, 9});
  stack.insert_many_back(4,3, 'v'); // static_cast()
  EXPECT_EQ(stack.top(), 'v');
  EXPECT_EQ(stack.size(), 5);
}
*/
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}

#endif
