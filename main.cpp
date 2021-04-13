#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <unordered_map>
#include <map>
#include <vector>
#include <iterator>
#include <sstream>
#include <algorithm>
#include "json.hpp"
using namespace std;
using json = nlohmann::json;

class Question
{
    string category;
    string air_date;
    string question;
    string value;
    string answer;
    string round;
    string show_number;

public:
    Question(string c, string ad, string q, string v, string ans, string r, string num)
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
    { //constructor for Final Jeopardy Questions and Tiebreakers so the value is correctly handled
        category = c;
        air_date = ad;
        question = q;
        value = "n/a";
        answer = ans;
        round = r;
        show_number = num;
    }
};

void prettyFile() //turns the messy questions file into a nice easy to read json file
{
    ifstream fin("messy_questions.json");
    json j;
    fin >> j;
    ofstream o("questions.json");
    o << setw(4) << j << endl;
}

void printFile(vector<Question> &questions)
{
    ifstream inFile("questions.json");
    json j;
    inFile >> j; //populates the json object with the file data
    vector<string> partial;

    for (auto it = j.begin(); it != j.end(); it++)
    {
        partial.push_back(to_string(it.value())); //adds each question's data as one string into the vector
        //each index is a separate question
    }
    // cout << partial.size() << endl;
    for (string s : partial)
    {
        int start = s.find("\":\"");
        int end = s.find("\":\"", start + 1);
        string date = s.substr(start + 3, end - start - 12);
        //  cout << date << endl;
        //this logic should work for all of the strings, just updating the -12 value to match the length of the key field

        start = end;
        end = s.find("\":\"", start + 1);
        string ans = s.substr(start + 3, end - start - 14);
        // cout << ans << endl;

        start = end;
        end = s.find("\":\"", start + 1);
        string cat = s.substr(start + 3, end - start - 14);
        // cout << cat << endl;

        start = end;
        end = s.find("\":\"", start + 1);
        string que = s.substr(start + 4, end - start - 13);
        //cout << que << endl;

        if (que.find("j-archive") != string::npos){ //this skips any of the video/picture questions with links
            continue;
        }

        start = end;
        end = s.find("\":\"", start + 1);
        string round = s.substr(start + 3, end - start - 17);
        // cout << round << endl;

        start = end;
        end = s.find("\":\"", start + 1);
        string show = s.substr(start + 3, 4); //assuming that all show numbers will be four digits long, which I think is true
        // cout << show << endl;

        if (round == "Final Jeopardy!" || round == "Tiebreaker")
        { //deals with the fact that these have null values
            questions.push_back(Question(cat, date, que, ans, round, show));
            continue;
        }

        start = s.find("$", end);
        end = s.find("}", start + 1);
        string val = s.substr(start, end - start - 1);
        // cout << val << endl;

        questions.push_back(Question(cat, date, que, val, ans, round, show));
    }
}

