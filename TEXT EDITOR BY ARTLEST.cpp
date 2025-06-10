/*
 * Simple Console Text Editor
 * A basic text editor implementation in C++
 * 
 * Features:
 * - Create and edit text documents
 * - Save and load files
 * - View document content with line numbers
 * - Clear document content
 * 
 * Developer: artlest
 * GitHub: github.com/artlest
 * License: MIT
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <limits>

using namespace std;

// Function declarations
void displayMenu();
void addTextLine(vector<string>& lines);
void displayDocument(const vector<string>& lines);
void saveToFile(const vector<string>& lines);
void loadFromFile(vector<string>& lines);
void clearDocument(vector<string>& lines);
bool getUserChoice(int& choice);
void clearScreen();
void pauseScreen();

int main() {
    vector<string> documentLines;
    int userChoice;
    bool running = true;
    
    clearScreen();
    cout << "Simple Text Editor" << endl;
    cout << "Developer: artlest" << endl;
    cout << "==================" << endl;
    
    while (running) {
        displayMenu();
        
        if (!getUserChoice(userChoice)) {
            cout << "Invalid input. Please enter a number between 1-6." << endl;
            pauseScreen();
            continue;
        }
        
        switch (userChoice) {
            case 1:
                addTextLine(documentLines);
                break;
            case 2:
                displayDocument(documentLines);
                break;
            case 3:
                saveToFile(documentLines);
                break;
            case 4:
                loadFromFile(documentLines);
                break;
            case 5:
                clearDocument(documentLines);
                break;
            case 6:
                cout << "\nThank you for using artlest's Text Editor!" << endl;
                cout << "Exiting..." << endl;
                running = false;
                break;
            default:
                cout << "Invalid choice. Please select 1-6." << endl;
        }
        
        if (running) {
            pauseScreen();
        }
    }
    
    return 0;
}

void clearScreen() {
    // Cross-platform screen clearing - works on IDEs and online compilers
    cout << "\033[2J\033[H"; // ANSI escape codes
    cout.flush();
}

void pauseScreen() {
    cout << "\nPress Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void displayMenu() {
    cout << "\n--- MENU ---" << endl;
    cout << "1. Add text line" << endl;
    cout << "2. View document" << endl;
    cout << "3. Save to file" << endl;
    cout << "4. Load from file" << endl;
    cout << "5. Clear document" << endl;
    cout << "6. Exit" << endl;
    cout << "Choice: ";
}

void addTextLine(vector<string>& lines) {
    string input;
    
    cout << "\nEnter text (empty line to finish):" << endl;
    
    while (true) {
        cout << "Line " << (lines.size() + 1) << ": ";
        getline(cin, input);
        
        if (input.empty()) {
            break;
        }
        
        lines.push_back(input);
    }
    
    if (!lines.empty()) {
        cout << "\nText added successfully!" << endl;
        cout << "Total lines in document: " << lines.size() << endl;
    } else {
        cout << "No text was added." << endl;
    }
}

void displayDocument(const vector<string>& lines) {
    clearScreen();
    
    if (lines.empty()) {
        cout << "Document Viewer - artlest Text Editor" << endl;
        cout << "=====================================" << endl;
        cout << "\nDocument is empty." << endl;
        cout << "Use option 1 to add text or option 4 to load a file." << endl;
        return;
    }
    
    cout << "Document Viewer - artlest Text Editor" << endl;
    cout << "=====================================" << endl;
    cout << "Total lines: " << lines.size() << endl;
    cout << "\n--- DOCUMENT CONTENT ---" << endl;
    
    for (size_t i = 0; i < lines.size(); ++i) {
        cout << setw(4) << right << (i + 1) << ": " << lines[i] << endl;
    }
    
    cout << "--- END OF DOCUMENT ---" << endl;
}

void saveToFile(const vector<string>& lines) {
    if (lines.empty()) {
        cout << "\nNo content to save." << endl;
        cout << "Please add some text first using option 1." << endl;
        return;
    }
    
    string filename;
    cout << "\nEnter filename (e.g., document.txt): ";
    getline(cin, filename);
    
    // Add .txt extension if none provided
    if (filename.find('.') == string::npos) {
        filename += ".txt";
    }
    
    ofstream file(filename.c_str()); // .c_str() for better compatibility
    
    if (!file.is_open()) {
        cout << "Error: Could not create file '" << filename << "'" << endl;
        cout << "Please check the filename and try again." << endl;
        return;
    }
    
    for (size_t i = 0; i < lines.size(); ++i) {
        file << lines[i];
        if (i < lines.size() - 1) {
            file << endl;
        }
    }
    
    file.close();
    
    cout << "\nSuccess! Document saved to '" << filename << "'" << endl;
    cout << "Lines saved: " << lines.size() << endl;
}

void loadFromFile(vector<string>& lines) {
    string filename;
    cout << "\nEnter filename to load: ";
    getline(cin, filename);
    
    ifstream file(filename.c_str()); // .c_str() for better compatibility
    
    if (!file.is_open()) {
        cout << "Error: Could not open file '" << filename << "'" << endl;
        cout << "Please make sure the file exists and try again." << endl;
        return;
    }
    
    vector<string> tempLines; // Use temporary vector to avoid clearing on failure
    string line;
    
    while (getline(file, line)) {
        tempLines.push_back(line);
    }
    
    file.close();
    
    lines = tempLines; // Only update main vector after successful load
    
    cout << "\nSuccess! Loaded '" << filename << "'" << endl;
    cout << "Lines loaded: " << lines.size() << endl;
}

void clearDocument(vector<string>& lines) {
    if (lines.empty()) {
        cout << "\nDocument is already empty." << endl;
        return;
    }
    
    size_t lineCount = lines.size();
    lines.clear();
    
    cout << "\nDocument cleared successfully!" << endl;
    cout << "Lines removed: " << lineCount << endl;
}

bool getUserChoice(int& choice) {
    if (cin >> choice) {
        // Clear input buffer properly for all compilers
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return choice >= 1 && choice <= 6;
    } else {
        // Clear error state and input buffer
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }
}