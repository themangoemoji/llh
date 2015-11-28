#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
using namespace std;

string numToLL(int hash_num) {
  const char* args[] = {"abcdefghijklmnopqrstuvwxyz", "abcdefghijklmnopqrstuvwxyz", "abcdefghijklmnopqrstuvwxyz"};
  vector<string> dictionary(args, end(args));
  string returnString = "";
  int first = 0;
  int second = hash_num / 26;
  int third = hash_num % 26;
  returnString += dictionary[2][first];
  returnString += dictionary[1][second];
  returnString += dictionary[0][third];

  return returnString;
}

int main() {
  const char* FILENAM = "hash_num.txt";
  ifstream i(FILENAM, ios::binary);
  map<string, string> url_to_ll_hash;
  map<string, string> ll_to_url_hash;
  string url = "";
  int global_hash_num;
  i.read((char*)&global_hash_num, sizeof(global_hash_num));


  cout << "URL to hash: ";
  cin >> url;
  cout << numToLL(++global_hash_num) << endl;
  cout << url << endl;

  ofstream o(FILENAM,ios::binary);
  o.write((char*)&global_hash_num, sizeof(global_hash_num));
  o.close();

  return 1;
}

