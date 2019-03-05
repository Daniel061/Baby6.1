#ifndef C_LANGUAGE_H
#define C_LANGUAGE_H
#include <c_Sentence.h>
#include <c2_Sentence.h>
#include <c_LongTermMemory.h>
#include <string>
#include <iostream>
extern bool Verbose;
extern int  ThisSpeed;
extern bool StoryMode;

using namespace std;

/*    Language Helper Class

      This class is responsible for the first setting  of word types
         (based on a small set of standards, finalizing word type setting is done elsewhere)
       deconstruction of  plurals,
       comparing patterns for proper form and/or stored patterns,
       Finding the subject and/or indirect object of a sentence,
       Sending responses to the console, delayed to appear as typing,
       Receiving user responses,
       and, finding the 'Gist' of the sentence and store that.

*/

class c_Language : public c_LongTermMemory
{
    public:
        c_Language();
        virtual ~c_Language();


    protected:

    private:
       c2_Sentence SlowSentence;
       c2_Sentence tmpSentence;

    public:
//-------------------------Pattern Review  ------------------------
 string PatternReview(string LocPattern, int& ConfidenceLevel){
   if(Verbose)cout << "[c_Language::PatternReview]: " ;
   string CorrectedPattern, LeftOfJoiner, RightOfJoiner;
   CorrectedPattern = GetFromSentencePattern();
   string WorkingWord = "";
   ConfidenceLevel = -1;  // no suggestion
   int LeftOfJoinerLocation,RightOfJoinerLocation;
   LeftOfJoinerLocation = -1; RightOfJoinerLocation = 1;
   int  JoinerLocation     = -1;
   bool Result             = false;
   bool VerifyPattern      = false;
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
    CorrectedPattern = GetFromSentencePattern();
    JoinerLocation = LocPattern.find("j");
    if((JoinerLocation >=1) & (JoinerLocation < int(LocPattern.size()))){  //not the first word and not the last word
        LeftOfJoiner = LocPattern.substr(JoinerLocation + LeftOfJoinerLocation,1);
        RightOfJoiner = LocPattern.substr(JoinerLocation + RightOfJoinerLocation,1);
        if(RightOfJoiner == "d"){
            RightOfJoinerLocation++; //move past determiner
            RightOfJoiner[0] = LocPattern[JoinerLocation + RightOfJoinerLocation];} //get new character

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

///*************CHANGE PATTERN STORAGE TO STRING STRING - no tokens
     if(GetMemoryCellIsSet(CorrectedPattern,Result,'l')==true){  //seen this pattern before
            //PatternPointer       = GetMemoryCellPointerToNextPattern(Tokenize(CorrectedPattern,false),'l');
            //CorrectedPattern     = GetMemoryCellRawData(Result,"",PatternPointer,'l');
            //VerifyPattern        = true;
     }

    else{
            PatternPointer = GetFromSentencePattern().find("Aun");
            if(PatternPointer >= 0){
                CorrectedPattern                   = GetFromSentencePattern();
                CorrectedPattern[PatternPointer+1] = 'a';
                ConfidenceLevel                    = 100;}
            if(LocPattern == "duvu"){
                CorrectedPattern = "dnvu";
                ConfidenceLevel = 100;}
            if(LocPattern == "dun"){
                CorrectedPattern = "dan";
                ConfidenceLevel = 100;}
            if(LocPattern == "duva"){
                CorrectedPattern = "dnva";
                ConfidenceLevel = 100;}
            if(LocPattern == "uuv"){
                CorrectedPattern = "dnv";
                ConfidenceLevel = 100;}
            if(LocPattern == "dvdun"){
                CorrectedPattern = "dvdan";
                ConfidenceLevel = 100;}
            if(LocPattern == "dvdu"){
                CorrectedPattern = "dvdn";
                ConfidenceLevel = 100;}
            if(LocPattern == "dnup"){
                CorrectedPattern = "dnvp";
                ConfidenceLevel = 100;}
            if(LocPattern == "avdu"){
                CorrectedPattern = "avdn";
                ConfidenceLevel = 100;}
            if (LocPattern == "dntua"){
                CorrectedPattern = "dntva";
                ConfidenceLevel = 100;}
          }

      if(VerifyPattern){
        //check rules

        //(1) first check proper noun rule of must start with a capital letter
        //(2) Sentence should not start with adjective
        //(3) there should be a verb in the sentence

        //(1)
        PatternPointer = CorrectedPattern.find('P');
        if(PatternPointer >=0){
            WorkingWord = GetswWords(PatternPointer);
            if((WorkingWord[0]>='A') && (WorkingWord[0]<='Z')){
                //rule passed
                if(Verbose)
                    cout << "[c_Language.h::PatternReview] Pattern accepted,\n    proper noun rule passed.\n";
                 }
              else
                //rule failed
                {CorrectedPattern = GetFromSentencePattern();
                ConfidenceLevel = -1;
                if(Verbose)
                    cout << "[c_Language.h::PatternReview] Pattern rejected,\n    proper noun indicated but did not start with a capital!\n";
                }
        }
      } //end verify pattern

     if(Verbose)cout << " Received Pattern:" << GetFromSentencePattern() << " Correct Pattern:" << CorrectedPattern << endl;

   return CorrectedPattern;
 }
//--------------------------End Language Review------------------------------------------------


//-------------------------Find Word Type------------------------------------------------------
 char FindWordType(string tmpWord, int LocationInSentence = -1){

           if(Verbose)cout << "[c_Language::FindWordType] :";


           string OrigWord;
           string OrigWordUC;


           char tmpWordType = 'u';

           string ProNounsInward =      " you your yours ";
           string ProNounsOther =       " they them he him his she her it we ";
           string ProNounsOutward =     " me mine my I i ";
           string Determiners =         " the a an each every certain this that these those any all each some few either little many much ";
           string Questions =           " what where how when who ";
           string Verbs =               " go went can will be have do say get make go know take is see come fell ran think look want give use find tell ask work seem feel try leave call am been ";
           string PluralVerbs =         " are ";
           string SubjectReplacements = " it that this its ";
           string Adverbs =             " very again ";
           string Directives =          " compare same about ";
           string JoiningWords =        " and ";
           string AssociativeWord =     " name name's ";
           string PluralPronoun =       " both ";
           string ThrowAwayWords =      " of also ";
           string GenderIndicator =     " boy male man men girl female woman women ";
           string MaleGenderClass =     " boy male man men ";
           string FemaleGenderClass =   " girl female woman women ";
           string GenderDeterminer =    " gender ";
           string GreetingsWord =       " hello hi ";
           string ConjunctionWords =    " or either ";
           string PrepositionWords =    " in into after to on with within of at until over across among throughout during towards upon across ";
           string SingularWord  =       "";
           string UCWord        =       GetswWords(LocationInSentence);

           int  isPreposition       = -1;
           int  isThrowAwayWord     = -1;
           int  isPluralPronoun     = -1;
           int  isPluralVerb        = -1;
           int  isDirective         = -1;
           int  isDeterminer        = -1;
           int  isQuestion          = -1;
           int  isVerb              = -1;
           int  isSubRep            = -1;
           int  isAdverb            = -1;
           int  isJoiner            = -1;
           int  isProNounsOther     = -1;
           int  isProNounsInward    = -1;
           int  isProNounsOutward   = -1;
           int  isAssociativeWord   = -1;
           int  isGenderIndicator   = -1;
           int  isGreetingsWord     = -1;
           int  isConjunction       = -1;
           int  isMaleGenderClass   = -1;
           int  isFemaleGenderClass = -1;
           int  isGenderDeterminer  = -1;
           int  QuoteMarker         = -1;
           int  PatternMarker       = -1;
           int  ActionMarker        = -1;
           bool RuleTesting         = true;
           bool IsPlural            = false;
           bool Result              = false;




              for(int t = 0; t < int(tmpWord.size()); t++){
                tmpWord[t] = tolower(tmpWord[t]);}
              OrigWord     = tmpWord;
              OrigWordUC   = GetswWords(LocationInSentence);
              tmpWord = " " + tmpWord + " ";

                ActionMarker        = tmpWord.find("ing");
                isPreposition       = PrepositionWords.find(tmpWord);
                isConjunction       = ConjunctionWords.find(tmpWord);
                isPluralVerb        = PluralVerbs.find(tmpWord);
                isGenderDeterminer  = GenderDeterminer.find(tmpWord);
                isMaleGenderClass   = MaleGenderClass.find(tmpWord);
                isFemaleGenderClass = FemaleGenderClass.find(tmpWord);
                isGreetingsWord     = GreetingsWord.find(tmpWord);
                isGenderIndicator   = GenderIndicator.find(tmpWord);
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
                QuoteMarker         = tmpWord.find("'");


                  if (QuoteMarker >= 0){
                      tmpWordType   = 'C';}
                  if (isConjunction >= 0){
                      tmpWordType  = 'c';}
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
                       tmpWordType = 'q';
                       SetInSentenceIsQuestion(true);}
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
                        SetInSentenceHasPluralPronoun(true);}
                  if (isThrowAwayWord >=0){
                        tmpWordType = 't';}
                  if (isGenderIndicator >=0){
                        tmpWordType = 'G';
                        SetInSentenceHasGenderReference(true);}
                  if (isGreetingsWord >=0){
                        tmpWordType = 'W';
                        SetInSentenceHasGreetingsWord(true);}
                  if (isGenderDeterminer >=0){
                        tmpWordType = 'B';
                        SetInSentenceHasGenderDeterminer(true);}
                  if ((isFemaleGenderClass >=0) && (LocationInSentence != -1)){
                        SetswGenderClassInSentence(LocationInSentence,'f');}
                  if ((isMaleGenderClass >=0) && (LocationInSentence != -1)){
                        SetswGenderClassInSentence(LocationInSentence,'m');}
                  if(isPluralVerb >=0){
                        tmpWordType = 'v';
                        SetswIsPluralWord(LocationInSentence,true);
                        SetswPluralWordFlag(LocationInSentence,'p');}
                  if(isPreposition >=0){
                        tmpWordType = 'I';
                        SetInSentenceHasPreposition(true);
                        SetInSentencePrepositionPosition(LocationInSentence);}

