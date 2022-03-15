#include "include.hpp"

void	stack_test()
{
	std::cout << 			"//STACK" << std::endl;
	std::cout << "\t" <<	"//CONSTRUCTOR" << std::endl;
    {
        std::deque<int> mydeque (3,100);          // deque with 3 elements
        NAMESPACE::vector<int> myvector (2,200);        // vector with 2 elements

        NAMESPACE::stack<int> first;                    // empty stack
        NAMESPACE::stack<int, std::deque<int> > second (mydeque);         // stack initialized to copy of deque

        NAMESPACE::stack<int,NAMESPACE::vector<int> > third;  // empty stack using vector
        NAMESPACE::stack<int,NAMESPACE::vector<int> > fourth (myvector);

        std::cout << "size of first: " << first.size() << '\n';
        std::cout << "size of second: " << second.size() << '\n';
        std::cout << "size of third: " << third.size() << '\n';
        std::cout << "size of fourth: " << fourth.size() << '\n';
    }
	std::cout << "\t" <<	"//EMPTY" << std::endl;
    {
        NAMESPACE::stack<int> mystack;
        int sum (0);

        for (int i=1;i<=10;i++) mystack.push(i);

        while (!mystack.empty())
        {
           sum += mystack.top();
           mystack.pop();
        }

        std::cout << "total: " << sum << '\n';
    }
	std::cout << "\t" <<	"//SIZE" << std::endl;
    {
        NAMESPACE::stack<int> myints;
        std::cout << "0. size: " << myints.size() << '\n';

        for (int i=0; i<5; i++) myints.push(i);
        std::cout << "1. size: " << myints.size() << '\n';

        myints.pop();
        std::cout << "2. size: " << myints.size() << '\n';
    }
	std::cout << "\t" <<	"//TOP" << std::endl;
    {
        NAMESPACE::stack<int> mystack;

        mystack.push(10);
        mystack.push(20);

        mystack.top() -= 5;

        std::cout << "mystack.top() is now " << mystack.top() << '\n';
    }
	std::cout << "\t" <<	"//PUSH/POP" << std::endl;
    {
        NAMESPACE::stack<int> mystack;

        for (int i=0; i<5; ++i) mystack.push(i);

        std::cout << "Popping out elements...";
        while (!mystack.empty())
        {
           std::cout << ' ' << mystack.top();
           mystack.pop();
        }
        std::cout << '\n';
    }
	std::cout << "\t" <<	"//RELATIONAL OPERATORS" << std::endl;
    {
        NAMESPACE::vector<int> vecfoo (3,100);   // three ints with a value of 100
        NAMESPACE::vector<int> vecbar (3,100);   // three ints with a value of 100

        NAMESPACE::stack<int, NAMESPACE::vector<int> > foo (vecfoo);   // three ints with a value of 100
		NAMESPACE::stack<int, NAMESPACE::vector<int> > bar (vecbar);   // two ints with a value of 200

		if (foo==bar) std::cout << "foo and bar are equal\n";
		if (foo!=bar) std::cout << "foo and bar are not equal\n";
		if (foo< bar) std::cout << "foo is less than bar\n";
		if (foo> bar) std::cout << "foo is greater than bar\n";
		if (foo<=bar) std::cout << "foo is less than or equal to bar\n";
		if (foo>=bar) std::cout << "foo is greater than or equal to bar\n";
    }
    

}
