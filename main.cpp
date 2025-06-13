#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_set>
#include <algorithm>

using namespace std;
using ll = long long;

const ll P = 31;        // Prime base for hashing
const ll MOD = 1e9 + 9; // Large prime for modulo

// Read all words from a file into a vector
vector<string> readWordsFromFile(const string& filename) {
    vector<string> words;
    ifstream file(filename);
    string word, line;

    if (!file.is_open()) {
        cerr << "Could not open file: " << filename << endl;
        return words;
    }

    while (getline(file, line)) {
        stringstream ss(line);
        while (ss >> word) {
            words.push_back(word);
        }
    }

    file.close();
    return words;
}

// Convert k-word sequences into rolling hashes
vector<ll> getHashes(const vector<string>& words, size_t k) {
    vector<ll> hashes;
    if (words.size() < k) return hashes;

    // Precompute powers of P
    vector<ll> powers(k);
    powers[0] = 1;
    for (size_t i = 1; i < k; ++i) {
        powers[i] = (powers[i - 1] * P) % MOD;
    }

    // First hash
    ll hash = 0;
    for (size_t i = 0; i < k; ++i) {
        for (char c : words[i]) {
            hash = (hash + (c - 'a' + 1) * powers[i]) % MOD;
        }
    }
    hashes.push_back(hash);

    // Rolling hash
    for (size_t i = k; i < words.size(); ++i) {
        for (char c : words[i - k]) {
            hash = (hash - (c - 'a' + 1) * powers[0] + MOD) % MOD;
        }
        hash = (hash * P) % MOD;
        for (char c : words[i]) {
            hash = (hash + (c - 'a' + 1)) % MOD;
        }
        hashes.push_back(hash);
    }

    return hashes;
}

int main() {
    string file1, file2;
    cout << "Enter first file name: ";
    cin >> file1;
    cout << "Enter second file name: ";
    cin >> file2;

    vector<string> words1 = readWordsFromFile(file1);
    vector<string> words2 = readWordsFromFile(file2);

    cout << "File 1 has " << words1.size() << " words." << endl;
    cout << "File 2 has " << words2.size() << " words." << endl;

    cout << "First 5 words from each file:\n";
    size_t limit1 = min(words1.size(), size_t(5));
    size_t limit2 = min(words2.size(), size_t(5));

    for (size_t i = 0; i < limit1; ++i)
        cout << words1[i] << " ";
    cout << endl;

    for (size_t i = 0; i < limit2; ++i)
        cout << words2[i] << " ";
    cout << endl;

    // Set window size for phrase comparison
    size_t k = 5;

    // Generate rolling hashes
    vector<ll> hashes1 = getHashes(words1, k);
    vector<ll> hashes2 = getHashes(words2, k);

    // Optional: Print substrings from each file
    cout << "\nSubstrings from file1:\n";
    for (size_t i = 0; i + k <= words1.size(); ++i) {
        for (size_t j = i; j < i + k; ++j)
            cout << words1[j] << " ";
        cout << "\n";
    }

    cout << "\nSubstrings from file2:\n";
    for (size_t i = 0; i + k <= words2.size(); ++i) {
        for (size_t j = i; j < i + k; ++j)
            cout << words2[j] << " ";
        cout << "\n";
    }

    // Compare using sets
    unordered_set<ll> set1(hashes1.begin(), hashes1.end());
    int matchCount = 0;

    for (ll h : hashes2) {
        if (set1.count(h)) ++matchCount;
    }

    // Display result
    cout << "\n============================\n";
    cout << "Matching sequences: " << matchCount << " out of " << hashes2.size() << endl;
    double score = hashes2.empty() ? 0.0 : (matchCount * 100.0) / hashes2.size();
    cout << "Plagiarism Score: " << score << "%" << endl;
    cout << "============================\n";

    return 0;
}
