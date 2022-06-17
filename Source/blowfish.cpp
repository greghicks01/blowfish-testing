//---------------------------------------------------------------------------
/*
 *                     Copyright © 2007
 *                     Mr Gregory Hicks
 *
 *                 Software Project Engineer
 *                 Mr Gregory Hicks BIT CQU
 *
 *  $Revision: 1.2 $
 *
 *  $Log: blowfish.cpp $
 *  Revision 1.2  2007/08/22 03:31:36  Administrator
 *  updated to correct conversions
 *  ,
 *
 *  Revision 1.1  2007/08/21 03:45:55  Administrator
 *  Initial revision
 *
 *
 *
*/

// blowfish.cpp   C++ class implementation of the BLOWFISH encryption algorithm
// _THE BLOWFISH ENCRYPTION ALGORITHM_
// by Bruce Schneier
// Revised code--3/20/94
// Converted to C++ class 5/96, Jim Conger

#pragma hdrstop

#include "blowfish.h"

#include "blowfish.h2"	// holds the random digit tables
//---------------------------------------------------------------------------

#pragma package(smart_init)


#define S(x,i) (SBoxes[i][x.w.byte##i])
#define bf_F(x) (((S(x,0) + S(x,1)) ^ S(x,2)) + S(x,3))
#define ROUND(a,b,n) (a.dword ^= bf_F(b) ^ PArray[n])

//---------------------------------------------------------------------------
/*
 * Purpose:
 * Accepts:
 * Returns:
*/
__fastcall  TBlowFish::TBlowFish ( AnsiString key ) : Inherited ( NULL )
{
 	PArray = new DWORD [18] ;
 	SBoxes = new DWORD [4][256] ;

        Fkey    = NULL ;
        pInput  = NULL ; 
        pOutput = NULL ;

        LoadByteArray ( Fkey , FKSze , key , false ) ; 

        Initialize ( Fkey , FKSze ) ;
}

//---------------------------------------------------------------------------
/*
 * Purpose:
 * Accepts:
 * Returns:
*/


__fastcall  TBlowFish::~TBlowFish ()
{
	delete PArray ;
	delete [] SBoxes ;
}

//---------------------------------------------------------------------------
/*
 * Purpose:
 * Accepts:
 * Returns:
*/

// the low level (private) encryption function
void __fastcall  TBlowFish::Blowfish_encipher (DWORD *xl, DWORD *xr)
{
	union aword  Xl, Xr ;

	Xl.dword = *xl ;
	Xr.dword = *xr ;

	Xl.dword ^= PArray [0];
	ROUND (Xr, Xl, 1) ;  ROUND (Xl, Xr, 2) ;
	ROUND (Xr, Xl, 3) ;  ROUND (Xl, Xr, 4) ;
	ROUND (Xr, Xl, 5) ;  ROUND (Xl, Xr, 6) ;
	ROUND (Xr, Xl, 7) ;  ROUND (Xl, Xr, 8) ;
	ROUND (Xr, Xl, 9) ;  ROUND (Xl, Xr, 10) ;
	ROUND (Xr, Xl, 11) ; ROUND (Xl, Xr, 12) ;
	ROUND (Xr, Xl, 13) ; ROUND (Xl, Xr, 14) ;
	ROUND (Xr, Xl, 15) ; ROUND (Xl, Xr, 16) ;
	Xr.dword ^= PArray [17] ;

	*xr = Xl.dword ;
	*xl = Xr.dword ;
}
//---------------------------------------------------------------------------
/*
 * Purpose:
 * Accepts:
 * Returns:
*/

// the low level (private) decryption function
void __fastcall  TBlowFish::Blowfish_decipher (DWORD *xl, DWORD *xr)
{
   union aword  Xl ;
   union aword  Xr ;

   Xl.dword = *xl ;
   Xr.dword = *xr ;

   Xl.dword ^= PArray [17] ;
   ROUND (Xr, Xl, 16) ;  ROUND (Xl, Xr, 15) ;
   ROUND (Xr, Xl, 14) ;  ROUND (Xl, Xr, 13) ;
   ROUND (Xr, Xl, 12) ;  ROUND (Xl, Xr, 11) ;
   ROUND (Xr, Xl, 10) ;  ROUND (Xl, Xr, 9) ;
   ROUND (Xr, Xl, 8) ;   ROUND (Xl, Xr, 7) ;
   ROUND (Xr, Xl, 6) ;   ROUND (Xl, Xr, 5) ;
   ROUND (Xr, Xl, 4) ;   ROUND (Xl, Xr, 3) ;
   ROUND (Xr, Xl, 2) ;   ROUND (Xl, Xr, 1) ;
   Xr.dword ^= PArray[0];

   *xl = Xr.dword;
   *xr = Xl.dword;
}