                  if((UCWord[0] >='A') && (UCWord[0] <='Z') &&(tmpWordType == 'u') ) {
                        tmpWordType = 'P';}


                  if( (ActionMarker >=0) && (tmpWordType == 'u') ) {
                         tmpWordType = 'v';}


                  /// **TODO**  Check for plural verbs, i.e. are->is
                  ///           Try to set tense flag
                  //***check for plural word and set if so*****
                  //*rules:
                  //   1) Must not be a verb
                  //   2) Words ending in -ch, -s, -sh, -x, -z  get -es added
                  //           i.e. wash - washes, box - boxes,
                  //   3) Some words ending in f or fe change to ves:
                  //           knife - knives, life - lives, wife - wives, shelf - shelves
                  //   4) Words ending in ff add s:
                  //            cliffs, sniffs, scoffs, toffs stiffs, tiffs
                  //   5) Change y to ies or s
                  //        a. If the word ends in a vowel (a,e,i,o,u) + y then just add s:
                  //             boy - boys, journey - journeys, key - keys, tray - trays
                  //        b. If the word ends in a consonant + y change y to ies:
                  //             country - countries, baby - babies, body - bodies, memory - memories
                  //      ***Exceptions: add s: roof - roofs, proof - proofs, chief - chiefs
                  //    6) Adding s or es to words ending in O:
                  //        a. If a word ends in a vowel (a,e,i,o,u) + 'o' then we sometimes add s.
                  //            radio - radios, stereo - stereos, video - videos
                  //        b. If a words ends in a consonant + 'o', we sometimes add s, sometimes es. No rules for this
                  //            kilo - kilos, zero - zeros, piano - pianos, photo - photos
                  //            ****but hero - heroes, potato - potatoes, volcano - volcanoes, tomato - tomatoes.
                  //    7) Irregular plurals
                  //            woman - women, man - men, child - children, person - people, tooth - teeth, foot - feet, mouse - mice, penny - pence
                  //    8) Regular plurals end in -s
                  //            i.e. dog-dogs
                  //    9) Plural proper nouns end in ' if the proper noun ends in s
                  //            i.e. Jones - Jones' Texas - Texas'




