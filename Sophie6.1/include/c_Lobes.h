#ifndef C_LOBES_H
#define C_LOBES_H
#include <Library.h>
#include <c_MemoryCell.h>
#include <unordered_map>
#include <map>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>
#include <time.h>

extern bool   Verbose;
extern string Version;



class c_Lobes : public c_MemoryCell
{

    public:
        c_Lobes();
        virtual ~c_Lobes();

    protected:

    private:
        unordered_map <int, c_MemoryCell> RightLobeMemoryMap;
        unordered_map <int, c_MemoryCell> LeftLobeMemoryMap;
        unordered_map <int, c_MemoryCell>::iterator mapIT;
        unordered_map <int, c_MemoryCell>::iterator fileIT;
        //new map form ~ in transition
        map <string, c_MemoryCell> RightLobeCellMap;
        map <string, c_MemoryCell> LeftLobeCellMap;
        map <string, c_MemoryCell>::iterator CellMapIT;

        c_MemoryCell WorkingCell;

            /* Private Function to search the map to see if
               the address (token value of the data) exists.
               if it does, modifies the address of the bool at Result to TRUE and
               ALWAYS returns the iterator.
               = end() if not found.
            */

            unordered_map <int, c_MemoryCell>::iterator FindAddressInMap(int Address, bool &Result, char SideToCheck = 'r'){
            Result = false;
            if(SideToCheck == 'r'){
                mapIT = RightLobeMemoryMap.find(Address);
                if(mapIT != RightLobeMemoryMap.end())Result = true;
                }
            else{
                mapIT = LeftLobeMemoryMap.find(Address);
                if(mapIT != LeftLobeMemoryMap.end())Result = true;
            }
            return mapIT;
            }



            /* Private Function to search the map to see if
               the string is indexed.
               if it is not, modifies the address of the bool at Result to TRUE and
               ALWAYS returns the iterator.
               = end() if not found.
               For use with Pattern data, set UseLowerCase to false
            */
            map <string, c_MemoryCell>::iterator FindStringInMap(string strToSearch, bool &Result, char SideToCheck = 'r', bool UseLowerCase = true){
            Result = false;
            if(UseLowerCase)
                strToSearch = MakeStringLowerCase(strToSearch);
            if(SideToCheck == 'r'){
                CellMapIT = RightLobeCellMap.find(strToSearch);
                if(CellMapIT != RightLobeCellMap.end())Result = true;
                }
            else{
                CellMapIT = LeftLobeCellMap.find(strToSearch);
                if(CellMapIT != LeftLobeCellMap.end())Result = true;
            }
            return CellMapIT;
            }



    public:



//------------------------NEW STRING INDEXED MEMORY CELL MAP FUNCTIONS----------------

//-----------------SET FUNCTIONS----------------------------------

        /// Sets pDaysOld if strSearchBase exists,
        ///  returns True if added, else false if updated,
        ///  send pResolvedPattern data in strData,
        ///  send owner word in strSearchBase.
        bool SetMemoryCellpDaysOld(string strSearchBase, int DaysOld){
           bool Result   = false;
           CellMapIT     = FindStringInMap(strSearchBase, Result);
               if (Result){
                    CellMapIT->second.SetpDaysOld(DaysOld);}
               return Result;}

        /// Sets pResolvedPattern if exists,
        ///  returns True if added, else false if updated,
        ///  send pResolvedPattern data in strData,
        ///  send owner word in strSearchBase.
        bool SetMemoryCellpPointerToNextPattern(string strSearchBase, string strData ){
           bool Result = false;
           CellMapIT   = FindStringInMap(strSearchBase, Result);
               if (Result){
                    CellMapIT->second.SetpCellResolvedPattern(strData);}
               return Result;}


        /// Sets pToken if exists
        ///  returns True if added, else false if updated
        ///  send pToken data in intData
        ///  send owner word in strSearchBase
        bool SetMemoryCellpToken(string strSearchBase, int intData ){
           bool Result = false;
           CellMapIT   = FindStringInMap(strSearchBase, Result);
               if (Result){
                    CellMapIT->second.SetpCellToken(intData);}
               return Result;}


        /// Sets pNextNoun if exists
        ///  returns True if added, else false if updated
        ///  send pNextNoun data in intData
        ///  send owner word in strSearchBase
        bool SetMemoryCellpNextNoun(string strSearchBase, int intData ){
           bool Result = false;
           CellMapIT   = FindStringInMap(strSearchBase, Result);
               if (Result){
                    CellMapIT->second.SetpCellNextNoun(intData);}
               return Result;}


        /// Sets pNextVerb if exists
        ///  returns True if added, else false if updated
        ///  send pNextVerb data in intData
        ///  send owner word in strSearchBase
        bool SetMemoryCellpNextVerb(string strSearchBase, int intData ){
           bool Result = false;
           CellMapIT   = FindStringInMap(strSearchBase, Result);
               if (Result){
                    CellMapIT->second.SetpCellNextVerb(intData);}
               return Result;}


        /// Sets pCellSingularLocation if exists
        ///  returns True if added, else false if updated
        ///  send pCellSingularLocation data in intData
        ///  send owner word in strSearchBase
        bool SetMemoryCellpCellSingularLocation(string strSearchBase, int intData ){
           bool Result = false;
           CellMapIT   = FindStringInMap(strSearchBase, Result);
               if (Result){
                    CellMapIT->second.SetpCellSingularLocation(intData);}
               return Result;}


        /// Sets pCellIsSingular if exists
        ///  returns True if added, else false if updated
        ///  send pIsSingular data in charData
        ///  send owner word in strSearchBase
        bool SetMemoryCellpCellIsSingular(string strSearchBase, char charData ){
           bool Result = false;
           CellMapIT   = FindStringInMap(strSearchBase, Result);
               if (Result){
                    CellMapIT->second.SetpCellIsSingular(charData);}
               return Result;}


        /// Sets pIsSingularPossessive if exists,
        /// -returns True if added, else false if updated,
        /// -send pIsSingularPossessive data in boolData,
        /// -send owner word in strSearchBase.
        bool SetMemoryCellpIsSingularPossessive(string strSearchBase, bool boolData ){
           bool Result = false;
           CellMapIT   = FindStringInMap(strSearchBase, Result);
               if (Result){
                    CellMapIT->second.SetpIsSingularPossessive(boolData);}
               return Result;}

        /// Sets pIsPluralPossessive if strSearchBase exists,
        /// -returns True if added, else false if updated,
        /// -send pIsPluralPossessive data in boolData,
        /// -send owner word in strSearchBase.
        bool SetMemoryCellpIsPluralPossessive(string strSearchBase, bool boolData ){
           bool Result = false;
           CellMapIT   = FindStringInMap(strSearchBase, Result);
               if (Result){
                    CellMapIT->second.SetpIsPluralPossessive(boolData);}
               return Result;}


        /// Sets ContractionLongFormSecond if exists
        ///  returns True if added, else false if updated
        ///  send LongFormSecond data in strData
        ///  send Word cell string for index search to apply this to in strSearchBase
        bool SetMemoryCellContractionLongSecond(string strSearchBase, string strData ){
           bool Result = false;
           CellMapIT   = FindStringInMap(strSearchBase, Result);
               if (Result){
                    CellMapIT->second.SetpCellContractionLongFormSecond(strData);}
               return Result;}


        /// Sets ContractionLongFormFirst if exists
        ///  returns True if added, else false if updated
        ///  send LongFormFirst data in strData
        ///  send Word cell string for index search to apply this to in strSearchBase
        bool SetMemoryCellContractionLongFirst(string strSearchBase, string strData){
           bool Result = false;
           CellMapIT   = FindStringInMap(strSearchBase, Result);
               if (Result){
                    CellMapIT->second.SetpCellContractionLongFormFirst(strData);}
               return Result;}


