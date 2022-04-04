// Imports
#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <string>
#include <regex>
using namespace std;

/*
Credits:
tokenize(): GeeksForGeeks (modified)

Github Copilot:
replaceSubstr()

StackOverflow:
includes(): https://stackoverflow.com/a/2340309 (modified)
*/
 
// Global vars
int status = 6;
int doing = 0;
int curline = 1;
char loopType = 'n'; // n = no loop
int loopRevsLeft = 0; // Loop revolutions left

// Constants
const string nl = "\n";
const string sl = "----------------------";

// Config definers and default configger (might delete ui configs, idk)
vector<bool> boolConfigs;
bool boolConfigsAllSet = false;
vector<int> intConfigs;
bool intConfigsAllSet = false;
vector<string> strConfigs;
bool strConfigsAllSet = false;
vector<string> uiConfigs;
bool uiConfigsAllSet = false;

void setDefaultConfigs() {
  boolConfigs = {false,
    true, // 1. AutoAddSemicolons
    false, // 2. DisallowDuplicateFeatures (aka strict mode)
    false, // 3. StronglyTyped
    true, // 4. ShowLogs
    true, // 5. ShowErrors
    true, // 6. ShowDebugInfos
    true, // 7. AllowSelfTriggeredErrors
  };
  intConfigs = {0,};
  strConfigs = {"",};
  uiConfigs = {"",
    "----------------------\n|/ Pizn Interpreter \\|\n|\\  (coded in C++)  /|\n----------------------\n\n...\n\n", // 1. WrapperStart
    "\n\n...\n\n(All done!)", // 2. WrapperEnd
  };
}

// Temp vars
string tempStr1;
string tempStr2;
string tempStr3;
string tempStr4;
string tempStr5;

// Log-related
vector<string> logs;
vector<string> errors;
int totalErrorCount = 0;

void log(string message) {
  logs.push_back(message);
  if (boolConfigs[4] == true) {
    cout << sl << nl << "Something logged: " << message << nl << sl;
  }
}

// Note: All errors in Pizn arent fatal
void error(string message) {
  tempStr1 = "Error: ";
  logs.push_back(tempStr1.append(message));
  if (boolConfigs[5] == true) {
    cout << sl << nl << "Error at line " << curline << ":" << nl << "  " << message << nl << sl;
  }
}

// debugInfo() is just for temporary use to debug broken stuff - after its fixed delete the debugInfo()
void debugInfo(string message) {
  tempStr1 = "Debug info: ";
  logs.push_back(tempStr1.append(message));
  if (boolConfigs[6] == true) {
    cout << sl << nl << "Debug info: " << message << nl << sl;
  }
}

void lineIs(string message,int line = curline) {
  tempStr1 = "Line ";
  tempStr2 = " is ";
  log(tempStr1.append(to_string(line).append(tempStr2.append(message))));
}

// Function-returning functions
void returns(string returns) {
  tempStr1 = "A function returned: ";
  tempStr2 = " (temporary)";
  log(tempStr1.append(returns.append(tempStr2)));
}

// Common string functions
vector<string> tokenize(string s,string del = " ") {
  int start = 0;
  int end = s.find(del);
  vector<string> tokenized;
  while (end != -1) {
    tokenized.push_back(s.substr(start, end - start));
    start = end + del.size();
    end = s.find(del, start);
  }
  tokenized.push_back(s.substr(start, end - start));
  return tokenized;
}

string replaceSubstr(string str, string substr, string replacement) {
  size_t pos = 0;
  while ((pos = str.find(substr, pos)) != string::npos) {
    str.replace(pos, substr.length(), replacement);
    pos += replacement.length();
  }
  return str;
}

bool isBlank(string blankOrNot) {
  return blankOrNot == "";
}

string stripWrapped(string str,char inputWrapper) { // Delete the stuff in certain quotes
  int so = 2;
  string tchar;
  string removed;
  string realWrapper = string(1,inputWrapper);
  for (int i = 0; i < str.length(); ++i) {
    tchar = str[i];
    if (so == 2) { // were not in quotes right now
      removed = removed.append(tchar);
      if (tchar == realWrapper) {
        so = 1;
        removed = removed.substr(0,removed.size() - 1);
      }
    } else if (so == 1) {// were in quotes
      if (tchar == realWrapper) {
        so = 2;
      }
    }
  }
  return removed;
}

string stripInner(string str) {
  tempStr1 = str;
  tempStr1 = stripWrapped(tempStr1,'"');
  tempStr1 = stripWrapped(tempStr1,'\'');
  return tempStr1;
}

bool includes(string str,string substr) {
  if (str.find(substr) != string::npos) {
    return true;
  }
  return false;
}

// Solve function (not coatings)
void solveFunction(string module,string command,vector<string> params) {
  // This just calls the other files which are the actual ones that do the function stuff
}

// Solve basic arithmetics
int solveBasicAriths(string expr) {
  return 0; // temporary
}

// Run one line
void runOneLine(string lineContent) {
  // Check if it's not blank
  if (isBlank(lineContent)) {
    return;
  }
  
  // Is it a variable declaration or data edit
  if (includes(stripInner(lineContent),"=")) {
    int equalsPos = stripInner(lineContent).find("=");
  } else {
    tempStr1 = "Invalid expression \"";
    tempStr2 = "\" given.";
    error(tempStr1.append(lineContent.append(tempStr2)));
  }
}

// Run code (many lines)
void runPiznCode(string codeAsStr) {
  // Init and get code
  if (boolConfigs[1] == true) {
    codeAsStr = replaceSubstr(codeAsStr,"\n",";");
  }
  vector<string> codeAsVec = tokenize(codeAsStr,";");
  
  // Run each line
  doing = 0;
  curline = 1;
  for (auto &i: codeAsVec) {
    runOneLine(i);
    doing++;
    curline++;
  }
}

// int main
int main() {
  // Set configs to defaults and welcome message
  setDefaultConfigs();
  status = 2;
  cout << uiConfigs[1];
  
  // Run code
  runPiznCode("he=y;there!;");
  
  // We're done
  status = 3;
  cout << uiConfigs[2];
  return 0;
}