int main()
{
    // //for option 1... practice by category. need to have all the category options in here. no dups.
    // //vector<string> categories;
    // unordered_map<string, int> categories;
    // //for option 2... practice by dollar amount. no dups.
    // unordered_map<string, int> d_amt;
    // //for option 3...final jeopardy
    // unordered_map<string, Question> fj;

    // //mega map
    // unordered_map<string, Question> qmap;

    // string full = "";
    // ifstream qfile;
    // qfile.open("JEOPARDY_QUESTIONS1.JSON");
    // if (qfile.is_open())
    // {
    //     while (!qfile.eof())
    //     {
    //         bool final = false;

    //         getline(qfile, full, '}');
    //         size_t pos = full.find(':');
    //         full.erase(0, pos + 1);

    //         //category
    //         pos = full.find(',');
    //         string cat = full.substr(0, pos);
    //         if (cat.find('\"') != string::npos)
    //         {
    //             cat.erase(remove(cat.begin(), cat.end(), '\"'), cat.end());
    //         }
    //         if (categories.find(cat) == categories.end())
    //         {
    //             categories.insert(make_pair(cat, 1));
    //         }

    //         full.erase(0, pos + 1);
    //         pos = full.find(':');
    //         full.erase(0, pos + 1);

    //         //air date
    //         pos = full.find(',');
    //         string ad = full.substr(0, pos);
    //         if (ad.find('\"') != string::npos)
    //         {
    //             ad.erase(remove(ad.begin(), ad.end(), '\"'), ad.end());
    //         }

    //         full.erase(0, pos + 1);
    //         pos = full.find(':');
    //         full.erase(0, pos + 1);

    //         //question
    //         pos = full.find(',');
    //         string quest = full.substr(0, pos);
    //         if (quest.find('\"') != string::npos)
    //         {
    //             quest.erase(remove(quest.begin(), quest.end(), '\"'), quest.end());
    //         }

    //         full.erase(0, pos + 1);
    //         pos = full.find(':');
    //         full.erase(0, pos + 1);

    //         //value
    //         pos = full.find(',');
    //         string val = full.substr(0, pos);
    //         if (val.find('\"') != string::npos)
    //         {
    //             val.erase(remove(val.begin(), val.end(), '\"'), val.end());
    //         }
    //         if (d_amt.find(val) == d_amt.end())
    //         {
    //             d_amt.insert(make_pair(val, 1));
    //         }

    //         full.erase(0, pos + 1);
    //         pos = full.find(':');
    //         full.erase(0, pos + 1);

    //         //answer
    //         pos = full.find(',');
    //         string ans = full.substr(0, pos);
    //         if (ans.find('\"') != string::npos)
    //         {
    //             ans.erase(remove(ans.begin(), ans.end(), '\"'), ans.end());
    //         }

    //         full.erase(0, pos + 1);
    //         pos = full.find(':');
    //         full.erase(0, pos + 1);

    //         //round
    //         pos = full.find(',');
    //         string round = full.substr(0, pos);
    //         if (round.find('\"') != string::npos)
    //         {
    //             round.erase(remove(round.begin(), round.end(), '\"'), round.end());
    //         }
    //         //check double jeopardy
    //         if (round == "Final Jeopardy!")
    //         {
    //             final = true;
    //         }

    //         full.erase(0, pos + 1);
    //         pos = full.find(':');
    //         full.erase(0, pos + 1);

    //         //show number
    //         pos = full.find(',');
    //         string sn = full.substr(0, pos);
    //         if (sn.find('\"') != string::npos)
    //         {
    //             sn.erase(remove(sn.begin(), sn.end(), '\"'), sn.end());
    //         }

    //         ////CREATING THE PAIR HERE DOES NOT WORK. NEED HELP
    //         auto q = new Question(cat, ad, quest, val, ans, round, sn);
    //         pair<string, Question> nq(round, q);
    //         qmap.insert(nq);

    //         if (final)
    //         {
    //             ////CREATING THE PAIR HERE DOES NOT WORK. NEED HELP
    //             fj.insert(make_pair(round, q));
    //         }
    //     }
    // }
    vector<Question> questions;
    printFile(questions);
    cout << "made it!" << endl;
    cout << questions.size();
    // int in;
    // cout << "Welcome to the Jeopardy! Simulator\n1. Practice by Category\n";
    // cout << "2. Practice by Dollar Amount\n3. Random Final Jeopardy\n";
    // cout << "4. Random Question\n5. Lifetime Statistics\n6. Exit";

    // cin >> in;

    // switch (in)
    // {
    // case 1:
    //     cout << "Which Category?\n";
    //     for (auto &i : categories)
    //     {
    //         cout << i.first << endl;
    //     }
    // case 2:
    // case 3:
    // case 4:
    // case 5:
    // case 6:
    //     break;
    // default:
    //     cout << "Please enter a valid number\n";
    // }
    return 0;
}
