#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

//Notes:

// The assignment does not specify how to data in the text file is separated, The entire program assumes the txt
// file makes use of data which is separated using white spaces.

// all arrays have 100 spaces allocated as specified by the assignment

// line implies that the variable took an input

// assignment does not specify an OOP approach, regardless an OOP design could easily be implemented using the below
// due to mainly using functions

// Function which displays data:
void displayData(){

    ifstream  myFile("Tas.txt"); //opens Tas.txt file


    // Initializes relevant variables

    string eduLevel;
    int age, id, workingHours;
    int static count;

    // The data is temporarily stored and printed out

    if(myFile.is_open()){
        while (myFile >> eduLevel >> age >> id >> workingHours){
            cout<<eduLevel<<" "<<age<<" "<<id<<" "<<workingHours<<endl;

        }

    }
    // exception notifies if the file was not opened
    else{
        cout<<"File could not be opened"<<endl;

    }

    myFile.close();

}
// Function which counts entries:
int countEntries(){

    // the following function is the same as the above. The only difference being that it count the number of
    // entries

    ifstream  myFile("Tas.txt");


    string eduLevel;
    int age, id, workingHours;
    int count = 0;

    if(myFile.is_open()){
        while (myFile >> eduLevel >> age >> id >> workingHours){
            count++;
        }

    }
    else{
        cout<<"File could not be opened"<<endl;

    }

    myFile.close();

    return count;

}
// Function which removes entries with "Allum":
void filterData(){

    // Function creates a temporary txt file dubbed "temp.txt", it copies data from the already existing Tas.txt
    // However, if the status is == to "Allum" the program will skip over it and the next 3 values

    ofstream temporary("temp.txt");
    vector<string> temporary_data;

    ifstream  myFile("Tas.txt");
    string eduLevel;
    int age, id, workingHours;
    if(myFile.is_open()){
        while (myFile >> eduLevel >> age >> id >> workingHours){

            if (eduLevel == "Alum") continue; // line which removes Allum

            // converts everything to string for ease of storage in the vector defined above
            string data = eduLevel + " " + to_string(age) + " " + to_string(id) + " " + to_string(workingHours) + " ";
            temporary_data.push_back(data);
        }
    }
    else{
        cout<<"File could not be opened"<<endl;
    }
    for (string data: temporary_data){
        temporary << data;
    }
    myFile.close();
    temporary.close();
    remove("Tas.txt"); // deleting Tas.txt


    // Code for renaming tempt.txt to Tas.txt

    int result;
    char oldName[] ="temp.txt";
    char newName[] ="Tas.txt";
    result= rename(oldName , newName );

    if (!(result == 0))
        perror( "Error renaming file" );

}


// Function for adding new TAs:
void addNewTa() {

    // The same process of copying data from Tas.txt and storing it in a temporary file is also done here


    // code to get an array of IDs:
    // This stores all of the IDs in an array

    ifstream id_myFile("Tas.txt");
    string id_eduLevel;
    int id_age, id_, id_workingHours;
    int i = 0;

    int id_arr[100] = {};

    if (id_myFile.is_open()) {
        while (id_myFile >> id_eduLevel >> id_age >> id_ >> id_workingHours) {

            id_arr[i] = id_;
            i++;
        }
    } else {
        cout << "File could not be opened" << endl;

    }


    id_myFile.close();

    // code to get ID arr ends here

    ofstream temporary("temp.txt"); //creating temporary file
    vector<string> temporary_data;

    ifstream myFile("Tas.txt"); //opening Tas.txt
    string eduLevel;
    int age, id, workingHours;

    string line_eduLevel;
    int line_age, line_id, line_workingHours;

    // user input prompts includes exception handling:


    // Status


    cout << "enter status" << endl;
    cin >> line_eduLevel;


    while (!(line_eduLevel == "Grad" || line_eduLevel == "UGrad" || line_eduLevel == "Alum")) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Please enter a valid status (Grad, UGrad, Alum)" << endl;
        cin >> line_eduLevel;
    }

    // Age

    cout << "enter age" << endl;
    cin >> line_age;
    while (cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Please enter an integer" << endl;
        cin >> line_age;
    }

    // ID

    cout << "enter id" << endl;
    cin >> line_id;

    while (cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Please enter an integer" << endl;
        cin >> line_id;
    }

    // loop which checks if ID being entered is in use

    for (int j = 0; j < 100; ++j) {
        if (line_id == id_arr[j]) {
            cout << "ID already in use" << endl;
            cout << "Enter id:" << endl;
            cin >> line_id;
            while (cin.fail()) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Please enter an integer" << endl;
                cin >> line_id;
            }
        } else continue;
    }

    // Working Hours

    cout << "enter working hours" << endl;
    cin >> line_workingHours;
    while (cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Please enter an integer" << endl;
        cin >> line_workingHours;
    }

    // user input prompts end here


    // The below copies the data from Tas.txt and adds the data entered by the user to the copied data
    // it has the same functionality as filterData() minus removing Allum and adding the user inputted
    // data types.



    if (myFile.is_open()) {
        while (myFile >> eduLevel >> age >> id >> workingHours) {
            string data = eduLevel + " " + to_string(age) + " " + to_string(id) + " " + to_string(workingHours) + " ";
            temporary_data.push_back(data);
        }
        string line_data = line_eduLevel + " " + to_string(line_age) + " " + to_string(line_id) + " " +
                           to_string(line_workingHours) + " ";
        temporary_data.push_back(line_data);
    } else {
        cout << "File could not be opened" << endl;
    }
    for (string data: temporary_data) {
        temporary << data;
    }
    myFile.close();
    temporary.close();
    remove("Tas.txt");

    int result;
    char oldName[] = "temp.txt";
    char newName[] = "Tas.txt";
    result = rename(oldName, newName);

    if (!(result == 0))
        perror("Error renaming file");

    displayData(); // displaying data after completion


}


