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
   pXLIT[(BYTE)'À'] = 'A';
   pXLIT[(BYTE)'Á'] = 'B';
   pXLIT[(BYTE)'Â'] = 'V';
   pXLIT[(BYTE)'Ã'] = 'G';
   pXLIT[(BYTE)'Ä'] = 'D';
   pXLIT[(BYTE)'Å'] = 'E';
   pXLIT[(BYTE)'¨'] = 'E';
   pXLIT[(BYTE)'Æ'] = 'J';
   pXLIT[(BYTE)'Ç'] = 'Z';
   pXLIT[(BYTE)'È'] = 'I';
   pXLIT[(BYTE)'É'] = 'I';
   pXLIT[(BYTE)'Ê'] = 'K';
   pXLIT[(BYTE)'Ë'] = 'L';
   pXLIT[(BYTE)'Ì'] = 'M';
   pXLIT[(BYTE)'Í'] = 'N';
   pXLIT[(BYTE)'Î'] = 'O';
   pXLIT[(BYTE)'Ï'] = 'P';
   pXLIT[(BYTE)'Ð'] = 'R';
   pXLIT[(BYTE)'Ñ'] = 'S';
   pXLIT[(BYTE)'Ò'] = 'T';
   pXLIT[(BYTE)'Ó'] = 'U';
   pXLIT[(BYTE)'Ô'] = 'F';
   pXLIT[(BYTE)'Õ'] = 'H';
   pXLIT[(BYTE)'Ö'] = 'C';
   pXLIT[(BYTE)'×'] = 'HC';   // Reverse order !
   pXLIT[(BYTE)'Ø'] = 'HS';   // Reverse order !
   pXLIT[(BYTE)'Ù'] = 'CS';   // Reverse order !
   pXLIT[(BYTE)'Ú'] = -1;
   pXLIT[(BYTE)'Û'] = 'Y';
   pXLIT[(BYTE)'Ü'] = -1;
   pXLIT[(BYTE)'Ý'] = 'E';
   pXLIT[(BYTE)'Þ'] = 'UI';   // Reverse order !
   pXLIT[(BYTE)'ß'] = 'AI';   // Reverse order !

   // Cyrillic Lower case
   pXLIT[(BYTE)'à'] = 'a';
   pXLIT[(BYTE)'á'] = 'b';
   pXLIT[(BYTE)'â'] = 'v';
   pXLIT[(BYTE)'ã'] = 'g';
   pXLIT[(BYTE)'ä'] = 'd';
   pXLIT[(BYTE)'å'] = 'e';
   pXLIT[(BYTE)'¸'] = 'e';
   pXLIT[(BYTE)'æ'] = 'j';
   pXLIT[(BYTE)'ç'] = 'z';
   pXLIT[(BYTE)'è'] = 'i';
   pXLIT[(BYTE)'é'] = 'i';
   pXLIT[(BYTE)'ê'] = 'k';
   pXLIT[(BYTE)'ë'] = 'l';
   pXLIT[(BYTE)'ì'] = 'm';
   pXLIT[(BYTE)'í'] = 'n';
   pXLIT[(BYTE)'î'] = 'o';
   pXLIT[(BYTE)'ï'] = 'p';
   pXLIT[(BYTE)'ð'] = 'r';
   pXLIT[(BYTE)'ñ'] = 's';
   pXLIT[(BYTE)'ò'] = 't';
   pXLIT[(BYTE)'ó'] = 'u';
   pXLIT[(BYTE)'ô'] = 'f';
   pXLIT[(BYTE)'õ'] = 'h';
   pXLIT[(BYTE)'ö'] = 'c';
   pXLIT[(BYTE)'÷'] = 'hc';   // Reverse order !
   pXLIT[(BYTE)'ø'] = 'hs';   // Reverse order !
   pXLIT[(BYTE)'ù'] = 'cs';   // Reverse order !
   pXLIT[(BYTE)'ú'] = -1;
   pXLIT[(BYTE)'û'] = 'y';
   pXLIT[(BYTE)'ü'] = -1;
   pXLIT[(BYTE)'ý'] = 'e';
   pXLIT[(BYTE)'þ'] = 'ui';   // Reverse order !
   pXLIT[(BYTE)'ÿ'] = 'ai';   // Reverse order !

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
