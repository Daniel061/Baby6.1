#ifndef C_BRAIN_H
#define C_BRAIN_H

#include <c_Cerebellum.h>
extern string Version;

class c_Brain : public c_Cerebellum
{
    public:
        c_Brain();
        virtual ~c_Brain();





        c_Personality UserPersonality;
        c_ShortTermMemory ShortTermMemory;

        c_Sentence SlowSpeakSentence;
        c_Sentence LastSentence;
        c_Sentence CommandCheckSentence;


        int rBrainCellCount;
        int lBrainCellCount;
        char GenClass;


    public:
        void SetMyName (string NewVal){SetName(NewVal);}
        void SetUserName (string NewVal){UserPersonality.SetName(NewVal);}
        void SetMyGender (char NewVal){SetGender(NewVal);}
        void SetUserGender (char NewVal){UserPersonality.SetGender(NewVal);}








//---------------------------------------------------------------------------------------------------------------------------------------------------
//********************************************* First Processing Point / Cortex is Main Processor****************************************************

        void ProcessUserInput(string& strData){
            if(Verbose)cout << "[c_Brain.h::ProcessUserInput]" << endl;
            int CommandFound, ConfidenceLevel;
            string CheckedPattern,Root,LongFormFirst,LongFormSecond;
            int SubjectLocation;
            string FirstPattern = "";
            CommandFound = 0;
            bool OwnerShip,Plural,NeedRerun;


            CommandCheckSentence.Parse(strData);
            CommandFound = CommandTrap();
            Parse(strData);                                                              //break sentence down

            if(CommandFound == 0){                                                        //check for command  0 = no command
                 SaveReceivedInput(strData,true);                                             //update short term memory
                 SaveSentenceInLongTermMemory(strData);                                       //update Long Term Memory
                 GatherAndSetAllSentenceData();
                 //SetWordTypes();                                                              //try to set all word types
                 if(IsThisSentenceDuplicated(strData))
                    SlowSpeak("You said that before.");
                 if(GetHasContraction()){
                   NeedRerun = DeconstructContractions(OwnerShip,Plural,Root,LongFormFirst,LongFormSecond,strData);
                   if(NeedRerun){
                    Parse(strData);
                    //SetWordTypes();
                    GatherAndSetAllSentenceData();
                    SaveReceivedInput(strData,true);
                    SaveSentenceInLongTermMemory(strData);
                   }
                 }
                 SubjectLocation = FindSubject();                                             //try to located subject
                 SetSubjectLocation(SubjectLocation);                                         //set the suggestion
                 RebuildPattern();
                 FirstPattern = GetPattern();
                 CheckedPattern = PatternReview(GetPattern(),ConfidenceLevel);                //see if language class can enhance pattern
                 if(Verbose){
                        cout << "Processed Pattern:" << CheckedPattern << ":" << GetPattern() << "Confidence level: " << ConfidenceLevel << endl;}
                 if(CheckedPattern != GetPattern()){
                    SetPattern(CheckedPattern);
                    for(int x = 0; x < GetWordCount(); x++){
                        SetWordType(CheckedPattern[x],x);
                    }
                    SubjectLocation = FindSubject();
                    SetSubjectLocation(SubjectLocation);
                 }
                 DecipherCurrentSentence();                                           //work with sentence

                 SubjectLocation = FindSubject();                                                      // need to run this again to see if any indirect objects
                 SetSubjectLocation(SubjectLocation);                                                  //store the location or -1
                 StoreNewWords();                                                                  //save any new words in rBrainCells
                 RebuildPattern();
                 SaveProcessedPattern(GetPattern());                                                   //update short term memory
                 if(SubjectLocation >=0)
                    SetSubjectInStack(GetWordTokens(SubjectLocation),GetWords(SubjectLocation),GetOriginalString());
                 SavePreAndPostPatternConstruction(FirstPattern,GetPattern());                      //save learned pattern for future// language helper to use this
                 SaveCurrentSentenceInMap();
               }
               else
                if(CommandFound == -1){  //exit commands
                strData = "end";}//stop the loop

            }
//-----------------------------------------------END FIRST PROCESSING---------------------------------------------------------------------------------



