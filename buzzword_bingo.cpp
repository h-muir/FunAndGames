//Buzzword bingo for LSC seminar 1

#include <iostream> 
#include <string>
#include <fstream>
#include <vector>
#include <cmath>
#include <stdlib.h>
#include <assert.h>
//#include <bits/stdc++.h>

using namespace std;

//GLOBAL VARIABLES:
bool end_program;

template<typename T>
void print2DVector(vector< vector<T> > vec){
    int y = vec.size();
    int x = vec[0].size();
    for(int j = 0; j<y; ++j){
        for(int i = 0; i<x; ++i){
            cout << vec[j][i];
        }
        cout << "\n";
    }
}

void ready_to_play(){
    
    cout << "Ready to begin buzzword bingo? (yes/no) \n >> ";

    string play; 
    cin >> play;

    if(play == "no"){
        cout << "ending program, restart when ready" << endl;
        end_program = 1;
    }else if(play == "yes"){
        cout << "here is your bingo card: " << endl;
    }else{
        cout << "*invalid response* \n" << endl;
        ready_to_play();
    } 

}

void print_list(vector<string> word_vector){    
    cout << "word list length: " << word_vector.size() << endl;
    for(int i =0; i<word_vector.size(); ++i){
        cout << word_vector[i] << endl;
    }
}

bool repeated_num(int num, vector<int> existing_nums){
    bool flag = 0;
    for(int i=0; i< existing_nums.size(); ++i){
        if(num == existing_nums[i]){
            flag = 1;
            return flag;
        }
    }
    return flag;
}

vector < vector<string> > make_box(string word, int num, bool crossed){

    string str_num = to_string(num+1);
    int grid_x = 29;
    int grid_y = 11;
    vector<string> mid_row(grid_x, " ");
    mid_row[0] = "|";
    mid_row[grid_x-1] = "|";
    vector<string> top_row(grid_x, "-");
    top_row[0] = "o";
    top_row[grid_x-1] = "o";  
    int word_len = word.length();
    int left_space = (grid_x-word_len)/2;
    vector<string> word_row = mid_row;
    for(int i=0; i<word_len; ++i){
        assert(left_space+i+1 < grid_x && "word is too big for box");
        word_row[left_space+i+1] = word[i];
    }
    int top_space = grid_y/2;  
    vector< vector<string> > BOX(grid_y, mid_row);
    BOX[0] = top_row;
    BOX[grid_y-1] = top_row;
    BOX[top_space] = word_row; 
    if(num+1 <=9 ){
        BOX[top_space-1][grid_x/2+0] = "(";
        BOX[top_space-1][grid_x/2+1] = str_num;
        BOX[top_space-1][grid_x/2+2] = ")";
    }else if(num+1 >= 10){
        BOX[top_space-1][grid_x/2-1] = "(";
        BOX[top_space-1][grid_x/2+0] = str_num[0];
        BOX[top_space-1][grid_x/2+1] = str_num[1];
        BOX[top_space-1][grid_x/2+2] = ")";
    }
        

    if(crossed){
        for(int j =1; j<grid_y-1; ++j){
            if(j != top_space){
                BOX[j][3*j-1] = "\\";
                BOX[j][grid_x-3*j] = "/";
            }else{
                //BOX[top_space][grid_x/2] = "X";
            }
        }
    }

    return BOX;
}

void print3boxes(vector < vector<string> > BOX1, vector < vector<string> > BOX2, 
                    vector < vector<string> > BOX3){

    //assumes boxes all the same size:
    int y = BOX1.size();
    int x = BOX1[0].size();
    for(int j = 0; j<y; ++j){
        for(int i = 0; i<x; ++i){
            cout << BOX1[j][i];
        }
        cout << " ";
        for(int i = 0; i<x; ++i){
            cout << BOX2[j][i];
        }
        cout << " ";
        for(int i = 0; i<x; ++i){
            cout << BOX3[j][i];
        }

        cout << "\n";
    }


}

void print4boxes(vector < vector<string> > BOX1, vector < vector<string> > BOX2, 
                    vector < vector<string> > BOX3, vector < vector<string> > BOX4){

    //assumes boxes all the same size:
    int y = BOX1.size();
    int x = BOX1[0].size();
    for(int j = 0; j<y; ++j){
        for(int i = 0; i<x; ++i){
            cout << BOX1[j][i];
        }
        cout << " ";
        for(int i = 0; i<x; ++i){
            cout << BOX2[j][i];
        }
        cout << " ";
        for(int i = 0; i<x; ++i){
            cout << BOX3[j][i];
        }
        cout << " ";
        for(int i = 0; i<x; ++i){
            cout << BOX4[j][i];
        }

        cout << "\n";
    }


}

void print_card(vector<string> your_words, vector<bool> found_words, int n){

    assert(n==9 || n==16);
    assert(your_words.size()==n);
    assert(found_words.size()==n);

    if(n==9){

        vector< vector< vector<string> > > nine_boxes(9);

        for(int i = 0; i < 9; ++i){
            nine_boxes[i] = make_box(your_words[i], i, found_words[i]);
        }

        print3boxes(nine_boxes[0],nine_boxes[1],nine_boxes[2]); 
        print3boxes(nine_boxes[3],nine_boxes[4],nine_boxes[5]); 
        print3boxes(nine_boxes[6],nine_boxes[7],nine_boxes[8]);

    }else if(n==16){

        vector< vector< vector<string> > > sixteen_boxes(16);

        for(int i = 0; i < 16; ++i){
            sixteen_boxes[i] = make_box(your_words[i], i, found_words[i]);
        }

        print4boxes(sixteen_boxes[0],sixteen_boxes[1],sixteen_boxes[2], sixteen_boxes[3]); 
        print4boxes(sixteen_boxes[4],sixteen_boxes[5],sixteen_boxes[6], sixteen_boxes[7]); 
        print4boxes(sixteen_boxes[8],sixteen_boxes[9],sixteen_boxes[10], sixteen_boxes[11]);
        print4boxes(sixteen_boxes[12],sixteen_boxes[13],sixteen_boxes[14], sixteen_boxes[15]);

    }

}