                  //Rule #3 comes before Rule #2 because pattern matching finds es before ves
                  while (RuleTesting){

                        //Rule #1 Must Not be verb, must not be preset as pronoun
                        if(tmpWordType == 'v') {RuleTesting = false; break;}
                        if((tmpWordType == 'p') || (tmpWordType == 'm') || (tmpWordType == 'y')) {SetInSentenceHasPronoun(true); RuleTesting = false; break;}

                        //Rule #9 Plural Proper Noun Check
                        PatternMarker = OrigWord.find("s'");
                        if ((PatternMarker >=0)&&((PatternMarker+2)==int(OrigWord.size())) && ((OrigWordUC[0]>='A') && (OrigWordUC[0] <= 'Z')) ){
                            SingularWord = OrigWord.substr(0,PatternMarker+1);
                            SetswIsPluralWord(LocationInSentence,true);
                            SetswPluralRoot(LocationInSentence,SingularWord);
                            SetswPluralWordFlag(LocationInSentence,'p');
                            tmpWordType = 'P'; //proper noun
                            RuleTesting = false;
                            IsPlural    = true;
                            break; }

                        //Rule #3 Some words ending in f or fe change to ves: knife - knives, life - lives, wife - wives, shelf - shelves
                        PatternMarker = OrigWord.find("ves");
                        //Location must be the ending
                        if((PatternMarker >=0)&&((PatternMarker+3)==int(OrigWord.size()))){
                            SingularWord = OrigWord.substr(0,PatternMarker);
                            //exceptions
                            if(SingularWord == "shel")
                                SingularWord += "f";
                                else
                                    SingularWord +="fe";
                            SetswIsPluralWord(LocationInSentence,true);
                            SetswPluralRoot(LocationInSentence,SingularWord);
                            SetswPluralWordFlag(LocationInSentence,'p');
                            SetswWordType(GetMemoryCellcharWordType(SingularWord,Result),LocationInSentence);
                            tmpWordType = GetMemoryCellcharWordType(SingularWord,Result);
                            RuleTesting = false;
                            IsPlural    = true;
                            break;
                        }

                        //"ses" Rule Some words ending in s  change to ses: house - houses
                        PatternMarker = OrigWord.find("ses");
                        //Location must be the ending
                        if((PatternMarker >=0)&&((PatternMarker+3)==int(OrigWord.size()))){
                            SingularWord = OrigWord.substr(0,PatternMarker);
                            SingularWord +="se";
                            SetswIsPluralWord(LocationInSentence,true);
                            SetswPluralRoot(LocationInSentence,SingularWord);
                            SetswPluralWordFlag(LocationInSentence,'p');
                            tmpWordType = GetMemoryCellcharWordType(SingularWord,Result);
                            SetswWordType(GetMemoryCellcharWordType(SingularWord,Result),LocationInSentence);
                            RuleTesting = false;
                            IsPlural    = true;
                            break;
                        }


                        //Rule #4 Words ending in ff add s: cliffs, sniffs, scoffs, toffs stiffs, tiffs
                        PatternMarker = OrigWord.find("ffs");
                        //Location must be the ending
                        if((PatternMarker >=0)&&((PatternMarker+3)==int(OrigWord.size()))){
                            SingularWord = OrigWord.substr(0,PatternMarker);
                            SingularWord +="ff";
                            SetswIsPluralWord(LocationInSentence,true);
                            SetswPluralRoot(LocationInSentence,SingularWord);
                            SetswPluralWordFlag(LocationInSentence,'p');
                            SetswWordType(GetMemoryCellcharWordType(SingularWord,Result),LocationInSentence);
                            tmpWordType = GetMemoryCellcharWordType(SingularWord,Result);
                            RuleTesting = false;
                            IsPlural    = true;
                            break;
                        }


                        //Rule #2 Words ending in -ch, -s, -sh, -x, -z  get -es added  i.e. wash - washes, box - boxes
                        //      NOTE - houses needs fixed
                        PatternMarker = OrigWord.find("es");
                        //Location must be the ending
                        if((PatternMarker >=0)&&((PatternMarker+2)==int(OrigWord.size()))){
                            SingularWord = OrigWord.substr(0,PatternMarker);
                            SetswIsPluralWord(LocationInSentence,true);
                            SetswPluralRoot(LocationInSentence,SingularWord);
                            SetswPluralWordFlag(LocationInSentence,'p');
                            SetswWordType(GetMemoryCellcharWordType(SingularWord,Result),LocationInSentence);
                            tmpWordType = GetMemoryCellcharWordType(SingularWord,Result);
                            RuleTesting = false;
                            IsPlural    = true;
                            break;
                        }


                        //Rule #8 Regular Plurals: dogs, cats, cars
                        //   Last letter = 's' must not be 'ss'
                        PatternMarker = OrigWord.size()-1;
                        if(OrigWord[PatternMarker] == 's'){
                            PatternMarker = OrigWord.find("ss");
                            if((PatternMarker >=0)&&((PatternMarker+2)==int(OrigWord.size()))){
                              // end in ss don't proceed
                            }
                            else{
                                SingularWord = OrigWord.substr(0,PatternMarker);
                                SetswIsPluralWord(LocationInSentence,true);
                                SetswPluralRoot(LocationInSentence,SingularWord);
                                SetswPluralWordFlag(LocationInSentence,'p');
                                SetswWordType(GetMemoryCellcharWordType(SingularWord,Result),LocationInSentence);
                                tmpWordType = GetMemoryCellcharWordType(SingularWord,Result);
                                RuleTesting = false;
                                IsPlural    = true;
                                break;}
                        }


                        RuleTesting = false;
                  }
                  if(!IsPlural){
                      SetswPluralWordFlag(LocationInSentence,'s');  //set as singular
                  }