// All sorting functions:
// All of the sorting functions are copy pastes of one another with a single line of code changed across all of them
// (said line will be specified on the first function below; sortByStatus_ascending() )
// Due to the other sorting functions being identical copies, comments will allow be prevalent in sortByStatus_ascending()


// This the only sorting function I remember from COEN 243, I don't know how I would sort the entire database
// using built in sorting functions, hence this work around.

void sortByStatus_ascending(){

    string eduLevel_arr[100] = {};
    int age_arr[100] = {};
    int id_arr[100] = {};
    int workingHours_arr[100] = {};



    // code to get above arrays:

    ifstream  arrays_myFile("Tas.txt");
    string arrays_eduLevel;
    int arrays_age, arrays_id, arrays_workingHours;
    int i = 0;


    if(arrays_myFile.is_open()){
        while (arrays_myFile >> arrays_eduLevel >> arrays_age >> arrays_id >> arrays_workingHours){

            eduLevel_arr[i] = arrays_eduLevel;
            age_arr[i] = arrays_age;
            id_arr[i] = arrays_id;
            workingHours_arr[i] = arrays_workingHours;

            i++;
        }
    }
    else{
        cout<<"File could not be opened"<<endl;

    }
    arrays_myFile.close();


    string tempEduLevel_arr[100] = {};
    int tempAge_arr[100] = {}, tempId_arr[100] = {}, tempWorkingHours_arr[100] = {};


    string tempEdu;
    int tempAge, tempID, tempHours;


    vector<string> sortedData;


    //sorting:

    for (int k = 0; k < 100; ++k) {

        for (int j = k + 1; j < 100; ++j) {

            if(eduLevel_arr[k] > eduLevel_arr[j]){ /// This is the only line being changed among all the sorting functions


                //sorting all other columns in reference to the above

                //edu

                tempEdu = eduLevel_arr[k];
                eduLevel_arr[k] = eduLevel_arr[j];
                eduLevel_arr[j] = tempEdu;

                //age

                tempAge = age_arr[k];
                age_arr[k] = age_arr[j];
                age_arr[j] = tempAge;


                //id

                tempID = id_arr[k];
                id_arr[k] = id_arr[j];
                id_arr[j] = tempID;


                //hours

                tempHours = workingHours_arr[k];
                workingHours_arr[k] = workingHours_arr[j];
                workingHours_arr[j] = tempHours;

            }

        }

    }

    // the for loops are for removing all the white spaces and 0s which take up all the irrelevant array spots
    // at the start of the array

    for (int j = 0; j < 100; ++j) {
        if (eduLevel_arr[j] == "") continue;

        tempEduLevel_arr[j] = eduLevel_arr[j];
    }


    for (int j = 0; j < 100; ++j) {
        if (age_arr[j] == 0) continue;

        tempAge_arr[j] = age_arr[j];
    }

    for (int j = 0; j < 100; ++j) {
        if (id_arr[j] == 0) continue;
        tempId_arr[j] = id_arr[j];
    }

    for (int j = 0; j < 100; ++j) {
        if (workingHours_arr[j] == 0) continue;
        tempWorkingHours_arr[j] = workingHours_arr[j];
    }

    // Same idea as before replacing Tas.txt with the defined temp file.

    ofstream tempSorted("tempSorted.txt");

    for (int k = 0; k < 100; ++k) {

        if (tempWorkingHours_arr[k] == 0 || tempAge_arr[k] == 0 || tempId_arr[k] == 0) continue;
        if (tempEduLevel_arr[k] == "") continue;
        string sorted_data = tempEduLevel_arr[k] + " " + to_string(tempAge_arr[k]) + " "
                             + to_string(tempId_arr[k]) + " " + to_string(tempWorkingHours_arr[k]) + " ";

        sortedData.push_back(sorted_data);

    }

    for (string data: sortedData){
        tempSorted << data;
    }
    tempSorted.close();
    remove("Tas.txt");

    int result;
    char oldName[] ="tempSorted.txt";
    char newName[] ="Tas.txt";
    result= rename(oldName , newName );
    if (!(result == 0))
        perror( "Error renaming file" );


}
void sortByStatus_descending(){

    string eduLevel_arr[100] = {};
    int age_arr[100] = {};
    int id_arr[100] = {};
    int workingHours_arr[100] = {};



    // code to get above arrays:

    ifstream  arrays_myFile("Tas.txt");
    string arrays_eduLevel;
    int arrays_age, arrays_id, arrays_workingHours;
    int i = 0;


    if(arrays_myFile.is_open()){
        while (arrays_myFile >> arrays_eduLevel >> arrays_age >> arrays_id >> arrays_workingHours){

            eduLevel_arr[i] = arrays_eduLevel;
            age_arr[i] = arrays_age;
            id_arr[i] = arrays_id;
            workingHours_arr[i] = arrays_workingHours;

            i++;
        }
    }
    else{
        cout<<"File could not be opened"<<endl;

    }
    arrays_myFile.close();


    string tempEduLevel_arr[100] = {};
    int tempAge_arr[100] = {}, tempId_arr[100] = {}, tempWorkingHours_arr[100] = {};


    string tempEdu;
    int tempAge, tempID, tempHours;


    vector<string> sortedData;


    //sorting:

    for (int k = 0; k < 100; ++k) {

        for (int j = k + 1; j < 100; ++j) {

            if(eduLevel_arr[k] < eduLevel_arr[j]){

                //edu

                tempEdu = eduLevel_arr[k];
                eduLevel_arr[k] = eduLevel_arr[j];
                eduLevel_arr[j] = tempEdu;

                //age

                tempAge = age_arr[k];
                age_arr[k] = age_arr[j];
                age_arr[j] = tempAge;


                //id

                tempID = id_arr[k];
                id_arr[k] = id_arr[j];
                id_arr[j] = tempID;


                //hours

                tempHours = workingHours_arr[k];
                workingHours_arr[k] = workingHours_arr[j];
                workingHours_arr[j] = tempHours;

            }

        }

    }

    for (int j = 0; j < 100; ++j) {
        if (eduLevel_arr[j] == "") continue;

        tempEduLevel_arr[j] = eduLevel_arr[j];
    }


    for (int j = 0; j < 100; ++j) {
        if (age_arr[j] == 0) continue;

        tempAge_arr[j] = age_arr[j];
    }

    for (int j = 0; j < 100; ++j) {
        if (id_arr[j] == 0) continue;
        tempId_arr[j] = id_arr[j];
    }

    for (int j = 0; j < 100; ++j) {
        if (workingHours_arr[j] == 0) continue;
        tempWorkingHours_arr[j] = workingHours_arr[j];
    }

    ofstream tempSorted("tempSorted.txt");

    for (int k = 0; k < 100; ++k) {

        if (tempWorkingHours_arr[k] == 0 || tempAge_arr[k] == 0 || tempId_arr[k] == 0) continue;
        if (tempEduLevel_arr[k] == "") continue;
        string sorted_data = tempEduLevel_arr[k] + " " + to_string(tempAge_arr[k]) + " "
                             + to_string(tempId_arr[k]) + " " + to_string(tempWorkingHours_arr[k]) + " ";

        sortedData.push_back(sorted_data);

    }

    for (string data: sortedData){
        tempSorted << data;
    }
    tempSorted.close();
    remove("Tas.txt");

    int result;
    char oldName[] ="tempSorted.txt";
    char newName[] ="Tas.txt";
    result= rename(oldName , newName );
    if (!(result == 0))
        perror( "Error renaming file" );



}

