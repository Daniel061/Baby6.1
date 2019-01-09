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
            int AdjectiveLocation;
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
            int AdverbLocation;
            int DirectiveLocation;
            int JoinerLocation;
            int DirectObjectLocation;
            int IndirectObjectLocation;
            int PluralPossessiveLocation;
            int PluralPronounLocation;
            int ProperNounLocation;
            float UnderstandingRatio;
            bool ISQ;


    public:
        void DecipherCurrentSentence(){


            if(Verbose){cout << "[c_Cortex.h::DeciperCurrentSentence]" << endl;}
            SubjectLoc = GetSubjectLocation();
            AdjectiveLocation  = -1; FirstUnknown = -1; ContractionLocation = -1;
            DeterminerLocation = -1; ProNounOtherLocation = -1; ISQ = false;
            Pattern = ""; NounLocation = -1; Control = -1; UnderstandingLevel = 0;
            UnderstandingRatio = 0.0; UnknownCount = 0; QuestionLocation = 0;
            AdverbLocation = -1; DirectiveLocation = -1; JoinerLocation = -1;
            DirectObjectLocation = -1; IndirectObjectLocation = -1; PluralPossessiveLocation = -1;
            ProNounInwardLocation = -1; ProNounOutwardLocation = -1; AssociativeWordLocation = -1;
            PluralPronounLocation = -1; ProperNounLocation = -1;

            for(int x =0; x < GetWordCount(); x++){                                                                  // Build pattern string i.e. duvu  4 word sentence
                    Pattern += GetWordType(x);
                    tmpWordType = GetWordType(x);
                    if (tmpWordType == 't') {UnderstandingLevel++;}
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
                    if (tmpWordType == 'D') {DirectObjectLocation = x; UnderstandingLevel++;}
                    if (tmpWordType == 'I') {IndirectObjectLocation = x; UnderstandingLevel++;}
                    if (tmpWordType == 'N') {PluralPronounLocation = x; UnderstandingLevel++;}
                    if (tmpWordType == 'u') {
                            UnknownCount++; UnKnownLocation = x;
                            if(FirstUnknown == -1) FirstUnknown = x;
                            }
            }
            SetPattern(Pattern);
            ISQ = GetIsQuestion();
            if(UnderstandingLevel > 0)
                UnderstandingRatio = float(UnderstandingLevel) / float(GetWordCount());

            ///Set the understanding degree weighted with the ratio
            if(UnderstandingRatio == 1) UnderstandingDegree = 100;
             else
                if(UnderstandingRatio >= .75) UnderstandingDegree = 75;
             else
                if(UnderstandingRatio >= .50) UnderstandingDegree = 50;
             else
                if(UnderstandingRatio >= .25) UnderstandingDegree = 25;
             else
                if(UnderstandingRatio >= .10) UnderstandingDegree = 10;
             else
                UnderstandingDegree = 0;
            if(Verbose)
             cout << "Pattern: " + Pattern + " Understanding Level:" << UnderstandingLevel << " Ratio:" << UnderstandingRatio<< " Is Question:" << ISQ << " Degree:" << UnderstandingDegree << " Unknown Count:" << UnknownCount << "\n";

            if(ISQ == true)UnderstandingDegree = 1;               //question trap
            if(DirectiveLocation >=0)UnderstandingDegree = 2;     //directive trap
            if(PluralPronounLocation >=0)UnderstandingDegree = 3; //plural pronoun trap
            switch (UnderstandingDegree)
            {
               case 0:{  ///All new words, lots of work to do
                   if (Verbose)
                    cout << "Case 0" << endl;


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
                   QuestionSentenceBreakDown();
                   HandleQuestion();
                   break;}

               case 2:{ //directive trap
                    HandleDirective();
                    break;}

               case 3:{ //plural pronoun trap
                    HandlePluralPronoun(PluralPronounLocation);
                    break;}

                case 10:{  ///Only 1 known but could have a ratio of 100%
                   if (Verbose)
                    cout << "Case 10" << endl;

                 SlowSpeak("I'm going to have to work on this.");
                 break;}

                case 25:{  ///Some understanding but depends on ratio
                   if (Verbose)
                    cout << "Case 25" << endl;

                 SlowSpeak("I don't know "  + GetWords(FirstUnknown)+"?");
                 break;}

                case 50:{  ///stronger understanding but also depends on ratio
                   if (Verbose)
                    cout << "Case 50" << endl;
                 WorkWithHalfLevel(Pattern,DeterminerLocation);
                 break;}

                case 75:{  ///Much stronger
                   if (Verbose)
                    cout << "Case 75" << endl;
                 Handle75LevelUnderstanding();
                 break;}

                case 100:{  ///very strong
                   if (Verbose)
                    cout << "Case 100" << endl;
                    string tmpSubject;
                 tmpSubject = GetWords(SubjectLoc);
                 SetSubject(GetWordTokens(SubjectLoc),tmpSubject);
                 if(GetWordType(GetSubjectLocation())=='p'){
                    CheckForImpliedGender();}
                 SlowSpeak("Okay.");
                 IncreaseMoodLevel();
                 SlowSpeak(":)");
                 break;}

            }

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

    }


    return -1;
}
//---------------------------------------end greetings-------------------------------------------------------------------------------