            if(Verbose)
                cout << "tmpWord " << tmpWord <<" type:" << tmpWordType << endl;
            return tmpWordType;

 }
//--------------------------------end Find Word Type--------------------------------------

//-----------------------SlowSpeak--------------------------------------------------------
void SlowSpeak(string str_Data, bool Recording = true, int Delay = ThisSpeed, bool CarriageReturn = true ){
    if(StoryMode == false){
             string WorkingWord;
             if(Recording){
                SaveResponsesSent(str_Data);}
             SlowSentence.Parse(str_Data);
             for(int x = 0; x < SlowSentence.GetWordCount(); x++){

                WorkingWord = SlowSentence.GetWords(x);
                for(int y = 0; y < int(WorkingWord.size()); y++){
                    cout << WorkingWord[y];
                    for(int dly = 0; dly < Delay; dly++);
                }
                cout  << " ";

             }
                cout << "\b";
                if(CarriageReturn) cout << SlowSentence.GetPunctuation() << endl;
    }//end Story Mode
}
//--------------------------------End SlowSpeak------------------------------------------

//-------------------------Request User Response-----------------------------------------
int RequestUserResponse(string AltPositiveResponse = "", string AltNegativeResponse = "", string OtherResponse = "")
{
    if(StoryMode == false){
            int Matched = -1;

            string PositiveResponse = " yes Yes OK ok Ok correct Correct right Right Exactly exactly ye ";
            string NegativeResponse = " No no wrong Wrong What what n ";
            string Response         = "";
            if(AltPositiveResponse != "") PositiveResponse = AltPositiveResponse;
            if(AltNegativeResponse != "") NegativeResponse = AltNegativeResponse;

            while (Response == ""){
                cout << ">?";
                getline (cin,Response);}
            tmpSentence.Parse(Response);
            Response = tmpSentence.GetWords(0);
            Matched = PositiveResponse.find(" " + Response + " ");
            if(Matched >= 0)
                return 1;
            Matched = NegativeResponse.find(" " + Response + " ");
            if(Matched >= 0)
                return -1;

            Matched = OtherResponse.find(" " + Response + " ");
            if(Matched >= 0)
                return -2;
    }//end story mode check
    return 1;
}
//-------------------------End Request User Response-----------------------------------------

