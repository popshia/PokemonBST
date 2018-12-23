// 10627130 資工二甲 林冠良 & 10627131 資工二甲 李峻瑋 // CodeBlocks 17.12
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <iomanip>
#include <algorithm>
#include <time.h>

using namespace std ;

typedef struct DataStruct {
    string number = "0" ;
    string name = "\0" ;
    string type1 = "\0" ;
    int total = 0 ;
    int HP = 0 ;
    int ATK = 0 ;
    int DEF = 0 ;
    string whole = "\0" ;
    DataStruct* parent = NULL ;
    DataStruct* leftChild = NULL ;
    DataStruct* rightChild = NULL ;
    DataStruct* same = NULL ;
    bool visit = false ;
} DataStruct ;

static ifstream input ;
static ofstream output ;
static string FileN = "0" ;
static int Count = 1 ;

class CollegeHighGoGoGo {
    int visit = 0 ;
    DataStruct* root = NULL ;
    vector<DataStruct*> qualified ;
public:
    DataStruct* GetRoot() {
        return root ;
    } // get root

    int GetHeight( DataStruct* depth ) {
        if ( depth == NULL ) return 0 ;
        else {
            int leftDepth = GetHeight( depth->leftChild ) ;
            int rightDepth = GetHeight( depth->rightChild ) ;
            if ( leftDepth > rightDepth ) return leftDepth+1 ;
            else return rightDepth+1 ;
        } //else
    } // GetHeight

    void Insert( DataStruct* tempData ) {
        bool NotYet = true ;
        DataStruct* sameWalker = NULL ;
        DataStruct* treeWalker = NULL ;


        if ( root == NULL ) {
            root = tempData ;
            tempData = NULL ;
            // cout << root->HP << endl ;
        }
        else {
            treeWalker = root ;
            do {
                // cout << treeWalker->HP << "\t" << tempData->HP << endl ;
                if ( treeWalker->HP == tempData->HP ) {
                    sameWalker = treeWalker ;
                    while ( sameWalker->same != NULL )
                        sameWalker = sameWalker->same ;
                    tempData->parent = sameWalker ;
                    sameWalker->same = tempData ;
                    NotYet = false ;
                    // cout << "same" << endl;
                } // if

                else if ( treeWalker->HP < tempData->HP ) {
                    if ( treeWalker->rightChild == NULL ) {
                        tempData->parent = treeWalker ;
                        treeWalker->rightChild = tempData ;
                        NotYet = false ;
                        // cout << "larger" << endl;
                    } // if

                    else treeWalker = treeWalker->rightChild ;
                } // if

                else if ( treeWalker->HP > tempData->HP ) {
                    if ( treeWalker->leftChild == NULL ) {
                        tempData->parent = treeWalker ;
                        treeWalker->leftChild = tempData ;
                        NotYet = false ;
                        // cout << "smaller" << endl;
                    } // if

                    else treeWalker = treeWalker->leftChild ;
                } // if
            } while ( NotYet ) ;
        } // else
    } // Insert by HP, print out the data

    void Analyze() {
        root = NULL ;
        DataStruct* tempData = NULL ;
        string value = "\0" ;
        getline( input, value ) ; // read the labels in the first line
        tempData = new DataStruct ;
        cout << "\t#\tName\t\t\t\tType 1\t\tHP\tAttack\tDefense" << endl ;

        while ( getline( input, value ) ) {
            tempData->whole = value ;
            // cout << tempData->whole << endl ;
            vector<string> cut ;
            string token ;
            istringstream cutStream( value ) ;

            while ( getline( cutStream, token, '\t' ) ) // cut the token one by one
                cut.push_back( token ) ;

            tempData->number = cut[0] ;
            if ( Count < 10 ) cout << "[  " << Count << "]\t" << cut[0] << "\t" ;
            else if ( Count >= 10 && Count < 100 ) cout << "[ " << Count << "]\t" << cut[0] << "\t" ;
            else if ( Count >= 100 ) cout << "[" << Count << "]\t" << cut[0] << "\t" ;
            // print number
            tempData->name = cut[1] ;
            if ( strlen( cut[1].c_str() ) < 8 ) cout << cut[1] << "\t\t\t\t" ;
            else if ( strlen( cut[1].c_str() ) >= 8 && strlen( cut[1].c_str() ) < 17 ) cout << cut[1] << "\t\t\t" ;
            else cout << cut[1] << "\t\t" ;
            // print name
            tempData->type1 = cut[2] ;
            if ( strlen( cut[2].c_str() ) < 8 ) cout << cut[2] << "\t\t" ;
            else cout << cut[2] << "\t" ;
            // print type
            tempData->total = atoi( cut[4].c_str() ) ;
            tempData->HP = atoi( cut[5].c_str() ) ;
            cout << cut[5] << "\t" ;
            // print HP
            tempData->ATK = atoi( cut[6].c_str() ) ;
            cout << cut[6] << "\t" ;
            // print ATK
            tempData->DEF = atoi( cut[7].c_str() ) ;
            cout << cut[7] << endl ;

            Count++ ;
            // cout<< tempData->HP<< endl ;
            Insert( tempData ) ;
            tempData = NULL ;
            tempData = new DataStruct ;
        } // get the whole file

        DataStruct* depth = root ;
        cout << "HP Tree Height: " << GetHeight( depth ) << endl << endl ;
    } // Analyze the whole input file

