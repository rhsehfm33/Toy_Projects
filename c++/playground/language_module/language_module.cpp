#include "magic_enum.hpp"
#include <bits/stdc++.h>

using namespace std;

enum class ELanguage
{
    KOREAN,
    ENGLISH,
};

enum class ESentence
{
    STAGE_0,
    STAGE_1,
    STAGE_2,
    STAGE_3,
};

class LanguageModule
{
private:
    bool isInitSuccess = true;

    inline int getTargetIndex(ELanguage eLanguage, ESentence eSentence)
    {
        return (int(eLanguage) * magic_enum::enum_count<ESentence>()) + int(eSentence);
    }

    inline int getSizeOfSentences()
    {
        return magic_enum::enum_count<ELanguage>() * magic_enum::enum_count<ESentence>();
    }

    void insertSentence(ELanguage eLanguage, ESentence eSentence, string sentence)
    {
        int targetIndex = getTargetIndex(eLanguage, eSentence);

        if (sentences[targetIndex].empty())
        {
            sentences[targetIndex] = sentence;
        }
        else
        {
            cout << "Duplication occured!" << endl;
            cout << "Language: " << magic_enum::enum_name(eLanguage) << endl;
            cout << "Sentence: " << magic_enum::enum_name(eSentence) << endl;
            cout << "Original sentence: " << sentences[targetIndex] << endl;
            cout << "Inserted sentence: " << sentence << endl << endl;
            isInitSuccess = false;
        }
    }

    void checkAnyAbsentSentence()
    {
        for (ELanguage eLanguage : magic_enum::enum_values<ELanguage>())
        {
            for (ESentence eSentence : magic_enum::enum_values<ESentence>())
            {
                if (sentences[getTargetIndex(eLanguage, eSentence)].empty())
                {
                    cout << endl;
                    cout << "Language: " << magic_enum::enum_name(eLanguage) << endl;
                    cout << "Sentence: " << magic_enum::enum_name(eSentence) << endl;
                    cout << "is absent now!" << endl << endl;
                    isInitSuccess = false;
                }
            }
        }
    }

    static LanguageModule* instance;
    vector<string> sentences;

    LanguageModule()
    {
        // Initialize every senteces
        sentences.resize(getSizeOfSentences(), "");

        insertSentence(ELanguage::KOREAN, ESentence::STAGE_0, "스테이지0");
        insertSentence(ELanguage::KOREAN, ESentence::STAGE_1, "스테이지1");
        insertSentence(ELanguage::KOREAN, ESentence::STAGE_2, "스테이지2");
        insertSentence(ELanguage::KOREAN, ESentence::STAGE_3, "스테이지3");
        insertSentence(ELanguage::ENGLISH, ESentence::STAGE_0, "Stage0");
        insertSentence(ELanguage::ENGLISH, ESentence::STAGE_1, "Stage1");
        insertSentence(ELanguage::ENGLISH, ESentence::STAGE_2, "Stage2");
        insertSentence(ELanguage::ENGLISH, ESentence::STAGE_3, "Stage3");
        
        checkAnyAbsentSentence();

        assert(isInitSuccess);
    }

public:
    static LanguageModule& GetInstance()
    {
        if (instance == nullptr)
        {
            instance = new LanguageModule();
        }

        return *instance;
    }

    string& getSentence(ELanguage eLanguage, ESentence eSentence)
    {
        int targetIndex = getTargetIndex(eLanguage, eSentence);

        return sentences[targetIndex];
    }
};
LanguageModule* LanguageModule::instance = nullptr;

int main()
{
    cout << LanguageModule::GetInstance().getSentence(ELanguage::KOREAN, ESentence::STAGE_0) << endl;
    return 0;
}