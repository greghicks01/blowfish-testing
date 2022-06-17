//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "blowform.h"
#include "blowfish.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
        TBlowFish * b = new TBlowFish ( KeyData->Text  ) ;
        Edit1->Text = IntToStr(KeyData->Text.Length()) ;

        b->cypher = input->Text ;
        Edit2->Text = IntToStr(input->Text.Length()) ;

        Encoded->Text = b->cypher ;
        Edit3->Text = IntToStr(Encoded->Text.Length()) ;

        b->decyph = Encoded->Text ;

        Decoded->Text = b->decyph ;
        Edit4->Text = IntToStr(Encoded->Text.Length()) ;

        if ( StrToInt ( input->Text ) == StrToInt ( Decoded->Text ) )
                Shape1->Brush->Color = clLime ;
        else
                Shape1->Brush->Color = clRed ;

        delete b ;
        input->SetFocus() ; /*
        Edit1->Text = IntToStr ( KeyData->Text.Length ( ) ) ;

        if ( KeyData->Text.Length() % 2 )
                input->Text = KeyData->Text + "0" ;
        else
                input->Text = KeyData->Text ;

        Edit2->Text = IntToStr ( input->Text.Length   ( ) ) ;

        if ( input->Text.Length() % 16 )
                Encoded->Text = input->Text + AnsiString::StringOfChar( '0' , 16 - input->Text.Length() % 16 ) ;

        Edit3->Text = IntToStr ( Encoded->Text.Length   ( ) ) ;


        if ( Encoded->Text.Length() % 16 == 0  )
                Shape1->Brush->Color = clLime ;
        else
                Shape1->Brush->Color = clRed ;  */
}
//---------------------------------------------------------------------------
