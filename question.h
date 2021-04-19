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
    struct HeapSwap
    {
        bool operator()(Question a, Question b)
        {
            if (a.getValue() < b.getValue())
            {
                return false;
            }
            else
            {
                return true;
            }
        }
    };

    Question()
    {
        category = "";
        air_date = "";
        question = "";
        value = 0;
        answer = "";
        round = "";
        show_number = "";
    }
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
    Question &operator=(const Question &t)
    {
        this->category = t.category;
        this->air_date = t.air_date;
        this->question = t.question;
        this->value = t.value;
        this->answer = t.answer;
        this->round = t.round;
        this->show_number = t.show_number;
        return *this;
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
    bool checkAnswer(string attempt)
    {
        if (attempt == "") //covers the edge case of an accidental submission
        {
            return false;
        }
        //put both strings to lowercase so the check is case insensitive
        transform(answer.begin(), answer.end(), answer.begin(), ::tolower);
        transform(attempt.begin(), attempt.end(), attempt.begin(), ::tolower);
        if (answer.find(attempt) == string::npos) //the attempt string is not found in the answer
            return false;
        else
            return true;
    }
    bool playNormal()
    {
        string attempt;
        cout << "\nThis is a " << round << " question!" << endl;
        cout << "This question's category is: " << category << endl;
        cout << "For $" << value << ", " << question << endl;
        cout << "What is your answer? ";
        getline(cin, attempt);
        return checkAnswer(attempt);
    }
    string getAnswer()
    {
        return answer;
    }
    string getDate()
    {
        return air_date;
    }
    string getNum()
    {
        return show_number;
    }
    bool playFinal()
    {
        if (round == "Final Jeopardy!")
        {
            string attempt;
            cout << "\nThis question's category is: " << category << endl;
            cout << "The question is: " << question << endl;
            getline(cin, attempt);
            return checkAnswer(attempt);
        }
        else
        {
            cout << "This question isn't a final Jeopardy! Mx. Programmer! Fix your code :D" << endl;
            return false;
        }
    }
};