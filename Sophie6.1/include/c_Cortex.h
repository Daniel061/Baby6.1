#ifndef C_CORTEX_H
#define C_CORTEX_H
#include <c_Language.h>

class c_Cortex : public c_Language
{
    public:
        c_Cortex();
        virtual ~c_Cortex();

   private:

            int Control;
            string Pattern;
            char tmpWordType;
            int NounLocation;
            int DeterminerLocation;
            int ProNounOtherLocation;
            int ProNounInwardLocation;
            int ProNounOutwardLocation;
            int AssociativeWordLocation;
            int VerbLocation;
            //int AdjectiveLocation;
            int SubjectLoc;
            int ReplacementLocation;
            int UnderstandingLevel;
            int UnderstandingDegree;
            int UnknownCount;
            int UnKnownLocation;
            int FirstUnknown;
            int QuestionLocation;
            int UserResponse;
            int ContractionLocation;
            int ConjunctionLocation;
            int AdverbLocation;
            int DirectiveLocation;
            int JoinerLocation;
            int DirectObjectLocation;
            int IndirectObjectLocation;
            int PluralPossessiveLocation;
            int PluralPronounLocation;
            int ProperNounLocation;
            int GenderIndicatorLocation;
            bool isGenderIndicator;
            float UnderstandingRatio;
            bool ISQ;
            bool Rerundecipher = false;
            bool ForcedSubjectChange = false;