        /// Sets pCellMiniDefinition if strSearchBase exists
        ///  returns True if set, else false
        ///  send pCellMiniDefinition data in strMiniDefinition
        ///  send owner word in strSearchBase
        bool SetMemorypCellMiniDefinition(string strSearchBase, string strMiniDefinition){
           bool Result = false;
           CellMapIT   = FindStringInMap(strSearchBase, Result);
               if (Result){
                  CellMapIT->second.SetpCellMiniDefinition(strMiniDefinition);}
               return Result;}


        /// Sets pGivenName if strSearchBase exists
        ///  returns True if set, else false
        ///  send pGivenName data in strGivenName
        ///  send owner word in strSearchBase
        bool SetMemorypGivenName(string strSearchBase, string strGivenName){
           bool Result = false;
           CellMapIT   = FindStringInMap(strSearchBase, Result);
               if (Result){
                  CellMapIT->second.SetpCellGivenName(strGivenName);}
               return Result;}



        /// Sets pIsPluralPossessive if strSearchBase exists
        ///  returns True if set, else false
        ///  send pIsPluralPossessive data in boolIsPluralPossessive
        ///  send owner word in strSearchBase
        bool SetMemorypIsPluralPossessive(string strSearchBase, bool boolIsPluralPossessive){
           bool Result = false;
           CellMapIT   = FindStringInMap(strSearchBase, Result);
               if (Result){
                  CellMapIT->second.SetpIsPluralPossessive(boolIsPluralPossessive);}
               return Result;}


        /// Sets pIsRoot if strSearchBase exists
        ///  returns True if set, else false
        ///  send pIsRoot data in boolIsRoot
        ///  send owner word in strSearchBase
        bool SetMemorypIsRoot(string strSearchBase, bool boolIsRoot){
           bool Result = false;
           CellMapIT   = FindStringInMap(strSearchBase, Result);
               if (Result){
                  CellMapIT->second.SetpCellIsRoot(boolIsRoot);}
               return Result;}



        /// Sets pGenderClass if strSearchBase exists
        ///  returns True if set, else false
        ///  send pGenderClass data in charGenderClass
        ///  send owner word in strSearchBase
        bool SetMemorypGenderClass(string strSearchBase, char charGenderClass){
           bool Result = false;
           CellMapIT   = FindStringInMap(strSearchBase, Result);
               if (Result){
                  CellMapIT->second.SetpCellGenderClass(charGenderClass);}
               return Result;}


        /// Sets pAlternateType if strSearchBase exists
        ///  returns True if set, else false
        ///  send pAlternateType data in charAlternateType
        ///  send owner word in strSearchBase
        bool SetMemorypAlternateType(string strSearchBase, char charAlternateType){
           bool Result = false;
           CellMapIT   = FindStringInMap(strSearchBase, Result);
               if (Result){
                  CellMapIT->second.SetpCellAlternateType(charAlternateType);}
               return Result;}


        /// Sets pSecondaryType if strSearchBase exists
        ///  returns True if set, else false
        ///  send pSecondaryType data in charSecondaryType
        ///  send owner word in strSearchBase

        bool SetMemorypSecondaryType(string strSearchBase, char charSecondaryType){
           bool Result = false;
           CellMapIT   = FindStringInMap(strSearchBase, Result);
               if (Result){
                  CellMapIT->second.SetpCellSecondaryType(charSecondaryType);}
               return Result;}


        /// Sets pWordTense if strSearchBase exists
        ///  returns True if set, else false
        ///  send pWordTense data in charWordTense
        ///  send owner word in strSearchBase
        bool SetMemorypWordTense(string strSearchBase, char charWordTense){
           bool Result = false;
           CellMapIT   = FindStringInMap(strSearchBase, Result);
               if (Result){
                  CellMapIT->second.SetpCellWordTense(charWordTense);}
               return Result;}


        /// Sets pWordType if strSearchBase exists,
        ///  -returns True if set, else false
        ///  -send pWordType data in charWordType
        ///  -send owner word in strSearchBase

        bool SetMemorypWordType(string strSearchBase, char charWordType){
           bool Result = false;
           CellMapIT   = FindStringInMap(strSearchBase, Result);     /// find it
               if (Result){
                  CellMapIT->second.SetpCellWordType(charWordType);} /// store it
               return Result;}



        /// Sets pCellPurpose if strSearchBase exists
        ///  returns True if set, else false
        ///  send pCellPurpose data in charCellPurpose
        ///  send owner word in strSearchBase
        bool SetMemorypCellPurpose(string strSearchBase, char charCellPurpose){
           bool Result = false;
           CellMapIT   = FindStringInMap(strSearchBase, Result);
               if (Result){
                  CellMapIT->second.SetpCellPurpose(charCellPurpose);}
               return Result;}



        /// Sets PossessiveRootType if strSearchBase exists
        ///  returns True if set, else false
        ///  send PossessiveRootType data in charPossessiveRootDataType
        ///  send owner word in strSearchBase
        bool SetMemoryCellPossessiveRootType(string strSearchBase, char charPossessiveRootDataType){
           bool Result = false;
           CellMapIT   = FindStringInMap(strSearchBase, Result);
               if (Result){
                  CellMapIT->second.SetpPossessiveRootType(charPossessiveRootDataType);}
               return Result;}


        /// Sets PossessiveRoot if strSearchBase exists
        ///  returns True if added, else false
        ///  send pPossessiveRoot data in strPossessiveRootData
        ///  send owner word in strSearchBase
        bool SetMemoryCellPossessiveRoot(string strSearchBase, string strPossessiveRootData){
           bool Result = false;
           CellMapIT   = FindStringInMap(strSearchBase, Result);
               if (Result){
                  CellMapIT->second.SetpPossessiveRoot(strPossessiveRootData);}
               return Result;}



        /// Updates or Adds pCellData if exists
        ///  returns True if added, else false if updated
        ///  send pCellData data in strSearchBase
        bool SetMemoryCellpCellData(string strSearchBase){
           bool Result = false;
           CellMapIT   = FindStringInMap(strSearchBase, Result);
               if (!Result){
                  WorkingCell.SetpCellDataString(strSearchBase);
                  WorkingCell.SetpCellDataLC(MakeStringLowerCase(strSearchBase));
                  RightLobeCellMap.emplace(strSearchBase,WorkingCell);
                  Result = true;}
                  else{
                    CellMapIT->second.SetpCellDataString(strSearchBase);}
               return Result;}



        /// Updates or Adds pCellDataLC if strSearchBase exists,
        ///  -returns True if added, else false if updated,
        ///  -send [pCellDataLC] in strSearchBase,
        ///  -strSearchBase will be made lowercase before storage.
        //
        bool SetMemoryCellpCellDataLC(string strSearchBase){
           bool Result = false;
           CellMapIT   = FindStringInMap(strSearchBase, Result);
               if (!Result){
                  WorkingCell.SetpCellDataString(strSearchBase);
                  WorkingCell.SetpCellDataLC(MakeStringLowerCase(strSearchBase));
                  RightLobeCellMap.emplace(strSearchBase,WorkingCell);
                  Result = true;}
                  else{
                    CellMapIT->second.SetpCellDataLC(MakeStringLowerCase(strSearchBase));}
               return Result;}




///---------------------END SET FUNCTIONS---------------------------------------

///------------------------GET FUNCTIONS----------------------------------------

        /// Gets pDaysOld if strSearchBase exists, else return 0,
        ///  Returns True in the address of &Result if exists
        ///  Returns pDaysOld
        int GetMemoryCellpDaysOld(string strSearchBase, bool &Result){
           Result = false;
           CellMapIT   = FindStringInMap(strSearchBase, Result);
               if (Result){
                    return CellMapIT->second.GetpDaysOld();}
               else
                    return 0;}


