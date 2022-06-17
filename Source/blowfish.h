//---------------------------------------------------------------------------

#ifndef blowfishH
#define blowfishH
//---------------------------------------------------------------------------
// blowfish.h     interface file for blowfish.cpp
// _THE BLOWFISH ENCRYPTION ALGORITHM_
// by Bruce Schneier
// Revised code--3/20/94
// Converted to C++ class 5/96, Jim Conger

#include <vcl.h>

#define MAXKEYBYTES 	56		// 448 bits max
#define NPASS           16		// SBox passes

#define DWORD  		unsigned long
#define WORD  		unsigned short
#define BYTE  		unsigned char

class EBlowFish : public Exception
{
public:
        EBlowFish( AnsiString message ) : Exception( message ){} ;
};                                         

class PACKAGE TBlowFish : public TComponent
{
typedef TComponent Inherited ;

private:                              
        BYTE       * Fkey     ,  // contains the key
                   * pInput   ,  // input data
                   * pOutput  ;  // output data
        int          FSize    ,  // pInput and POutput Size
                     FKSze    ;  // key Size

	DWORD 	   * PArray   ;

        AnsiString   Fcypher  , // encoded string
                     Fdecyph  ;  // decoded string
        int          FStrSize ;

	DWORD      ( * SBoxes ) [ 256 ] ;
        
	void       __fastcall Initialize        ( BYTE * key , int len )    ;

	DWORD      __fastcall GetOutputLength   ( DWORD lInputLong )        ;

	DWORD      __fastcall Encode            ( BYTE * pin , BYTE * pout , int lSize ) ;
	void       __fastcall Decode            ( BYTE * pin , BYTE * pout , int lSize ) ;

	void       __fastcall Blowfish_encipher ( DWORD * xl , DWORD * xr ) ;
	void       __fastcall Blowfish_decipher ( DWORD * xl , DWORD * xr ) ;

        void       __fastcall Setcypher         ( AnsiString v ) ;  // data to be encoded
        AnsiString __fastcall Getcypher         ( ) ;

        void       __fastcall Setdecyph         ( AnsiString v ) ;  // data to be decoded
        AnsiString __fastcall Getdecyph         ( ) ;

        // convert string to BYTE array
        void       __fastcall LoadByteArray     ( BYTE *& b , int &sz , AnsiString s , bool padding ) ;
        AnsiString __fastcall UnloadByteArray   ( BYTE * b , int sz ) ;

protected:

public:
                __fastcall  TBlowFish ( AnsiString key ) ;
        virtual __fastcall ~TBlowFish ( ) ;  

        static int __fastcall HexToInt          ( AnsiString v ) ;
        AnsiString __fastcall BFE(AnsiString v);
        AnsiString __fastcall BFD(AnsiString v);  // conversion utility

__published:
        __property AnsiString cypher  = { read=Getcypher, write=Setcypher };
        __property AnsiString decyph  = { read=Getdecyph, write=Setdecyph };

} ;

// choose a byte order for your hardware
#define ORDER_DCBA	// chosing Intel in this case

#ifdef ORDER_DCBA  	// DCBA - little endian - intel
	union aword {
	  DWORD dword    ;
          WORD  word [2] ;
          struct {
            unsigned wrd1:16;
            unsigned wrd2:16;
          } wd ;
	  BYTE  byte [4] ;
	  struct {
	    unsigned int byte3:8;
	    unsigned int byte2:8;
	    unsigned int byte1:8;
	    unsigned int byte0:8;
	  } w;
	};
#endif

#ifdef ORDER_ABCD  	// ABCD - big endian - motorola
	union aword {
	  DWORD dword;
	  BYTE byte [4];
	  struct {
	    unsigned int byte0:8;
	    unsigned int byte1:8;
	    unsigned int byte2:8;
	    unsigned int byte3:8;
	  } w;
	};
#endif

#ifdef ORDER_BADC  	// BADC - vax
	union aword {
	  DWORD dword;
	  BYTE byte [4];
	  struct {
	    unsigned int byte1:8;
	    unsigned int byte0:8;
	    unsigned int byte3:8;
	    unsigned int byte2:8;
	  } w;
};
#endif



#endif
 