void sortByAge_ascending(){

    string eduLevel_arr[100] = {};
    int age_arr[100] = {};
    int id_arr[100] = {};
    int workingHours_arr[100] = {};



    // code to get above arrays:

    ifstream  arrays_myFile("Tas.txt");
    string arrays_eduLevel;
    int arrays_age, arrays_id, arrays_workingHours;
    int i = 0;


    if(arrays_myFile.is_open()){
        while (arrays_myFile >> arrays_eduLevel >> arrays_age >> arrays_id >> arrays_workingHours){

            eduLevel_arr[i] = arrays_eduLevel;
            age_arr[i] = arrays_age;
            id_arr[i] = arrays_id;
            workingHours_arr[i] = arrays_workingHours;

            i++;
        }
    }
    else{
        cout<<"File could not be opened"<<endl;

    }
    arrays_myFile.close();


    string tempEduLevel_arr[100] = {};
    int tempAge_arr[100] = {}, tempId_arr[100] = {}, tempWorkingHours_arr[100] = {};


    string tempEdu;
    int tempAge, tempID, tempHours;


    vector<string> sortedData;


    //sorting:

    for (int k = 0; k < 100; ++k) {

        for (int j = k + 1; j < 100; ++j) {

            if(age_arr[k] > age_arr[j]){

                //edu

                tempEdu = eduLevel_arr[k];
                eduLevel_arr[k] = eduLevel_arr[j];
                eduLevel_arr[j] = tempEdu;

                //age

                tempAge = age_arr[k];
                age_arr[k] = age_arr[j];
                age_arr[j] = tempAge;


                //id

                tempID = id_arr[k];
                id_arr[k] = id_arr[j];
                id_arr[j] = tempID;


                //hours

                tempHours = workingHours_arr[k];
                workingHours_arr[k] = workingHours_arr[j];
                workingHours_arr[j] = tempHours;

            }

        }

    }

    for (int j = 0; j < 100; ++j) {
        if (eduLevel_arr[j] == "") continue;

        tempEduLevel_arr[j] = eduLevel_arr[j];
    }


    for (int j = 0; j < 100; ++j) {
        if (age_arr[j] == 0) continue;

        tempAge_arr[j] = age_arr[j];
    }

    for (int j = 0; j < 100; ++j) {
        if (id_arr[j] == 0) continue;
        tempId_arr[j] = id_arr[j];
    }

    for (int j = 0; j < 100; ++j) {
        if (workingHours_arr[j] == 0) continue;
        tempWorkingHours_arr[j] = workingHours_arr[j];
    }

    ofstream tempSorted("tempSorted.txt");

    for (int k = 0; k < 100; ++k) {

        if (tempWorkingHours_arr[k] == 0 || tempAge_arr[k] == 0 || tempId_arr[k] == 0) continue;
        if (tempEduLevel_arr[k] == "") continue;
        string sorted_data = tempEduLevel_arr[k] + " " + to_string(tempAge_arr[k]) + " "
                             + to_string(tempId_arr[k]) + " " + to_string(tempWorkingHours_arr[k]) + " ";

        sortedData.push_back(sorted_data);

    }

    for (string data: sortedData){
        tempSorted << data;
    }
    tempSorted.close();
    remove("Tas.txt");

    int result;
    char oldName[] ="tempSorted.txt";
    char newName[] ="Tas.txt";
    result= rename(oldName , newName );
    if (!(result == 0))
        perror( "Error renaming file" );

}
void sortByAge_descending(){

    string eduLevel_arr[100] = {};
    int age_arr[100] = {};
    int id_arr[100] = {};
    int workingHours_arr[100] = {};



    // code to get above arrays:

    ifstream  arrays_myFile("Tas.txt");
    string arrays_eduLevel;
    int arrays_age, arrays_id, arrays_workingHours;
    int i = 0;


    if(arrays_myFile.is_open()){
        while (arrays_myFile >> arrays_eduLevel >> arrays_age >> arrays_id >> arrays_workingHours){

            eduLevel_arr[i] = arrays_eduLevel;
            age_arr[i] = arrays_age;
            id_arr[i] = arrays_id;
            workingHours_arr[i] = arrays_workingHours;

            i++;
        }
    }
    else{
        cout<<"File could not be opened"<<endl;

    }
    arrays_myFile.close();


    string tempEduLevel_arr[100] = {};
    int tempAge_arr[100] = {}, tempId_arr[100] = {}, tempWorkingHours_arr[100] = {};


    string tempEdu;
    int tempAge, tempID, tempHours;


    vector<string> sortedData;


    //sorting:

    for (int k = 0; k < 100; ++k) {

        for (int j = k + 1; j < 100; ++j) {

            if(age_arr[k] < age_arr[j]){

                //edu

                tempEdu = eduLevel_arr[k];
                eduLevel_arr[k] = eduLevel_arr[j];
                eduLevel_arr[j] = tempEdu;

                //age

                tempAge = age_arr[k];
                age_arr[k] = age_arr[j];
                age_arr[j] = tempAge;


                //id

                tempID = id_arr[k];
                id_arr[k] = id_arr[j];
                id_arr[j] = tempID;


                //hours

                tempHours = workingHours_arr[k];
                workingHours_arr[k] = workingHours_arr[j];
                workingHours_arr[j] = tempHours;

            }

        }

    }

    for (int j = 0; j < 100; ++j) {
        if (eduLevel_arr[j] == "") continue;

        tempEduLevel_arr[j] = eduLevel_arr[j];
    }


    for (int j = 0; j < 100; ++j) {
        if (age_arr[j] == 0) continue;

        tempAge_arr[j] = age_arr[j];
    }

    for (int j = 0; j < 100; ++j) {
        if (id_arr[j] == 0) continue;
        tempId_arr[j] = id_arr[j];
    }

    for (int j = 0; j < 100; ++j) {
        if (workingHours_arr[j] == 0) continue;
        tempWorkingHours_arr[j] = workingHours_arr[j];
    }

    ofstream tempSorted("tempSorted.txt");

    for (int k = 0; k < 100; ++k) {

        if (tempWorkingHours_arr[k] == 0 || tempAge_arr[k] == 0 || tempId_arr[k] == 0) continue;
        if (tempEduLevel_arr[k] == "") continue;
        string sorted_data = tempEduLevel_arr[k] + " " + to_string(tempAge_arr[k]) + " "
                             + to_string(tempId_arr[k]) + " " + to_string(tempWorkingHours_arr[k]) + " ";

        sortedData.push_back(sorted_data);

    }

    for (string data: sortedData){
        tempSorted << data;
    }
    tempSorted.close();
    remove("Tas.txt");

    int result;
    char oldName[] ="tempSorted.txt";
    char newName[] ="Tas.txt";
    result= rename(oldName , newName );
    if (!(result == 0))
        perror( "Error renaming file" );

}