//---------------------------------------------------------------------------
/*
 * Purpose: Constructs the enctryption sieve
 * Accepts: Key as array of bytes, keybytes in length
 * Returns: NIL
*/
void __fastcall  TBlowFish::Initialize ( BYTE * key , int keybytes )
{
	int  		i, j ;
	DWORD  		data, datal, datar ;
	union aword temp ;

	// first fill arrays from data tables
	for (i = 0 ; i < 18 ; i++)
		PArray [i] = bf_P [i] ;

	for (i = 0 ; i < 4 ; i++)
	{
	 	for (j = 0 ; j < 256 ; j++)
	 		SBoxes [i][j] = bf_S [i][j] ;
	}


	j = 0 ;
	for (i = 0 ; i < NPASS + 2 ; ++i)
	{
		temp.dword = 0 ;
		temp.w.byte0 = key[j];
		temp.w.byte1 = key[(j+1) % keybytes] ;
		temp.w.byte2 = key[(j+2) % keybytes] ;
		temp.w.byte3 = key[(j+3) % keybytes] ;
		data = temp.dword ;
		PArray [i] ^= data ;
		j = (j + 4) % keybytes ;
	}

	datal = 0 ;
	datar = 0 ;

	for (i = 0 ; i < NPASS + 2 ; i += 2)
	{
		Blowfish_encipher (&datal, &datar) ;
		PArray [i] = datal ;
		PArray [i + 1] = datar ;
	}

	for (i = 0 ; i < 4 ; ++i)
	{
		for (j = 0 ; j < 256 ; j += 2)
		{
		  Blowfish_encipher (&datal, &datar) ;
		  SBoxes [i][j] = datal ;
		  SBoxes [i][j + 1] = datar ;
		}
	}
}

//---------------------------------------------------------------------------
/*
 * Purpose:
 * Accepts:
 * Returns:
*/

// get output length, which must be even MOD 8
DWORD __fastcall  TBlowFish::GetOutputLength ( DWORD lInputLong )
{
	DWORD 	lVal ;

	lVal = lInputLong % 8 ;	// find out if uneven number of bytes at the end
	if (lVal != 0)
		return lInputLong + 8 - lVal ;
	else
		return lInputLong ;
}

//---------------------------------------------------------------------------
/*
 * Purpose:
 * Accepts:
 * Returns:
*/

// Encode pIntput into pOutput.  Input length in lSize.  Returned value
// is length of output which will be even MOD 8 bytes.  Input buffer and
// output buffer can be the same, but be sure buffer length is even MOD 8.
DWORD __fastcall  TBlowFish::Encode ( BYTE * pInput , BYTE * pOutput , int lSize )
{
	DWORD 	lCount, lOutSize, lGoodBytes ;
	BYTE	*pi, *po ;
	int		i, j ;
	int		SameDest = (pInput == pOutput ? 1 : 0) ;

	lOutSize = GetOutputLength (lSize) ;
	for (lCount = 0 ; lCount < lOutSize ; lCount += 8)
	{
		if (SameDest)	// if encoded data is being written into input buffer
		{
                        // warning comparing signed and unsigned - safely ignore here
                        #pragma warn -8012
		 	if (lCount < lSize - 7)	// if not dealing with uneven bytes at end
                        #pragma warn .8012
		 	{
		 	 	Blowfish_encipher ((DWORD *) pInput,
		 	 		(DWORD *) (pInput + 4)) ;
		 	}
		 	else	// pad end of data with null bytes to complete encryption
		 	{
				po = pInput + lSize ;	// point at byte past the end of actual data
				j = (int) (lOutSize - lSize) ;	// number of bytes to set to null
				for (i = 0 ; i < j ; i++)
					*po++ = 0 ;
		 	 	Blowfish_encipher ((DWORD *) pInput,
		 	 		(DWORD *) (pInput + 4)) ;
		 	}
		 	pInput += 8 ;
		}
		else 	// output buffer not equal to input buffer, so must copy
		{       // input to output buffer prior to encrypting

                        // warning comparing signed and unsigned - safely ignore here
                        #pragma warn -8012
		 	if (lCount < lSize - 7)	// if not dealing with uneven bytes at end
                        #pragma warn .8012
		 	{
		 		pi = pInput ;
		 		po = pOutput ;
		 		for (i = 0 ; i < 8 ; i++)
                                        // copy bytes to output
		 			*po++ = *pi++ ;
		 	 	Blowfish_encipher ((DWORD *) pOutput,	// now  encrypt them
		 	 		(DWORD *) (pOutput + 4)) ;
		 	}
		 	else		// pad end of data with null bytes to complete encryption
		 	{
		 		lGoodBytes = lSize - lCount ;	// number of remaining data bytes
		 		po = pOutput ;
		 		for (i = 0 ; i < (int) lGoodBytes ; i++)
		 			*po++ = *pInput++ ;
		 		for (j = i ; j < 8 ; j++)
		 			*po++ = 0 ;
		 	 	Blowfish_encipher ((DWORD *) pOutput,
		 	 		(DWORD *) (pOutput + 4)) ;
		 	}
		 	pInput += 8 ;
		 	pOutput += 8 ;
		}
	}
	return lOutSize ;
}

//---------------------------------------------------------------------------
/*
 * Purpose:
 * Accepts:
 * Returns:
*/

