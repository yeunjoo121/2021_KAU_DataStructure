#include <iostream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <string>
#include <sstream>
using namespace std;

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

class BST;
class TreeNode
{
friend class BST;
private:
    int data;
    TreeNode *leftChild;
    TreeNode *rightChild;
public:
    TreeNode(int data = 0, TreeNode *leftChild = NULL, TreeNode *rightChild = NULL)
    {
        this->data = data;
        this->leftChild = leftChild;
        this->rightChild = rightChild;
    }
    /*
    int getData()//제대로 나오는지 확인하기 위한 함수
    {
        return (data);
    }*/
};

class BST {
public:
    BST(int data = 0)
    {
        root = new TreeNode(data);
    }
    bool IsEmpty()const
    {
        return (root == NULL);
    }
    TreeNode *Get(int k);
    void Insert(int thePair);
    int NonrecInorder();
private:
    TreeNode *root;
};

TreeNode* BST::Get(int k)//값을 가지고 있는 노드의 주소를 반환
{
    TreeNode *currentNode = root;
    while(currentNode)
    {
        if (k < currentNode->data)
            currentNode = currentNode->leftChild;
        else if (k > currentNode->data)
            currentNode = currentNode->rightChild;
        else
            return (currentNode);
    }
    return 0;
}

void BST::Insert(int thePair)
{
    TreeNode *p = root, *pp = 0;
    while (p)
    {
        pp = p;
        if (thePair < p->data)
            p = p->leftChild;
        else if (thePair > p->data)
            p = p->rightChild;
        else
        {
            //같으면 아무것도 하지 않는다.
            return ;
        }
    }
    p = new TreeNode(thePair);
    if (root)
        if (thePair < pp->data)
            pp->leftChild = p;
        else
            pp->rightChild = p;
    else
        root = p;
}

int BST::NonrecInorder()//순회하면서 트리 내 정수 합 리턴
{
    Stack<TreeNode*> s;
    int sum = 0;
    TreeNode *currentNode = root;
    cout << "AO LIST : ";
    while (1)
    {
        while (currentNode)
        {
            s.Push(currentNode);
            currentNode = currentNode->leftChild;
        }
        if (s.IsEmpty())
            return(sum);
        currentNode = s.Top();
        s.Pop();
        cout << currentNode->data << " ";
        sum = sum + currentNode->data;
        currentNode = currentNode->rightChild;
    }
    return (sum);
}

int isinChar(string arr)//오류 시 -1, 제대로 된 입력 시 1 반환
{
    int i = 0;
    //첫번째 인덱스가 유효하면(-이거나 0부터 9 사이이면)
    if (arr[0] == '-' || arr[0] == '+' || (arr[0] >= '0' && arr[0] <= '9'))
    {
        i++;
    }
    else
    {
        return (-1);
    }
    //1부터 끝까지 char있는지 검사
    for(i = 1; i < arr.size(); i++)
    {
        if (!(arr[i] >= '0' && arr[i] <= '9'))
        {
            return (-1);
        }
    }
    return (1);
}

int inputError(string input, vector<int> *arr)//오류 시 -1반환. 성공 시 1반환
{
    if (isinChar(input) == 1)
    {
        arr->push_back(stoi(input));
    }
    else
    {
        return (-1);
    }
    return (1);
}

int main(void)
{
    vector<int> arr;
    string input;
    cin >> input;
    while (input != "#")
    {
        if (inputError(input, &arr) == -1)
        {
            cout << "wrong input. rewrite number first." << endl;
            arr.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        cin >> input;
    }
    //이원탐색트리에 삽입하기
    BST bst = BST(arr[0]);
    for(int i = 1; i < arr.size(); i++)
    {
        int temp = arr[i];
        bst.Insert(temp);
    }
    int sum = bst.NonrecInorder();
    cout << endl << "SUM : " << sum << endl;
    return 0;
}