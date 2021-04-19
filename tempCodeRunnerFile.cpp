start = chrono::high_resolution_clock::now(); //saves the time before heapsort

            vector<Question> sorted;
            heapSort(no_final, sorted);

            end = chrono::high_resolution_clock::now();                                   //saves the time after heapsort
            time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count(); //time between start and end
            time_taken *= 1e-9;
            cout << "\nTime to sort questions by dollar value using QuickSort: " << fixed << time_taken << setprecision(9)
                 << " seconds" << endl;
            no_final.clear(); //empties the sorted vector
            for (Question q : questions)
            {
                if (q.getRound() != "Final Jeopardy!")
                {
                    no_final.push_back(q); //repopulating the vector so it is the same as it was pre-sort
                }
            }
            cout << "Questions successfully reset for the next sort." << endl;