        void Report(){
        int WC = GetWordCount();
        cout << "Punctuation Flag:" << boolalpha << GetHasPunctuation() << "  Punctuation Character:" << GetPunctuation() << endl;
        cout << "Word Count:" << WC << " Pattern:" << GetPattern() << endl;
        cout << "Subject location:" << GetSubjectLocation() << "\nIndirect Object Location:" << GetIndirectObjectLocation() << endl;
        for (int x = 0; x < WC; x++){
            cout << x << " " << GetWords(x) << ":" << GetWordTokens(x) <<  " Type:"
            << GetWordType(x) << " isContraction:" << GetisContraction(x) << " Quote Location:" << GetQuoteLocation(x) << endl;
        }
            cout << "Cell Usage(r):" << GetRightLobeCellCount() <<  " Cell Usage(l):" << GetLeftLobeCellCount() << "\n"
                 << " Number of Sentences in LTM:" << GetNumberOfSentencesSaved() << " Sentence Map Count:" << GetSentenceStorageCountInMap() << endl;
        }







        int CommandTrap()
        {
            int Command;
            int Count;
            Command = 0;
            int Control; Control =0;
            Count   = CommandCheckSentence.GetWordCount();
            Command = CommandCheckSentence.GetWordTokens(0);
            if(Count >1)
             Command = Command + CommandCheckSentence.GetWordTokens(1);



            switch (Command)
            {

            case 623: //end
                {
                    Control = -1;
                    SlowSpeak( "Good Bye!");
                    break;
                }
            case 1090: // exit
                {
                    Control =  -1;
                    SlowSpeak( "Good Bye!");
                    break;
                }
            case 2699: // mood level
                {
                    cout << "MoodLevel = " << GetMoodLevel() << endl;
                    Control = 2;
                    break;
                }
            case 2979: // goodbye
                {
                    Control =  -1;
                    SlowSpeak( "Good Bye!");
                    break;
                }
            case 3337:    // cell report
                {
                    int WorkingWord = CommandCheckSentence.GetWordTokens(2);
                    int AdjectivesInMap[20];
                    int AdverbsInMap[20];
                    int VerbsInMap[20];
                    int RelatedNounsInMap[20];
                    int y = 0;
                    bool Result = false;
                    cout << "Cell Report:Right Brain" << endl << endl;
                    cout << "Cell String:" << GetMemoryCellRawStringData(Result,"",WorkingWord)<< endl;
                    cout << "Cell String (LC):" << GetMemoryCellWordLC("",WorkingWord) << endl;
                    cout << "Cell Word Type:" << GetMemoryCellWordType(WorkingWord) << endl;
                    //cout << "Cell Secondary Word Type:" << RightLobeMemory[WorkingWord].GetSecondaryType() << endl;
                    //cout << "Cell Alternate Word Type:" << RightLobeMemory[WorkingWord].GetAlternateType() << endl;
                    cout << "Cell Gender:" << GetMemoryCellGenderClass(WorkingWord) << endl;
                    cout << "Cell Primary Usage:" << GetMemoryCellPurpose(WorkingWord) << endl;
                   // cout << "Cell Root Pointer:" << RightLobeMemory[WorkingWord].GetpNextNoun() << endl;
                    cout << "Cell Data is Set:" << boolalpha << GetMemoryCellIsSet(WorkingWord) << endl;
                    cout << "Cell Location by token:" << WorkingWord << endl;
                    cout << "Cell adjectives stored in map:" << GetMemoryCellAdjectives(WorkingWord,AdjectivesInMap) << endl;
                    cout << "Cell verbs stored in map:" << GetMemoryCellVerbs(WorkingWord,VerbsInMap) << endl;
                    cout << "Cell adverbs stored in map:" << GetMemoryCellAdverbs(WorkingWord,AdverbsInMap) << endl;
                    cout << "Cell Adjectives, Verbs, Adverbs:\n";
                       for(int x = 0; x< GetMemoryCellAdjectiveCount(WorkingWord); x++){
                         cout  << "   " << GetMemoryCellWordLC("",AdjectivesInMap[x]) << " " << GetMemoryCellWordLC("",VerbsInMap[x]) << " " << GetMemoryCellWordLC("",AdverbsInMap[x]) << endl;
                       }
                    cout << endl;
                    y = GetMemoryCellRelatedNouns(WorkingWord,RelatedNounsInMap);
                    cout << "Cell related Nouns("  << y << "):\n";

                       for(int x = 0; x< y;x++){
                         cout << "   " << GetMemoryCellWordLC("",RelatedNounsInMap[x]) << endl;
                       }

                    Control = 2;
                    break;
                }
            case 3058:   //verbose
                {
                    if(Verbose)
                        Verbose = false;
                    else
                        Verbose = true;

                    Control = 2;
                    break;
                }
            case 3109:  //version
                {
                    cout << "Version:" << Version << endl;
                    Control = 2;
                    break;
                }
            case 3387:  //report flow
                {
                    ReportStorageFlow();
                    Control = 2;
                    break;
                }

            case 3383:  //report last
                {
                    Report();
                    Control = 2;
                    break;
                }
            case 4854:  //moodlevel
                {
                    cout << "MoodLevel = " << GetMoodLevel() << endl;
                    Control = 2;
                    break;
                }
            case 5352:  //subject report
                {
                    Control = 2;
                    cout << "no.\tToken\tMemory\t\tString\tOriginal sentence string.\n";
                    for(int x =0; x<GetSubjectStackCount(); x++){
                        if(GetSubjectInStack(x)>0)
                            cout << x << ":\t" << GetSubjectInStack(x) << "\t" << GetMemoryCellWordLC("",GetSubjectInStack(x)) << "\t\t" << GetstrSubjectInStack(x) << "\t" << GetOriginalStringInStack(x) << endl;}
                    break;
                }
            case 5365:   // pattern report 'duvu'
                {
                    Control = 2;
                    cout << GetMemoryCellWordLC("",CommandCheckSentence.GetWordTokens(2)) << " points to "
                         << GetMemoryCellWordLC("",GetMemoryCellPointerToNextPattern(CommandCheckSentence.GetWordTokens(2))) << endl;

                    break;

                }



            }
            if((Control != 0)&(Verbose))
                cout << "[c_Brain.h::CommandTrap]-successful\n";
            else
                if(Verbose) cout << "[c_Brain.h::CommandTrap]-no command found\n";
            return Control;
        }