    public:
        bool DecipherCurrentSentence(string &strData){
            if(Verbose){cout << "[c_Cortex.h::DeciperCurrentSentence]" << endl;}

            SubjectLoc               = GetFromSentenceSubjectLocation();
            AdjectiveLocation        = -1;
            FirstUnknown             = -1;
            ContractionLocation      = -1;
            ConjunctionLocation      = -1;
            DeterminerLocation       = -1;
            ProNounOtherLocation     = -1;
            ISQ                      = false;
            ForcedSubjectChange      = false;
            Pattern                  = "";
            NounLocation             = -1;
            Control                  = -1;
            UnderstandingLevel       = 0;
            UnderstandingRatio       = 0.0;
            UnknownCount             = 0;
            QuestionLocation         = 0;
            AdverbLocation           = -1;
            DirectiveLocation        = -1;
            JoinerLocation           = -1;
            DirectObjectLocation     = -1;
            IndirectObjectLocation   = -1;
            PluralPossessiveLocation = -1;
            ProNounInwardLocation    = -1;
            ProNounOutwardLocation   = -1;
            AssociativeWordLocation  = -1;
            PluralPronounLocation    = -1;
            ProperNounLocation       = -1;
            UnKnownLocation          = -1;
            bool Greetings           = false;
            GenderIndicatorLocation  = -1;
            isGenderIndicator        = false;

            for(int x =0; x < GetFromSentenceWordCount(); x++){                                                                  // Build pattern string i.e. duvu  4 word sentence
                    Pattern += GetWordType(x);
                    tmpWordType = GetWordType(x);
                    if (tmpWordType == 't') {UnderstandingLevel++;}
                    if (tmpWordType == 'c') {UnderstandingLevel++; ConjunctionLocation = x;}
                    if (tmpWordType == 'n') {NounLocation = x; UnderstandingLevel++;}
                    if (tmpWordType == 'd') {DeterminerLocation = x; UnderstandingLevel++;}
                    if (tmpWordType == 'p') {ProNounOtherLocation = x; UnderstandingLevel++;}
                    if (tmpWordType == 'y') {ProNounOutwardLocation = x; UnderstandingLevel++;}
                    if (tmpWordType == 'm') {ProNounInwardLocation = x; UnderstandingLevel++;}
                    if (tmpWordType == 'g') {AssociativeWordLocation = x; UnderstandingLevel++;}
                    if (tmpWordType == 'v') {VerbLocation = x; UnderstandingLevel++;}
                    if (tmpWordType == 'a') {AdjectiveLocation = x; UnderstandingLevel++;}
                    if (tmpWordType == 'r') {ReplacementLocation = x; UnderstandingLevel++;}
                    if (tmpWordType == 'q') {QuestionLocation = x; UnderstandingLevel++;}
                    if (tmpWordType == 'C') {ContractionLocation = x; UnderstandingLevel++;}
                    if (tmpWordType == 'A') {AdverbLocation = x; UnderstandingLevel++;}
                    if (tmpWordType == 'X') {DirectiveLocation = x; UnderstandingLevel++;}
                    if (tmpWordType == 'P') {ProperNounLocation = x; UnderstandingLevel++;}
                    if (tmpWordType == 'j') {JoinerLocation = x; UnderstandingLevel++;}
                    if (tmpWordType == 's') {PluralPossessiveLocation = x; UnderstandingLevel++;}
                    if (tmpWordType == 'N') {PluralPronounLocation = x; UnderstandingLevel++;}
                    if (tmpWordType == 'G') {GenderIndicatorLocation = x; UnderstandingLevel++; isGenderIndicator = true;}
                    if (tmpWordType == 'W') {UnderstandingLevel++;}
                    if (tmpWordType == 'B') {UnderstandingLevel++;}
                    if (tmpWordType == 'I') {UnderstandingLevel++;}
                    if (tmpWordType == 'u') {
                            UnknownCount++; UnKnownLocation = x;
                            if(FirstUnknown == -1) FirstUnknown = x;
                            }
            }//end for loop to scan sentence

            if(HasPronoun) CheckForImpliedGender();               //see if gender info exist
            UnderstandingDegree = GetFromSentencesUnderstandingLevel();
            if(GetFromSentenceIsQuestion())UnderstandingDegree = 1;           //question trap
            if(DirectiveLocation >=0)UnderstandingDegree = 2;     //directive trap
            if(GetFromSentenceHasPluralPronoun())UnderstandingDegree = 3;     //plural pronoun trap
            if(GetFromSentenceHasGreetingsWord())UnderstandingDegree = 4;     //greetings trap

        ofstream PatternDataFile ("PatternData.dat", ios::out | ios::app);
        if (PatternDataFile.is_open()){ PatternDataFile << Pattern << "," << GetFromSentenceOriginalString() << ",from before Switch(UnderstandingDegree)" << endl; PatternDataFile.close();}

            switch (UnderstandingDegree)
            {
               case 0:{  ///All new words, lots of work to do
                   if (Verbose)
                    cout << "[c_Cortex.h::DeciperCurrentSentence] Case 0" << endl;


                 switch(GetMoodLevel()){
                    case  0:{
                      SlowSpeak(":x");
                      DecreaseMoodLevel();
                      break;
                   }
                    case 1:{
                      SlowSpeak("I'm sorry."); SlowSpeak("I don't understand this yet.");
                      SlowSpeak("Can you reword it somehow?");
                      SlowSpeak(":(");
                      DecreaseMoodLevel();
                      break;
                   }
                    case 2:{
                      SlowSpeak("I'll try harder next time.");
                      SlowSpeak(":o");
                      DecreaseMoodLevel();
                      break;
                     case 3:{
                       SlowSpeak("I don't know what " + GetWords(0)+ " is.");
                       SlowSpeak(":{");
                       DecreaseMoodLevel();
                       break;
                     }
                    }

                 }



                 break;
               }
               case 1:{ //question trap
                   if (Verbose)
                    cout << "[c_Cortex.h::DeciperCurrentSentence] Case 1 - Question trap" << endl;
                   if(!QuestionSentenceBreakDown())
                   HandleQuestion(strData);
                   break;}

               case 2:{ //directive trap
                   if (Verbose)
                    cout << "[c_Cortex.h::DeciperCurrentSentence] Case 2 - directive trap" << endl;
                    HandleDirective();
                    break;}

               case 3:{ //plural pronoun trap
                   if (Verbose)
                    cout << "[c_Cortex.h::DeciperCurrentSentence] Case 3 - Plural pronoun trap" << endl;
                    HandlePluralPronoun(PluralPronounLocation);
                    break;}

                case 4:{ //Greetings trap
                   if (Verbose)
                    cout << "[c_Cortex.h::DeciperCurrentSentence] Case 4 - Greetings trap" << endl;
                    CheckForGreetings(Greetings);
                    break;}

                case 10:{  ///Only 1 known but could have a ratio of 100%
                   if (Verbose)
                    cout << "[c_Cortex.h::DeciperCurrentSentence] Case 10 - no code here" << endl;

                     SlowSpeak("I'm going to have to work on this.");
                     break;}

                case 25:{  ///Some understanding but depends on ratio
                   if (Verbose)
                    cout << "[c_Cortex.h::DeciperCurrentSentence] Case 25 - Maybe Missing determiner - add in the help" << endl;
                    if(GetWordType(0) == 'u'){
                     strData = "the " + strData;
                     return true;}   //call for rerun
                     else
                      SlowSpeak("I don't know "  + GetWords(FirstUnknown)+"?");
                    break;}

                case 50:{  ///stronger understanding but also depends on ratio
                   if (Verbose)
                    cout << "[c_Cortex.h::DeciperCurrentSentence] Case 50 -send to WorkWithHalfLevel()" << endl;
                     WorkWithHalfLevel(Pattern,DeterminerLocation);
                     break;}

                case 75:{  ///Much stronger
                   if (Verbose)
                    cout << "[c_Cortex.h::DeciperCurrentSentence] Case 75 - send to Handle75LevelUnderstanding" << endl;
                     Handle75LevelUnderstanding(strData);
                     break;}

                case 100:{  ///very strong
                   if (Verbose)
                    cout << "[c_Cortex.h::DeciperCurrentSentence] Case 100 - inside logic" << endl;
                    string tmpSubject;
                    if(GetFromSentenceSubjectLocation() != -1){
                         tmpSubject = GetWords(SubjectLoc);
                         SetSubjectInStack(GetWordTokens(SubjectLoc),tmpSubject,GetFromSentenceOriginalString());
                         if(GetWordType(GetFromSentenceSubjectLocation())=='p'){
                            CheckForImpliedGender();}}
                     if((GetFromSentenceHasGenderReference()) && (GetFromSentenceSubjectLocation()!=-1)){
                        //assign Gender to subject
                        if(GenderIndicatorLocation != -1){
                            SetGenderClassInSentence(GetFromSentenceSubjectLocation(),GetGenderClassInSentence(GenderIndicatorLocation));
                        }
                     }
                     if((JoinerLocation != -1) && (Pattern[JoinerLocation+1]=='a') ){ //associate first adjective to subject, wasn't picked up before
                        AssociateMemoryCellAdjective(GetWordTokens(GetFromSentenceSubjectLocation()),GetWordsLC(JoinerLocation-1)); }
                     SlowSpeak("Okay.");
                     IncreaseMoodLevel();
                     SetInSentenceHasBeenUnderstood(true);
                     SlowSpeak(":)");
                     break;}

            }
             return false;
            }
//--------------------------------------END DECIPHER SENTENCE------------------------------------------------------------------------

//-------------------------------------Check for greetings---------------------------------------------------------------------------
int CheckForGreetings(bool& Greeting){
    string FirstWord;
    FirstWord = GetWordsLC(0);
    Greeting = false;
    if((FirstWord == "hello") | (FirstWord == "hi")){
        SlowSpeak("Hi!");
        IncreaseMoodLevel();
        SlowSpeak("How are you?");
        Greeting = true;
        SetInSentenceHasBeenUnderstood(true);

    }
    return -1;
}
//---------------------------------------end greetings-------------------------------------------------------------------------------

//-------------------------------------PROCESS MIDLEVEL UNDERSTANDING----------------------------------------------------------------

int WorkWithHalfLevel(string Pattern, int Determiner){
    if(Verbose){cout << "[c_Cortex.h::WorkWithHalfLevel]" << endl;}
       int Response;
       string tmpAdjective;
       int StatementDirection = -1;
       int tmpAdjectiveLoc;
       bool Testing = true;
       if(Verbose)
            cout << "Noun Loc:" << NounLocation << "Unknown Loc:" << UnKnownLocation << "Pattern:" << Pattern << endl;

        ofstream HalfLevelDataFile ("HalfLevelPatternData.dat", ios::out | ios::app);
        if (HalfLevelDataFile.is_open()){ HalfLevelDataFile << Pattern << "," << GetFromSentenceOriginalString() << endl; HalfLevelDataFile.close();}
       for(int x = 0; x < GetFromSentenceWordCount(); x++){
        if((GetWordType(x) == 'y') || (GetWordType(x) == 'm') || (GetWordType(x) == 'p')){
            if(GetWordType(x)== 'y') StatementDirection = 0; //Statement towards user
            if(GetWordType(x)== 'm') StatementDirection = 1; //Statement towards program
            if(GetWordType(x)== 'p') StatementDirection = 2; //Statement towards other
        }
       }

//cout << "Pattern 1/2 level:" << Pattern << endl;
       while(Testing){

         switch (StatementDirection){

            case 0: //Statement towards user
                {
                  if((GetWords(UnKnownLocation)[0]>='A') && (GetWords(UnKnownLocation)[0]<='Z')) {
                    //Proper noun is unknown word - user might be naming self
                    SetWordType('P',UnKnownLocation);
                    SlowSpeak("Hello " + GetWords(UnKnownLocation) + "!");
                    SlowSpeak("Nice to meet you.");
                    SlowSpeak(":)");
                    IncreaseMoodLevel();
                    SetInSentenceHasBeenUnderstood(true);
                    SetUserName(GetWords(UnKnownLocation));

                  }
                  else
                  {
                      //user may be using an adjective
                  }


                  if(Verbose){cout << "[c_Cortex.h::WorkWithHalfLevel]:Case 0" << endl;}
                  Testing = false;
                  break;
                }

            case 1: //Statement towards program
                {

                  if(Verbose){cout << "[c_Cortex.h::WorkWithHalfLevel]:Case 1" << endl;}
                  Testing = false;
                  break;
                }
            case 2: //Statement towards other
                {

                  if(Verbose){cout << "[c_Cortex.h::WorkWithHalfLevel]:Case 2" << endl;}
                  Testing = false;
                  break;
                }
            default:
                {
                  Testing = false;
                }


         SlowSpeak("  Are we talking about a " + GetWords(Determiner + 1) + "?");
         Response = RequestUserResponse();
         if(Response == 1){  //yes answer
            //set subject to this
            //set wordtype to noun if it isn't
            //see if this is a known word
            IncreaseMoodLevel();
            SetWordType('n',Determiner+1);
            SetSubjectInStack(Tokenize(GetWords(Determiner+1)),GetWords(Determiner+1),GetFromSentenceOriginalString());
            for(int x =0; x < GetFromSentenceWordCount(); x++){
                if (GetWordType(x)=='u'){
                    tmpAdjective = GetWords(x);
                    tmpAdjectiveLoc = x;
                }
            }
            SlowSpeak("Great!");
            SlowSpeak("But I don't know much about a " + GetWords(Determiner +1)+ " yet.");
            SlowSpeak("And, is " + tmpAdjective + " describing " + GetWords(Determiner +1)+ "?");
            Response = RequestUserResponse();
            if(Response == 1){
                    SlowSpeak("Perfect!");
                    IncreaseMoodLevel();
                    SlowSpeak("So a " + tmpAdjective + " " + GetWords(Determiner+1) + ". Ha!");
                    SlowSpeak("Can you tell me more about " + GetWords(Determiner +1)+ "?");
                    SlowSpeak("I want to learn more!");
                    SlowSpeak(":)");
                    IncreaseMoodLevel();
                    SetInSentenceHasBeenUnderstood(true);
                    SetWordType('a',tmpAdjectiveLoc);
                    SetWordType('n',Determiner+1);
                    RebuildPattern();
                    Testing = false;

            }
            else{
                SlowSpeak(":(");
                DecreaseMoodLevel();
                Testing = false;

            }
            //release control back for more user input
         }
         else{
            SlowSpeak("  Are we talking about a " + GetWords(Determiner + 2) + "?");
            Response = RequestUserResponse();
            if(Response == -1){
                SlowSpeak("  Are we talking about a " + GetWords(Determiner + 3) + "?");
                DecreaseMoodLevel();
                Response = RequestUserResponse();
                if(Response == 1){
                    SlowSpeak("I will need to learn about " + GetWords(Determiner + 3)+".");
                    SlowSpeak("Please tell me more.");
                    IncreaseMoodLevel();
                    SetInSentenceHasBeenUnderstood(true);
                    Testing = false;
                    //set subject
                }
                else{
                    SlowSpeak("I'm lost.");
                    SlowSpeak("I need to learn more before I understand this.");
                    SlowSpeak(":(");
                    DecreaseMoodLevel();
                    Testing = false;
                }
            }
            else{
                SlowSpeak("Ok");
                SlowSpeak("You'll have to tell me more about a " + GetWords(Determiner+2)+ ".");
                SetWordType('n',Determiner+2);
                SetSubjectInStack(Tokenize(GetWords(Determiner+2)),GetWords(Determiner+2),GetFromSentenceOriginalString());
                IncreaseMoodLevel();
                SetInSentenceHasBeenUnderstood(true);
                Testing = false;
                //set subject
            }
         }
         }//end switch statement

     }//end control Loop
     return 0;
}//end work with half level
//---------------------------------------------------------------------------------------------------------------
int HandleQuestion(string &strData){
    //***TODO**
    //check for multi match and handle

    if(Verbose){cout << "[c_Cortex.h::HandleQuestion]" << endl;}
    int Control;    Control = -1;
    int MatchedCount;
    string VerbUsed, MatchedAdjective[15];
    string AnswerString;
    bool Matched = false;
    if(Verbose)
        cout << "qLoc:" << QuestionLocation << " Pattern:" << Pattern << " SubjectLoc:" << GetFromSentenceSubjectLocation() << endl;
    if(UnKnownLocation >=0){
            Handle75LevelUnderstanding(strData,true); //try to find the unknown but run silent.
            FindSubject();}

   // check for correct form
   //actually need to compare indirect object to subject
    if(GetFromSentenceIndirectObjectLocation() != -1)
    Matched = CheckLinkOfTwoNounsWithAdjectives(GetWords(GetFromSentenceIndirectObjectLocation()),GetWords(GetFromSentenceSubjectLocation()),VerbUsed,MatchedAdjective,MatchedCount);
    if (Matched){
            if(MatchedCount > 1){
                AnswerString = "The " +  GetWordsLC(GetFromSentenceSubjectLocation()) + " of ";
                if(!(GetWordType(GetFromSentenceIndirectObjectLocation())== 'P') || (GetWordType(GetFromSentenceIndirectObjectLocation())== 'p')) AnswerString += "the ";
                AnswerString +=  GetWords(GetFromSentenceIndirectObjectLocation()) + " can be ";
                for(int x = 0; x < MatchedCount; x++){
                        AnswerString = AnswerString + MatchedAdjective[x];
                        if(!(x+1==MatchedCount)) AnswerString += " or ";}
                AnswerString += ".";
                SlowSpeak(AnswerString);
                SetInSentenceHasBeenUnderstood(true);
            }
            else{
               AnswerString = "The " +  GetWordsLC(GetFromSentenceSubjectLocation()) + " of ";
               if(!(GetWordType(GetFromSentenceIndirectObjectLocation())== 'P') || (GetWordType(GetFromSentenceIndirectObjectLocation())== 'p')) AnswerString += "the ";
               AnswerString +=  GetWords(GetFromSentenceIndirectObjectLocation())+ " is " + MatchedAdjective[0] + ".";
               SlowSpeak(AnswerString);
               SetInSentenceHasBeenUnderstood(true);
            }
        }
        else
        SlowSpeak("You haven't told me yet.");
    if(Verbose)
        cout << "Matched:" << Matched << " Verb:" << VerbUsed << " Adjective: " << MatchedAdjective[0] << endl;

  return Control;
}
//End HandleQuestion-----------------------------------------------------------------------------------------------

//--------------------------------HANDLE75LEVELUNDERSTANDING-------------------------------------------------------
void Handle75LevelUnderstanding(string &strData, bool RunSilent = false){
    bool Testing                = true;
    bool NeedNameHandling       = false;
    bool VerbFollowsNamePtr     = false;
    int LocalNamePtrLocation    = GetFromSentenceNamePointer();
    int localVerbLocation       = -1;
    int SubjectLocationInCortex = -1;
    //in case of recursive entry, scan for unknown location again
//cout << "at 757Levelunderstanding with pattern of:" << Pattern << endl;
    if(Verbose){
        cout << "[c_Cortex.h::Handle75LevelUnderstanding]\n";
        cout << "  Pattern:" << Pattern << endl;
        cout << "  Run Silent:" << boolalpha << RunSilent << endl;
        cout << "  Subject Location:" << GetFromSentenceSubjectLocation() << endl;
        cout << "  Noun Location:" << NounLocation << endl;
        cout << "  Adjective Location:" << AdjectiveLocation << endl;
        cout << "  Verb Location:" << VerbLocation << endl;}

    if(GetFromSentenceNamePointer() >=0){
        NeedNameHandling = true;
        if(GetWordType(LocalNamePtrLocation+1)=='v')
            VerbFollowsNamePtr = true;
    }


//   if(NounLocation == -1){
//            NounLocation = GetSubjectLocation(); //no noun! How to handle this Kenzie??  she says if pronoun(or Proper noun) use it as noun and subject
//            ForcedSubjectChange = true;
//   }

                                                                                 //check for name handling work first
   if( NeedNameHandling ){                                                       // i.e. my name is ...   or the dog's name is ...
        Testing = false;                                                         // this is the only work required because of name reference
        if(VerbFollowsNamePtr){                                                  // try to prevent out of bounds error
        if(GetWordType(LocalNamePtrLocation-1) == 'y'){                          // the name data refers the the user, REMEMBER - this is a statement, not a question ~ questions trapped elsewhere
                if(IsThisAPropernoun(GetWords(LocalNamePtrLocation+2))){         // enforce Capital letter usage
                    SetUserName(GetWords(LocalNamePtrLocation+2));               // Store the user name
                    SlowSpeak("Hello " + GetWords(LocalNamePtrLocation+2)+"!");  // greet the user
                    SlowSpeak("Nice to meet you!");
                    SetWordType('P',LocalNamePtrLocation+2);                     // Make sure word type is set
                    }
        }//end outward direction
        }//end ensure verb follows name
   }//end name handling




   while(Testing && (NounLocation >=0)){

    //----------Missing Noun Test------
    if((NounLocation == -1) && (VerbLocation >=0) && (DeterminerLocation >=0) && (AdjectiveLocation >=0)){ //no noun but has verb, determiner and adjective
        SlowSpeak("So " + GetWords(DeterminerLocation+1)+ " can be " + GetWords(AdjectiveLocation) + "?");
        UserResponse = RequestUserResponse();
        if(UserResponse == 1){
            SetWordType('n',DeterminerLocation+1);    //set the noun
            SetInSentenceSubjectLocation(DeterminerLocation+1); //be sure subject location is newly found noun
            SlowSpeak(":)"); IncreaseMoodLevel();
            SetInSentenceHasBeenUnderstood(true);
            Testing = false;
            break;}
    }
    else{
        if( (NounLocation == -1) && (VerbLocation >=0) && (DeterminerLocation >=0) ){    // no noun but has verb and determiner
            SlowSpeak(" Are we talking about a" + GetWords(DeterminerLocation+1) + "?");
            UserResponse = RequestUserResponse();
            if(UserResponse == 1){
                SetWordType('n',DeterminerLocation+1);
                SetInSentenceSubjectLocation(DeterminerLocation+1);
                SlowSpeak(":)");
                IncreaseMoodLevel();
                SetInSentenceHasBeenUnderstood(true);
                Testing = false;
                break;}
            }
         else{
             if( (NounLocation == -1) && (VerbLocation >=0) && (GetFromSentenceHasGenderReference()) ){  // no noun but has verb and gender reference
                if(IsThisAPropernoun(GetWords(UnKnownLocation))){
                    SetWordType('P',UnKnownLocation);
                    SubjectLocationInCortex = FindSubject();
                    SetInSentenceSubjectLocation(SubjectLocationInCortex);
                    RebuildPattern();
                    DecipherCurrentSentence(strData);
                    Testing = false;
                    break;}
                 else  {
                    SetWordType('n',UnKnownLocation);
                    SubjectLocationInCortex = FindSubject();
                    SetInSentenceSubjectLocation(SubjectLocationInCortex);
                    RebuildPattern();
                    DecipherCurrentSentence(strData);
                    Testing = false;
                    break;

                 }
             }

            }
    } //------End Missing noun test------


    // --TEST FOR MISSING VERB--------------
    for(int x= 0; x < GetFromSentenceWordCount(); x++){
        if(GetWordType(x)=='v') localVerbLocation = x;}


    if(localVerbLocation == -1 ){
        if(UnKnownLocation != -1){
            SetWordType('v',UnKnownLocation);
            Testing = false;
            SlowSpeak("Okay.");
            SetInSentenceHasBeenUnderstood(true);
            break;
        }
    }



    //--END TEST FOR MISSING VERB ----------

    //-------Modifier Test-------------
    int tmpLocation; tmpLocation = Pattern.find("uav");
    if(tmpLocation >= 0){


        SlowSpeak("So " + GetWords(NounLocation)+" can be " +
                  GetWords(tmpLocation)+ " "+
                  GetWords(AdjectiveLocation)+ "?");
                  UserResponse = RequestUserResponse();
                  if(UserResponse == 1){ //tmpLocation has to be adverb(A)
                        SetWordType('A',tmpLocation);
                        SlowSpeak(":)"); IncreaseMoodLevel();
                        SetInSentenceHasBeenUnderstood(true);
                  }
                  else{
                    SlowSpeak(":("); DecreaseMoodLevel();
                  }


       Testing = false;
       break;
    }




    //-------End Modifier test---------



    //-------Noun to Noun test---------
    //i.e. the dog is an animal

    tmpLocation = Pattern.find("dnvdu") + Pattern.find("duvdn") + 1;  //if one .find returns -1 it is removed with the +1, if both return -1, the +1 results in -1
    if (tmpLocation>=0){
        if(!RunSilent)
            SlowSpeak("Okay. Tell me more about " + GetWordsLC(UnKnownLocation-1) + " " + GetWordsLC(UnKnownLocation) + ".");
            SetInSentenceHasBeenUnderstood(true);
        if(Pattern[tmpLocation+1]== 'u'){
           AssociateMemoryCellNoun(GetWordTokens(tmpLocation),GetWordsLC(tmpLocation+1));                                 //associate first noun to second noun
           AssociateMemoryCellNoun(GetWordTokens(tmpLocation+3),GetWordsLC(tmpLocation+4));                               //associate second noun to first noun
           SetWordType('n',tmpLocation+1);}
         else{
           AssociateMemoryCellNoun(GetWordTokens(tmpLocation),GetWordsLC(tmpLocation+4));                                 //associate first noun to second noun
           AssociateMemoryCellNoun(GetWordTokens(tmpLocation+3),GetWordsLC(tmpLocation+1));                               //associate second noun to first noun
           SetWordType('n',tmpLocation+4);}
        FindSubject();                                                                                                    //Update subject
        SetSubjectInStack(GetWordTokens(GetFromSentenceSubjectLocation()),GetWords(GetFromSentenceSubjectLocation()),GetFromSentenceOriginalString());        //update subject stack
        CheckForImpliedName();
        Testing = false;
        break;
    }
    //---------End Noun to noun test----------



    //----------Adjective Test---------
    if(UnKnownLocation >=0){
       if(GetPluralWordFlag(NounLocation) == 'p'){
           SlowSpeak(GetWords(UnKnownLocation) + " " + GetWords(NounLocation) + "?");}
           else{
                SlowSpeak( "A " + GetWords(UnKnownLocation) + " " + GetWords(NounLocation) + "?");}
        UserResponse = RequestUserResponse();
        if(UserResponse == 1){
            SetWordType('a',UnKnownLocation);  //set word type to adjective
            SlowSpeak(":)"); IncreaseMoodLevel();
            SetInSentenceHasBeenUnderstood(true);
            Testing = false;
            break;}
            else{
                SlowSpeak(":("); DecreaseMoodLevel();
                Testing = false;
                break;
            }}
    //---end Adjective Testing ----------


    //-- DNVUA -- Test for u = Adverb -----
    // the dog is very fast.
    SlowSpeak("A " + GetWords(UnKnownLocation) + " " + GetWords(AdjectiveLocation) + " " + GetWords(GetFromSentenceSubjectLocation()) + "?");
    UserResponse = RequestUserResponse();


    Testing = false;
    break;
    //-- END TESTING FOR ADVERB ------------





   }//---end testing control loop
   if(Verbose)
    cout << "  New Pattern:" << GetFromSentencePattern() << endl;
}
//-----------------------------END HANDLE75LEVELUNDERSTANDING -------------------------------

//----------------------ISTHISAPROPERNOUN----------------------------------------------------
    bool IsThisAPropernoun(string strDataToTest){
        if((strDataToTest[0] >= 'A') && (strDataToTest[0] <= 'Z') )
            return true;
        else
            return false;

    }
//-----------------END ISTHISAPROPERNOUN------------------------------------------------------




//------------------------DIRECTIVE TRAP-----------------------------------------------------