        /// Gets pCellData if exists, else return ""
        ///  Returns True in the address of &Result if exists
        ///  Returns pCellData
        string GetMemoryCellRawData(string strSearchBase, bool &Result){
           Result = false;
           CellMapIT   = FindStringInMap(strSearchBase, Result);
               if (Result){
                    return CellMapIT->second.GetpCellDataString();}
               else
                    return "";}


        /// Gets pCellDataLC if exists, else return ""
        ///  Returns True in the address of &Result if exists
        ///  Returns pCellDataLC
        ///  Send owner word in strSearchBase
        string GetMemoryCellDataLC(string strSearchBase, bool &Result){
           Result = false;
           CellMapIT   = FindStringInMap(strSearchBase, Result);
               if (Result){
                    return CellMapIT->second.GetpCellDataLC();}
               else
                    return "";}

        /// Gets pCellGivenName if exists, else return ""
        ///  Returns True in the address of &Result if exists
        ///  Returns pCellGivenName
        ///  Send owner word in strSearchBase

        string GetMemoryCellGivenName(string strSearchBase, bool &Result){
           Result = false;
           CellMapIT   = FindStringInMap(strSearchBase, Result);
               if (Result){
                    return CellMapIT->second.GetpCellGivenName();}
               else
                    return "";}


        /// Gets pCellMiniDefinition if exists, else return ""
        ///  Returns True in the address of &Result if exists
        ///  Returns pCellMiniDefinition
        ///  Send owner word in strSearchBase
        ///  Send which minidef to get in intWhich
        string GetMemoryCellMiniDef(string strSearchBase, bool &Result, int intWhich){
           Result = false;
           CellMapIT   = FindStringInMap(strSearchBase, Result);
               if (Result){
                    return CellMapIT->second.GetpCellMiniDefinition(intWhich);}
               else
                    return "";}

        /// Gets pCellMiniDefinitionCount
        int  GetMemoryCellMiniDefinitionCount(string strSearchBase, bool &Result){
            Result    = false;
            CellMapIT = FindStringInMap(strSearchBase, Result);
            if(Result){
                return CellMapIT->second.GetpCellMiniDefinitionCount();}
            else
                return -1;}

        /// Gets Contraction first form if exists, else return ""
        ///  Returns True in the address of &Result if exists
        ///  Returns Contraction First
        ///  Send owner word in strSearchBase
        string GetMemoryCellContractionFirst(string strSearchBase, bool &Result){
           Result = false;
           CellMapIT   = FindStringInMap(strSearchBase, Result);
               if (Result){
                    return CellMapIT->second.GetpCellContractionLongFormFirst();}
               else
                    return "";}


        /// Gets Contraction Second form if exists, else return ""
        ///  Returns True in the address of &Result if exists
        ///  Returns Contraction First
        ///  Send owner word in strSearchBase
        string GetMemoryCellContractionSecond(string strSearchBase, bool &Result){
           Result = false;
           CellMapIT   = FindStringInMap(strSearchBase, Result);
               if (Result){
                    return CellMapIT->second.GetpCellContractionLongFormSecond();}
               else
                    return "";}

        /// Gets PossessiveRoot if exists, else return ""
        ///  Returns True in the address of &Result if exists
        ///  Returns PossessiveRoot
        ///  Send owner word in strSearchBase
        string GetMemoryCellPossessiveRoot(string strSearchBase, bool &Result){
           Result = false;
           CellMapIT   = FindStringInMap(strSearchBase, Result);
               if (Result){
                    return CellMapIT->second.GetpPossessiveRoot();}
               else
                    return "";}


        /// Gets PossessiveRootType if exists, else return 'u' - default
        ///  Returns True in the address of &Result if exists
        ///  Returns PossessiveRootType
        ///  Send owner word in strSearchBase
        char GetMemoryCellPossessiveRootType(string strSearchBase, bool &Result){
           Result = false;
           CellMapIT   = FindStringInMap(strSearchBase, Result);
               if (Result){
                    return CellMapIT->second.GetpPossessiveRootType();}
               else
                    return 'u';}


        /// Gets CellPurpose if exists, else return 'u' - default
        ///  Returns True in the address of &Result if exists
        ///  Returns CellPurpose
        ///  Send owner word in strSearchBase
        char GetMemoryCellcharPurpose(string strSearchBase, bool &Result){
           Result = false;
           CellMapIT   = FindStringInMap(strSearchBase, Result);
               if (Result){
                    return CellMapIT->second.GetpCellPurpose();}
               else
                    return 'u';}


        /// Gets CellWordType if exists, else return 'u' - default
        ///  Returns True in the address of &Result if exists
        ///  Returns CellWordType
        ///  Send owner word in strSearchBase
        char GetMemoryCellcharWordType(string strSearchBase, bool &Result){
           Result = false;
           CellMapIT   = FindStringInMap(strSearchBase, Result);
               if (Result){
                    return CellMapIT->second.GetpCellWordType();}
               else
                    return 'u';}


        /// Gets CellWordTense if exists, else return 'u' - default
        ///  Returns True in the address of &Result if exists
        ///  Returns CellWordTense
        ///  Send owner word in strSearchBase
        char GetMemoryCellcharWordTense(string strSearchBase, bool &Result){
           Result = false;
           CellMapIT   = FindStringInMap(strSearchBase, Result);
               if (Result){
                    return CellMapIT->second.GetpCellWordTense();}
               else
                    return 'u';}


        /// Gets CellSecondaryType if exists, else return 'u' - default
        ///  Returns True in the address of &Result if exists
        ///  Returns CellSecondaryType
        ///  Send owner word in strSearchBase
        char GetMemoryCellcharSecondaryWordType(string strSearchBase, bool &Result){
           Result = false;
           CellMapIT   = FindStringInMap(strSearchBase, Result);
               if (Result){
                    return CellMapIT->second.GetpCellSecondaryType();}
               else
                    return 'u';}


        /// Gets CellAlternateType if exists, else return 'u' - default
        ///  Returns True in the address of &Result if exists
        ///  Returns CellAlternateType
        ///  Send owner word in strSearchBase
        char GetMemoryCellcharAlternateWordType(string strSearchBase, bool &Result){
           Result = false;
           CellMapIT   = FindStringInMap(strSearchBase, Result);
               if (Result){
                    return CellMapIT->second.GetpCellAlternateType();}
               else
                    return 'u';}


        /// Gets CellGenderClass if exists, else return 'u' - default
        ///  Returns True in the address of &Result if exists
        ///  Returns CellGenderClass
        ///  Send owner word in strSearchBase
        char GetMemoryCellcharGenderClass(string strSearchBase, bool &Result){
           Result = false;
           CellMapIT   = FindStringInMap(strSearchBase, Result);
               if (Result){
                    return CellMapIT->second.GetpCellGenderClass();}
               else
                    return 'u';}


        /// Gets pCellIsRoot if exists, else false
        ///  Returns True in the address of &Result if exists
        ///  Returns bool pCellIsRoot
        ///  Send owner word in strSearchBase
        bool GetMemoryCellpIsRoot(string strSearchBase, bool &Result){
           Result = false;
           CellMapIT   = FindStringInMap(strSearchBase, Result);
               if (Result){
                    return CellMapIT->second.GetpCellIsRoot();}
               else
                    return Result;}


        /// Gets isPluralPossessive if exists, else false
        ///  Returns True in the address of &Result if exists
        ///  Returns bool isPluralPossessive
        ///  Send owner word in strSearchBase
        bool GetMemoryCellIsPluralPossessive(string strSearchBase, bool &Result){
           Result = false;
           CellMapIT   = FindStringInMap(strSearchBase, Result);
               if (Result){
                    return CellMapIT->second.GetpIsPluralPossessive();}
               else
                    return Result;}