      //------------------------SETWORDTYPES---------------------------------------------------------------------------
      //     scan sentence words and set their types
      //     Check memory storage first (search only lowercase storage)
      //     if already stored set the sentence word type to the memory value
      //     if not, has already been initialized to 'u' unless sentence parser has set something other than 'u'
      //     doCorrection is control to not override wordtype stored in brain  true = change it to whatever is set by others

       void SetWordTypes(bool doCorrection = false)
        {
            if(Verbose){cout << "[c_Brain.h::SetWordTypes]" << endl;}
            char tmpTypeInSentence, tmpTypeInMemoryCell, tmpTypeFromLanguageHelper;
            char tmpGenderClassFromMemoryCell;
            bool isSetInMemory;
            for(int x = 0; x < GetWordCount(); x++){
                    tmpTypeInSentence            = GetWordType(x);
                    tmpTypeInMemoryCell          = GetMemoryCellWordType(GetWordTokens(x));
                    tmpTypeFromLanguageHelper    = FindWordType(GetWordsLC(x),x);
                    isSetInMemory                = GetMemoryCellIsSet(GetWordTokens(x));
                    tmpGenderClassFromMemoryCell = GetMemoryCellGenderClass(GetWordTokens(x));
                    if(tmpGenderClassFromMemoryCell != '\0')
                        SetGenderClassInSentence(x,tmpGenderClassFromMemoryCell);
                    if(Verbose){
                        cout << "WordLC:  " << GetWordsLC(x) << endl;
                        cout << "  Sentence Set:" << tmpTypeInSentence << endl;
                        cout << "  MemoryCell Set:" << tmpTypeInMemoryCell << endl;
                        cout << "  Language helper Set:" << tmpTypeFromLanguageHelper << endl;
                        cout << "  Memory Cell Previously set?" << boolalpha << isSetInMemory << endl;}

                    if(isSetInMemory && doCorrection) isSetInMemory = false;

                    if(isSetInMemory == false){
                        if(tmpTypeInSentence == 'u')
                            SetWordType(tmpTypeFromLanguageHelper,x);}
                    else{
                        SetWordType(tmpTypeInMemoryCell,x);}

                     if( GetWordType(x) == 'q') SetIsQuestion(true);
                     if( GetWordType(x) == 'g') SetNamePointer(x);
                     if( GetWordType(x) == 'C') SetHasContraction(true);

            }
        }//------END SET WORD TYPES---------------------------------------------------------------

///------------------------------------------------------------------------------------------------


//------------------------------STORE NEW WORDS-----------------------------------------------------------------
        int StoreNewWords()
        {
         if(Verbose)cout << "[c_Brain.h::StoreNewWords]" << endl;
         int NewWords; NewWords = 0;
         int Noun1 = -1;
         int Noun2 = -1;

         for (int x = 0; x < GetWordCount(); x++)
         {
             if((GetWordType(x)=='n') && (Noun1 == -1) ) Noun1 = x; else if((GetWordType(x) == 'n') && (Noun2 == -1))  Noun2 =x;
             if( !( GetMemoryCellIsSet(GetWordTokens(x)) )) //   CheckForKnownWord(GetWords(x))))
                {NewWords++;}
                InstallNewWord(GetWords(x),GetWordType(x),'w',true,GetGenderClassInSentence(x));
                //Associate Adjective
                if(GetWordType(x)=='a'){
                        if(GetSubjectLocation() >=0 )
                            if(!AssociateMemoryCellAdjective(GetWordTokens(GetSubjectLocation()),GetWordsLC(x))){
                                InstallNewWord(GetWords(GetSubjectLocation()),GetWordType(GetSubjectLocation()),'w',true,GetGenderClassInSentence(GetSubjectLocation()));
                                AssociateMemoryCellAdjective(GetWordTokens(GetSubjectLocation()),GetWordsLC(x));
                                if(Verbose)
                                    cout << "Associating " << GetWords(x) << " with " << GetWords(GetSubjectLocation()) << endl;
                            }
                            if(GetIndirectObjectLocation() >=0)
                                if(!AssociateMemoryCellAdjective(GetWordTokens(GetIndirectObjectLocation()),GetWordsLC(x))){
                                    InstallNewWord(GetWords(GetIndirectObjectLocation()),GetWordType(GetIndirectObjectLocation()),'w',true,GetGenderClassInSentence(GetIndirectObjectLocation()));
                                    AssociateMemoryCellAdjective(GetWordTokens(GetIndirectObjectLocation()),GetWordsLC(x));
                                    if(Verbose)
                                       cout << "Associating " << GetWords(x) << " with " << GetWords(GetIndirectObjectLocation()) << endl;
                                }
                    int z; z = GetVerbPointingToAdjective();
                    if(z >=0)
                        AssociateMemoryCellVerbToAdjective(GetWordTokens(GetSubjectLocation()),GetWordsLC(z),GetWordsLC(x));
                        if(GetIndirectObjectLocation()>=0)
                            AssociateMemoryCellVerbToAdjective(GetWordTokens(GetIndirectObjectLocation()),GetWordsLC(z),GetWordsLC(x));
                }
                //Associate Adverb
                if(GetWordType(x) == 'A')
                    AssociateMemoryCellAdverbToVerb(GetWordTokens(GetSubjectLocation()),GetWordsLC(GetWordTokens(GetVerbPointingToAdjective())),GetWordsLC(x));
         }
         //Associate two nouns if not a question sentence
         if((GetNounCount() >=2)&& (!GetIsQuestion())){
                if(Verbose)
                   cout << "Associating " << GetWords(Noun1) << " with " << GetWords(Noun2) << endl;
                AssociateMemoryCellNoun(GetWordTokens(Noun1),GetWordsLC(Noun2));
                AssociateMemoryCellNoun(GetWordTokens(Noun2),GetWordsLC(Noun1));

         }
          //Associate Proper Noun to noun and vice versa
          if((GetWordType(GetIndirectObjectLocation())=='P') && (!GetIsQuestion()) ){
                AssociateMemoryCellNoun(GetWordTokens(GetSubjectLocation()),GetWordsLC(GetIndirectObjectLocation()));
                AssociateMemoryCellNoun(GetWordTokens(GetIndirectObjectLocation()),GetWordsLC(GetSubjectLocation()));
          }

          //Associate Noun to gender word and vice versa
          if((GetWordType(GetIndirectObjectLocation())=='P') && (!GetIsQuestion()) ){
                AssociateMemoryCellNoun(GetWordTokens(GetSubjectLocation()),GetWordsLC(GetIndirectObjectLocation()));
                AssociateMemoryCellNoun(GetWordTokens(GetIndirectObjectLocation()),GetWordsLC(GetSubjectLocation()));
          }

            return NewWords;

        }






 //----------------------------------FIRST RUN WELCOME MESSAGE--------------------------------------------------------

    void FirstRunWelcomeMessage(){
           //Recording turned off for this
            cout << "[Version:" << Version << "]\n";
            SlowSpeak("Hello there!",false);
            SlowSpeak("Thanks for helping me learn new things.",false);
            SlowSpeak("Right now I don't know much about anything. I need for you to teach me.",false);
            SlowSpeak("I will do my best to understand you but if I don't I may ask you a question about what you said.",false);
            SlowSpeak("If I do need to ask a question, you will see >? prompt. Please respond with a yes or no answer unless I ask something more specific.",false);
            SlowSpeak("This will help me to understand.");
            SlowSpeak("Thank you!");
            SlowSpeak(":)",false);








    }
//--------------------------------END FIRST RUN WELCOME MESSAGE-------------------------------------------------------------
};

#endif // C_BRAIN_H