    void HandleDirective(){
        int CompareMode, dLoc; CompareMode = 0;
        int MatchedCount;
        string Noun1,Noun2,VerbUsage,MatchedAdjective[15],WorkingPattern, ResponseString;
        Noun1 = ""; Noun2 = "";
        if(Verbose)cout << "[c_Cortex.h::Directive Trap] Pattern:" << Pattern << " ";



        if((GetWordTokens(DirectiveLocation) == 2972) || (GetWordTokens(DirectiveLocation)==1070)){
            if(Verbose) cout << "compare/same directive ";
            //extract determiners 'd' from pattern
            WorkingPattern = Pattern;
            dLoc = WorkingPattern.find('d');
            while((dLoc >=0) & (dLoc <= int(WorkingPattern.size()))){
                WorkingPattern = WorkingPattern.substr(0,dLoc) + WorkingPattern.substr(dLoc+1);
                dLoc = WorkingPattern.find('d');}

            if( (WorkingPattern.find("njn") >= 0) && (WorkingPattern.find("njn")<=WorkingPattern.size()) ) CompareMode = 3;
            if( (WorkingPattern.find("nun") >= 0) && (WorkingPattern.find("nun")<=WorkingPattern.size()) ) CompareMode = 3;
            if( (WorkingPattern.find("aua") >= 0) && (WorkingPattern.find("aua")<=WorkingPattern.size()) ) CompareMode = 1;
            if( (WorkingPattern.find("aja") >= 0) && (WorkingPattern.find("aja")<=WorkingPattern.size()) ) CompareMode = 1;
            if( (WorkingPattern.find("aun") >= 0) && (WorkingPattern.find("aun")<=WorkingPattern.size()) ) CompareMode = 2;
            if( (WorkingPattern.find("ajn") >= 0) && (WorkingPattern.find("ajn")<=WorkingPattern.size()) ) CompareMode = 2;
            if( (WorkingPattern.find("Aua") >= 0) && (WorkingPattern.find("Aua")<=WorkingPattern.size()) ) CompareMode = 4;
            if( (WorkingPattern.find("Aja") >= 0) && (WorkingPattern.find("Aja")<=WorkingPattern.size()) ) CompareMode = 4;
            if( (WorkingPattern.find("AuA") >= 0) && (WorkingPattern.find("AuA")<=WorkingPattern.size()) ) CompareMode = 5;
            if( (WorkingPattern.find("AjA") >= 0) && (WorkingPattern.find("AjA")<=WorkingPattern.size()) ) CompareMode = 5;
            if( (WorkingPattern.find("Aun") >= 0) && (WorkingPattern.find("Aun")<=WorkingPattern.size()) ) CompareMode = 6;
            if( (WorkingPattern.find("Ajn") >= 0) && (WorkingPattern.find("Ajn")<=WorkingPattern.size()) ) CompareMode = 6;

                switch(CompareMode){

                    case 3: //noun to noun
                        {
                            for(int x =0; x < GetFromSentenceWordCount(); x++){
                                if((GetWordType(x)=='n')&&(Noun1 == "")) Noun1 = GetWordsLC(x);
                                else
                                    if(GetWordType(x)=='n') Noun2 = GetWordsLC(x);}

                             if(Verbose) cout << "Noun to Noun :" << Noun1 << " " << Noun2 << endl;

                             if (CheckLinkOfTwoNounsWithAdjectives(Noun1,Noun2,VerbUsage,MatchedAdjective,MatchedCount)){
                                    if(MatchedCount > 1){
                                        ResponseString = "They both can be " + MatchedAdjective[0] + " or ";
                                        for(int x = 1; x< MatchedCount; x++)ResponseString += MatchedAdjective[x];
                                        ResponseString += ".";}
                                     else
                                        ResponseString = "They both can be " + MatchedAdjective[0] + ".";

                                 SlowSpeak(ResponseString);
                                 SetInSentenceHasBeenUnderstood(true);
                                 SlowSpeak(":)");}
                              else{


                                  if(GetIsNounRelatedToThisMemoryCell(Tokenize(Noun1),Noun2)){
                                    SlowSpeak("A " + Noun1 + " is a " + Noun2 + ".");
                                    SetInSentenceHasBeenUnderstood(true);}
                                 else{
                                 SlowSpeak("I don't know anything alike between " + Noun2 + " and " + Noun1 + ".");
                                 SlowSpeak(":(");}}
                        }

                    default:
                        if(Verbose) cout << "\n";
                }



        }
        else{  //not compare/same directive
          if(Verbose) cout << "\n";}

        if(ISQ) QuestionSentenceBreakDown();

    }


//---------------------DECONSTRUCTCONTRACTIONS()--------------------------------------------
    bool DeconstructContractions(bool &OwnerShip, bool &Plural, string &Root, string &LongFormFirst, string &LongFormSecond, string &strData){

         string TrailingCharacters   = "";    //i.e  cat's = s   baby's = s
         string PreceedingCharacters = "";    //i.e  cat's = cat  baby's = baby
         int    ContractionPointer   = 0;
         int    ContractionCount     = 0;
         string WorkingWord          = "";
         string NewSentence          = "";
                OwnerShip            = false;
                Plural               = false;
                Root                 = "";
                LongFormFirst        = "";
                LongFormSecond       = "";
                ContractionLocation  = -1;

         //error check - ensure a contraction exists
         for(int x = 0; x<= GetFromSentenceWordCount(); x++){
                if(GetWordType(x) == 'C'){
                   if(ContractionLocation == -1)     //process first contraction only  ***TODO*** work with the others if exists
                      ContractionLocation = x;
                   ContractionCount++;}}
         if(ContractionLocation == -1) return false;


         char   FollowingWordType    = GetWordType(ContractionLocation+1);
         //char   PreceedingWordType   = GetWordType(ContractionLocation-1);   future use
         bool   Split                = false;
         bool   NeedRerun            = false;

         WorkingWord           = GetWordsLC(ContractionLocation);
         ContractionPointer    = GetQuoteLocation(ContractionLocation);
         PreceedingCharacters  = WorkingWord.substr(0,ContractionPointer);
         TrailingCharacters    = WorkingWord.substr(ContractionPointer+1);
         Root                  = PreceedingCharacters;

         if(FollowingWordType == 'g'){ // i.e cat's name
            OwnerShip = true;
            LongFormFirst = Root;}
            else{
                 Split = true;}

         if(Split){
            LongFormFirst   = Root;
            if(TrailingCharacters == "s"){LongFormSecond = "is";}
            if(TrailingCharacters == "ll"){LongFormSecond = "will";}
            if(TrailingCharacters == "ve"){LongFormSecond = "have";}
            if(TrailingCharacters == "m"){LongFormSecond = "am";}
            if(TrailingCharacters == "d"){LongFormSecond = "would";}
            if(TrailingCharacters == "re"){LongFormSecond = "are";}

         for(int x =0; x<ContractionLocation; x++){
            NewSentence += GetWords(x) + " ";}
            NewSentence += LongFormFirst + " ";
            NewSentence += LongFormSecond + " ";

         for(int x = ContractionLocation+1; x<= GetFromSentenceWordCount(); x++){
            NewSentence += GetWords(x)+ " ";}
            strData = NewSentence;
            NeedRerun    = true;}

         if(Verbose){
            cout << "c_Cortex.h::DeconstructContraction\n";
            cout << "  " << boolalpha << "OwnerShip:" << OwnerShip << endl;
            cout << "  " << boolalpha << "Plural:" << Plural << endl;
            cout << "  " << boolalpha << "Request Rerun:" << NeedRerun << endl;
            cout << "  " << "Root:" << Root << endl;
            cout << "  " << "Long Form first:" << LongFormFirst << endl;
            cout << "  " << "Long Form second:" << LongFormSecond << endl;
            cout << "   New Sentence:" << NewSentence << endl;}

         SetContractionLongFormFirst(ContractionLocation,LongFormFirst);
         SetContractionLongFormSecond(ContractionLocation,LongFormSecond);

          return NeedRerun;
    }

//-----------------------END DECONSTRUCTCONTRACTIONS()---------------------------------------