//-------------------------------------PROCESS MIDLEVEL UNDERSTANDING----------------------------------------------------------------

int WorkWithHalfLevel(string Pattern, int Determiner){
    if(Verbose){cout << "[c_Cortex.h::WorkWithHalfLevel]" << endl;}
       int Response;
       string tmpAdjective;
       int tmpAdjectiveLoc;
       if(Verbose)
            cout << "Noun Loc:" << NounLocation << "Unknown Loc:" << UnKnownLocation << "Pattern:" << Pattern << endl;
         SlowSpeak("  Are we talking about a " + GetWords(Determiner + 1) + "?");
         Response = RequestUserResponse();
         if(Response == 1){  //yes answer
            //set subject to this
            //set wordtype to noun if it isn't
            //see if this is a known word
            IncreaseMoodLevel();
            SetWordType('n',Determiner+1);
            SetSubject(Tokenize(GetWords(Determiner+1)),GetWords(Determiner+1));
            for(int x =0; x < GetWordCount(); x++){
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
                    SetWordType('a',tmpAdjectiveLoc);
                    SetWordType('n',Determiner+1);
                    RebuildPattern();

            }
            else{
                SlowSpeak(":(");
                DecreaseMoodLevel();

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
                    //set subject
                }
                else{
                    SlowSpeak("I'm lost.");
                    SlowSpeak("I need to learn more before I understand this.");
                    SlowSpeak(":(");
                    DecreaseMoodLevel();
                }
            }
            else{
                SlowSpeak("Ok");
                SlowSpeak("You'll have to tell me more about a " + GetWords(Determiner+2)+ ".");
                SetWordType('n',Determiner+2);
                SetSubject(Tokenize(GetWords(Determiner+2)),GetWords(Determiner+2));
                IncreaseMoodLevel();
                //set subject
            }
         }

      return 0;

}//end work with half level
//---------------------------------------------------------------------------------------------------------------
int HandleQuestion(){
    //***TODO**
    //check for multi match and handle

    if(Verbose){cout << "[c_Cortex.h::HandleQuestion]" << endl;}
    int Control;    Control = -1;
    int MatchedCount;
    string VerbUsed, MatchedAdjective[15];
    string AnswerString;
    bool Matched = false;
    if(Verbose)
        cout << "qLoc:" << QuestionLocation << " Pattern:" << Pattern << " SubjectLoc:" << GetSubjectLocation() << endl;

   // check for correct form
   //actually need to compare indirect object to subject
    if(GetIndirectObjectLocation() != -1)
    Matched = CheckLinkOfTwoNounsWithAdjectives(RightLobeMemory[GetWordTokens(GetIndirectObjectLocation())].GetpCellDataString(),
                                                RightLobeMemory[GetWordTokens(GetSubjectLocation())].GetpCellDataString(),
                                                VerbUsed,MatchedAdjective, MatchedCount);
    if (Matched){
            if(MatchedCount > 1){
                AnswerString = "The " +  GetWordsLC(GetSubjectLocation()) + " of ";
                if(!(GetWordType(GetIndirectObjectLocation())== 'P') || (GetWordType(GetIndirectObjectLocation())== 'p')) AnswerString += "the ";
                AnswerString +=  GetWords(GetIndirectObjectLocation()) + " can be ";
                for(int x = 0; x < MatchedCount; x++){
                        AnswerString = AnswerString + MatchedAdjective[x];
                        if(!(x+1==MatchedCount)) AnswerString += " or ";}
                AnswerString += ".";
                SlowSpeak(AnswerString);
            }
            else{
               AnswerString = "The " +  GetWordsLC(GetSubjectLocation()) + " of ";
               if(!(GetWordType(GetIndirectObjectLocation())== 'P') || (GetWordType(GetIndirectObjectLocation())== 'p')) AnswerString += "the ";
               AnswerString +=  GetWords(GetIndirectObjectLocation())+ " is " + MatchedAdjective[0] + ".";
               SlowSpeak(AnswerString);
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
void Handle75LevelUnderstanding(){
    bool Testing; Testing = true;
    int localVerbLocation = -1;
    int localUnknownLocation = -1;

    if(Verbose){
        cout << "c_Cortex.h::Handle75LevelUnderstanding\n";
        cout << "  Pattern:" << Pattern << endl;
        cout << "  Subject Location:" << GetSubjectLocation() << endl;
        cout << "  Noun Location:" << NounLocation << endl;
        cout << "  Adjective Location:" << AdjectiveLocation << endl;
        cout << "  Verb Location:" << VerbLocation << endl;}


   while(Testing && (NounLocation >=0)){   //no noun! How to handle this Kenzie??  she says if pronoun use it as noun and subject

    //----------Missing Noun Test------
    if((NounLocation == -1) && (VerbLocation >=0) && (DeterminerLocation >=0) && (AdjectiveLocation >=0)){ //no noun but has verb, determiner and adjective
        SlowSpeak("So " + GetWords(DeterminerLocation+1)+ " can be " + GetWords(AdjectiveLocation) + "?");
        UserResponse = RequestUserResponse();
        if(UserResponse == 1){
            SetWordType('n',DeterminerLocation+1);    //set the noun
            SetSubjectLocation(DeterminerLocation+1); //be sure subject location is newly found noun
            SlowSpeak(":)"); IncreaseMoodLevel();
            Testing = false;
            break;}
    }
    else{
        if( (NounLocation == -1) && (VerbLocation >=0) && (DeterminerLocation >=0) ){    // no noun but has verb and determiner
            SlowSpeak(" Are we talking about a" + GetWords(DeterminerLocation+1) + "?");
            UserResponse = RequestUserResponse();
            if(UserResponse == 1){
                SetWordType('n',DeterminerLocation+1);
                SetSubjectLocation(DeterminerLocation+1);
                SlowSpeak(":)");
                IncreaseMoodLevel();
                Testing = false;
                break;}
            }
    }


    //------End Missing noun test------


    // --TEST FOR MISSING VERB--------------
    for(int x= 0; x < GetWordCount(); x++){
        if(GetWordType(x)=='v') localVerbLocation = x;
        if(GetWordType(x)=='u') localUnknownLocation =x;}

    if(localVerbLocation == -1 ){
        if(UnKnownLocation != -1){
            SetWordType('v',UnKnownLocation);
            Testing = false;
            SlowSpeak("Okay.");
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

    tmpLocation = Pattern.find("nvdu") + Pattern.find("uvdn") + 1;  //if one .find returns -1 it is removed with the +1, if both return -1, the +1 results in -1
    if (tmpLocation>=0){
        SlowSpeak("Okay. Tell me more about " + GetWordsLC(tmpLocation+2) + " " + GetWordsLC(tmpLocation+3) + ".");
        SetWordType('n',tmpLocation+3);
        SetWordType('n',tmpLocation);
        L_AssociateNounToNoun(GetWordsLC(tmpLocation),GetWordsLC(tmpLocation+3));       //associate first noun to second noun
        L_AssociateNounToNoun(GetWordsLC(tmpLocation+3),GetWordsLC(tmpLocation));       //associate second noun to first noun
        FindSubject();                                                                  //Update subject
        SetSubject(GetWordTokens(GetSubjectLocation()),GetWords(GetSubjectLocation())); //update subject stack
        CheckForImpliedName();
        Testing = false;
        break;
    }
    //---------End Noun to noun test----------



    //----------Adjective Test---------

    SlowSpeak( "A " + GetWords(UnKnownLocation) + " " + GetWords(NounLocation) + "?");
    UserResponse = RequestUserResponse();
    if(UserResponse == 1){
        SetWordType('a',UnKnownLocation);  //set word type to adjective
        SlowSpeak(":)"); IncreaseMoodLevel();
        Testing = false;
        break;}
        else{
            SlowSpeak(":("); DecreaseMoodLevel();
            Testing = false;
            break;
        }
    //---end Adjective Testing ----------


    //-- DNVUA -- Test for u = Adverb -----
    // the dog is very fast.
    SlowSpeak("A " + GetWords(UnKnownLocation) + " " + GetWords(AdjectiveLocation) + " " + GetWords(GetSubjectLocation()) + "?");
    UserResponse = RequestUserResponse();


    Testing = false;
    break;
    //-- END TESTING FOR ADVERB ------------





   }//---end testing control loop
}

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
            while((dLoc >=0) & (dLoc <= WorkingPattern.size())){
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
                            for(int x =0; x < GetWordCount(); x++){
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
                                 SlowSpeak(":)");}
                              else{

                                 if(L_CheckForRelatedNoun(Noun1,Noun2)){
                                    SlowSpeak("A " + Noun1 + " is a " + Noun2 + ".");}
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



    void DeconstructContractions(){
    }


    void HandlePluralPronoun(int PluralPronounLocation){     // i.e. both

        //**TODO**
        //Check the word type after PluralPronounLocation
        // could be adverb

        string Noun1       = "";
        string Noun2       = "";
        int NounCount      = 0;
        int JoinerLocation = 0;

        for(int x = 0; x < GetWordCount(); x++){
           if(GetWordType(x)=='n'){
                NounCount++;
                if(Noun1 =="")Noun1 = GetWordsLC(x); else Noun2 = GetWordsLC(x);}
            if(GetWordType(x)=='j') JoinerLocation = x;}


         if((JoinerLocation >0)&(NounCount==2)){ //two nouns with joiner
                RightLobeMemory[Tokenize(Noun1)].AccociateAdjective(GetWordTokens(PluralPronounLocation+1));
                RightLobeMemory[Tokenize(Noun2)].AccociateAdjective(GetWordTokens(PluralPronounLocation+1));
                SetWordType('a',PluralPronounLocation+1);
                SlowSpeak("Alright.");
                SlowSpeak(":)");
                IncreaseMoodLevel();}
          else{
                SlowSpeak(":{");
                DecreaseMoodLevel();}
    }

//--------------------Question Sentence Break Down----------------------------------------------------------
    void QuestionSentenceBreakDown(){
        int QuestionMode = -1;
        int PatternMatch = 0;
        int DirectionOfQuestion = 4;
        string WorkingPattern = GetPattern();

        PatternMatch = WorkingPattern.find("vmv");      //i.e. do you know
        if (PatternMatch >=0){
            DirectionOfQuestion = 0;}
        PatternMatch = WorkingPattern.find("qdnv") + WorkingPattern.find("qvdn") + 1;
        if (PatternMatch >= 0){
            DirectionOfQuestion = 2;}

        switch (DirectionOfQuestion){

            case 0: {
                if(Verbose)
                    cout << "[c_Cortex::QuestionSentenceBreakDown()] Question direction toMe\n";
                break;}
            case 1: {
                if(Verbose)
                    cout << "[c_Cortex::QuestionSentenceBreakDown()] Question direction toUser\n";
                break;}
            case 2: {
                if(Verbose)
                    cout << "[c_Cortex::QuestionSentenceBreakDown()] Question direction to Report\n";
                break;}
            case 3: {
                if(Verbose)
                    cout << "[c_Cortex::QuestionSentenceBreakDown()] Question direction Yes/No\n";
                break;}

            default: if(Verbose) cout << "No direction detected.\n";
        }






    }

//--------------------------CHECK FOR IMPLIED NAME------------------------------------------------------------
 void CheckForImpliedName(){


    // Subject must be noun
    // must also start with capital letter

    int Response = -1;
    char FirstWordFirstLetter = GetWords(GetSubjectLocation())[0];
    if (FirstWordFirstLetter >='A' && FirstWordFirstLetter <= 'Z' && GetWordType(GetSubjectLocation()) == 'n'){
        SlowSpeak("Is " + GetWords(GetSubjectLocation())+ " the " + GetWords(GetIndirectObjectLocation()) + "'s name?");
        Response = RequestUserResponse();
        if(Response == 1){ // yes
            //set subject to Proper Noun
            SetWordType('P',GetSubjectLocation());
            SlowSpeak(":)");
            SetSubject(GetWordTokens(GetSubjectLocation()),GetWords(GetSubjectLocation()));
            IncreaseMoodLevel();
        }
    }



 }
 //-------------------------------------END OF CHECK FOR IMPLIED NAME------------------------------------------------

 //--------------------------CHECK FOR IMPLIED GENDER----------------------------------------------------------------
 void CheckForImpliedGender(){
        //qualification;
        // subject must be pronoun   he,she,her, him
        string MaleProNouns      = " he him his ";
        string FemaleProNouns    = " she her ";
        string SubjectText       = RightLobeMemory[GetSubject(1)].GetpCellDataString();   //pronoun has already been set as subject so get next
        string ProNounResolution = "";
        char GenderClass         = '\0';
        int MatchedM             = MaleProNouns.find(" " + GetWordsLC(GetSubjectLocation())+" ");
        int MatchedF             = FemaleProNouns.find(" " + GetWordsLC(GetSubjectLocation())+" ");
        int Response             = -1;

        if(MatchedF >=0){
            ProNounResolution = "girl";
            GenderClass       = 'G';}
        else
            if(MatchedM >=0){
                ProNounResolution = "boy";
                GenderClass       = 'M';}

        if( (GetWordType(GetSubjectLocation()) == 'p') && ((MatchedF + MatchedM +1) >=0) ){
            SlowSpeak("So " + SubjectText + " is a " + ProNounResolution + "?");
            Response = RequestUserResponse();
            if(Response == 1){
                RightLobeMemory[GetSubject(1)].SetGenderClass(GenderClass);
                SlowSpeak("Okay."); SlowSpeak(":)"); IncreaseMoodLevel();
            }
        }

 }
 //-----------------------------------END OF CHECK FOR IMPLIED GENDER-------------------------------------------------
};

#endif // C_CORTEX_H
