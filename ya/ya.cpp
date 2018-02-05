/* ******************************************************************** **
** @@ For Yandex mail filename transliterator
** @  Copyrt : 
** @  Author : 
** @  Modify :
** @  Update :
** @  Dscr   :
** ******************************************************************** */

/* ******************************************************************** **
**                uses pre-compiled headers
** ******************************************************************** */

#include <stdafx.h>

#include "..\shared\file_find.h"

/* ******************************************************************** **
** @@                   internal defines
** ******************************************************************** */

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#ifdef NDEBUG
#pragma optimize("gsy",on)
#pragma comment(linker,"/FILEALIGN:512 /MERGE:.rdata=.text /MERGE:.data=.text /SECTION:.text,EWR /IGNORE:4078")
#endif 

#define ASCII_SIZE      (256)

/* ******************************************************************** **
** @@                   internal prototypes
** ******************************************************************** */

/* ******************************************************************** **
** @@                   external global variables
** ******************************************************************** */

extern DWORD   dwKeepError = 0;

/* ******************************************************************** **
** @@                   static global variables
** ******************************************************************** */
                  
static int  pXLIT[ASCII_SIZE];

/* ******************************************************************** **
** @@                   real code
** ******************************************************************** */

/* ******************************************************************** **
** @@ Error()
** @  Copyrt :
** @  Author :
** @  Modify :
** @  Modify :
** @  Notes  :
** ******************************************************************** */

void Error()
{
   char*    pBuf = NULL;

   FormatMessage
   (
      FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,   // Source and Processing Options
      NULL,                                                          // Pointer to Message Source
      dwKeepError,                                                   // Requested Message Identifier
      MAKELANGID(LANG_NEUTRAL,SUBLANG_DEFAULT),                      // Language Identifier for Requested Message
      (LPTSTR)&pBuf,                                                 // Pointer to Message Buffer
      0,                                                             // Maximum Size of Message Buffer
      NULL                                                           // Address of Array of Message Inserts
   );

   MessageBox(GetActiveWindow(),pBuf,"Error",MB_OK | MB_ICONSTOP);

   LocalFree(pBuf);
}

/* ******************************************************************** **
** @@ Cyrillic_2_Latin()
** @  Copyrt : 
** @  Author : 
** @  Modify :
** @  Update : 
** @  Notes  :
** ******************************************************************** */

static void Cyrillic_2_Latin(char* pszName,const char* const pszFile)
{
   *pszName = 0;  // Reset

   int   iLen = strlen(pszFile);

   for (int ii = 0; ii < iLen; ++ii)
   {
      int   iRet = pXLIT[(BYTE)pszFile[ii]];

      if (iRet != -1)
      {
         strcat(pszName,(char*)&iRet); 
      }
   }
}

/* ******************************************************************** **
** @@ ShowHelp()
** @  Copyrt : 
** @  Author : 
** @  Modify :
** @  Update :
** @  Notes  :
** ******************************************************************** */

void ShowHelp()
{
   const char  pszCopyright[] = "-*-   Ya 1.0   *   (c) Gazlan, 2009   -*-";
   const char  pszDescript [] = "For Yandex mail filename transliterator";
   const char  pszE_Mail   [] = "complains_n_suggestions direct to gazlan@yandex.ru";

   printf("%s\n\n",pszCopyright);
   printf("%s\n\n",pszDescript);
   printf("Usage: ya.com [wildcards]\n\n");
   printf("%s\n",pszE_Mail);
}

/* ******************************************************************** **
** @@ main()
** @  Copyrt : 
** @  Author : 
** @  Modify :
** @  Update : 
** @  Notes  :
** ******************************************************************** */