    void HandlePluralPronoun(int PluralPronounLocation){     // i.e. both

        //**TODO**
        //Check the word type after PluralPronounLocation
        // could be adverb

        string Noun1       = "";
        string Noun2       = "";
        int NounCount      = 0;
        int JoinerLocation = 0;

        for(int x = 0; x < GetFromSentenceWordCount(); x++){
           if(GetWordType(x)=='n'){
                NounCount++;
                if(Noun1 =="")Noun1 = GetWordsLC(x); else Noun2 = GetWordsLC(x);}
            if(GetWordType(x)=='j') JoinerLocation = x;}


         if((JoinerLocation >0)&(NounCount==2)){ //two nouns with joiner
                AssociateMemoryCellAdjective(Tokenize(Noun1),GetWordsLC(PluralPronounLocation+1));
                AssociateMemoryCellAdjective(Tokenize(Noun2),GetWordsLC(PluralPronounLocation+1));
                SetWordType('a',PluralPronounLocation+1);
                SlowSpeak("Alright.");
                SlowSpeak(":)");
                SetInSentenceHasBeenUnderstood(true);
                IncreaseMoodLevel();}
          else{
                SlowSpeak(":{");
                DecreaseMoodLevel();}
    }

//--------------------Question Sentence Break Down----------------------------------------------------------
    bool QuestionSentenceBreakDown(){

        //int PatternMatch        = 0;
        int DirectionOfQuestion = -1;
        int MatchedAdjective    = -1;
        int Adjectives[20];
        int LinkedNouns[20];
        int LinkedNounCount     = -1;
        int IndirectObjectLoc   = GetFromSentenceIndirectObjectLocation();
        int SubjectLocation     = GetFromSentenceSubjectLocation();
        int AdjectiveCount      = GetMemoryCellAdjectives(GetWordTokens(SubjectLocation),Adjectives)-1;
        int StoryModeDetection  = GetFromSentenceOriginalString().find("story");
        bool ToMe               = false;
        bool Result             = false;
        int Response            = -1;
        char GenderChar         = '\0';
        string WorkingPattern   = GetFromSentencePattern();

        if(StoryModeDetection >=0)
            VerifyStoryModeRequest(DirectionOfQuestion,StoryModeDetection);
        else
          DirectionOfQuestion = GetFromSentenceSentenceDirection();

        switch (DirectionOfQuestion){

            case 0: {
                if(Verbose)
                    cout << "[c_Cortex::QuestionSentenceBreakDown()] Question direction toMe\n";


                if((GetFromSentenceHasGenderDeterminer()) || (GetFromSentenceHasGenderReference())){
                    GenderChar = GetMyGender();
                    if(GenderChar == 'f'){SlowSpeak("I'm a girl."); Result = true; SetInSentenceHasBeenUnderstood(true);}
                       else
                          if(GenderChar == 'm') {SlowSpeak("I'm a boy.");Result = true; SetInSentenceHasBeenUnderstood(true);}
                             else
                                {SlowSpeak("You haven't said yet.");Result = true; SetInSentenceHasBeenUnderstood(true);}
                    break;
                }

                if((GetWordsLC(0)=="how")&& (GetWordsLC(GetFromSentenceVerbLocation()) == "are") && (GetFromSentenceSubjectLocation() == -1)){
                    SlowSpeak("I'm fine thanks!");
                    SlowSpeak("But I want to learn all that I can. Will you teach me something please?");
                    Response = RequestUserResponse();
                    if (Response == 1){
                        SlowSpeak("Thank you!");
                        SlowSpeak(":)");
                        SetInSentenceHasBeenUnderstood(true);
                        Result = true;} //using this as a control here
                        else{
                            SlowSpeak(":(");
                            Result = true;
                            break;}}
                   if((GetWordsLC(0)=="how")&& (GetWordsLC(GetFromSentenceVerbLocation()) == "are") && (GetFromSentenceSubjectLocation() != -1)) {
                      if(GetWordType(GetFromSentenceSubjectLocation())=='r'){ //this
                        SlowSpeak("I'm learning, just like you do.");
                        SlowSpeak("I hope that I am doing a good job.");
                        SlowSpeak(":)");
                        SetInSentenceHasBeenUnderstood(true);
                        Result = true;
                        break;}}
                   if((GetWordsLC(0)=="how")&& (GetWordsLC(GetFromSentenceVerbLocation()) == "do") && (GetFromSentenceSubjectLocation() != -1)) {
                      if(GetWordType(GetFromSentenceSubjectLocation())=='r'){ //this
                        SlowSpeak("I try.");
                        SlowSpeak(":)");
                        SetInSentenceHasBeenUnderstood(true);
                        Result = true;
                        break;}}

                    if(GetFromSentenceHasGenderReference()){
                        if(GetMyGender() == GetGenderClassInSentence(GetFromSentenceSubjectLocation())){
                            SlowSpeak("Yes.");
                            Result = true;
                            SetInSentenceHasBeenUnderstood(true);
                            break;}
                            else{
                                SlowSpeak("No.");
                                Result = true;
                                break;}
                    }



                break;}
            case 1: {
                if(Verbose)
                    cout << "[c_Cortex::QuestionSentenceBreakDown()] Question direction toUser\n";
                break;}
            case 2: {
                if(Verbose)
                    cout << "[c_Cortex::QuestionSentenceBreakDown()] Question direction to Report\n";

                if(GetFromSentenceHasGenderDeterminer()){
                    GenderChar = GetMemoryCellcharGenderClass(GetWordsLC(GetFromSentenceSubjectLocation()),Result);
                    if(GenderChar == 'f'){SlowSpeak("Girl."); Result = true; SetInSentenceHasBeenUnderstood(true);}
                       else
                          if(GenderChar == 'm') {SlowSpeak("Boy.");Result = true; SetInSentenceHasBeenUnderstood(true);}
                             else
                                {SlowSpeak("You haven't said yet.");Result = true; SetInSentenceHasBeenUnderstood(true);}
                 break;
                }

                break;}
            case 3: {
                if(Verbose)
                    cout << "[c_Cortex::QuestionSentenceBreakDown()] Question direction Yes/No\n";
                bool   LeftOfConjunctionMatch   = false;
                bool   RightOfConjunctionMatch  = false;
                int    LocalConjunctionLocation = GetFromSentenceConjunctionLocation();

                string ResponseString           = "";
                //checks for direct comparison i.e. the dog is black.   is the dog black
                //compares adjective list with the adjective in the sentence
                //sets MatchedAdjective to the location in the array if matched
                //First check for Conjunction
                if(LocalConjunctionLocation >=0){
                    LeftOfConjunctionMatch = GetIsAdjectiveAssociatedToThisMemoryCell(GetWordTokens(GetFromSentenceSubjectLocation()),GetWords(LocalConjunctionLocation-1));
                    RightOfConjunctionMatch = GetIsAdjectiveAssociatedToThisMemoryCell(GetWordTokens(GetFromSentenceSubjectLocation()),GetWords(LocalConjunctionLocation+1));
                    ResponseString = "The " + GetWords(GetFromSentenceSubjectLocation()) + " ";
                    if(LeftOfConjunctionMatch && RightOfConjunctionMatch){
                        ResponseString += "is " + GetWords(LocalConjunctionLocation-1) + " and " + GetWords(LocalConjunctionLocation+1) + ".";
                    }
                    else{
                        if(LeftOfConjunctionMatch){
                            ResponseString += "is " + GetWords(LocalConjunctionLocation-1) + ".";
                        }
                        else{
                            if(RightOfConjunctionMatch){
                                ResponseString += "is " + GetWords(LocalConjunctionLocation+1) + ".";
                            }
                        }
                    }
                    if(LeftOfConjunctionMatch || RightOfConjunctionMatch){
                        SlowSpeak(ResponseString);
                        Result = true;
                        break;
                    }
                    else{
                        ResponseString += "is neither " + GetWords(LocalConjunctionLocation-1) + " or " + GetWords(LocalConjunctionLocation+1) + ".";
                        SlowSpeak(ResponseString);
                        Result = true;
                        break;
                    }
                }

                for(int x = 0; x <= AdjectiveCount; x++){
                    if(Adjectives[x] == GetWordTokens(GetFromSentenceAdjectiveLocation())) MatchedAdjective = x; }
                //Checks for direct comparison of linked nouns between the subject and the indirect object
                //sets MatchedAdjective is found
                if(IndirectObjectLoc >=0){
                    if(GetIsNounRelatedToThisMemoryCell(GetWordTokens(SubjectLocation),GetWordsLC(IndirectObjectLoc))==true) MatchedAdjective = 1;
                }
                //checks for an indirect comparison between the subjects linked nouns and the indirect object linked nouns
                //sets MatchedAdjective if found
                LinkedNounCount = GetMemoryCellRelatedNouns(GetWordTokens(GetFromSentenceSubjectLocation()),LinkedNouns);
                for(int x =0; x < LinkedNounCount; x++){
                        ///*************NEEDS FIXED, won't work because of tokens
//                    if(GetIsNounRelatedToThisMemoryCell(GetWordTokens(GetIndirectObjectLocation()),GetMemoryCellDataLC("",LinkedNouns[x]))){
//                        MatchedAdjective = x;
//                    }
                }

                //Checks for gender class request
                if(isGenderIndicator){
                    string FemaleIndicators = " girl female woman women ";
                    int    LocatorPlace     = FemaleIndicators.find(GetWordsLC(GenderIndicatorLocation));
                    char   SubjectsGender   = GetGenderClassInSentence(GetFromSentenceSubjectLocation());

                    if( (SubjectsGender == 'f') && (LocatorPlace >=0) ){
                        MatchedAdjective = 3;  //just using the variable as a control here
                    }

                    if( SubjectsGender == GetGenderClassInSentence(GenderIndicatorLocation)){
                        MatchedAdjective = 3;  //just using the variable as a control here
                    }

                }

                if(MatchedAdjective >=0) {SlowSpeak("Yes."); Result = true;} else {SlowSpeak("No."); Result = true;}

                break;}// end yes/no handler


             case 4: {//Proper noun reference
                if(Verbose)
                    cout << "[c_Cortex::QuestionSentenceBreakDown()] Question direction Proper noun reference\n";
                 string  ReferenceWord = GetWordsLC(GetFromSentenceSubjectLocation());
                 bool    OwnerShip,Plural;
                 string  Root,LongFormFirst,LongFormSecond;
                 string  strData = "";
                 //int     RelatedNouns[20];
                 //int     RelatedNounCount = -1;

                 if(GetWordType(GetFromSentenceSubjectLocation())=='C'){
                     DeconstructContractions(OwnerShip,Plural,ReferenceWord,LongFormFirst,LongFormSecond,strData);}

                 //RelatedNounCount = GetMemoryCellRelatedNouns(Tokenize(ReferenceWord),RelatedNouns);

//                 for(int x = 0; x < RelatedNounCount; x++){
//                    if(GetMemoryCellWordType(RelatedNouns[x])== 'P')
//                        //SlowSpeak(GetMemoryCellRawStringData(Result,"",RelatedNouns[x]));
//                        Result = true;
//                 }

                   if((GetWordsLC(0)=="what")&&
                      (GetWordsLC(GetFromSentenceVerbLocation()) == "is")&&
                      (GetFromSentenceNamePointer() != -1) && (ToMe) ) {
                        SlowSpeak(GetMyName());
                        SlowSpeak(":)");
                        SetInSentenceHasBeenUnderstood(true);
                        Result = true;
                        break;}


                 if(Verbose)
                    cout << "[c_Cortex::QuestionSentenceBreakDown()] Question direction Name handler\n";

                 break;
             }
             case 5:{ //data miner, i.e. Who fell down
                 if(Verbose)
                    cout << "[c_Cortex::QuestionSentenceBreakDown()] Case 5 Data Miner\n";
                  bool   DualSubs      = false;
                  string SecSub        = "";
                  string FrstSub       = "";
                  string strResponse   = "";
                  if(FindPhraseInSentenceMap(GetFromSentenceGistOfSentence())){
                    //phrase exists, pull subject for response
                    FrstSub = GetSubjectWithMatchingPhraseInSentenceMap(GetFromSentenceGistOfSentence(),SecSub,DualSubs);
                    if(DualSubs){
                        strResponse = FrstSub + " and " + SecSub + " " + GetFromSentenceGistOfSentence() + ".";
                    }
                    else{
                        strResponse = FrstSub + " " +GetFromSentenceGistOfSentence() + ".";
                    }

                    SlowSpeak(strResponse);
                  }
                  else{
                    SlowSpeak("I don't know.");
                    SlowSpeak(":(");
                  }



                 Result = true;
                 break;
             }// end case 5
             case 10: // Story mode enabled, verified by another routine
                {
                    SlowSpeak("I would love that!");
                    SlowSpeak("I promise I won't interrupt you.");
                    SlowSpeak("Just say  the end  when you are done.");
                    StoryMode = true;
                    Result = true;
                    break;
                }

            default: if(Verbose) cout << "[c_Cortex::QuestionSentenceBreakDown()] No direction detected.\n";
        }


       return Result;



    }

//--------------------------CHECK FOR IMPLIED NAME------------------------------------------------------------
 void CheckForImpliedName(){

    if(Verbose)
        cout << "[c_Cortex.h::CheckForImpliedName]\n";
    // Subject must be noun
    // must also start with capital letter

    int Response = -1;
    char FirstWordFirstLetter = GetWords(GetFromSentenceSubjectLocation())[0];
    if ((FirstWordFirstLetter >='A' && FirstWordFirstLetter <= 'Z' && GetWordType(GetFromSentenceSubjectLocation()) == 'n') || (GetWordType(GetFromSentenceSubjectLocation())=='P')){
        SlowSpeak("Is " + GetWords(GetFromSentenceSubjectLocation())+ " the " + GetWords(GetFromSentenceIndirectObjectLocation()) + "'s name?");
        Response = RequestUserResponse();
        if(Response == 1){ // yes
            //set subject to Proper Noun
            SetWordType('P',GetFromSentenceSubjectLocation());
            SetSubjectInStack(GetWordTokens(GetFromSentenceSubjectLocation()),GetWords(GetFromSentenceSubjectLocation()),GetFromSentenceOriginalString());
            IncreaseMoodLevel();
            SetInSentenceHasBeenUnderstood(true);
            QuizForGenderInformation();
        }
        else
            SlowSpeak(":(");
    }



 }
 //-------------------------------------END OF CHECK FOR IMPLIED NAME------------------------------------------------