        /// Gets isSingularPossessive if exists, else false
        ///  Returns True in the address of &Result if exists
        ///  Returns bool isSingularPossessive
        ///  Send owner word in strSearchBase
        bool GetMemoryCellIsSingularPossessive(string strSearchBase, bool &Result){
           Result = false;
           CellMapIT   = FindStringInMap(strSearchBase, Result);
               if (Result){
                    return CellMapIT->second.GetpIsSingularPossessive();}
               else
                    return Result;}


        /// Gets IsSingular if exists, else return 'u' - default
        ///  Returns True in the address of &Result if exists
        ///  Returns IsSingular
        ///  Send owner word in strSearchBase
        char GetMemoryCellcharIsSingular(string strSearchBase, bool &Result){
           Result = false;
           CellMapIT   = FindStringInMap(strSearchBase, Result);
               if (Result){
                    return CellMapIT->second.GetpCellIsSingular();}
               else
                    return 'u';}


        /// Gets Singular Location if exists, else return -1 - default
        ///  Returns True in the address of &Result if exists
        ///  Returns Singular Location
        ///  Send owner word in strSearchBase
        int GetMemoryCellintSingularLocation(string strSearchBase, bool &Result){
           Result = false;
           CellMapIT   = FindStringInMap(strSearchBase, Result);
               if (Result){
                    return CellMapIT->second.GetpCellSingularLocation();}
               else
                    return -1;}


        /// Gets Next Verb Location if exists, else return -1 - default
        ///  Returns True in the address of &Result if exists
        ///  Returns Next Verb Location Location
        ///  Send owner word in strSearchBase
        int GetMemoryCellintNextVerbLocation(string strSearchBase, bool &Result){
           Result = false;
           CellMapIT   = FindStringInMap(strSearchBase, Result);
               if (Result){
                    return CellMapIT->second.GetpCellNextVerb();}
               else
                    return -1;}



        /// Gets Next Noun Location if exists, else return -1 - default
        ///  Returns True in the address of &Result if exists
        ///  Returns Next Noun Location Location
        ///  Send owner word in strSearchBase
        int GetMemoryCellintNextNounLocation(string strSearchBase, bool &Result){
           Result = false;
           CellMapIT   = FindStringInMap(strSearchBase, Result);
               if (Result){
                    return CellMapIT->second.GetpCellNextNoun();}
               else
                    return -1;}


        /// Gets pToken if exists, else return -1 - default
        ///  Returns True in the address of &Result if exists
        ///  Returns pToken
        ///  Send owner word in strSearchBase
        int GetMemoryCellintpToken(string strSearchBase, bool &Result){
           Result = false;
           CellMapIT   = FindStringInMap(strSearchBase, Result);
               if (Result){
                    return CellMapIT->second.GetpCellToken();}
               else
                    return -1;}



        /// Gets pResolvedPattern if strSearch base exists, else return -1 - default
        /// Returns True in the address of &Result if exists
        /// Returns pResolvedPattern
        /// Send owner word in strSearchBase
        string GetMemoryCellpResolvedPattern(string strSearchBase, bool &Result){
           Result      = false;
           CellMapIT   = FindStringInMap(strSearchBase, Result);
               if (Result){
                    return CellMapIT->second.GetpCellResolvedPattern();}
               else
                    return "";}

        /// Gets number of adjectives if strSearch base exists, else return -1 - default
        /// Returns True in the address of &Result if exists
        /// Returns int number of adjectives
        /// Send owner word in strSearchBase
       int     GetMemoryCellNumberOfAdjectives(string strSearchBase, bool &Result){
           Result      = false;
           CellMapIT   = FindStringInMap(strSearchBase, Result);
                if(Result){
                    return CellMapIT->second.GetNumberOfAdjectivesInList();}
                else{
                    return -1;}}

        /// Gets number of adverbs if strSearch base exists, else return -1 - default
        /// Returns True in the address of &Result if exists
        /// Returns int number of adverbs
        /// Send owner word in strSearchBase
       int     GetMemoryCellNumberOfAdVerbs(string strSearchBase, bool &Result){
           Result      = false;
           CellMapIT   = FindStringInMap(strSearchBase, Result);
                if(Result){
                    return CellMapIT->second.GetNumberOfAdverbsInList();}
                else{
                    return -1;}}

        /// Gets number of verbs if strSearch base exists, else return -1 - default
        /// Returns True in the address of &Result if exists
        /// Returns int number of verbs
        /// Send owner word in strSearchBase
       int     GetMemoryCellNumberOfVerbs(string strSearchBase, bool &Result){
           Result      = false;
           CellMapIT   = FindStringInMap(strSearchBase, Result);
                if(Result){
                    return CellMapIT->second.GetNumberOfVerbsInList();}
                else{
                    return -1;}}

        /// Gets number of related nouns if strSearch base exists, else return -1 - default
        /// Returns True in the address of &Result if exists
        /// Returns int number of related nouns
        /// Send owner word in strSearchBase
       int     GetMemoryCellNumberOfRelatedNouns(string strSearchBase, bool &Result){
           Result      = false;
           CellMapIT   = FindStringInMap(strSearchBase, Result);
                if(Result){
                    return CellMapIT->second.GetNumberOfRelatedNounsInList();}
                else{
                    return -1;}}

         /// Get adjective from memory cell list if strSearchBase exists
         /// Returns string adjective and true in address of Result if exists,
         /// otherwise returns "" and false;
        string  GetMemoryCellAdjectiveFromList(string strSearchBase, int intWhich, bool &Result){
            Result     = false;
            CellMapIT  = FindStringInMap(strSearchBase,Result);
                 if(Result){
                    return CellMapIT->second.GetAdjectiveFromList(intWhich);}
                 else
                    return "";}

         /// Get adverb from memory cell list if strSearchBase exists
         /// Returns string adverb and true in address of Result if exists,
         /// otherwise returns "" and false;
        string  GetMemoryCellAdverbFromList(string strSearchBase, int intWhich, bool &Result){
            Result     = false;
            CellMapIT  = FindStringInMap(strSearchBase,Result);
                 if(Result){
                    return CellMapIT->second.GetAdverbFromList(intWhich);}
                 else
                    return "";}


         /// Get Verb from memory cell list if strSearchBase exists
         /// Returns string Verb and true in address of Result if exists,
         /// otherwise returns "" and false;
        string  GetMemoryCellVerbFromList(string strSearchBase, int intWhich, bool &Result){
            Result     = false;
            CellMapIT  = FindStringInMap(strSearchBase,Result);
                 if(Result){
                    return CellMapIT->second.GetVerbFromList(intWhich);}
                 else
                    return "";}



         /// Get Noun from memory cell list if strSearchBase exists
         /// Returns string Noun and true in address of Result if exists,
         /// otherwise returns "" and false;
        string  GetMemoryCellNounFromList(string strSearchBase, int intWhich, bool &Result){
            Result     = false;
            CellMapIT  = FindStringInMap(strSearchBase,Result);
                 if(Result){
                    return CellMapIT->second.GetNounFromList(intWhich);}
                 else
                    return "";}

///-----------------------Old Memory cell map functions-----------------------------///

//        /// Returns -1 if doesn't exist, else returns adjective count
//        ///  CORRECTED/UPDATED  FOUND NO CALLS TO HERE
//        int GetMemoryXellAdjectiveCount(string strSearchBase){
//            int Result        = -1;
//            bool SearchResult = false;
//            CellMapIT             = FindStringInMap(strSearchBase,SearchResult);
//                if(SearchResult){
//                    Result = CellMapIT->second.GetNumberOfAdjectivesInList();}
//            return Result;
//        }

