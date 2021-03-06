#ifndef PROJ2_MATRIXSEARCHABLE_H
#define PROJ2_MATRIXSEARCHABLE_H

#include "Searchable.h"
#include <list>
#include <vector>
#include <string>
#include <string.h>

using namespace std;

template <class T>
class MatrixSearchable: public Searchable<T>{
    vector<vector<State<T>*>> matrix;
    State <T>* initialState;
    State <T>* goalState;
    int rowCount;

public:

    MatrixSearchable(){
        this->rowCount = 0;
    }

    State<T>* getInitialState(){
        return this->initialState;
    }
    State<T>* getGoalState(){
        return this->goalState;
    }

    void setGoalState(State<T>* state){
        this->goalState = state;
    }

    void setInitialState(State<T>* state){
        this->initialState = state;
    }

    list<State<T>*> getAllPossibleStates(State<T>* state){
        list<State<T>*> succerssors;
        string name = state->getState();
        State<T>* temp;

        char* divide = const_cast<char *>(name.c_str());
        int i = stoi(strtok(divide, ","));
        int j = stoi(strtok(NULL, ","));
        int matrixSize = matrix[0].size() - 1;

        if ((j + 1) <= matrixSize){
            temp = matrix[i][j + 1];
            if(temp->getCost() != -1) {
                succerssors.push_back(matrix[i][j + 1]); //right
            }
        }
        if ((j - 1) >= 0){
            temp = matrix[i][j - 1];
            if(temp->getCost() != -1) {
                succerssors.push_back(matrix[i][j - 1]); //left
            }
        }
        if ((i + 1) <= (this->rowCount - 1)){
            temp = matrix[i + 1][j];
            if(temp->getCost() != -1) {
                succerssors.push_back(matrix[i + 1][j]); //down
            }
        }
        if ((i - 1) >= 0){
            temp = matrix[i - 1][j];
            if(temp->getCost() != -1) {
                succerssors.push_back(matrix[i - 1][j]); //up
            }
        }

        return succerssors;

    }

    void addRowToMatrix(string row){
        vector<State<T>*> rowVector;
        double cost;
        int col = 0;

        char* temp = const_cast<char *>(row.c_str());
        temp = strtok(temp, ",");

        while (temp != NULL) {
            cost = atof(temp);
            temp = strtok(NULL, ",");

            State<string>* newState = new State<string>();
            string name = to_string(this->rowCount) + "," + to_string(col);

            newState->setState(name);
            newState->setCost(cost);
            rowVector.push_back(newState);

            col++;
        }

        this->matrix.push_back(rowVector);
        this->rowCount++;
    }

    void createMatrix(string newMatrixString){
        list<string>strings;
        char* temp = const_cast<char *>(newMatrixString.c_str());
        temp = strtok(temp, ";");

        while (temp != NULL){
            strings.push_back(temp);
            temp = strtok(NULL, ";");
        }

        int size = strings.size();
        int count = 0;

        list<string>::iterator it;
        it = strings.begin();

        while (count != size - 3) {
            string newRow = (*it);
            this->addRowToMatrix(newRow);
            it++;
            count++;
        }

        //the last values will be the initial state and the goal state
        string start = (*it);

        temp = const_cast<char*>(start.c_str());
        int i = stoi(strtok(temp, ","));
        int j = stoi(strtok(NULL, ","));

        setInitialState(this->getStateByIndex(i, j));
        it++;

        start = *it;
        temp = const_cast<char*>(start.c_str());


        i = stoi(strtok(temp, ","));
        j = stoi(strtok(NULL, ","));

        setGoalState(this->getStateByIndex(i, j));
    }

    State<T>* getStateByIndex(int row, int col){
        return this->matrix[row][col];
    }

    virtual ~MatrixSearchable(){
        int size = this->matrix.size();
        for(int i = 0; i < size; ++i){
            vector<State<string>*> temp = this->matrix[i];
            int tempSize = temp.size();
            for(int j = 0; j < tempSize; ++j){
                delete temp[j];
            }
        }
    };

};


#endif //PROJ2_MATRIXSEARCHABLE_H