void sortByID_ascending(){

    string eduLevel_arr[100] = {};
    int age_arr[100] = {};
    int id_arr[100] = {};
    int workingHours_arr[100] = {};



    // code to get above arrays:

    ifstream  arrays_myFile("Tas.txt");
    string arrays_eduLevel;
    int arrays_age, arrays_id, arrays_workingHours;
    int i = 0;


    if(arrays_myFile.is_open()){
        while (arrays_myFile >> arrays_eduLevel >> arrays_age >> arrays_id >> arrays_workingHours){

            eduLevel_arr[i] = arrays_eduLevel;
            age_arr[i] = arrays_age;
            id_arr[i] = arrays_id;
            workingHours_arr[i] = arrays_workingHours;

            i++;
        }
    }
    else{
        cout<<"File could not be opened"<<endl;

    }
    arrays_myFile.close();


    string tempEduLevel_arr[100] = {};
    int tempAge_arr[100] = {}, tempId_arr[100] = {}, tempWorkingHours_arr[100] = {};


    string tempEdu;
    int tempAge, tempID, tempHours;


    vector<string> sortedData;


    //sorting:

    for (int k = 0; k < 100; ++k) {

        for (int j = k + 1; j < 100; ++j) {

            if(id_arr[k] > id_arr[j]){

                //edu

                tempEdu = eduLevel_arr[k];
                eduLevel_arr[k] = eduLevel_arr[j];
                eduLevel_arr[j] = tempEdu;

                //age

                tempAge = age_arr[k];
                age_arr[k] = age_arr[j];
                age_arr[j] = tempAge;


                //id

                tempID = id_arr[k];
                id_arr[k] = id_arr[j];
                id_arr[j] = tempID;


                //hours

                tempHours = workingHours_arr[k];
                workingHours_arr[k] = workingHours_arr[j];
                workingHours_arr[j] = tempHours;

            }

        }

    }

    for (int j = 0; j < 100; ++j) {
        if (eduLevel_arr[j] == "") continue;

        tempEduLevel_arr[j] = eduLevel_arr[j];
    }


    for (int j = 0; j < 100; ++j) {
        if (age_arr[j] == 0) continue;

        tempAge_arr[j] = age_arr[j];
    }

    for (int j = 0; j < 100; ++j) {
        if (id_arr[j] == 0) continue;
        tempId_arr[j] = id_arr[j];
    }

    for (int j = 0; j < 100; ++j) {
        if (workingHours_arr[j] == 0) continue;
        tempWorkingHours_arr[j] = workingHours_arr[j];
    }

    ofstream tempSorted("tempSorted.txt");

    for (int k = 0; k < 100; ++k) {

        if (tempWorkingHours_arr[k] == 0 || tempAge_arr[k] == 0 || tempId_arr[k] == 0) continue;
        if (tempEduLevel_arr[k] == "") continue;
        string sorted_data = tempEduLevel_arr[k] + " " + to_string(tempAge_arr[k]) + " "
                             + to_string(tempId_arr[k]) + " " + to_string(tempWorkingHours_arr[k]) + " ";

        sortedData.push_back(sorted_data);

    }

    for (string data: sortedData){
        tempSorted << data;
    }
    tempSorted.close();
    remove("Tas.txt");

    int result;
    char oldName[] ="tempSorted.txt";
    char newName[] ="Tas.txt";
    result= rename(oldName , newName );
    if (!(result == 0))
        perror( "Error renaming file" );




}
void sortByID_descending(){

    string eduLevel_arr[100] = {};
    int age_arr[100] = {};
    int id_arr[100] = {};
    int workingHours_arr[100] = {};



    // code to get above arrays:

    ifstream  arrays_myFile("Tas.txt");
    string arrays_eduLevel;
    int arrays_age, arrays_id, arrays_workingHours;
    int i = 0;


    if(arrays_myFile.is_open()){
        while (arrays_myFile >> arrays_eduLevel >> arrays_age >> arrays_id >> arrays_workingHours){

            eduLevel_arr[i] = arrays_eduLevel;
            age_arr[i] = arrays_age;
            id_arr[i] = arrays_id;
            workingHours_arr[i] = arrays_workingHours;

            i++;
        }
    }
    else{
        cout<<"File could not be opened"<<endl;

    }
    arrays_myFile.close();


    string tempEduLevel_arr[100] = {};
    int tempAge_arr[100] = {}, tempId_arr[100] = {}, tempWorkingHours_arr[100] = {};


    string tempEdu;
    int tempAge, tempID, tempHours;


    vector<string> sortedData;


    //sorting:

    for (int k = 0; k < 100; ++k) {

        for (int j = k + 1; j < 100; ++j) {

            if(id_arr[k] < id_arr[j]){

                //edu

                tempEdu = eduLevel_arr[k];
                eduLevel_arr[k] = eduLevel_arr[j];
                eduLevel_arr[j] = tempEdu;

                //age

                tempAge = age_arr[k];
                age_arr[k] = age_arr[j];
                age_arr[j] = tempAge;


                //id

                tempID = id_arr[k];
                id_arr[k] = id_arr[j];
                id_arr[j] = tempID;


                //hours

                tempHours = workingHours_arr[k];
                workingHours_arr[k] = workingHours_arr[j];
                workingHours_arr[j] = tempHours;

            }

        }

    }

    for (int j = 0; j < 100; ++j) {
        if (eduLevel_arr[j] == "") continue;

        tempEduLevel_arr[j] = eduLevel_arr[j];
    }


    for (int j = 0; j < 100; ++j) {
        if (age_arr[j] == 0) continue;

        tempAge_arr[j] = age_arr[j];
    }

    for (int j = 0; j < 100; ++j) {
        if (id_arr[j] == 0) continue;
        tempId_arr[j] = id_arr[j];
    }

    for (int j = 0; j < 100; ++j) {
        if (workingHours_arr[j] == 0) continue;
        tempWorkingHours_arr[j] = workingHours_arr[j];
    }

    ofstream tempSorted("tempSorted.txt");

    for (int k = 0; k < 100; ++k) {

        if (tempWorkingHours_arr[k] == 0 || tempAge_arr[k] == 0 || tempId_arr[k] == 0) continue;
        if (tempEduLevel_arr[k] == "") continue;
        string sorted_data = tempEduLevel_arr[k] + " " + to_string(tempAge_arr[k]) + " "
                             + to_string(tempId_arr[k]) + " " + to_string(tempWorkingHours_arr[k]) + " ";

        sortedData.push_back(sorted_data);

    }

    for (string data: sortedData){
        tempSorted << data;
    }
    tempSorted.close();
    remove("Tas.txt");

    int result;
    char oldName[] ="tempSorted.txt";
    char newName[] ="Tas.txt";
    result= rename(oldName , newName );
    if (!(result == 0))
        perror( "Error renaming file" );




}