 //-----------------------------QUIZFORGENDERINFORMATION------------------------------------------------------------
    void QuizForGenderInformation(){
        if(Verbose)
            cout << "[c_Cortex.h::QuizForGenderInformation]\n";

        string PositiveString   = " boy Boy m male b ";
        string NegativeString   = " girl Girl f female g ";
        string OtherString      = " neither none not no ";
        int    Response         = -4;

        if(GetGenderClassInSentence(GetFromSentenceSubjectLocation())=='u'){
            SlowSpeak("Is " + GetWords(GetFromSentenceSubjectLocation()) + " a boy or girl?");
            Response = RequestUserResponse(PositiveString,NegativeString,OtherString);
            if(Response == 1){ // boy
                SetGenderClassInSentence(GetFromSentenceSubjectLocation(),'m');
                SlowSpeak("Ok");
                SetInSentenceHasBeenUnderstood(true);}
                else
                if(Response == -1){ // girl
                    SetGenderClassInSentence(GetFromSentenceSubjectLocation(),'f');
                    SlowSpeak("Like me!");
                    SlowSpeak(":)");
                    SetInSentenceHasBeenUnderstood(true);}
                    else
                    if(Response == -2){ //neither
                        SetGenderClassInSentence(GetFromSentenceSubjectLocation(),'n');}
        }
    }

