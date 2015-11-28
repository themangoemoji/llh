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
  int third = hash_num % 26;
  int second = hash_num / 26;
  int first = second / 26;

  // Append the chars to the returnString
  returnString += dictionary[2][first];
  returnString += dictionary[1][second];
  returnString += dictionary[0][third];

  return returnString;
}

int WritePersistentHashMaps(string &filename, map<string, string> *hashmap) {
  int count = 0;
  if (hashmap->empty())
    return 0;

  FILE *fp = fopen(filename.c_str(), "w");
  if (!fp)
    return -errno;

  for(auto it = hashmap->begin(); it != hashmap->end(); it++) {
    fprintf(fp, "%s=%s\n", it->first.c_str(), it->second.c_str());
  }

  fclose(fp);
  return count;
}

void ReadGlobalHashNum(string &filename, int& hash_num) {
  ifstream i(filename, ios::binary);
  i.read((char*)&hash_num, sizeof(hash_num));
}

void WritePersistentHashNum(string &filename, int& hash_num) {
    ofstream o(filename,ios::binary);
    o.write((char*)&hash_num, sizeof(hash_num));
    o.close();
}

int ReadPersistentHashMaps(string &fname, map<string, string> *m) {
  int count = 0;
  if (access(fname.c_str(), R_OK) < 0)
    return -errno;

  FILE *fp = fopen(fname.c_str(), "r");
  if (!fp)
    return -errno;

  m->clear();

  char *buf = 0;
  size_t buflen = 0;

  while(getline(&buf, &buflen, fp) > 0) {
    char *nl = strchr(buf, '\n');
    if (nl == NULL)
      continue;
    *nl = 0;

    char *sep = strchr(buf, '=');
    if (sep == NULL)
      continue;
    *sep = 0;
    sep++;

    string s1 = buf;
    string s2 = sep;

    (*m)[s1] = s2;

    count++;
  }

  if (buf)
    free(buf);

  fclose(fp);
  return count;
}


int main ( int argc, char *argv[] ) {
  // Open persistent hash number to increment string val
  string PERSISTENT_HASH_NUM = "hash_num.txt";
  string PERSISTENT_URLS = "persistent_urls.txt";
  string PERSISTENT_LL = "persistent_lls.txt";
  map<string, string> url_to_ll_hash;
  map<string, string> ll_to_url_hash;
  string user_in = argv[1];
  int global_hash_num;

  // Open the persistent hash number
  ReadGlobalHashNum(PERSISTENT_HASH_NUM, global_hash_num);

  // Open persistent maps of URLs and LLs
  ReadPersistentHashMaps(PERSISTENT_URLS, &url_to_ll_hash);
  ReadPersistentHashMaps(PERSISTENT_LL, &ll_to_url_hash);

  // Loop user input unitl quit is directed
  while (1) {
    // Check user input to end program
    //cin >> user_in;
    if (user_in == "q" || user_in == "Q") {
      break;
    }

    // Deliver an existing URL from shorthash
    if (ll_to_url_hash[user_in] != "") {
      cout << ll_to_url_hash[user_in] << endl;
    }

    // Deliver an existing shorthash code from URL
    else if (url_to_ll_hash[user_in] != "") {
      cout << url_to_ll_hash[user_in] << endl;
    }

    // Add unfarmiliar URL (ideally) to hashmaps, increment unique hash num
    else if (url_to_ll_hash[user_in] == "") {
      cout << url_to_ll_hash[user_in] << endl;
      url_to_ll_hash[user_in] = numToLL(global_hash_num);
      ll_to_url_hash[url_to_ll_hash[user_in]] = user_in;
      ++global_hash_num;
    }
    user_in = "q";
  }

  // Write the hash num and maps so that they are persistent through next run
  WritePersistentHashMaps(PERSISTENT_URLS, &url_to_ll_hash);
  WritePersistentHashMaps(PERSISTENT_LL, &ll_to_url_hash);
  WritePersistentHashNum(PERSISTENT_HASH_NUM, global_hash_num);

  return 1;
}

