#include <iostream>
#include <sstream>
#include <iomanip>
#include <openssl/md5.h>
using namespace std;

string calculateMD5(const string &input)
{
    MD5_CTX context;
    MD5_Init(&context);
    MD5_Update(&context, input.c_str(), input.size());
    unsigned char digest[MD5_DIGEST_LENGTH];
    MD5_Final(digest, &context);

    stringstream ss;
    ss << hex << setfill('0');
    for (int i = 0; i < MD5_DIGEST_LENGTH; ++i)
    {
        ss << setw(2) << static_cast<unsigned int>(digest[i]);
    }

    return ss.str();
}

int main()
{
    string secretKey = "ckczppom"; // Replace with your actual secret key
    int number = 1;

    while (true)
    {
        string input = secretKey + to_string(number);
        string hash = calculateMD5(input);

        // Check if the hash has at least five leading zeroes
        if (hash.substr(0, 6) == "000000")
        {
            cout << "Found AdventCoin: " << number << endl;
            break;
        }

        number++;
    }

    return 0;
}