//---------------------------------FINDSUBJECT()--------------------------------------------------
        int FindSubject()
        {
            //********TODO**********************
            //  Check for and flag/store dual subjects, i.e. Jack and Jill
            //Order Of Preference:
            //  Proper Noun
            ///  Pronoun   ****TODO***Check and use the other two types of Pronouns; ProNounsInward-m,ProNounsOutward-y, and still use ProNounsOther-p
            //  Noun
            //  Determiner +1
            //  Unknown word

            if(Verbose)cout << "[c_Language.h::FindSubject]" << endl;
            int DeterminerLocation;       DeterminerLocation = -1;
            int UnknownLocation;          UnknownLocation    = -1;
            int WordCount;                WordCount          =  0;
            int SubLocation;              SubLocation        = -1;
            int NounLocation;             NounLocation       = -1;
            int SecondNounLocation;       SecondNounLocation = -1;
            int ProNounLocation;          ProNounLocation    = -1;
            int ProperNounLocation;       ProperNounLocation = -1;
            int JoinerLocation;           JoinerLocation     = -1;
            string Pattern;               Pattern            = "";
            bool PickingSubject;          PickingSubject     = true;

            WordCount = GetFromSentenceWordCount();

            if ((GetswWordsLC(0)== "is") || (GetswWordsLC(0)=="can") || (GetswWordsLC(0)=="will") || (GetswWordsLC(0)=="are") ) SetInSentenceIsQuestion(true);

            for(int x = 0; x < WordCount; x++){
                if(GetswWordType(x)== 'd') if(DeterminerLocation == -1) DeterminerLocation = x;
                if(GetswWordType(x)== 'u') if(UnknownLocation == -1)    UnknownLocation    = x;
                if(GetswWordType(x)== 'n'){if(NounLocation == -1)    { NounLocation       = x;} else SecondNounLocation = x;}
                if(GetswWordType(x)== 'r') if(SubLocation == -1)        SubLocation        = x;
                if(GetswWordType(x)== 'p') if(ProNounLocation == -1)    ProNounLocation    = x;
                if(GetswWordType(x)== 'P') if(ProperNounLocation == -1) ProperNounLocation = x;
                if(GetswWordType(x)== 'm') if(ProNounLocation == -1) ProNounLocation = x;
                if(GetswWordType(x)== 'y') if(ProNounLocation == -1) ProNounLocation = x;
                if(GetswWordType(x)== 'j') JoinerLocation = x;
                if(GetswWordType(x)== 'v'){ SetInSentenceVerbLocation(x);}
                if(GetswWordType(x)== 'a'){ SetInSentenceAdjectiveLocation(x);}
                if(GetswWordType(x)== 'A'){ SetInSentenceAdverbLocation(x);}
                if(GetswWordType(x)== 'I'){ SetInSentencePrepositionPosition(x);}
                Pattern += GetswWordType(x);
            }
            SetInSentencePattern(Pattern);
            if(SecondNounLocation != -1) SetInSentenceIndirectObjectLocation(SecondNounLocation); else SetInSentenceIndirectObjectLocation(-1);
            if(SecondNounLocation != -1) SetInSentenceNounCount(2); else SetInSentenceNounCount(1);

            if( (ProperNounLocation != -1) && (NounLocation != -1) ){
                SetInSentenceIndirectObjectLocation(NounLocation);       //set indirect object
                SubLocation = ProperNounLocation;
                PickingSubject = false;}
            else
                if ((ProNounLocation != -1) && (NounLocation != -1)){
                    SetInSentenceIndirectObjectLocation(NounLocation);
                    SubLocation = ProNounLocation;
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

                if(JoinerLocation >= 1){                      //check for dual subjects
                    if((JoinerLocation +1) == SubLocation){
                        SetInSentenceHasDualSubjects(true);
                        SetInSentenceSecondSubject(GetswWords(JoinerLocation - 1));
                        SetInSentenceSecondSubjectLocation(JoinerLocation - 1);}
                     else {
                        if((JoinerLocation - 1) == SubLocation)
                        {SetInSentenceHasDualSubjects(true);
                         SetInSentenceSecondSubject(GetswWords(JoinerLocation + 1));
                         SetInSentenceSecondSubjectLocation(JoinerLocation + 1);}
                     }
                }

            if(Verbose)
                    cout << "Suggested subject location:" << SubLocation << " Pattern:" << GetFromSentencePattern() << " Indirect Object Location:" << GetFromSentenceIndirectObjectLocation()<< endl;
            SetInSentenceSubjectLocation(SubLocation);
            return SubLocation;
        }
//--------------------------------------------------end Find Subject----------------------------------------------------------


//----------------------------Find and Set Gist of Current Sentence-----------------------------------------------------------

        bool FindAndSetGistOfSentence(){
        if(Verbose)cout << "[c_Language::FindAndSetGistOfSentence] :";
            //***TODO*** Find and set subGistOfSentence
            //  also save and read this new data, plus Preposition flag and position in Long Term Memory
            bool   Result          = false;
            bool   Checking        = true;
            int    VerbPointer     = -1;
            int    QuestionPointer = -1;
            int    JoinerPointer   = -1;
            int    StopPoint       = -1;
            int    GistStart       = -1;
            string GistString      = "";
            string subGistString   = "";
            string SupportiveGist  = "";
            string LocalPattern    =GetFromSentencePattern();

            for(int x = 0; x <=int(LocalPattern.size()); x++){
                if(LocalPattern[x] == 'v') VerbPointer     = x;
                if(LocalPattern[x] == 'q') QuestionPointer = x;
                if(LocalPattern[x] == 'j') JoinerPointer   = x;
            }

            if( (VerbPointer < 0) && (!GetFromSentenceIsQuestion()) ) Checking = false; //no verb, cannot find gist without it(yet)
            while (Checking){
                    if(GetFromSentenceIsQuestion()){
                        //process gist of question
                        GistStart = QuestionPointer+1;
                        for (int x = QuestionPointer+1; x <= GetFromSentenceWordCount(); x++){
                            GistString += " " + GetswWords(x);
                        }
                        Result = true;     //control, Gist was found
                        Checking = false;
                    }
                    else
                    {
                        //process gist of statement
                        //for now, gist is verb to the end of sentence or until preposition is found
                        if(GetFromSentenceHasPreposition()){
                            StopPoint = GetFromSentencePrepositionPosition()-1;
                            if(StopPoint < VerbPointer) StopPoint = GetFromSentenceWordCount();
                        }
                        else{
                            if(JoinerPointer >=0)
                               StopPoint = JoinerPointer-1;
                            else
                               StopPoint = GetFromSentenceWordCount();
                        }
                        GistStart = VerbPointer;
                        for(int x = VerbPointer; x <= StopPoint; x++){
                            GistString += " " + GetswWords(x);
                        }
                        Result   = true;  //control, Gist was found
                        Checking = false;
                        //since there is a verb, Get sub-Gist of I type word (preposition)
                        if(GetFromSentenceHasPreposition()){
                            //Get sub-Gist including preposition, to verb pointer or end of sentence
                            if(VerbPointer < GetFromSentencePrepositionPosition()){
                               StopPoint = GetFromSentenceWordCount();
                            }
                            else{
                                StopPoint = VerbPointer;
                            }
                            for (int x = GetFromSentencePrepositionPosition(); x < StopPoint; x++){
                                subGistString += " " + GetswWords(x);
                            }
                        }
                        else
                        if(JoinerPointer>=0){
                            for(int x = JoinerPointer+1; x <=GetFromSentenceWordCount(); x++){
                                subGistString += " " + GetswWords(x);
                            }
                        }
                    }

            }//end while checking

            if(Result){ //extract supportive gist to the beginning of the gist
                    for(int x = 0; x<= GistStart-1; x++){
                        SupportiveGist += GetswWords(x) + " ";
                    }

            }

            if(Result){
                //store the Gist and subGist phrase
                //  trim leading space
                string  NewGistString     = "";
                string  NewSubGist        = "";
                string  NewSupportiveGist = "";
                for(int x = 1; x<= int(GistString.size()-1); x++){
                    NewGistString += GistString[x];
                }
                for(int x = 1; x <=int(subGistString.size()-1); x++){
                    NewSubGist += subGistString[x];
                }
                for(int x = 0; x <=int(SupportiveGist.size()-1); x++){
                    NewSupportiveGist += SupportiveGist[x];
                }
                SetInSentenceSupportivePhrase(NewSupportiveGist);
                SetInSentenceGistOfSentence(NewGistString);
                SetInSentenceSubGistOfSentence(NewSubGist);
                if (Verbose){
                    cout << "\n  Gist =" << GistString << endl;
                    cout << "  subGist =" << subGistString << endl;
                 }
            }


            return Result;

        }
//------------------------END of Bool FINDANDSETGISTOFSENTENCE()----------------------------------------------------------------

//-------------------------Imply Unknowns()-------------------------------------------------------------------------------------

        void ImplyUnknowns(){
        //look for unknown word types inside certain patterns and assert their type
        // note:This pattern work and assumptions comes from observing patterns stored in PatternData.file for this purpose
        //local vars
        string    LocalPattern      = GetFromSentencePattern();
        bool      SettingPattern    = true;
        int       PatternPointer    = -1;

        while(SettingPattern){

            //Check for noun possible in this pattern 'duIduvu'
            // the unknown follows a determiner and then has a preposition, most likely a noun a position 1
            PatternPointer = LocalPattern.find("duI");
            while(PatternPointer >=0){
                LocalPattern[PatternPointer+1] = 'n';
                SetswWordType('n',PatternPointer+1);
                SetInSentencePattern(LocalPattern);
                PatternPointer = LocalPattern.find("duI");   //check again
                SettingPattern = false;
                //break;} // allow next pattern check to proceed
                }

            PatternPointer = LocalPattern.find("duvu");
            if(PatternPointer >= 0){
                LocalPattern[PatternPointer+1] = 'n';
                SetswWordType('n',PatternPointer+1);
                SetInSentencePattern(LocalPattern);
                break;}


            PatternPointer = LocalPattern.find("pu"); //check for implied noun by ownership, i.e. "his bone"
            if(PatternPointer >= 0){
               if((GetswWordsLC(PatternPointer) == "his") || (GetswWordsLC(PatternPointer) == "her")){
                   LocalPattern[PatternPointer+1] = 'n';
                   SetswWordType('n',PatternPointer+1);
                   SetInSentencePattern(LocalPattern);
                   SettingPattern = false;
                   break;}
            }

         SettingPattern = false;
        }//end while loop



    }
//-------------------------------END IMPLY UNKNOWNS------------------------------------------------------------------------------
};

#endif // C_LANGUAGE_H