int main(int argc,char** argv)
{
   if (argc < 2)
   {
      ShowHelp();
      return 0;
   }

   if (argc == 2)
   {
      if ((!strcmp(argv[1],"?")) || (!strcmp(argv[1],"/?")) || (!strcmp(argv[1],"-?")) || (!stricmp(argv[1],"/h")) || (!stricmp(argv[1],"-h")))
      {
         ShowHelp();
         return 0;
      }
   }
   
   // Initialize
   for (int ii = 0; ii < ASCII_SIZE; ++ii)
   {
      pXLIT[ii] = ii;
   }

   // Space
   pXLIT[0x20] = '_';


   // Hi ASCII
   // Do nothing !                         
   for (int jj = 0x80; jj <= 0xBF; ++jj)
   {
      pXLIT[jj] = -1;
   }

   // Ukrainian Upper Case 
   pXLIT[0xB2] = 'I';
   pXLIT[0xA5] = 'G';
   pXLIT[0xAA] = 'E';
   pXLIT[0xAF] = 'I';

   // Ukrainian Lower Case 
   pXLIT[0xB3] = 'i';
   pXLIT[0xB4] = 'g';
   pXLIT[0xBA] = 'e';
   pXLIT[0xBF] = 'i';

   // Cyrillic Upper case
   pXLIT[(BYTE)'�'] = 'A';
   pXLIT[(BYTE)'�'] = 'B';
   pXLIT[(BYTE)'�'] = 'V';
   pXLIT[(BYTE)'�'] = 'G';
   pXLIT[(BYTE)'�'] = 'D';
   pXLIT[(BYTE)'�'] = 'E';
   pXLIT[(BYTE)'�'] = 'E';
   pXLIT[(BYTE)'�'] = 'J';
   pXLIT[(BYTE)'�'] = 'Z';
   pXLIT[(BYTE)'�'] = 'I';
   pXLIT[(BYTE)'�'] = 'I';
   pXLIT[(BYTE)'�'] = 'K';
   pXLIT[(BYTE)'�'] = 'L';
   pXLIT[(BYTE)'�'] = 'M';
   pXLIT[(BYTE)'�'] = 'N';
   pXLIT[(BYTE)'�'] = 'O';
   pXLIT[(BYTE)'�'] = 'P';
   pXLIT[(BYTE)'�'] = 'R';
   pXLIT[(BYTE)'�'] = 'S';
   pXLIT[(BYTE)'�'] = 'T';
   pXLIT[(BYTE)'�'] = 'U';
   pXLIT[(BYTE)'�'] = 'F';
   pXLIT[(BYTE)'�'] = 'H';
   pXLIT[(BYTE)'�'] = 'C';
   pXLIT[(BYTE)'�'] = 'HC';   // Reverse order !
   pXLIT[(BYTE)'�'] = 'HS';   // Reverse order !
   pXLIT[(BYTE)'�'] = 'CS';   // Reverse order !
   pXLIT[(BYTE)'�'] = -1;
   pXLIT[(BYTE)'�'] = 'Y';
   pXLIT[(BYTE)'�'] = -1;
   pXLIT[(BYTE)'�'] = 'E';
   pXLIT[(BYTE)'�'] = 'UI';   // Reverse order !
   pXLIT[(BYTE)'�'] = 'AI';   // Reverse order !

   // Cyrillic Lower case
   pXLIT[(BYTE)'�'] = 'a';
   pXLIT[(BYTE)'�'] = 'b';
   pXLIT[(BYTE)'�'] = 'v';
   pXLIT[(BYTE)'�'] = 'g';
   pXLIT[(BYTE)'�'] = 'd';
   pXLIT[(BYTE)'�'] = 'e';
   pXLIT[(BYTE)'�'] = 'e';
   pXLIT[(BYTE)'�'] = 'j';
   pXLIT[(BYTE)'�'] = 'z';
   pXLIT[(BYTE)'�'] = 'i';
   pXLIT[(BYTE)'�'] = 'i';
   pXLIT[(BYTE)'�'] = 'k';
   pXLIT[(BYTE)'�'] = 'l';
   pXLIT[(BYTE)'�'] = 'm';
   pXLIT[(BYTE)'�'] = 'n';
   pXLIT[(BYTE)'�'] = 'o';
   pXLIT[(BYTE)'�'] = 'p';
   pXLIT[(BYTE)'�'] = 'r';
   pXLIT[(BYTE)'�'] = 's';
   pXLIT[(BYTE)'�'] = 't';
   pXLIT[(BYTE)'�'] = 'u';
   pXLIT[(BYTE)'�'] = 'f';
   pXLIT[(BYTE)'�'] = 'h';
   pXLIT[(BYTE)'�'] = 'c';
   pXLIT[(BYTE)'�'] = 'hc';   // Reverse order !
   pXLIT[(BYTE)'�'] = 'hs';   // Reverse order !
   pXLIT[(BYTE)'�'] = 'cs';   // Reverse order !
   pXLIT[(BYTE)'�'] = -1;
   pXLIT[(BYTE)'�'] = 'y';
   pXLIT[(BYTE)'�'] = -1;
   pXLIT[(BYTE)'�'] = 'e';
   pXLIT[(BYTE)'�'] = 'ui';   // Reverse order !
   pXLIT[(BYTE)'�'] = 'ai';   // Reverse order !

   FindFile   FF;
   
   FF.SetMask(argv[1]);

   while (FF.Fetch())
   {
      if ((FF._w32fd.dwFileAttributes | FILE_ATTRIBUTE_NORMAL) && !(FF._w32fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
      {
         char     pszBackName[_MAX_PATH];
         char     pszDrive   [_MAX_DRIVE];
         char     pszDir     [_MAX_DIR];
         char     pszFName   [_MAX_FNAME];
         char     pszExt     [_MAX_EXT];

         _splitpath(FF._w32fd.cFileName,pszDrive,pszDir,pszFName,pszExt);

         char  pszName[MAX_PATH + 1];

         Cyrillic_2_Latin(pszName,pszFName);

         _makepath(pszBackName,pszDrive,pszDir,pszName,pszExt);

         if (!MoveFile(FF._w32fd.cFileName,pszBackName))
         {
            dwKeepError = GetLastError();

            Error();
         }
      }
   }

   return 0;
}

/* ******************************************************************** **
** @@                   End of File
** ******************************************************************** */
