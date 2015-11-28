#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
using namespace std;

string numToLL(int hash_num) {
  // We will choose 3 chars, one from each set
  const char* args[] = {"abcdefghijklmnopqrstuvwxyz", "abcdefghijklmnopqrstuvwxyz", "abcdefghijklmnopqrstuvwxyz"};
  vector<string> dictionary(args, end(args));
  string returnString = "";

  // Pick the three chars
  int first = 0;
  int second = hash_num / 26;
  int third = hash_num % 26;

  // Append the chars to the returnString
  returnString += dictionary[2][first];
  returnString += dictionary[1][second];
  returnString += dictionary[0][third];

  return returnString;
}

int main() {
  // Open persistent hash number to increment string val
  const char* FILENAM = "hash_num.txt";
  ifstream i(FILENAM, ios::binary);
  map<string, string> url_to_ll_hash;
  map<string, string> ll_to_url_hash;
  string url = "";
  int global_hash_num;
  i.read((char*)&global_hash_num, sizeof(global_hash_num));

  // Loop user input unitl quit is directed
  while (1) {
    cout << "URL to hash: ";
    cin >> url;
    // Check user input to end program
    if (url == "q" || url == "Q") {
      break;
    }
    cout << "URL to hash: ";
    // Get new alpha string for each url if not already present
    if (url_to_ll_hash[url] == "") {
      cout << "HASH " << endl;
      url_to_ll_hash[url] = numToLL(global_hash_num);
      ll_to_url_hash[url_to_ll_hash[url]] = url;
      cout << numToLL(++global_hash_num) << endl;
      cout << "URL TO LLH --> " << url_to_ll_hash[url] << endl;
      cout << "LLH TO URL --> " << ll_to_url_hash[url_to_ll_hash[url]] << endl;
    }
    else {
      cout << "ELSE " << endl; 
      cout << "URL TO LLH --> " << url_to_ll_hash[url] << endl;
      cout << "LLH TO URL --> " << ll_to_url_hash[url_to_ll_hash[url]] << endl;
      cout << url << endl;
    }

    ofstream o(FILENAM,ios::binary);
    o.write((char*)&global_hash_num, sizeof(global_hash_num));
    o.close();
  }

  return 1;
}

