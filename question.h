#include <string>
#include <algorithm>
using namespace std;

class Question
{
    string category;
    string air_date;
    string question;
    int value;
    string answer;
    string round;
    string show_number;

public:
    Question(string c, string ad, string q, int v, string ans, string r, string num)
    {
        category = c;
        air_date = ad;
        question = q;
        value = v;
        answer = ans;
        round = r;
        show_number = num;
    }
    Question(string c, string ad, string q, string ans, string r, string num)
    { //constructor for Final Jeopardy Questions and Tiebreakers so the null value is correctly handled
        category = c;
        air_date = ad;
        question = q;
        value = 0;
        answer = ans;
        round = r;
        show_number = num;
    }
    string getRound()
    {
        return round;
    }
    int getValue()
    {
        return value;
    }
    string getQuestion()
    {
        return question;
    }
};