        /// Checks to see if there is a memorycell for the Address given.
        ///  returns true if so, if not returns false.
        ///   CORRECTED/UPDATED  LANGUAGE AND BRAIN ARE USING THIS
        bool GetMemoryCellIsSet(string strSearchBase,bool &Result, char SideToCheck = 'r'){
            Result = false;
            FindStringInMap(strSearchBase,Result,SideToCheck);
            return Result;
        }


        //First checks to see if the cell at the address given exist.
        //if not, returns -1.
        //otherwise, returns the Adjective count and
        //by reference, the tokenized adjective value in the array Adjectives[]
        ///   NOT CORRECTED/UPDATED  MULTIPLE FUNCTIONS CALLING THIS
        int GetMemoryCellAdjectives(int Address,int Adjectives[]){
            bool Result  = false;
            int  Count   = -1;
            mapIT        = FindAddressInMap(Address,Result);
                if(Result){
                   Count = mapIT->second.GetNumberOfAdjectivesInList();
                   for(int x = 0; x<=(Count-1); x++){
                    Adjectives[x] = Tokenize(mapIT->second.GetAdjectiveFromList(x));
                   }}
                 return Count;
        }


        //First checks to see if the cell at the address given exist.
        //if not, returns -1.
        //otherwise, returns the RelatedNoun count and
        //by reference, the tokenized RelatedNoun value in the array RelatedNouns[]
        ///   NOT CORRECTED/UPDATED
        int GetMemoryCellRelatedNouns(int Address,int RelatedNouns[]){
            bool Result  = false;
            int  Count   = -1;
            mapIT        = FindAddressInMap(Address,Result);
                if(Result){
                   Count = mapIT->second.GetNumberOfRelatedNounsInList();
                   for(int x = 0; x<=(Count-1); x++){
                    RelatedNouns[x] = Tokenize(mapIT->second.GetNounFromList(x));
                   }}
                 return Count;
        }




        //First checks to see if the cell at the address given exist.
        //if not, returns -1.
        //otherwise, returns the Verb count and
        //by reference, the tokenized Verb value in the array Verbs[]
        ///   NOT CORRECTED/UPDATED
        int GetMemoryCellVerbs(int Address,int Verbs[]){
            bool Result  = false;
            int  Count   = -1;
            mapIT        = FindAddressInMap(Address,Result);
                if(Result){
                   Count = mapIT->second.GetNumberOfVerbsInList();
                   for(int x = 0; x<=(Count-1); x++){
                    Verbs[x] = Tokenize(mapIT->second.GetVerbFromList(x));
                   }}
                 return Count;
        }


         //First checks to see if the cell at the address given exist.
         //if not, returns -1.
         //otherwise, returns the Adverb count and
         //by reference, the tokenized Adverb value in the array Adverbs[]
         ///   NOT CORRECTED/UPDATED
         int GetMemoryCellAdverbs(int Address,int Adverbs[]){
             bool Result  = false;
             int  Count   = -1;
             mapIT        = FindAddressInMap(Address,Result);
                  if(Result){
                     Count = mapIT->second.GetNumberOfAdverbsInList();
                     for(int x = 0; x<=(Count-1); x++){
                      Adverbs[x] = Tokenize(mapIT->second.GetAdverbFromList(x));
                     }}
                   return Count;
          }



          //First makes sure the address given exists,
          //then associates adjective to the address given.
          //NOTE:will not duplicate Adjectives.
          ///   NOT CORRECTED/UPDATED
          bool AssociateMemoryCellAdjective(int Address, string AdjectiveToAssociate){
               bool Result = false;
               mapIT = FindAddressInMap(Address,Result);
               if(Result){
                    mapIT->second.AssociateAdjectiveInMap(AdjectiveToAssociate);}
               return Result;
          }


          //First makes sure the address given exists,
          //then associates Noun to the address given.
          //NOTE:will not duplicate Nouns.
          ///   NOT CORRECTED/UPDATED
          bool AssociateMemoryCellNoun(int Address, string NounToAssociate){
               bool Result = false;
               mapIT = FindAddressInMap(Address,Result);
               if(Result){
                    mapIT->second.AssociateNounInMap(NounToAssociate);}
               return Result;
          }



          //First makes sure the address given exists,
          //then associates Adverb to verb in the address given.
          //NOTE:will not duplicate Adverbs.
          ///   NOT CORRECTED/UPDATED
          bool AssociateMemoryCellAdverbToVerb(int Address, string AdverbToAssociate, string VerbToAssociate){
               bool Result = false;
               mapIT = FindAddressInMap(Address,Result);
               if(Result){
                    mapIT->second.AssociateAdverbToVerbInMap(AdverbToAssociate,VerbToAssociate);}
               return Result;

          }


          //First makes sure the address given exists,
          //then associates Verb to adjective in the address given.
          //NOTE:will not duplicate Adverbs.
          ///   NOT CORRECTED/UPDATED
          bool AssociateMemoryCellVerbToAdjective(int Address, string AdverbToAssociate, string VerbToAssociate){
               bool Result = false;
               mapIT = FindAddressInMap(Address,Result);
               if(Result){
                    mapIT->second.AssociateAdverbToVerbInMap(AdverbToAssociate,VerbToAssociate);}
               return Result;
          }


          //First Checks to see if cell address given exists,
          //if so, checks to see if NounToCheck is related to this cell address.
          //Returns true if so, false if not or cell doesn't exist
          ///   NOT CORRECTED/UPDATED
          bool GetIsNounRelatedToThisMemoryCell(int Address, string NounToCheck){
               bool Result = false;
               mapIT       = FindAddressInMap(Address,Result);
                   if(Result){
                      Result = mapIT->second.IsNounRelatedToMe(NounToCheck);}
               return Result;
          }

//====================================================================================
          /// First Checks to see if cell address given exists,
          ///  if so, checks to see if AdjectiveToCheck is associated to this cell address.
          ///  Returns true if so, false if not or cell doesn't exist
          ///   NOT CORRECTED/UPDATED
          bool GetIsAdjectiveAssociatedToThisMemoryCell(int Address, string AdjectiveToCheck){
               bool Result = false;
               mapIT       = FindAddressInMap(Address,Result);
                   if(Result){
                      Result = mapIT->second.IsAdjectiveAssociatedToMe(AdjectiveToCheck);}
               return Result;
          }

          /// Returns the Memory cell count in RightLobe memory map
          int GetRightLobeCellCount(){
              return RightLobeMemoryMap.size();
          }

          /// Returns the Memory cell count in LeftLobe memory map
          int GetLeftLobeCellCount(){
              return LeftLobeMemoryMap.size();
          }



