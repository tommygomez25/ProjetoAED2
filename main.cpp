#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;
int main() {
    string fileName;
    cout << "NAME OF THE FILE? " ; cin >> fileName;

    vector<vector<string>> content;
    vector<string> row;
    string line,word;

    fstream file(fileName,ios::in);
    if (file.is_open()){
        while(getline(file,line)){

            row.clear();
            stringstream str(line);

            while(getline(str,word,',')){
                row.push_back(word);
            }
            content.push_back(row);
        }
    }
    else {
        cout << "Cant open";
    }

    for(int i=0;i<content.size();i++)
    {
        for(int j=0;j<content[i].size();j++)
        {
            cout<<content[i][j]<<" ";
        }
        cout<<"\n";
    }

}

