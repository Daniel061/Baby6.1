#ifndef C_LANGUAGE_H
#define C_LANGUAGE_H
#include <c_Sentence.h>
#include <c2_Sentence.h>
#include <string>
#include <iostream>
extern bool Verbose;
using namespace std;

class c_Language : public c_Sentence
{
    public:
        c_Language();
        virtual ~c_Language();


    protected:

    private:
       c2_Sentence SlowSentence;
       c2_Sentence tmpSentence;

    public:
//-------------------------Pattern Review  i.e. Language Helper ------------------------
 string PatternReview(string Pattern, int& ConfidenceLevel){
   if(Verbose)cout << "[c_Language::PatternReview]: " ;
   string CorrectedPattern, LeftOfJoiner, RightOfJoiner; CorrectedPattern = Pattern;
   ConfidenceLevel = -1;  // no suggestion
   int LeftOfJoinerLocation,RightOfJoinerLocation;
   LeftOfJoinerLocation = -1; RightOfJoinerLocation = 1;
   int  JoinerLocation     = -1;
   bool Result             = false;
   int  PatternPointer     = 0;


   /*Check for a joiner word and assist if possible
      Possible combinations are;
        unknown-type joiner known-type              can assume unknown-type = known-type
        unknown-type joiner unknown-type            cannot help here
        known-type joiner unknown-type              can assume unknown-type = known-type
        known-type joiner known-type                no help needed here
        unknown-type joiner determiner known-type   can assume unknown-type = known-type after skipping determiner

        Working principle~ you cannot join unlike word types i.e. dog and cat ~ ok     dirty and dog ~ improper form
        Possible exception~ The cat is fast and the dog is too.  The joining word 'and' would trigger this routine to match dog and fast as the same word types

    */
    CorrectedPattern = Pattern;
    JoinerLocation = Pattern.find("j");
    if((JoinerLocation >=0) & (JoinerLocation < int(Pattern.size()))){
        LeftOfJoiner = Pattern.substr(JoinerLocation + LeftOfJoinerLocation,1);
        RightOfJoiner = Pattern.substr(JoinerLocation + RightOfJoinerLocation,1);
        if(RightOfJoiner == "d"){
            RightOfJoinerLocation++; //move past determiner
            RightOfJoiner[0] = Pattern[JoinerLocation + RightOfJoinerLocation];} //get new character

        if(LeftOfJoiner == RightOfJoiner){ // if both known-type or unknown-type  cannot help

        }
        else
            if(LeftOfJoiner == "u") LeftOfJoiner = RightOfJoiner;                             //assume left is same as right
                else
                    if(RightOfJoiner == "u" )  RightOfJoiner = LeftOfJoiner;                  //assume right is same as left. the tests for unknowns prevents matching dissimilar types


    CorrectedPattern[JoinerLocation + LeftOfJoinerLocation]  = LeftOfJoiner[0];
    CorrectedPattern[JoinerLocation + RightOfJoinerLocation] = RightOfJoiner[0];
    }
   /*  Check for stored pattern
       and if it has a solution
       pull it into CorrectPattern
   */

//    if(LeftLobeMemory[Tokenize(CorrectedPattern,false)].GetpIsSet() == true){                     //seen this pattern before
//        CorrectedPattern = LeftLobeMemory[LeftLobeMemory[Tokenize(Pattern,false)].GetPointerToNextPattern()].GetpCellDataString();
//        ConfidenceLevel = 100;}
     if(GetMemoryCellIsSet(Tokenize(CorrectedPattern,false),'l')==true){
            PatternPointer       = GetMemoryCellPointerToNextPattern(Tokenize(CorrectedPattern,false),'l');
            CorrectedPattern     = GetMemoryCellRawStringData(Result,"",PatternPointer,'l');
     }

    else{
            if(Pattern == "duvu"){
                CorrectedPattern = "dnvu";
                ConfidenceLevel = 100;}
            if(Pattern == "dun"){
                CorrectedPattern = "dan";
                ConfidenceLevel = 100;}
            if(Pattern == "duva"){
                CorrectedPattern = "dnva";
                ConfidenceLevel = 100;}
            if(Pattern == "uuv"){
                CorrectedPattern = "dnv";
                ConfidenceLevel = 100;}
            if(Pattern == "dvdun"){
                CorrectedPattern = "dvdan";
                ConfidenceLevel = 100;}
            if(Pattern == "dvdu"){
                CorrectedPattern = "dvdn";
                ConfidenceLevel = 100;}
            if(Pattern == "dnup"){
                CorrectedPattern = "dnvp";
                ConfidenceLevel = 100;}
            if(Pattern == "avdu"){
                CorrectedPattern = "avdn";
                ConfidenceLevel = 100;}
            if (Pattern == "dntua"){
                CorrectedPattern = "dntva";
                ConfidenceLevel = 100;}
          }

     if(Verbose)cout << " Received Pattern:" << Pattern << " Correct Pattern:" << CorrectedPattern << endl;
   return CorrectedPattern;
 }
//--------------------------End Language Review------------------------------------------------


//-------------------------Find Word Type------------------------------------------------------
 char FindWordType(string tmpWord){

           if(Verbose)cout << "[c_Language::FindWordType] :";


           string OrigWord;


           char tmpWordType = 'u';

           string ProNounsInward =      " you your yours ";
           string ProNounsOther =       " they them he him she her it we ";
           string ProNounsOutward =     " me mine my I i ";
           string Determiners =         " the a an each every certain this that these those any all each some few either little many much ";
           string Questions =           " what where how when who what's ";
           string Verbs =               " can will be have do say get make go know take see is are come think look want give use find tell ask work seem feel try leave call ";
           string SubjectReplacements = " it that this ";
           string Adverbs =             " very ";
           string Directives =          " compare same about ";
           string JoiningWords =        " and ";
           string AssociativeWord =     " name name's ";
           string PluralPronoun =       " both ";
           string ThrowAwayWords =      " of also can ";

           int isThrowAwayWord   = -1;
           int isPluralPronoun   = -1;
           int isDirective       = -1;
           int isDeterminer      = -1;
           int isQuestion        = -1;
           int isVerb            = -1;
           int isSubRep          = -1;
           int isAdverb          = -1;
           int isJoiner          = -1;
           int isProNounsOther   = -1;
           int isProNounsInward  = -1;
           int isProNounsOutward = -1;
           int isAssociativeWord = -1;



              for(int t = 0; t < int(tmpWord.size()); t++){
                tmpWord[t] = tolower(tmpWord[t]);}
              OrigWord = tmpWord;
              tmpWord = " " + tmpWord + " ";

                isThrowAwayWord     = ThrowAwayWords.find(tmpWord);
                isPluralPronoun     = PluralPronoun.find(tmpWord);
                isJoiner            = JoiningWords.find(tmpWord);
                isDirective         = Directives.find(tmpWord);
                isDeterminer        = Determiners.find(tmpWord);
                isProNounsOther     = ProNounsOther.find(tmpWord);
                isProNounsInward    = ProNounsInward.find(tmpWord);
                isProNounsOutward   = ProNounsOutward.find(tmpWord);
                isQuestion          = Questions.find(tmpWord);
                isVerb              = Verbs.find(tmpWord);
                isSubRep            = SubjectReplacements.find(tmpWord);
                isAdverb            = Adverbs.find(tmpWord);
                isAssociativeWord   = AssociativeWord.find(tmpWord);

                  if (isVerb >= 0){
                      tmpWordType = 'v';}
                  if (isDeterminer >= 0){
                       tmpWordType = 'd';}
                  if (isProNounsOther >= 0){
                       tmpWordType = 'p';}
                  if (isProNounsInward >=0){
                       tmpWordType = 'm';}
                  if (isProNounsOutward >=0){
                       tmpWordType = 'y';}
                  if (isQuestion >= 0){
                       tmpWordType = 'q';}
                  if (isSubRep >=0){
                        tmpWordType = 'r';}
                  if (isAdverb >=0){
                        tmpWordType = 'A';}
                  if (isDirective >=0){
                        tmpWordType = 'X';}
                  if (isJoiner >=0){
                        tmpWordType = 'j';}
                  if (isAssociativeWord >=0){
                        tmpWordType = 'g';}
                  if (isPluralPronoun >=0){
                        tmpWordType = 'N';
                        SetHasPluralPronoun(true);}
                  if (isThrowAwayWord >=0){
                        tmpWordType = 't';}
            if(Verbose)
                cout << "tmpWord " << tmpWord <<" type:" << tmpWordType << endl;
            return tmpWordType;

 }
//--------------------------------end Find Word Type--------------------------------------


void SlowSpeak(string str_Data, int Delay = 30000000 )
{
     string WorkingWord;
     SaveResponsesSent(str_Data);
     SlowSentence.Parse(str_Data);
     for(int x = 0; x < SlowSentence.GetWordCount(); x++){

        WorkingWord = SlowSentence.GetWords(x);
        for(int y = 0; y < int(WorkingWord.size()); y++){
            cout << WorkingWord[y];
            for(int dly = 0; dly < Delay; dly++);
        }
        cout  << " ";

     }
     cout << "\b" << SlowSentence.GetPunctuation() << endl;
}

int RequestUserResponse()
{
    int Matched;

    string PositiveResponse = " yes Yes OK ok Ok correct Correct right Right Exactly exactly ye ";
    string NegativeResponse = " No no wrong Wrong What what n ";
    string Response         = "";

    while (Response == ""){
        cout << ">?";
        getline (cin,Response);}
    tmpSentence.Parse(Response);
    Response = tmpSentence.GetWords(0);
    Matched = PositiveResponse.find(" " + Response + " ");
    if(Matched >= 0) return 1;
    Matched = NegativeResponse.find(" " + Response + " ");
    if(Matched >= 0) return -1;

    return 0;
}

//---------------------------------FINDSUBJECT()--------------------------------------------------
        int FindSubject()
        {
            //Order Of Preference:
            //  Proper Noun
            //  Pronoun
            //  Noun
            //  Determiner +1
            //  Unknown word

            if(Verbose)cout << "[c_Language.h::FindSubject]" << endl;
            int DeterminerLocation;       DeterminerLocation = -1;
            int UnknownLocation;          UnknownLocation    = -1;
            int WordCount;                WordCount          =  0;
            int SubLocation;              SubLocation        = -1;
            int AdjectiveLocation;        AdjectiveLocation  = -1;
            int NounLocation;             NounLocation       = -1;
            int VerbLocationFound;        VerbLocationFound  = -1;
            int SecondNounLocation;       SecondNounLocation = -1;
            int ProNounLocation;          ProNounLocation    = -1;
            int ProperNounLocation;       ProperNounLocation = -1;
            string Pattern;               Pattern            = "";
            bool PickingSubject;          PickingSubject     = true;

            WordCount = GetWordCount();

            if ((GetWordsLC(0)== "is") || (GetWordsLC(0)=="can") || (GetWordsLC(0)=="will")) SetIsQuestion(true);

            for(int x = 0; x < WordCount; x++){
                if(GetWordType(x)== 'd')if(DeterminerLocation == -1) DeterminerLocation = x;
                if(GetWordType(x)== 'u')if(UnknownLocation == -1)    UnknownLocation    = x;
                if(GetWordType(x)== 'n'){if(NounLocation == -1)    { NounLocation       = x;} else SecondNounLocation = x;}
                if(GetWordType(x)== 'r')if(SubLocation == -1)        SubLocation        = x;
                if(GetWordType(x)== 'p')if(ProNounLocation == -1)    ProNounLocation    = x;
                if(GetWordType(x)== 'P')if(ProperNounLocation == -1) ProperNounLocation = x;
                if(GetWordType(x)== 'v'){VerbLocationFound =x; SetVerbLocation(x);}
                if(GetWordType(x)== 'a'){AdjectiveLocation = x; SetAdjectiveLocation(x);}
                Pattern += GetWordType(x);
            }
            SetPattern(Pattern);
            if(SecondNounLocation != -1) SetIndirectObjectLocation(SecondNounLocation); else SetIndirectObjectLocation(-1);
            if(SecondNounLocation != -1) SetNounCount(2); else SetNounCount(1);
            if( (ProperNounLocation != -1) && (NounLocation != -1) ){
                SetIndirectObjectLocation(ProperNounLocation);
                SubLocation = NounLocation;
                PickingSubject = false;}
            else
                if ((ProNounLocation != -1) && (NounLocation != -1)){
                    SetIndirectObjectLocation(ProNounLocation);
                    SubLocation = NounLocation;
                    PickingSubject = false;}

            while(PickingSubject){
                if((SubLocation == -1) && (ProperNounLocation != -1))
                    SubLocation = ProperNounLocation;
                else
                    if((SubLocation == -1) && (ProNounLocation !=-1))
                        SubLocation = ProNounLocation;
                else
                    if((SubLocation == -1) && (NounLocation !=-1))
                        SubLocation = NounLocation;
                else
                    if((SubLocation == -1) && (DeterminerLocation != -1))
                        SubLocation = DeterminerLocation +1;
                else
                    if((SubLocation == -1) && (UnknownLocation != -1))
                        SubLocation = UnknownLocation;

              PickingSubject = false;
            }
            if(Verbose)
                    cout << "Suggested subject location:" << SubLocation << " Pattern:" << GetPattern() << " Indirect Object Location:" << GetIndirectObjectLocation()<< endl;
            SetSubjectLocation(SubLocation);
            return SubLocation;
        }
//--------------------------------------------------end Find Subject----------------------------------------------------------
};

#endif // C_LANGUAGE_H