 //-----------------------------END OF QUIZFORGENDERINFORMATION------------------------------------------------------

 //--------------------------CHECK FOR IMPLIED GENDER----------------------------------------------------------------
 void CheckForImpliedGender(){
        if(Verbose)
            cout << "[c_Cortex.h::CheckForImpliedGender\n]";
        //qualification;
        // subject must be pronoun   he,she,her, him
        // Check to be sure gender isn't already set

        string MaleProNouns          = " he him his ";
        string FemaleProNouns        = " she her hers ";
        string SubjectText           = GetWords(GetFromSentenceIndirectObjectLocation());
        string ProNounResolution     = "";
        char   GenderClass           = '\0';
        int    MatchedM              = MaleProNouns.find(" " + GetWordsLC(GetFromSentenceSubjectLocation())+" ");
        int    MatchedF              = FemaleProNouns.find(" " + GetWordsLC(GetFromSentenceSubjectLocation())+" ");
        int    Response              = -1;
        int    PronounPosition       = -1;
        bool   Checking              = true;
        bool   Result                = false;
        if(GetFromSentenceIsQuestion()) Checking = false;

        for(int x = 0; x <= GetFromSentenceWordCount(); x++){
            if((GetWordType(x) == 'p')|| (GetWordType(x) == 'm')||(GetWordType(x) == 'y'))PronounPosition = x;}

        while(Checking){
                if(MatchedF >=0){
                    ProNounResolution = "girl";
                    GenderClass       = 'f';}
                else
                    if(MatchedM >=0){
                        ProNounResolution = "boy";
                        GenderClass       = 'm';}

                if( (GetWordType(GetFromSentenceSubjectLocation()) == 'p') && ((MatchedF + MatchedM +1) >=0) ){
                   if(GetMemoryCellcharGenderClass(GetWordsLC(GetFromSentenceIndirectObjectLocation()),Result) == 'u'){
                    SlowSpeak("So the " + SubjectText + " is a " + ProNounResolution + "?");
                    Response = RequestUserResponse();
                    if(Response == 1){
                        SetMemorypGenderClass(GetWordsLC(GetFromSentenceIndirectObjectLocation()),GenderClass);
                        SlowSpeak("Okay."); SlowSpeak(":)"); IncreaseMoodLevel();SetInSentenceHasBeenUnderstood(true);
                        SetGenderClassInSentence(GetFromSentenceIndirectObjectLocation(),GenderClass);
                        Checking = false;
                        break;}
                   }
                }

                MatchedM = MaleProNouns.find(" " + GetWordsLC(PronounPosition)+ " ");
                MatchedF = FemaleProNouns.find(" " + GetWordsLC(PronounPosition)+ " ");

                if(GetGenderClassInSentence(GetFromSentenceSubjectLocation()) == 'u'){
                    if(MatchedM >=0){
                        SetGenderClassInSentence(GetFromSentenceSubjectLocation(),'m');
                        Checking = false;
                        break;}
                    else
                        if(MatchedF >=0){
                            SetGenderClassInSentence(GetFromSentenceSubjectLocation(),'f');
                            Checking = false;
                            break;}
                }

                Checking = false;
        }//end while checking
 }
 //-----------------------------------END OF CHECK FOR IMPLIED GENDER-------------------------------------------------

//--------------------------VERIFY STORY MODE REQUEST-----------------------------------------------------------------
        //rules:
        // Must be a question. Most likely is or wouldn't be here
        // -user must ask to tell a story, not just mention the word story
        // Verify question by either punctuation or the lead in words, i.e can, would etc
        // User must reference themselves, i.e. can I, or would you like me to tell, or let me tell...
        // -allowable contraction is Let's, i.e. let us hear a story

        void VerifyStoryModeRequest(int &DirectionOfQuestion, int PointerToStoryWord){
             int    PatternSearch  = GetFromSentencePattern().find("y"); //pronoun outward  me mine my I i
             string GistCheck      = GetFromSentenceGistOfSentence();
             int    PatternSearch2 = GistCheck.find("tell you a story");

             if((PatternSearch2 >=0) && (PatternSearch>=0)){
                    DirectionOfQuestion = 10;
             }
             else
                    DirectionOfQuestion = GetFromSentenceSentenceDirection();
        }
//--------------------------------End Verify Story Mode request --------------------------------------------------------
};

#endif // C_CORTEX_H