// Decode pIntput into pOutput.  Input length in lSize.  Input  buffer and
// output buffer can be the same, but be sure buffer length is even MOD 8.
void __fastcall  TBlowFish::Decode ( BYTE * pInput , BYTE * pOutput , int lSize )
{
	DWORD 	lCount ;
	BYTE	*pi, *po ;
	int		i ;
	int		SameDest = (pInput == pOutput ? 1 : 0) ;

        // warning comparing signed and unsigned - safely ignore here
        #pragma warn -8012
	for (lCount = 0 ; lCount < lSize ; lCount += 8) 
        #pragma warn .8012
	{
		if (SameDest)	// if encoded data is being written into input buffer
		{
	 	 	Blowfish_decipher ((DWORD *) pInput,
	 	 		(DWORD *) (pInput + 4)) ;
		 	pInput += 8 ;
		}
		else 			// output buffer not equal to input buffer
		{               // so copy input to output before decoding
	 		pi = pInput ;
	 		po = pOutput ;
	 		for (i = 0 ; i < 8 ; i++)
	 			*po++ = *pi++ ;
	 	 	Blowfish_decipher ((DWORD *) pOutput,
	 	 		(DWORD *) (pOutput + 4)) ;
		 	pInput += 8 ;
		 	pOutput += 8 ;
		}
	}
}  
//---------------------------------------------------------------------------
/*
 * Purpose:
 * Accepts:
 * Returns:
*/

void __fastcall TBlowFish::Setcypher(AnsiString value)
{
        //TODO: Add your source code here
        BYTE * pin = NULL;
        LoadByteArray ( pin , FSize , value , true ) ;
        Encode ( pin  , pin , FSize ) ;
        Fcypher = UnloadByteArray ( pin , FSize ) ;
        delete [] pin ;
}

//---------------------------------------------------------------------------
/*
 * Purpose:
 * Accepts:
 * Returns:
*/

AnsiString __fastcall TBlowFish::Getcypher()
{
        return Fcypher;
}

//---------------------------------------------------------------------------
/*
 * Purpose:
 * Accepts:
 * Returns:
*/

void __fastcall TBlowFish::Setdecyph(AnsiString value)
{
        //TODO: Add your source code here
        BYTE * pin = NULL ;
        LoadByteArray ( pin , FSize , value , true ) ;
        Decode ( pin  , pin , FSize ) ;
        Fdecyph = UnloadByteArray ( pin , FSize ) ;
        delete [] pin ;
}

//---------------------------------------------------------------------------
/*
 * Purpose:
 * Accepts:
 * Returns:
*/

AnsiString __fastcall TBlowFish::Getdecyph()
{
        return Fdecyph;
}

//---------------------------------------------------------------------------
/*
 * Purpose:
 * Accepts:
 * Returns:
*/
int __fastcall TBlowFish::HexToInt ( AnsiString v )
{
        //TODO: Add your source code here
        AnsiString hex = "0123456789ABCDEF" ;
        int start = 1 , stop = v.Length() , vInt = 0 ;

        while ( start < stop )
        {
                char t        = v [ start ] ;
                v [ start++ ] = v [ stop ] ;
                v [ stop--  ] = t ;
        }

        for ( int x = 0 ; x < v.Length() ; x++ )  
                vInt += ( hex.Pos( UpperCase ( v [ x + 1 ] ) ) - 1 ) << ( 4 * x ) ;

        return vInt ;
}

//---------------------------------------------------------------------------
/*
 * Purpose:
 * Accepts:
 * Returns:
*/

void __fastcall TBlowFish::LoadByteArray ( BYTE *& b , int & s , AnsiString v , bool padding)
{
        //TODO: Add your source code here
        AnsiString a = v ;

        FStrSize = a.Length() ;

        if ( FStrSize % 2 != 0 )
                a+= "0" ;

        int bytesize = a.Length()/2;

        if ( padding )
        {
                s = GetOutputLength ( bytesize ) ;
                if ( a.Length() % ( s * 2 ) != 0 )
                        a += AnsiString::StringOfChar('0' , ( s * 2 ) - ( bytesize * 2 ) ) ;
        }
        else
        {
                s =  bytesize ;
        }

        if ( b )
                delete [] &b ;

        b = new BYTE [ s ] ;

        for ( int x = 0 ; x < s ; x++  )
                b [ x ] = HexToInt ( a.SubString ( x * 2 + 1 , 2 ) ) ;
}

//---------------------------------------------------------------------------
/*
 * Purpose:
 * Accepts:
 * Returns:
*/

AnsiString __fastcall TBlowFish::UnloadByteArray ( BYTE * b , int s )
{
        //TODO: Add your source code here
        AnsiString a ;
        if ( b )
        {
                for ( int x = 0 ; x < s ; x++ )
                        a += IntToHex ( b [ x ] , 2 ) ;
        }
        return a ; //.SubString ( 1 , FStrSize ) ;
}

AnsiString __fastcall TBlowFish::BFE(AnsiString v)
{
        //TODO: Add your source code here
        cypher = v ;
        return cypher ;
}

AnsiString __fastcall TBlowFish::BFD(AnsiString v)
{
        //TODO: Add your source code here
        decyph = v ;
        return decyph ;
}