void sortByWorkingHours_ascending(){

    string eduLevel_arr[100] = {};
    int age_arr[100] = {};
    int id_arr[100] = {};
    int workingHours_arr[100] = {};



    // code to get above arrays:

    ifstream  arrays_myFile("Tas.txt");
    string arrays_eduLevel;
    int arrays_age, arrays_id, arrays_workingHours;
    int i = 0;


    if(arrays_myFile.is_open()){
        while (arrays_myFile >> arrays_eduLevel >> arrays_age >> arrays_id >> arrays_workingHours){

            eduLevel_arr[i] = arrays_eduLevel;
            age_arr[i] = arrays_age;
            id_arr[i] = arrays_id;
            workingHours_arr[i] = arrays_workingHours;

            i++;
        }
    }
    else{
        cout<<"File could not be opened"<<endl;

    }
    arrays_myFile.close();


    string tempEduLevel_arr[100] = {};
    int tempAge_arr[100] = {}, tempId_arr[100] = {}, tempWorkingHours_arr[100] = {};


    string tempEdu;
    int tempAge, tempID, tempHours;


    vector<string> sortedData;


    //sorting:

    for (int k = 0; k < 100; ++k) {

        for (int j = k + 1; j < 100; ++j) {

            if(workingHours_arr[k] > workingHours_arr[j]){

                //edu

                tempEdu = eduLevel_arr[k];
                eduLevel_arr[k] = eduLevel_arr[j];
                eduLevel_arr[j] = tempEdu;

                //age

                tempAge = age_arr[k];
                age_arr[k] = age_arr[j];
                age_arr[j] = tempAge;


                //id

                tempID = id_arr[k];
                id_arr[k] = id_arr[j];
                id_arr[j] = tempID;


                //hours

                tempHours = workingHours_arr[k];
                workingHours_arr[k] = workingHours_arr[j];
                workingHours_arr[j] = tempHours;

            }

        }

    }

    for (int j = 0; j < 100; ++j) {
        if (eduLevel_arr[j] == "") continue;

        tempEduLevel_arr[j] = eduLevel_arr[j];
    }


    for (int j = 0; j < 100; ++j) {
        if (age_arr[j] == 0) continue;

        tempAge_arr[j] = age_arr[j];
    }

    for (int j = 0; j < 100; ++j) {
        if (id_arr[j] == 0) continue;
        tempId_arr[j] = id_arr[j];
    }

    for (int j = 0; j < 100; ++j) {
        if (workingHours_arr[j] == 0) continue;
        tempWorkingHours_arr[j] = workingHours_arr[j];
    }

    ofstream tempSorted("tempSorted.txt");

    for (int k = 0; k < 100; ++k) {

        if (tempWorkingHours_arr[k] == 0 || tempAge_arr[k] == 0 || tempId_arr[k] == 0) continue;
        if (tempEduLevel_arr[k] == "") continue;
        string sorted_data = tempEduLevel_arr[k] + " " + to_string(tempAge_arr[k]) + " "
                             + to_string(tempId_arr[k]) + " " + to_string(tempWorkingHours_arr[k]) + " ";

        sortedData.push_back(sorted_data);

    }

    for (string data: sortedData){
        tempSorted << data;
    }
    tempSorted.close();
    remove("Tas.txt");

    int result;
    char oldName[] ="tempSorted.txt";
    char newName[] ="Tas.txt";
    result= rename(oldName , newName );
    if (!(result == 0))
        perror( "Error renaming file" );

}
void sortByWorkingHours_descending(){

    string eduLevel_arr[100] = {};
    int age_arr[100] = {};
    int id_arr[100] = {};
    int workingHours_arr[100] = {};



    // code to get above arrays:

    ifstream  arrays_myFile("Tas.txt");
    string arrays_eduLevel;
    int arrays_age, arrays_id, arrays_workingHours;
    int i = 0;


    if(arrays_myFile.is_open()){
        while (arrays_myFile >> arrays_eduLevel >> arrays_age >> arrays_id >> arrays_workingHours){

            eduLevel_arr[i] = arrays_eduLevel;
            age_arr[i] = arrays_age;
            id_arr[i] = arrays_id;
            workingHours_arr[i] = arrays_workingHours;

            i++;
        }
    }
    else{
        cout<<"File could not be opened"<<endl;

    }
    arrays_myFile.close();


    string tempEduLevel_arr[100] = {};
    int tempAge_arr[100] = {}, tempId_arr[100] = {}, tempWorkingHours_arr[100] = {};


    string tempEdu;
    int tempAge, tempID, tempHours;


    vector<string> sortedData;


    //sorting:

    for (int k = 0; k < 100; ++k) {

        for (int j = k + 1; j < 100; ++j) {

            if(workingHours_arr[k] < workingHours_arr[j]){

                //edu

                tempEdu = eduLevel_arr[k];
                eduLevel_arr[k] = eduLevel_arr[j];
                eduLevel_arr[j] = tempEdu;

                //age

                tempAge = age_arr[k];
                age_arr[k] = age_arr[j];
                age_arr[j] = tempAge;


                //id

                tempID = id_arr[k];
                id_arr[k] = id_arr[j];
                id_arr[j] = tempID;


                //hours

                tempHours = workingHours_arr[k];
                workingHours_arr[k] = workingHours_arr[j];
                workingHours_arr[j] = tempHours;

            }

        }

    }

    for (int j = 0; j < 100; ++j) {
        if (eduLevel_arr[j] == "") continue;

        tempEduLevel_arr[j] = eduLevel_arr[j];
    }


    for (int j = 0; j < 100; ++j) {
        if (age_arr[j] == 0) continue;

        tempAge_arr[j] = age_arr[j];
    }

    for (int j = 0; j < 100; ++j) {
        if (id_arr[j] == 0) continue;
        tempId_arr[j] = id_arr[j];
    }

    for (int j = 0; j < 100; ++j) {
        if (workingHours_arr[j] == 0) continue;
        tempWorkingHours_arr[j] = workingHours_arr[j];
    }

    ofstream tempSorted("tempSorted.txt");

    for (int k = 0; k < 100; ++k) {

        if (tempWorkingHours_arr[k] == 0 || tempAge_arr[k] == 0 || tempId_arr[k] == 0) continue;
        if (tempEduLevel_arr[k] == "") continue;
        string sorted_data = tempEduLevel_arr[k] + " " + to_string(tempAge_arr[k]) + " "
                             + to_string(tempId_arr[k]) + " " + to_string(tempWorkingHours_arr[k]) + " ";

        sortedData.push_back(sorted_data);

    }

    for (string data: sortedData){
        tempSorted << data;
    }
    tempSorted.close();
    remove("Tas.txt");

    int result;
    char oldName[] ="tempSorted.txt";
    char newName[] ="Tas.txt";
    result= rename(oldName , newName );
    if (!(result == 0))
        perror( "Error renaming file" );

}


