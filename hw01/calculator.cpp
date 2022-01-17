#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

//전역변수 선언
char isoperator[4] = {'+', '-', '*', '/'};
char isparanthesis[2] = {'(', ')'};

//isp, icp 선언
int ispint[6] = {8, 2, 2, 3, 3, 100};
char ispch[6] = {'(', '*', '/', '+', '-', '#'};
int icpint[6] = {0, 2, 2, 3, 3, 8};
char icpch[6] = {'(', '*', '/', '+', '-', '#'};

template <class T>
void changeSize1D(T* &a, const int oldSize, const int newSize)
{
    //if (newSize < 0) throw "New length must be >= 0";
    if (newSize < 0) exit(-1);

    T* temp = new T[newSize];
    int number = min(oldSize, newSize);
    copy(a, a + number, temp);
    delete[]a;
    a = temp;
}
//스택 클래스 정의
template <class T>
class Stack {
private:
    T *stack;
    int top;
    int capacity;
public:
    Stack (int stackCapacity = 10);
    bool IsEmpty() const;
    T& Top() const;
    void Push(const T& item);
    void Pop();
};

template <class T>
Stack<T>::Stack (int stackCapacity): capacity(stackCapacity)
{
    //if (capacity < 1) throw "Stack capacity must be >= 0";
    if (capacity < 1) exit(-1);
    stack = new T[capacity];
    top = -1;
}

template <class T>
inline bool Stack<T>::IsEmpty() const
{
    return top == -1;
}

template<class T>
inline T& Stack<T>::Top() const
{
    //if(IsEmpty()) throw "Stack is empty";
    if (IsEmpty()) exit(-1);
    return stack[top];
}

template <class T>
void Stack<T>::Push(const T& x)
{
    if (top == capacity - 1)
    {
        changeSize1D(stack, capacity, 2*capacity);
        capacity *= 2;
    }
    stack[++top] = x;
}

template <class T>
void Stack<T>::Pop()
{
    //if (IsEmpty()) throw "Stack is empty. Cannot delete";
    if (IsEmpty())
        exit(-1);
    stack[top--].~T();
}

//스택 정의 끝
//함수 정의 시작

int isOperator(char infix)//연산자인지 확인해서 연산자이면 1, 아니면 0 반환
{
    int flag = 0;
    for(int i = 0; i < 4; i++)
    {
        if (infix == isoperator[i])
        {
            flag = 1;
        }
    }
    return flag;
}

int isParanthesis(char infix)//괄호인지 확인해서 괄호이면 1, 아니면 0 반환
{
    int flag = 0;
    for(int i = 0; i < 2; i++)
    {
        if (infix == isparanthesis[i])
        {
            flag = 1;
        }
    }
    return flag;
}
//에러발생 시 -1리턴, 아니면 1리턴
int checkError(char *input, char *infix)//에러가 발생했는지 확인하고, 에러가 발생하지 않았으면 infix에 피연산자, 연산자 넣음
{
    int operandNum = 0;//피연산자개수
    int operatorNum = 0;//연산자개수
    int openParanthesis = 0;//여는 괄호 '('의 개수
    int closeParanthesis = 0;//닫는 괄호 ')'의 개수
    int infixIndex = 0;//infix의 인덱스
    int arternate = 1;//연산자와 피연산자가 번갈아 나와야 함. 제일 첫번째는 피연산자가 나와야 하고, 마지막도 피연산자가 나와야 함. 피연산자 - 0, 연산자 - 1로.

    int i = 0;
    while(input[i] != '\0')
    {
        int number = 0;
        if (input[i] != ' ')//띄어쓰기 아니면 infix에 push
        {
            if (isOperator(input[i]) == 1)//연산자인가
            {
                if (arternate == 1)//이전 값이 연산자이면
                {
                    return (-1);
                }
                arternate = 1;
                operatorNum++;
            }
            else if (isParanthesis(input[i]) == 1)//괄호인가
            {
                if (input[i] == '(')//여는괄호이면
                    openParanthesis++;
                else if (input[i] == ')')//닫는괄호이면
                {
                    closeParanthesis++;
                    if (closeParanthesis > openParanthesis)//1.닫는 괄호가 더 많으면 에러처리.
                        return (-1);
                }
            }
            else if (isnumber(input[i]) == 1)
            {
                if (arternate == 0)//2.피연산자 전이 또 피연산자이면 오류
                {
                    return (-1);
                }
                arternate = 0;
                while (isnumber(input[i]) == 1)
                {
                    number = 1;
                    infix[infixIndex++] = input[i];
                    i++;
                }
            }
            else//3.숫자, 연산자, 괄호가 아닌 다른 char가 있으면 에러
            {
                return (-1);
            }
            operandNum += number;
            if (number == 0)//number이면 이미 숫자가 infix에 들어있음
                infix[infixIndex++] = input[i];
        }
        if (number == 0)//number이면 이미 i가 증가되어있음
        {
            i++;
        }
    }
    infix[infixIndex++] = '#';
    //에러 검사하기.
    //4. 여는 괄호와 닫는 괄호의 수가 다르면 에러
    if (openParanthesis != closeParanthesis)
        return (-1);
    //5. 연산자 수보다 피연산자 수가 1개 더 작지 않으면 에러
    if ((operatorNum + 1) != operandNum)
        return (-1);
    return (1);
}

