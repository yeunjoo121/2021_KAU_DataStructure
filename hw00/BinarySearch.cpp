#include <iostream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <string>
#include <sstream>
using namespace std;

void displayArr(vector<int> arr)
{
    for(int i = 0; i < arr.size(); i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void selectionSort(vector<int> *arr)
{
    int minIndex = 0;

    for (int i = 0; i < arr->size() - 1; i++)
    {
        minIndex = i;
        for (int j = i + 1; j < arr->size(); j++)
        {
            if ((*arr)[j] > (*arr)[minIndex])
            {
                minIndex = j;
            }
        }
        swap((*arr)[i], (*arr)[minIndex]);
    }
}

int BinarySearch(vector<int> arr, int target, int left, int right) 
{
    if (left > right)
        return (-1);

    int middle = (left + right) / 2;
    if (arr[middle] == target)
        return middle;
    else if (arr[middle] < target)
        return BinarySearch(arr, target, left, middle - 1);
    else
        return BinarySearch(arr, target, middle + 1, right);
}

int isinChar(string arr)
{
    int i = 0;
    //첫번째 인덱스가 유효하면(-이거나 0부터 9 사이이면)
    if (arr[0] == '-' || (arr[0] >= '0' && arr[0] <= '9'))
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

int makeArr(const string temp, vector<int> *arr, const int number)
{
    stringstream ss(temp);
    ss.str(temp);
    int flag = 0;
    int cnt = 0;

    string word;
    while (ss >> word)
    {
        if (isinChar(word) == 1)
        {
            arr->push_back(stoi(word));
            cnt++;
        }
        else
        {
            flag = 1;
            break;
        }
    }
    if (flag == 1)
        return (-1);
    if (cnt != number)
        return (0);
    return (1);
}

int main(void)
{
    string number;
    vector<int> arr;
    string key;
    char continueFlag = 'Y';
    char buffer[1000] = {0, };
    string temp;

    cout << "배열의 길이를 입력하시오." << endl;
    cin >> number;
    while (isinChar(number) == -1 || stoi(number) <= 0)
    {
        if (isinChar(number) == -1)
        {
            cout << "number must be integer. rewrite the number" << endl;
        }
        else
        {
            cout << "number must be greater than 0. rewrite the number" << endl;
        }
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "배열의 길이를 입력하시오." << endl;
        cin >> number;
    }
    cout << "배열에 넣을 값을 한번에 입력하시오." << endl;

    //스트림에 남아있는 공백문자 없애기
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cin.getline(buffer, 1000);
    
    temp = buffer;
    int res = makeArr(temp, &arr, stoi(number));//res 값이 1인 게 정상, 0이면 개수 충돌, -1이면 char입력된것
    while (res != 1)
    {
        memset(buffer, 0, 1000);//buffer 초기화
        arr.clear();//잘못된 값 넣은 것 모두 초기화
        if (res == -1)
        {
            cout << "value에 유효하지 않은 값이 있습니다. 다시 입력하세요" << endl;
        }
        else if (res == 0)
        {
            cout << "number와 입력한 값의 개수가 맞지 않습니다. 다시 입력하세요" << endl;
        }
        cout << "배열에 넣을 값을 한번에 입력하시오." << endl;
        cin.getline(buffer, 1000);
        temp = buffer;
        res = makeArr(temp, &arr, stoi(number));
    }
    cout << "입력 리스트 출력" << endl;
    displayArr(arr);
    cout << "정렬 리스트 출력" << endl;
    selectionSort(&arr);
    displayArr(arr);
    while (continueFlag == 'Y')//continueFlag가 Y일 때
    {
        cout << "Key> ";
        cin >> key;
        //search가 정수가 아님. 다시 key 입력받기
        if (isinChar(key) == -1)
        {
            cout << "Key is char. rewrite." << endl;
            continue;
        }
        int found = BinarySearch(arr, stoi(key), 0, arr.size() - 1);
        if (found >= 0)//찾음
        {
            cout << found << endl;
        }
        else if (found == -1)//못찾음
            cout << "Not found" << endl;
        while (continueFlag != 'N')//N되면 끝나야 함.
        {
            cout << "Continue(Y/N)?> ";
            cin >> continueFlag;
            if (continueFlag == 'N')
            {
                cout << "Bye.." << endl;
                break;
            }
            else if (continueFlag == 'Y')
            {
                break;
            }
            else//Y나 N도 아님
            {
                cout << "invalid char. rewrite (Y/N)" << endl;
            }
        }
    }
    return (0);
}