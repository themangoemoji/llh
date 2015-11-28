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
    cout << it->first << " <-- is the first elem of hash" ;
    fprintf(fp, "%s=%s\n", it->first.c_str(), it->second.c_str());
    cout << endl;
  }

  fclose(fp);
  return count;
}

void ReadGlobalHashNum(string &filename, int& hash_num) {
  ifstream i(filename, ios::binary);
  i.read((char*)&hash_num, sizeof(hash_num));
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


int main() {
  // Open persistent hash number to increment string val
  string PERSISTENT_HASH_NUM = "hash_num.txt";
  string PERSISTENT_URLS = "persistent_urls.txt";
  string PERSISTENT_LL = "persistent_lls.txt";
  map<string, string> url_to_ll_hash;
  map<string, string> ll_to_url_hash;
  string url = "";
  int global_hash_num;

  // Open the persistent hash number
  ReadGlobalHashNum(PERSISTENT_HASH_NUM, global_hash_num);

  // Open persistent maps of URLs and LLs
  ReadPersistentHashMaps(PERSISTENT_URLS, &url_to_ll_hash);
  ReadPersistentHashMaps(PERSISTENT_LL, &ll_to_url_hash);

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

    ofstream o(PERSISTENT_HASH_NUM,ios::binary);
    o.write((char*)&global_hash_num, sizeof(global_hash_num));
    o.close();
  }

  // Write the maps so that they are persistent to next run
  WritePersistentHashMaps(PERSISTENT_URLS, &url_to_ll_hash);
  WritePersistentHashMaps(PERSISTENT_LL, &ll_to_url_hash);

  return 1;
}