//in-stack-precedence에서 우선순위를 반환
int isp(char ch)
{
    int index = 0;
    for(int i = 0; i < 6; i++)
    {
        if (ispch[i] == ch)
        {
            index = i;
        }
    }
    return (ispint[index]);
}
//in-comming-precedence에서 우선순위를 반환
int icp(char ch)
{
    int index = 0;
    for(int i = 0; i < 6; i++)
    {
        if (icpch[i] == ch)
        {
            index = i;
        }
    }
    return (icpint[index]);
}
//중위연산을 후위연산으로 바꾸기
void infixToPostfix(char *postfix, char *infix, long long int *number)//number에 숫자 넣기. postfix에는 숫자가 있다는 뜻으로 .넣기. 안그러면 12 * 3했을 때 123*라 숫자 구분 x
{
    int postfixIndex = 0;
    Stack<char>stack;
    stack.Push('#');
    int i = 0;
    int isnum = 0;

    while (infix[i] != '#')
    {
        isnum = 0;
        if (infix[i] >= '0' && infix[i] <= '9')
        {
            //cout << infix[i];
            isnum = 1;
            long long int num = 0;
            while (infix[i] >= '0' && infix[i] <= '9')
            {
                num = num * 10 + (infix[i++] - '0');
                //postfix[postfixIndex++] = infix[i++];
            }
            postfix[postfixIndex] = '.';//값이 있다는 뜻으로 .넣기
            number[postfixIndex++] = num;
        }
        else if (infix[i] == ')')
        {
            while (stack.IsEmpty() != 1 && stack.Top() != '(')
            {
                //cout << stack.Top();
                postfix[postfixIndex++] = stack.Top();
                stack.Pop();
            }
            stack.Pop();//unstack '()
        }
        else
        {
            while (isp(stack.Top()) <= icp(infix[i]))
            {
                //cout << stack.Top();
                postfix[postfixIndex++] = stack.Top();
                stack.Pop();
            }
            stack.Push(infix[i]);
        }
        if (isnum == 0)//isnum이 1이면 이미 증가되어 있음
            i++;
    }
    while (stack.IsEmpty() != 1)
    {
        //cout << stack.Top();
        postfix[postfixIndex++] = stack.Top();
        stack.Pop();
    }
    //number의 마지막에 -1넣기
    number[postfixIndex] = -1;
}

//display
void display(char *arr, long long int *number)
{
    for(int i = 0; i < strlen(arr) - 1; i++)//마지막은 #
    {
        if (arr[i] == '.')
        {
            cout << number[i];
        }
        else
            cout << arr[i];
        if (i != strlen(arr) - 2)
            cout << ",";
    }
    cout << endl;
}

int calculate(char *postfix, long long int *number)
{
    Stack<long long int> stack;
    int i = 0;
    
    while (postfix[i] != '#')
    {
        if (postfix[i] == '.')
        {
            stack.Push(number[i]);
        }
        else
        {
            long long int second = stack.Top();
            stack.Pop();
            long long int first = stack.Top();
            stack.Pop();
            long long int res;
            if (postfix[i] == '*')
                res = first * second;
            else if (postfix[i] == '/')
            {
                if (second == 0)
                    return (INT_MAX-1);
                res = first / second;
            }
            else if (postfix[i] == '-')
                res = first - second;
            else if (postfix[i] == '+')
                res = first + second;
            if (res > INT_MAX)
                return (INT_MAX);
            else if (res < INT_MIN)
                return (INT_MIN);
            else
                stack.Push(res);
        }
        i++;
    }
    if (stack.Top() > INT_MAX)
        return (INT_MAX);
    else if (stack.Top() < INT_MIN)
        return (INT_MIN);
    return (stack.Top());
}

int main(void)
{
    char postfix[1000] = {0, };
    char infix[1000] = {0, };
    char input[1000] = {0, };
    long long int number[1000] = {0, };//overflow, underflow 처리 위한 long int형 배열

    //입력받기
    cout << "수식을 입력하세요" << endl;
    cin.getline(input, 1000);

    //입력 에러처리, 받은 수식을 infix에 파싱하기
    int error = checkError(input, infix);//error 값이 1인 게 정상
    while (error == -1)
    {
        memset(input, 0, 1000);//input 초기화
        memset(infix, 0, 1000);//infix 초기화
        if (error == -1)
        {
            cout << "수식에 유효하지 않은 값이 있습니다. 다시 입력하세요" << endl;
        }
        cout << "수식을 입력하세요" << endl;
        cin.getline(input, 1000);
        error = checkError(input, infix);
    }
    //중위 연산을 후위 연산으로 바꾸기
    infixToPostfix(postfix, infix, number);
    cout << "postfix : ";
    display(postfix, number);
    //후위 연산 계산하기
    int result = calculate(postfix, number);
    if (result == INT_MAX - 1)
        cout << "devided by zero. error" << endl;
    else if (result == INT_MAX)
        cout << "integer overflow. error" << endl;
    else if (result == INT_MIN)
        cout << "integer underflow. error" << endl;
    else
        cout << "계산결과 : " << calculate(postfix, number) << endl;
    return (0);
}
//0나누기 - 해결
//)개수 > (개수 - 해결
//오버플로우
//번갈아 나오게 하기 - 해결
//2147483647
//3000000000 - 1