          /**Checks to see if the NewWord exists first,
            * if so AND Update = true, Updates the data, returns Installed = false.
            * If NewWord doesn't exist,
            *Stores all the data and returns Installed = true.
           */
          bool InstallNewWord(string NewWord, char WordType, char Purpose, bool Update=false,
                              char GenderClass = 'u', string LongFormFirst = "", string LongFormSecond = "",
                              char SingularValue = 'u', int SingularRoot = 0){     //currently right side only
                if(Verbose)cout << "[c_Lobes.h::InstallNewWord]\n";
                int tmpToken     = 0;
                tmpToken         = Tokenize(NewWord);
                bool Result      = false;
                bool Installed   = false;
                string NewWordLC = MakeStringLowerCase(NewWord);
                mapIT            = FindAddressInMap(tmpToken,Result);
                if (!Result){
                            WorkingCell.InitializeAll();
                            WorkingCell.SetpCellDataString(NewWord);                        //stores raw data
                            WorkingCell.SetpCellWordType(WordType);                         //stores word type
                            WorkingCell.SetpCellPurpose(Purpose);                           //store cell purpose i.e 'w' - word
                            WorkingCell.SetpCellDataLC(NewWordLC);                          //store the raw data in lower case
                            WorkingCell.SetpCellGenderClass(GenderClass);                   //store the gender class
                            WorkingCell.SetpCellContractionLongFormFirst(LongFormFirst);    //store the contraction word long form
                            WorkingCell.SetpCellContractionLongFormSecond(LongFormSecond);  //store the contraction word long form
                            WorkingCell.SetpCellIsSingular(SingularValue);                  //store p - plural s - singular u - undetermined
                            WorkingCell.SetpCellSingularLocation(SingularRoot);             //address of root i.e. address of "color" for "colors"
                            WorkingCell.SetpCellToken(Tokenize(NewWord));                   //store the token value of the word


                            RightLobeMemoryMap.emplace(tmpToken,WorkingCell);               //Add this new cell to map.
                            Installed = true;                                               //flag this operation as happened.
                            if(Verbose)
                             cout << "Storing new word-->" << NewWord << " at " << tmpToken << " as WordType:" << WordType << " as Gender " << GenderClass << endl;
                            }
                        else
                            if(Update){
                                mapIT->second.SetpCellDataString(NewWord);
                                mapIT->second.SetpCellWordType(WordType);
                                mapIT->second.SetpCellPurpose(Purpose);
                                mapIT->second.SetpCellDataLC(NewWordLC);
                                mapIT->second.SetpCellGenderClass(GenderClass);
                                mapIT->second.SetpCellContractionLongFormFirst(LongFormFirst);
                                mapIT->second.SetpCellContractionLongFormSecond(LongFormSecond);
                                mapIT->second.SetpCellIsSingular(SingularValue);
                                mapIT->second.SetpCellSingularLocation(SingularRoot);
                                mapIT->second.SetpCellToken(Tokenize(NewWord));
                                if(Verbose)
                                    cout << "Updating -->" << NewWord << " at " << tmpToken << " as WordType:" << WordType << " as Gender " << GenderClass << endl;
                            }
                            else
                                if(Verbose)
                                 cout << "Not Storing -->" << NewWord << " at " << tmpToken << " as WordType:" << WordType << " as Gender " << GenderClass << endl;


                         return Installed;
        }


          bool CheckLinkOfTwoNounsWithAdjectives(string FirstNoun,string SecondNoun, string& VerbUsage, string MatchedAdjective[], int& MatchedCount){


                   VerbUsage           = "";
                   for(int x = 0; x<15; x++) MatchedAdjective[x] = "";
                   bool Result; Result = false;
                   int FirstNounAdjectiveCount,SecondNounAdjectiveCount;
                   int TokenFirstNoun,TokenSecondNoun;
                   int AdjectiveMatches; AdjectiveMatches = 0;
                   int AdjectivesFirstNoun[20];
                   int AdjectivesSecondNoun[20];
                   int Verbs[20];
                   TokenFirstNoun           = Tokenize(FirstNoun);
                   TokenSecondNoun          = Tokenize(SecondNoun);
                   FirstNounAdjectiveCount  = GetMemoryCellAdjectives(TokenFirstNoun,AdjectivesFirstNoun);
                   SecondNounAdjectiveCount = GetMemoryCellAdjectives(TokenSecondNoun,AdjectivesSecondNoun);

                   if((FirstNounAdjectiveCount == 0) | (SecondNounAdjectiveCount == 0)){
                      //can't match, no adjectives to compare
                      //returns empty strings and false.
                      }
                   else{
                      for(int x = 0; x < FirstNounAdjectiveCount; x++){
                        for(int y = 0; y < SecondNounAdjectiveCount; y++){
                            if(AdjectivesFirstNoun[x] == AdjectivesSecondNoun[y]){
                                Result                                = true;
                                //intMatchedAdjective                   = AdjectivesFirstNoun[x];
                                MatchedAdjective[AdjectiveMatches]    = GetMemoryCellDataLC(FirstNoun,Result);
                                //intVerbUsage                          = GetMemoryCellVerbs(intMatchedAdjective,Verbs);
                                VerbUsage                             = Verbs[0];
                                AdjectiveMatches++;}
                        } } }
                      MatchedCount = AdjectiveMatches;
                      return Result;
    }



          /// Stores Pre and Post Construction Patterns.
          ///  if doesn't exist, adds it
          ///  if does exist, updates it
          ///   CORRECTED/UPDATED - NEEDS VERIFICATION
          void SavePreAndPostPatternConstruction(string PreConstructionPattern,string PostConstructionPattern, int PostToken = 0){

                int PreToken  = Tokenize(PreConstructionPattern,false);
                if (PostToken == 0)
                    PostToken = Tokenize(PostConstructionPattern,false);
                bool Result   = false;
                mapIT         = FindAddressInMap(PreToken,Result,'l');

                if(!Result){
                    WorkingCell.InitializeAll();
                    WorkingCell.SetpCellDataString(PreConstructionPattern);
                    WorkingCell.SetpCellPurpose('1');    // pattern storage
                    WorkingCell.SetpCellToken(PreToken);
                    WorkingCell.SetpCellResolvedPattern(PostConstructionPattern);
                    LeftLobeMemoryMap.emplace(PreToken,WorkingCell);
                    mapIT  = FindAddressInMap(PostToken,Result,'l');
                    WorkingCell.InitializeAll();
                    WorkingCell.SetpCellDataString(PostConstructionPattern);
                    WorkingCell.SetpCellPurpose('1');    //pattern storage
                    WorkingCell.SetpCellToken(PostToken);
                    WorkingCell.SetpCellResolvedPattern(PostConstructionPattern);
                    LeftLobeMemoryMap.emplace(PostToken,WorkingCell);
                }
                else{
                     mapIT->second.SetpCellDataString(PreConstructionPattern);
                     mapIT->second.SetpCellPurpose('1');    // pattern storage
                     mapIT->second.SetpCellToken(PreToken);
                     mapIT->second.SetpCellResolvedPattern(PostConstructionPattern);

                     mapIT  = FindAddressInMap(PostToken,Result,'l');
                     if(Result){
                         mapIT->second.SetpCellDataString(PostConstructionPattern);
                         mapIT->second.SetpCellPurpose('1');    //pattern storage
                         mapIT->second.SetpCellToken(PostToken);
                         mapIT->second.SetpCellResolvedPattern(PostConstructionPattern);}
                         else{
                            WorkingCell.InitializeAll();
                            WorkingCell.SetpCellDataString(PostConstructionPattern);
                            WorkingCell.SetpCellPurpose('1');    //pattern storage
                            WorkingCell.SetpCellToken(PostToken);
                            WorkingCell.SetpCellResolvedPattern(PostConstructionPattern);
                            LeftLobeMemoryMap.emplace(PostToken,WorkingCell);
                         }


                }

    }

            /// Returns miniDefinition from memorycell,
            /// Returns "" if memorycell doesn't exist,
            /// can send string data or tokenized string data for address,
            /// currently rightside cells only, don't see a need for leftside yet.
            ///   OLD-DEPRECIATED VERIFY NOT IN USE!!
          string GetMemoryCellMiniDefinition(string strData = "", int Address = 0){
                bool Result = false;
                if(Address ==0) Address = Tokenize(strData);

                mapIT       = FindAddressInMap(Address,Result);
                if(Result){
                    return mapIT->second.GetpCellMiniDefinition(0);
                }
                else
                            return "";
          }

            /// Sets the memorycell minidefinition if the strSearchBase exists
            ///  send minidefinition string data in strDefinition
            ///    OLD-DEPRECIATED
          void SetMemoryCellMiniDefinition(string strSearchBase, string strDefinition){
               bool Result = false;
               CellMapIT       = FindStringInMap(strSearchBase,Result);
               if(Result){
                   CellMapIT->second.SetpCellMiniDefinition(strDefinition);
               }

          }


