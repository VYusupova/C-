

#include "s21_list.h"

int main() {


    /*std::list<int> list3= list();// = {9, 2, 4, 6, 2};
    s21::list<int> list4= list();// = {4, 2 , 3, 1, 7, 9};
 	std::cout << "list3.empty() - " << list3.empty() << '\n';
 	std::cout << "list4.empty() - " << list4.empty() << '\n';
*/

  
    std::list<int> list7;
    s21::list<int> list8;
    list7.push_back(3);
    list8.push_back(3);
    list7.push_back(4);
    list8.push_back(4);
    
 	std::cout << "list7.empty() - " << list7.front() << '\n';
 	std::cout << "list8.empty() - " << list8.back() << '\n';


    std::list<int> list9({9, 2, 4, 6, 2});
    s21::list<int> list10({4, 2 , 3, 1, 7, 9});
 	std::cout << "list9.empty() - " << list9.empty() << '\n';
 	std::cout << "list10.empty() - " << list10.empty() << '\n';

    /*for(auto to : list1){
        std::cout << to << " ";
    }
    

    for(auto to : list2){
        std::cout << to << " ";
    }
    std::cout << '\n';

    list1.merge(list2);

    for(auto to : list1){
        std::cout << to << " ";
    }
    std::cout << '\n';
ghbd
    for(auto to : list2){
        std::cout << to << " ";
    }
    std::cout << '\n';*/
    

    return 0;
}
