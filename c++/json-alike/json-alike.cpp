#include <bits/stdc++.h>

using namespace std;

#define Dictionary unordered_map

class Minson {
public:
    inline static int wholeIndex = 0;

    inline static Dictionary<string, int> root;

    inline static Dictionary<int, Dictionary<string, int>> indexToDictionary;
    inline static Dictionary<int, int> indexToInt;
    inline static Dictionary<int, float> indexToFloat;
    inline static Dictionary<int, string> indexToString;

    static Dictionary<string, int>* getNextKey(Dictionary<string, int>* keyToIndex, const string& key) {
        if (keyToIndex->count(key)) {
            return &indexToDictionary[keyToIndex->at(key)];
        }
        else {
            throw "There's no such key: " + key;
        }
    }
    
    static void setNextKey(Dictionary<string, int>* keyToIndex, const string& key) {
        indexToDictionary[wholeIndex] = Dictionary<string, int>();
        keyToIndex->insert({key, wholeIndex++});
    }

    static void getValue(Dictionary<string, int>* keyToIndex, const string& key, int& value) {
        value = indexToInt[keyToIndex->at(key)];;
    }

    static void getValue(Dictionary<string, int>* keyToIndex, const string& key, float& value) {
        value = indexToFloat[keyToIndex->at(key)];
    }

    static void getValue(Dictionary<string, int>* keyToIndex, const string& key, string& value) {
        value = indexToFloat[keyToIndex->at(key)];
    }

    static void setValue(Dictionary<string, int>* keyToIndex, const string& key, int& value) {
        indexToInt[wholeIndex] = value;
        keyToIndex->insert({key, wholeIndex++});
    }

    static void setValue(Dictionary<string, int>* keyToIndex, const string& key, float& value) {
        indexToFloat[wholeIndex] = value;
        keyToIndex->insert({key, wholeIndex++});
    }

    static void setValue(Dictionary<string, int>* keyToIndex, const string& key, string& value) {
        indexToString[wholeIndex] = value;
        keyToIndex->at(key) = wholeIndex++;
    }

    template <typename T>
    static void find(vector<string>& keys, T& value) {
        Dictionary<string, int>* lastKeyToIndex = &root;
        for (int i = 0; i < keys.size() - 1; ++i) {
            lastKeyToIndex = getNextKey(lastKeyToIndex, keys[i]);
        }
        getValue(lastKeyToIndex, keys.back(), value);
    }

    template <typename T>
    static void insert(vector<string>& keys, T value) {
        Dictionary<string, int>* lastKeyToIndex = &root;
        for (int i = 0; i < keys.size() - 1; ++i) {
            if (lastKeyToIndex->count(keys[i]) == 0) {
                setNextKey(lastKeyToIndex, keys[i]);
            }
            lastKeyToIndex = getNextKey(lastKeyToIndex, keys[i]);
        }

        setValue(lastKeyToIndex, keys.back(), value);
    }
};

int main() {
    vector<string> commands = {"fireball", "missile", "damage"};
    string conversation = "Hello";
    try {
        Minson::insert<string>(commands, conversation);
    }
    catch (string exception) {
        cout << exception << '\n';
    }

    string searchedConversation = 0;
    try {
        Minson::find<string>(commands, searchedConversation);
        cout << searchedConversation << '\n';
    }
    catch (string exception) {
        cout << exception << '\n';
    }

    return 0;
}