            /// Returns pCellSingularForm from memorycell
            ///  Returns "" null, if memorycell doesn't exist
            ///  Send owner string data in strSearchBase
            ///   currently right side cells only, don't see a need for left side yet
          string GetMemoryCellpSingularForm(string strSearchBase){
                bool Result = false;
                CellMapIT       = FindStringInMap(strSearchBase,Result);
                if(Result){
                    return CellMapIT->second.GetpSingularForm();
                }
                else
                return "";}

            /// Sets pCellIsSingular in memorycell
            ///  if memorycell exist
            ///  can send string data or tokenized string data for address
            ///  currently right side cells only, don't see a need for left side yet
          void SetMemoryCellpCellSingularForm(string strSearchBase, string SingularForm){
                bool Result = false;
                CellMapIT       = FindStringInMap(strSearchBase,Result);
                if(Result){
                    return CellMapIT->second.SetpSingularForm(SingularForm);
                }}



        void LobesStoreTheLearnedWords(){
            string Delim            = "\n";
            int    Count            = 0;
            ofstream LearnedDataFile ("LearnedData.dat", ios::out);
            if (LearnedDataFile.is_open()){
                    LearnedDataFile << "VERSION " << Version << ", file version" << Delim;
                for(CellMapIT = RightLobeCellMap.begin(); CellMapIT != RightLobeCellMap.end(); CellMapIT++ ){
                    LearnedDataFile << "Original string,"     << CellMapIT->second.GetpCellDataString() << Delim;
                    LearnedDataFile << "Lower Case string,"   << CellMapIT->second.GetpCellDataLC() << Delim;
                    LearnedDataFile << "Given name,"          << CellMapIT->second.GetpCellGivenName() << Delim;
                    LearnedDataFile << "Contraction 1st,"     << CellMapIT->second.GetpCellContractionLongFormFirst() << Delim;
                    LearnedDataFile << "Contraction 2nd,"     << CellMapIT->second.GetpCellContractionLongFormSecond() << Delim;
                    LearnedDataFile << "Cell purpose,"        << CellMapIT->second.GetpCellPurpose() << Delim;
                    LearnedDataFile << "Word Type,"           << CellMapIT->second.GetpCellWordType() << Delim;
                    LearnedDataFile << "Word tense,"          << CellMapIT->second.GetpCellWordTense() << Delim;
                    LearnedDataFile << "Secondary type,"      << CellMapIT->second.GetpCellSecondaryType() << Delim;
                    LearnedDataFile << "Alternate type,"      << CellMapIT->second.GetpCellAlternateType() << Delim;
                    LearnedDataFile << "Gender class,"        << CellMapIT->second.GetpCellGenderClass() << Delim;
                    LearnedDataFile << "Is root,"             << CellMapIT->second.GetpCellIsRoot() << Delim;
                    LearnedDataFile << "Is Locked(old is set)," << CellMapIT->second.GetpCellIsLocked() << Delim;
                    LearnedDataFile << "Is Singular,"         << CellMapIT->second.GetpCellIsSingular() << Delim;
                    LearnedDataFile << "Singular location,"   << CellMapIT->second.GetpCellSingularLocation() << Delim;
                    LearnedDataFile << "Next Verb,"           << CellMapIT->second.GetpCellNextVerb() << Delim;
                    LearnedDataFile << "Next Noun,"           << CellMapIT->second.GetpCellNextNoun() << Delim;
                    LearnedDataFile << "Token,"               << CellMapIT->second.GetpCellToken() << Delim;
                    LearnedDataFile << "Resolved Pattern,"    << CellMapIT->second.GetpCellResolvedPattern() << Delim;
                    LearnedDataFile << "Is Singular Possessive," << CellMapIT->second.GetpIsSingularPossessive() << Delim;
                    LearnedDataFile << "Is Plural Possessive,"<< CellMapIT->second.GetpIsPluralPossessive() << Delim;
                    LearnedDataFile << "Possessive Root,"     << CellMapIT->second.GetpPossessiveRoot() << Delim;
                    LearnedDataFile << "Possessive Root Type,"<< CellMapIT->second.GetpPossessiveRootType() << Delim;
                    LearnedDataFile << "Day stamp,"           << CellMapIT->second.GetpDaysOld() << Delim;

                Count = CellMapIT->second.GetpCellMiniDefinitionCount();
                LearnedDataFile << "Number of Mini Defs,"    << Count << Delim;
                for (int x = 0; x <= Count-1; x++){
                    LearnedDataFile << "Mini Def.,"          << CellMapIT->second.GetpCellMiniDefinition(x) << Delim;
                }

                Count = CellMapIT->second.GetNumberOfAdjectivesInList();
                LearnedDataFile << "Number of Adjectives,"    << Count << Delim;
                for (int x = 0; x <= Count-1; x++){
                    LearnedDataFile << "Adjective,"          << CellMapIT->second.GetAdjectiveFromList(x) << Delim;
                }
                Count = CellMapIT->second.GetNumberOfVerbsInList();
                LearnedDataFile << "Nunber of Verbs,"         << Count << Delim;
                for (int x = 0; x<=Count-1; x++){
                    LearnedDataFile << "Verb,"                << CellMapIT->second.GetVerbFromList(x) << Delim;
                }
                Count = CellMapIT->second.GetNumberOfAdverbsInList();
                LearnedDataFile << "Number of Adverbs,"       << Count << Delim;
                for (int x = 0; x<=Count-1; x++){
                    LearnedDataFile << "Adverb,"              << CellMapIT->second.GetAdverbFromList(x) << Delim;
                }
                Count = CellMapIT->second.GetNumberOfRelatedNounsInList();
                LearnedDataFile << "Related Nouns,"           << Count << Delim;
                for (int x = 0; x<=Count-1; x++){
                    LearnedDataFile << "Noun,"                << CellMapIT->second.GetNounFromList(x) << Delim;
                }
                 //++mapIT;
                }//end of loop of Words to store
            }//end if open
          LearnedDataFile.close();

          ofstream PatternFile ("PatternWorkLearned.dat", ios::out);
          if(PatternFile.is_open()){
                PatternFile << "VERSION " << Version << Delim;
                for(fileIT = LeftLobeMemoryMap.begin(); fileIT != LeftLobeMemoryMap.end(); fileIT++ ){
                    PatternFile << fileIT->second.GetpCellDataString() << Delim;
                    PatternFile << fileIT->second.GetpCellResolvedPattern() << Delim;
                }
          }
          PatternFile.close();

        }//end store memory cells


