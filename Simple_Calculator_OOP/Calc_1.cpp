#include <iostream>
using namespace std;

class clsCalculator
{

private:
    float _Result = 0;
    float _LastNumber = 0;
    string _LastOperation = "clear";
    float _PreviousResult = 0;

    bool _isZero(float Number)
    {
        return (Number == 0);
    }

public:
    void Add(float Number)
    {
        _LastNumber = Number;
        _PreviousResult = _Result;
        _LastOperation = "Adding";
        _Result += Number;
    }

    void Substract(float Number)
    {
        _LastNumber = Number;
        _PreviousResult = _Result;
        _LastOperation = "Substracting";
        _Result -= Number;
    }

    void Divide(float Number)
    {
        _LastNumber = Number;
        if (_isZero(Number))
        {
            Number = 1;
        }
        _PreviousResult = _Result;
        _LastOperation = "Dividing";
        _Result /= Number;
    }

    void Multiply(float Number)
    {
        _LastNumber = Number;
        _PreviousResult = _Result;
        _LastOperation = "Multiplying";
        _Result *= Number;
    }

    float getFinalNumber()
    {
        return _Result;
    }

    void clear()
    {
        _LastNumber = 0;
        _PreviousResult = 0;
        _LastOperation = "Clear";
        _Result = 0;
    }

    void cancelLastOperation()
    {
        _LastNumber = 0;
        _LastOperation = "Canceling operation";
        _Result = _PreviousResult;
    }

    void printResult()
    {
        cout << "Rsult after " << _LastOperation << " " << _LastNumber << " is : " << _Result << endl;
    }
};

int main()
{
    clsCalculator claculator1;
    claculator1.Add(10);
    claculator1.printResult();

    claculator1.Multiply(2);
    claculator1.printResult();

    claculator1.Substract(3);
    claculator1.printResult();

    claculator1.cancelLastOperation();
    claculator1.printResult();

    return 0;
}