// Menu function which takes user input
bool menu(){

    int line, line_sort, line_order;

    cout<<"Menu: "<<endl;
    cout<<"------------------------------"<<endl;
    cout<<"[1] Add a new entry"<<endl;
    cout<<"[2] Sort the available entries"<<endl;
    cout<<"[3] Quit the program"<<endl;

    cout<<"\nUser input: "<<endl;
    cin>>line;

    // exception handling

    while (cin.fail() || line > 3 || line < 1){
        cin.clear();
        cin.ignore(1000,'\n');
        cout<<"Please enter an integer from [1 - 3]"<<endl;
        cin>>line;
    }

    if (line == 1) addNewTa();

    if (line == 2) {

        cout<<"Select which column to sort by: "<<endl;
        cout<<"[1] Status"<<endl;
        cout<<"[2] Age"<<endl;
        cout<<"[3] Student ID"<<endl;
        cout<<"[4] Working Hours"<<endl;

        cout<<"\nUser input: "<<endl;
        cin >> line_sort;

        // exception handling

        while (cin.fail() || line_sort > 4 || line_sort < 1){
            cin.clear();
            cin.ignore(1000,'\n');
            cout<<"Please enter an integer from [1 - 4]"<<endl;
            cin>>line_sort;
        }

        cout<<"\nSelect one of the following: "<<endl;
        cout<<"[1] Ascending"<<endl;
        cout<<"[2] Descending"<<endl;

        cout<<"\nUser input: "<<endl;
        cin >> line_order;

        // exception handling

        while (cin.fail() || line_order > 2 || line_order < 1){
            cin.clear();
            cin.ignore(1000,'\n');
            cout<<"Please enter an integer from [1 - 2]"<<endl;
            cin>>line_order;
        }

        if (line_sort == 1 && line_order == 1) sortByStatus_ascending();
        if (line_sort == 1 && line_order == 2) sortByStatus_descending();

        if (line_sort == 2 && line_order == 1) sortByAge_ascending();
        if (line_sort == 2 && line_order == 2) sortByAge_descending();

        if (line_sort == 3 && line_order == 1) sortByID_ascending();
        if (line_sort == 3 && line_order == 2) sortByID_descending();

        if (line_sort == 4 && line_order == 1) sortByWorkingHours_ascending();
        if (line_sort == 4 && line_order == 2) sortByWorkingHours_descending();

        displayData();
        cout<<endl;



    }

    if (line == 3) return false;

    return true;

}

int main() {

    // Default operation defined by the assignment:

    cout<<"\nInitial Student File:\n"<<endl;
    cout<<countEntries()<<endl;
    displayData();

    cout<<"\nInitial Student File: After Correction:\n"<<endl;
    filterData();
    cout<<countEntries()<<endl;
    displayData();
    cout<<"\n"<<endl;

    // looping of menu option [3] was not specified in the assignment
    // Looping was incorporated so bug testing would be easier, I will leave it untouched for your benefit

    while (menu()){
        menu();
    }

    // prompt occurs when loop ends (i.e. when the user enters 3)

    cout<<"PROGRAM ENDS NOW"<<endl;


    return 0;
}