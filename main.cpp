#include <iostream>
#include <iomanip>
#include "question.h"
#include <fstream>
#include <vector>
#include <sstream>
#include "json.hpp"
#include <chrono>
#include <bits/stdc++.h>
using namespace std;
using json = nlohmann::json;

//turns the messy questions file into a nice easy to read json file
void prettyFile()
{
    ifstream fin("messy_questions.json");
    json j;
    fin >> j;
    ofstream o("questions.json");
    o << setw(4) << j << endl;
}

//reads the questions from the json file into the questions vector
void readFile(vector<Question> &questions)
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
    for (string s : partial) //I can't decide if this parsing solution is very elegant or very bad. But it works!
    {
        int start = s.find("\":\"");
        int end = s.find("\":\"", start + 1);
        string date = s.substr(start + 3, end - start - 12);
        //  cout << date << endl;
        //this logic should work for all of the strings, just updating the -12 value to match the length of the key field
        //this will allow us to dynamically find the substrings based upon their location relative to the keys

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

        if (que.find("j-archive") != string::npos)
        { //this skips any of the video/picture questions with links
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

        if (round == "Final Jeopardy!" || round == "Tiebreaker") //deals with the fact that these have null values
        {
            Question temp = Question(cat, date, que, ans, round, show);
            // cout << temp.getQuestion() << endl;
            // cout << temp.getValue() << endl;
            questions.push_back(temp);

            continue;
        }
        else
        {

            start = s.find("$", end);
            end = s.find("}", start + 1);
            string val = s.substr(start + 1, end - start - 2);
            //cout << val << endl;
            for (int i = 0, len = val.size(); i < len; i++)
            {
                // check whether parsing character is punctuation or not
                if (ispunct(val[i]))
                {
                    val.erase(i--, 1);
                    len = val.size();
                }
            }
            int value = stoi(val);

            questions.push_back(Question(cat, date, que, value, ans, round, show));
        }
    }
}

//function to print menu and get input
int menu()
{
    int option = -1;
    cout << "\nWelcome to the Jeopardy! Simulator\n1. Practice by Category\n";
    cout << "2. Practice by Dollar Amount\n3. Random Final Jeopardy\n";
    cout << "4. Random Question\n5. Lifetime Statistics\n6. Sorting Algorithm Performance\n7. Exit\n";
    cin >> option;
    while (option > 7 || option < 1)
    {
        cout << "Please enter a valid menu selection!" << endl;
        cin >> option;
    }
    return option;
}

//helper function to swap two Questions in a vector
void swap(vector<Question> &arr, int a, int b)
{
    Question temp = arr[a];
    arr[a] = arr[b];
    arr[b] = temp;
}

//helper function for quicksort
int partition(vector<Question> &questions, int left, int right)
{
    int pivotIndex = left + (right - left) / 2; //selects middle index as the pivot
    int pivotValue = questions[pivotIndex].getValue();
    int up = left, down = right;
    while (up <= down)
    {
        while (questions[up].getValue() < pivotValue)
        { //iterate until up is greater than the pivot
            up++;
        }
        while (questions[down].getValue() > pivotValue)
        { //iterate until down is less than the pivot
            down--;
        }
        if (up <= down)
        {
            swap(questions, up, down);
            up++;
            down--;
        }
    }
    return up;
}
void quickSort(vector<Question> &questions, int left, int right)
{
    if (left < right)
    {
        int pivotIndex = partition(questions, left, right);
        quickSort(questions, left, pivotIndex - 1);
        quickSort(questions, pivotIndex, right);
    }
}

// void heapSort(vector<Question> &questions, vector<Question> sorted)
// {
//     //int size = questions.size();
//     make_heap(questions.begin(), questions.end());

//     while (!questions.empty())
//     {
//         Question max = questions.front();
//         pop_heap(questions.begin(), questions.end());
//         sorted.push_back(max);
//     }

//     //return sorted;
// }

void writeScore(string name, int correct, int total){
    fstream out;
    out.open("scores.csv", ios::out | ios::app); //opens an existing file or creates a new one

    double percent = correct / total;
    out << name << ", " << correct << ", " << total << ", " << percent << ", " << endl;

    out.close();
}

int main()
{
    vector<Question> questions; //vector of all questions
    vector<Question> no_final;  //vector of questions without final jeopardys because their values can't be sorted
    cout << "Loading Jeopardy! questions..." << endl;
    readFile(questions);
    cout << "Successfully loaded all " << questions.size() << " Jeopardy! questions." << endl;

    string name; //holds the initials to track users
    cout << "Please enter your initials for score tracking: ";
    cin >> name;
    int correct, total = 0; //sets up score tracking features

    bool running;
    while (running)
    {
        int option = menu();

        if (option == 1)
        {
        }
        else if (option == 2)
        {
        }
        else if (option == 3)
        {
        }
        else if (option == 4)
        {
        }
        else if (option == 5)
        {
        }
        else if (option == 6)
        {
            cout << "Removing unsortable Final Jeopardy! questions..." << endl;
            for (Question q : questions)
            {
                if (q.getRound() != "Final Jeopardy!") //populating the vector without final jeopardy questions
                {
                    no_final.push_back(q);
                }
            }
            cout << "Final Jeopardy! questions removed." << endl;
            auto start = chrono::high_resolution_clock::now(); //saves the time before quicksort

            quickSort(no_final, 0, no_final.size() - 1);

            auto end = chrono::high_resolution_clock::now();                                     //saves the time after quicksort
            double time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count(); //time between start and end
            time_taken *= 1e-9;
            cout << "\nTime to sort questions by dollar value using QuickSort: " << fixed << time_taken << setprecision(9)
                 << " seconds" << endl;

            cout << "\nResetting the sorted questions for the next sorting algorithm..." << endl;
            no_final.clear(); //empties the sorted vector
            for (Question q : questions)
            {
                if (q.getRound() != "Final Jeopardy!")
                {
                    no_final.push_back(q); //repopulating the vector so it is the same as it was pre-sort
                }
            }
            cout << "Questions successfully reset for the next sort." << endl;

            //heapSort
            // start = chrono::high_resolution_clock::now(); //saves the time before heapsort

            // vector<Question> sorted;
            // heapSort(no_final, sorted);

            // end = chrono::high_resolution_clock::now();                                   //saves the time after heapsort
            // time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count(); //time between start and end
            // time_taken *= 1e-9;
            // cout << "\nTime to sort questions by dollar value using QuickSort: " << fixed << time_taken << setprecision(9)
            //      << " seconds" << endl;
            // no_final.clear(); //empties the sorted vector
            // for (Question q : questions)
            // {
            //     if (q.getRound() != "Final Jeopardy!")
            //     {
            //         no_final.push_back(q); //repopulating the vector so it is the same as it was pre-sort
            //     }
            // }
            // cout << "Questions successfully reset for the next sort." << endl;
        }
        else if (option == 7)
        {
            cout << "Bye!" << endl;
            running = false;
        }
    }
    return 0;
}