        void LobesReadTheLearnedWords(){
                //ensure datafile version is the same as our version, if not, delete the file
                string     strLineData     = "";
                int        Count           = 0;
                ifstream LearnedDataFile ("LearnedData.dat");
                string::size_type decType;
                cout << "..";
                if(LearnedDataFile.is_open()){
                        getline(LearnedDataFile,strLineData,',');
                        if(!VerifyFileVersion(strLineData)){
                            LearnedDataFile.close();
                            remove("LearnedData.dat");
                            strLineData = "";
                        }
                        else{ //skip to the data
                            getline(LearnedDataFile,strLineData);
                            getline(LearnedDataFile,strLineData,',');
                        }
                  while(strLineData != ""){
                        WorkingCell.InitializeAll();
                        getline(LearnedDataFile,strLineData);
                        WorkingCell.SetpCellDataString(strLineData);                        //set the original string data
                        getline(LearnedDataFile,strLineData,',');
                        getline(LearnedDataFile,strLineData);
                        WorkingCell.SetpCellDataLC(strLineData);                            //set the lower case string data
                        getline(LearnedDataFile,strLineData,',');
                        getline(LearnedDataFile,strLineData);
                        WorkingCell.SetpCellGivenName(strLineData);                         //set the given name string
                        getline(LearnedDataFile,strLineData,',');
                        getline(LearnedDataFile,strLineData);
                        WorkingCell.SetpCellContractionLongFormFirst(strLineData);          //set the Contraction long form first string
                        getline(LearnedDataFile,strLineData,',');
                        getline(LearnedDataFile,strLineData);
                        WorkingCell.SetpCellContractionLongFormSecond(strLineData);         //set the contraction long form second string
                        getline(LearnedDataFile,strLineData,',');
                        getline(LearnedDataFile,strLineData);
                        WorkingCell.SetpCellPurpose(strLineData[0]);                        //set the char cell purpose
                        getline(LearnedDataFile,strLineData,',');
                        getline(LearnedDataFile,strLineData);
                        WorkingCell.SetpCellWordType(strLineData[0]);                       //set the char wordtype
                        getline(LearnedDataFile,strLineData,',');
                        getline(LearnedDataFile,strLineData);
                        WorkingCell.SetpCellWordTense(strLineData[0]);                      //set the char wordtense
                        getline(LearnedDataFile,strLineData,',');
                        getline(LearnedDataFile,strLineData);
                        WorkingCell.SetpCellSecondaryType(strLineData[0]);                  //set the char secondary type
                        getline(LearnedDataFile,strLineData,',');
                        getline(LearnedDataFile,strLineData);
                        WorkingCell.SetpCellAlternateType(strLineData[0]);                  //set the char alternate type
                        getline(LearnedDataFile,strLineData,',');
                        getline(LearnedDataFile,strLineData);
                        WorkingCell.SetpCellGenderClass(strLineData[0]);                    //set the char Gender class
                        getline(LearnedDataFile,strLineData,',');
                        getline(LearnedDataFile,strLineData);
                        WorkingCell.SetpCellIsRoot(stoi(strLineData,&decType));             //set the bool cell is root
                        getline(LearnedDataFile,strLineData,',');
                        getline(LearnedDataFile,strLineData);
                        WorkingCell.SetpCellIsLocked(stoi(strLineData,&decType));           //set the bool pcellisSet
                        getline(LearnedDataFile,strLineData,',');
                        getline(LearnedDataFile,strLineData);
                        WorkingCell.SetpCellIsSingular(strLineData[0]);                     //set the char cell is singular
                        getline(LearnedDataFile,strLineData,',');
                        getline(LearnedDataFile,strLineData);
                        WorkingCell.SetpCellSingularLocation(stoi(strLineData,&decType));   //set the int singular location
                        getline(LearnedDataFile,strLineData,',');
                        getline(LearnedDataFile,strLineData);
                        WorkingCell.SetpCellNextVerb(stoi(strLineData,&decType));           //set the int next verb location
                        getline(LearnedDataFile,strLineData,',');
                        getline(LearnedDataFile,strLineData);
                        WorkingCell.SetpCellNextNoun(stoi(strLineData,&decType));           //set the int next noun location
                        getline(LearnedDataFile,strLineData,',');
                        getline(LearnedDataFile,strLineData);
                        WorkingCell.SetpCellToken(stoi(strLineData,&decType));              //set the int Token
                        getline(LearnedDataFile,strLineData,',');
                        getline(LearnedDataFile,strLineData);
                        WorkingCell.SetpCellResolvedPattern(strLineData);                    //set the int pointer to next pattern
                        getline(LearnedDataFile,strLineData,',');
                        getline(LearnedDataFile,strLineData);
                        WorkingCell.SetpIsSingularPossessive(stoi(strLineData,&decType));    //set singular possessive
                        getline(LearnedDataFile,strLineData,',');
                        getline(LearnedDataFile,strLineData);
                        WorkingCell.SetpIsPluralPossessive(stoi(strLineData,&decType));      //set plural possessive
                        getline(LearnedDataFile,strLineData,',');
                        getline(LearnedDataFile,strLineData);
                        WorkingCell.SetpPossessiveRoot(strLineData);                        //set Possessive root
                        getline(LearnedDataFile,strLineData,',');
                        getline(LearnedDataFile,strLineData);
                        WorkingCell.SetpPossessiveRootType(strLineData[0]);                 // set possessive root type
                        getline(LearnedDataFile,strLineData,',');
                        getline(LearnedDataFile,strLineData);
                        WorkingCell.SetpDaysOld(stoi(strLineData,&decType));                //set day stamp

                        getline(LearnedDataFile,strLineData,',');
                        getline(LearnedDataFile,strLineData);
                        Count = stoi(strLineData,&decType);                                  //got number of mini defs
                        //count = mini def count
                        for(int x = 0; x< Count; x++){
                            getline(LearnedDataFile,strLineData,',');
                            getline(LearnedDataFile,strLineData);                           //next store requires a string
                            WorkingCell.SetpCellMiniDefinition(strLineData);
                        }//end for mini def loop


                        getline(LearnedDataFile,strLineData,',');
                        getline(LearnedDataFile,strLineData);
                        Count = stoi(strLineData,&decType);                                  //got number of adjectives
                        //count = adjective count
                        for(int x = 0; x< Count; x++){
                            getline(LearnedDataFile,strLineData,',');
                            getline(LearnedDataFile,strLineData);                           //next store requires a string
                            WorkingCell.AssociateAdjectiveInMap(strLineData);
                        }//end for adjectives loop
                        getline(LearnedDataFile,strLineData,',');
                        getline(LearnedDataFile,strLineData);
                        Count = stoi(strLineData,&decType);
                        //Count = verb count
                        for(int x = 0; x< Count; x++){
                            getline(LearnedDataFile,strLineData,',');
                            getline(LearnedDataFile,strLineData);
                            WorkingCell.AssociateVerbToAdjectiveInMap("",strLineData);
                        }//end for verbs loop
                        getline(LearnedDataFile,strLineData,',');
                        getline(LearnedDataFile,strLineData);
                        Count = stoi(strLineData,&decType);
                        //Count = adverb count
                        for(int x = 0; x < Count; x++){
                            getline(LearnedDataFile,strLineData,',');
                            getline(LearnedDataFile,strLineData);
                            WorkingCell.AssociateAdverbToVerbInMap(strLineData,"");
                        }//end for adverbs loop
                        getline(LearnedDataFile,strLineData,',');
                        getline(LearnedDataFile,strLineData);
                        Count = stoi(strLineData,&decType);
                        //Count = Noun count
                        for(int x = 0; x < Count; x++){
                            getline(LearnedDataFile,strLineData,',');
                            getline(LearnedDataFile,strLineData);
                        //if(WorkingCell.GetpCellDataLC() == "dog") cout << " Dog related noun =" << strLineData << endl;
                            WorkingCell.AssociateNounInMap(strLineData);
                        }//end for nouns loop
                    getline(LearnedDataFile,strLineData,',');
                    RightLobeMemoryMap.emplace(WorkingCell.GetpCellToken(),WorkingCell);
                    RightLobeCellMap.emplace(WorkingCell.GetpCellDataString(),WorkingCell);

                    }//end while not empty loop

                }//end if open
              LearnedDataFile.close();
              cout << "..";

              ifstream PatternFile ("PatternWorkLearned.dat");
              string SecondLineData = "";
              if(PatternFile.is_open()){
                    getline(LearnedDataFile,strLineData);
                    //if(strLineData != "VERSION " + Version){
                    if(!VerifyFileVersion(strLineData)){
                        PatternFile.close();
                        remove("PatternWorkLearned.dat");
                    }
                    else{
                        getline(LearnedDataFile,strLineData);
                    }
                    while(strLineData != ""){
                        getline(LearnedDataFile,SecondLineData);
                        SavePreAndPostPatternConstruction(strLineData,"",stoi(SecondLineData,&decType));
                        getline(LearnedDataFile,strLineData);
                    }//end while loop
              }//end Pattern file
              PatternFile.close();
            cout << endl;
        }//end function

};


#endif // C_LOBES_H