void input_num(int n, int &word_num){

    //int word_num;

    cout << "wow Heather just said buzzword number: \n >> ";
    cin >> word_num;
    
    if(!cin){ //if(!cin.good()){
        cout << "that wasn't an integer - are you trying to break the program?! \n";// << endl;
        cout << "please be nice to buzzword_bingo.cpp and enter an integer: \n";// << endl;
        cin.clear();
        cin.ignore(100, '\n');
        input_num(n, word_num);
    }else if(word_num <= 0 || word_num > n){
        cout << "sorry, that's not a number between 1 and " << n << " \n";
        cout << "counting can be hard sometimes, but please try again: \n"; 
        input_num(n, word_num);
    }else{
        //continue to main
    }
}

int num_found_words(vector<bool> found_words){
    
    int num = 0;
    for(int i = 0; i<found_words.size(); ++i){
        if(found_words[i]){ ++num; }
    }

    return num;
}


int bingo_check(vector<bool> found_words, int n){

    assert(n==9 || n==16);
    assert(found_words.size()==n);

    //int=0 no bingo
    //int=1 for column bingo
    //int=2 for row bingo
    //int=3 for diagnonal bingo

    int draw_row = 0;
    int draw_column = 0;
    int diagonal1 = 0;
    int diagonal2 = 0;
    if(n==16){
        //row checks:
        for(int j=0; j<4; ++j){
            for(int i=0; i<4; ++i){
                if(i==0){
                    draw_row = 0;
                }
                if(found_words[j*4+i]){
                    ++draw_row;
                    if(draw_row == 4){
                        return 2;
                    }
                    if(j==i){
                        ++diagonal1;
                    }
                    if(diagonal1==4){
                        return 3;
                    }
                }
                if(i==0){
                    draw_column = 0;
                }
                if(found_words[i*4+j]){
                    ++draw_column;
                    if(draw_column==4){
                        return 1;
                    }
                    if(j==(3-i)){
                        ++diagonal2;
                    }
                    if(diagonal2==4){
                        return 3;
                    }
                }//end if's
            }//end i
        }//end j
    }//end if n==16

    return 0;

}


int main(){

    //pseudocode structure:
    /*
     * import words into word vector
     *
     * select 9 randomised words
     *
     * print numbered boxes for 9 words 
     * --> print box function
     *
     * read in a number to mark off box
     *
     * replace that number word with "X" 
     * --> reprint 9 boxes with X box
     *
     *  a reset option with the same words would be helpful
     *
     */

    cout << "-------------------------RULES----------------------------" << endl;
    cout << "Follow the prompts to mark off the numbered words on your " << endl;
    cout << "              buzzword bingo playing card.                " << endl;
    cout << "First person to mark of a line of four (row, column, or   " << endl;
    cout << "                diagonal), wins the game!                 " << endl;
    cout << "----------------------------------------------------------" << endl;

    ready_to_play();
    if(end_program){
        return 0;
    }
    ifstream buzzwords("buzz_words.txt");

    vector<string> word_list;
    string word;

    while( getline(buzzwords, word) ){
        //cout << word << endl;
        word_list.push_back(word);
    }
    //print_list(word_vector);
    int num_words = word_list.size();
    
    int n = 16;  //make 9 or 16
    vector<string> your_words(n);

    srand(time(NULL));
    vector<int> your_nums(n);
    int num;
    for(int i=0; i<n; ++i){
        num = rand()%(num_words-1)+1;
        //keep redrawing num if repeated 
        while(repeated_num(num, your_nums)){
            num = rand()%(num_words-1)+1;
        }
        your_nums[i] = num;
        your_words[i] = word_list[num];
    }


    vector<bool> found_words(n,0);
    
    int num_found = num_found_words(found_words);

    //cout << "your playing card: " << endl;
    //print_list(your_words);
    
    print_card(your_words, found_words, n);

    //cout << "you are *" << n-num_found << "* words away from BUZZWORD BINGO" << endl;


    int word_num;
    int bingo = 0;
    
    while(num_found < n && bingo==0){
        input_num(n, word_num); // contains cin with bounds checking in input_num function
        // cout << word_num;
        --word_num; //ie. 1-9 corresponds to 0-8 indexing
        if(found_words[word_num] == 0){
            found_words[word_num] = 1;
        }else if(found_words[word_num] == 1){
            found_words[word_num] = 0;
        }

        print_card(your_words, found_words, n);

        num_found = num_found_words(found_words);
        cout << "woohoo you have found *" << num_found << \
            "* words out of a total of *" << n << "* words." <<endl;

        bingo = bingo_check(found_words, n);
        //cout << "bingo check: " << bingo << endl;

    }
    
    cout <<   "  _     _  \n | |   (_) \n | |__  _ _ __   __ _  ___ \n | '_ \\| | '_ \\ / _` |/ _ \\ \n";
    cout <<   " | |_) | | | | | (_| | (_) | \n |_.__/|_|_| |_|\\__, |\\___/ \n                __/ |  \n";
    cout <<   "                |___/      \n \n";

    return 0;

}