    void SortAndPrintVisit() {
        for ( int one = 0 ; one < qualified.size() ; one++ ) {
            for ( int two = one+1 ; two < qualified.size() ; two++ ) {
                if ( qualified[one]->HP < qualified[two]->HP ) swap( qualified[one], qualified[two] ) ;
                else if ( qualified[one]->HP == qualified[two]->HP ) {
                    if ( atoi( qualified[one]->number.c_str() ) > atoi( qualified[two]->number.c_str() ) ) {
                        cout << qualified[one]->number << " " << qualified[two]->number << endl ;
                        swap( qualified[one], qualified[two] ) ;
                    }
                } // same hp
            } // for
        } // for
        cout << "\t#\tName\t\t\t\tType 1\t\tHP\tTotal\tAttack\tDefense" << endl ;
        for ( int i = 0 ; i < qualified.size() ; i++ ) {
            if ( i < 9 ) cout << "[  " << i+1 << "]\t" << qualified[i]->number << "\t" ;
            else if ( i >= 9 && Count < 100 ) cout << "[ " << i+1 << "]\t" << qualified[i]->number << "\t" ;
            else if ( i >= 100 ) cout << "[" << i+1 << "]\t" << qualified[i]->number << "\t" ;
            if ( strlen( qualified[i]->name.c_str() ) < 8 ) cout << qualified[i]->name << "\t\t\t\t" ;
            else if ( strlen( qualified[i]->name.c_str() ) >= 8 && strlen( qualified[i]->name.c_str() ) < 17 ) cout << qualified[i]->name << "\t\t\t" ;
            else cout << qualified[i]->name << "\t\t" ;
            // print name
            if ( strlen( qualified[i]->type1.c_str() ) < 8 ) cout << qualified[i]->type1 << "\t\t" ;
            else cout << qualified[i]->type1 << "\t" ;
            // print type
            cout << qualified[i]->total << "\t" ;
            // print total
            cout << qualified[i]->HP << "\t" ;
            // print HP
            cout << qualified[i]->ATK << "\t" ;
            // print ATK
            cout << qualified[i]->DEF << endl ;
        } // print out the datas
        cout << "Number of visited nodes = " << visit << endl << endl ;
        visit = 0 ;
        qualified.clear() ;
    } // Sort the qualified vector

    void Filter( int data, DataStruct* johnnyWalker ) {
        DataStruct* sameWalker = NULL ;
        if ( johnnyWalker == NULL ) return ;
        if ( johnnyWalker->HP >= data ) {
            if ( johnnyWalker->same == NULL ) qualified.push_back( johnnyWalker ) ;
            else {
                sameWalker = johnnyWalker ;
                while ( sameWalker != NULL ) {
                    qualified.push_back( sameWalker ) ;
                    sameWalker = sameWalker->same ;
                } // same
            } // else
        } // found
        if ( johnnyWalker->HP >= data ) Filter( data, johnnyWalker->leftChild ) ;
        Filter( data, johnnyWalker->rightChild ) ;
        if ( johnnyWalker->visit == false ) {
            visit++ ;
            johnnyWalker->visit = true ;
        } // check if visit or not
    } // Filter and save to new vector

    void Delete() {
        DataStruct* Largest = GetRightMost() ;
        DataStruct* temp = NULL ;
        if ( !Largest ) cout << "BST empty!" << endl ;
        else {
            if ( Largest->leftChild && Largest->rightChild ) {
                cout << Largest->whole << endl ;
                cout << "1" << endl ;
                temp = Largest->same ;
                temp->leftChild = Largest->leftChild ;
                Largest = Largest->parent ;
                Largest->rightChild = NULL;
                Largest->rightChild = temp ;
            } // if

            else if ( !Largest->leftChild && Largest->rightChild ) {
                cout << Largest->whole << endl ;
                cout << "2" << endl ;
                temp = Largest->same ;
                Largest = Largest->parent ;
                Largest->rightChild = NULL;
                Largest->rightChild = temp ;
            } // if

            else{
                cout << Largest->whole << endl ;
                cout << "3" << endl ;
                Largest = Largest->parent ;
                Largest->rightChild = NULL;
            } // else
        } // else
    } // Delete

    DataStruct* GetRightMost() {
        DataStruct* walk = root ;
        if ( walk->rightChild == NULL ) return walk ;
        while ( walk->rightChild != NULL )
            walk = walk->rightChild ;
        return walk ;
    } // get the biggest data
} ;

int main() {
    int command = 0 ;
    bool continueOrNot = false ;
    CollegeHighGoGoGo dataBase ;

    do {
        cout << "********************************************************" << endl ; // welcome message
        cout << "*****                  Pokemon BST                 *****" << endl ;
        cout << "***** 0 : Quit                                     *****" << endl ;
        cout << "***** 1 : Input by HP, and count the tree height   *****" << endl ;
        cout << "***** 2 : Filter and show                          *****" << endl ;
        cout << "***** 3 : Delete the largest node                  *****" << endl ;
        cout << "********************************************************" << endl ;
        cout << endl << "Please enter your choice:" << endl ;

        cin >> command ; // read in user command
        cout << endl ;

        if ( command == 0 ) { // bye :(((
            cout << "Bye :(((" << endl ;
            return 0 ;
        } // quit

        else if ( command > 3 || command < 0 ) {
            cout << "Error command! please enter an acceptable command:" << endl << endl ;
            continueOrNot = true ;
        } // wrong command

        else if ( command == 1 ) { // read, count and copy
            bool function1Confirm = false ;

            do {
                cout << "Please enter the file you want to analyze or [0] to quit:" << endl ;
                cin >> FileN ;

                if ( FileN == "0" ) {
                    function1Confirm = true ;
                    continueOrNot = true ;
                } // quit

                else {
                    string fileName = "input" + FileN + ".txt" ;
                    input.open( fileName.c_str() ) ;
                    if ( input.is_open() ) {
                        dataBase.Analyze() ;
                        function1Confirm = true ;
                        continueOrNot = true ;
                    } // open successfully
                    else cout << "*****  " << fileName << " does not exist!  *****" << endl ;
                } // open file and input data to BST
            } while( ! function1Confirm ) ;

            Count = 0 ;
            FileN = "0" ;
            input.close() ;
            output.close() ;
        } // mission 1

        else if ( command == 2 ) {
            bool function2Confirm = false ;

            do {
                if ( dataBase.GetRoot() == NULL ) {
                    cout << "*****  Execute Mission 1 first !  *****" << endl << endl ;
                    function2Confirm = true ;
                    continueOrNot = true ;
                } // first time
                else {
                    cout << "Type in a Threshold ( a positive integer ) or [0] to quit:" << endl ;
                    cin >> FileN ;
                    if ( atoi( FileN.c_str() ) < 1 || atoi( FileN.c_str() ) > dataBase.GetRightMost()->HP ) {
                        cout << "*****  " << FileN << " is not in the range of [1," << dataBase.GetRightMost()->HP << "]  *****" << endl ;
                        cout << "Try again!" << endl ;
                        cin >> FileN ;
                        function2Confirm = true ;
                    } // out of range
                    else {
                        DataStruct* johnnyWalker = dataBase.GetRoot() ;
                        dataBase.Filter( atoi( FileN.c_str() ), johnnyWalker ) ;
                        dataBase.SortAndPrintVisit() ;
                        function2Confirm = true ;
                    } // else
                } // function run
            } while ( ! function2Confirm ) ;

            Count = 0 ;
            FileN = "0" ;
            input.close() ;
            output.close() ;
        } // mission 2

        else if ( command == 3 ) {
            bool function3Confirm = false ;

            do {
                if ( dataBase.GetRoot() == NULL ) {
                    cout << "*****  Execute Mission 1 first !  *****" << endl << endl ;
                    function3Confirm = true ;
                    continueOrNot = true ;
                } // first time
                else {
                    DataStruct* johnnyWalker = dataBase.GetRoot() ;
                    cout << "#    Name    Type 1    Type 2    Total    HP    Attack    Defense    Sp. Atk    Sp. Def    Speed    Generation      Legendary" << endl ;
                    dataBase.Delete() ;
                    johnnyWalker = dataBase.GetRoot() ;
                    cout << "HP tree height = " << dataBase.GetHeight( johnnyWalker ) << endl ;
                    function3Confirm = true ;
                } // delete
            } while ( ! function3Confirm ) ;
        } // mission 3
    } while( continueOrNot ) ;
} // Main function
