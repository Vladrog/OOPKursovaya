//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.cpp"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
int X_b,Y_b;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{

int rr,gg,bb;
float res;
int radius=10;

for (int i = 0; i < 1201; i += 10) {


		for (int j = 0; j < 673; j += 10) {




			  res = Test->PhiMain(i,j);


		  res = res * 100;
		  if (res > 255) {
            res = res - 255;
            if (res > 255) {
              res = res - 255;
              rr = 255;
              gg = 255;
              bb = res;
            } else {
              rr = 255;
              gg = res;
              bb = 0;
			}
		  } else {
            rr = res;
			gg = 0;
            bb = 0;
		  }
		  if (res==0) {
			  rr=0;
			  gg=0;
              bb=0;
		  }
		  if (Test->PhiMain(i,j)>13.996) {
			  rr=0;
			  gg=0;
			  bb=255;
		  }
		 Image1->Canvas->Brush->Color=(TColor)RGB(rr,gg,bb);;
		 Image1->Canvas->Ellipse(TRect(i-radius, j-radius, i+radius, j+radius))  ;
		}
	  }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Image1MouseMove(TObject *Sender, TShiftState Shift, int X,
          int Y)
{

 float factor_x  = 0.0264 ;// Коэфициенты перевода пикселей в см
	   float factor_y  = 0.0264 ;
		float bias_x  = 600.9448818898; // Формула расчитывает что начало координат в середине поля
		float bias_y  = 336.3779527559; // bias -  смещение чтобы начало было в левом нижнем углу


        X_b=X;
        Y_b=Y;
		X=((X * factor_x) * 100) / 100  ;
		Y=(((Y * factor_y - 685.3149606299 * factor_y) * 100) / 100) * (-1);

 Form1->Label1->Caption="X:="+IntToStr(X);
 Form1->Label2->Caption="Y:="+IntToStr(Y);
 Form1->Label3->Caption="Phi="+FloatToStr(Test->PhiMain(X_b,Y_b)) ;

}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
 Image1->Canvas->Pen->Color=clBlack;
 Image1->Canvas->Brush->Color=clWhite;
 Image1->Canvas->Refresh();
 Image1->Canvas->Font->Color = clRed;
for (int x = 0; x <= 1210; x += 18.89) {
		Image1->Canvas->MoveTo(x, 0);
		Image1->Canvas->LineTo(x, 680);
	  }
	  for (int y = 0; y <= 685; y += 18.89) {
		Image1->Canvas->MoveTo(0, y);
		Image1->Canvas->LineTo(1210, y);
	  }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender)
{
	Image1->Canvas->Brush->Color = clWhite; // цвет кисти — белый
 Image1->Canvas->Rectangle(0,0,1210,685);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
   Test=new Potensial;

	Image1->Canvas->Brush->Color = clWhite; // цвет кисти — белый
 Image1->Canvas->Rectangle(0,0,1210,685);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button4Click(TObject *Sender)
{

int rr,gg,bb;
float res;
int radius=10;

for (int i = 0; i < 1210; i += 10) {


		for (int j = 0; j < 685; j += 10) {


			rr=255;
			gg=255;
            bb=255;

			  res = Test->PhiMain(i,j);


		 // res = res * 100;
		  if (res==0) {
			  rr=0;
			  gg=0;
              bb=0;
		  }
		  if (Test->PhiMain(i,j)>13.996) {
			  rr=0;
			  gg=0;
			  bb=255;
		  }

          Image1->Canvas->Pen->Color=clWhite;
		 Image1->Canvas->Brush->Color=(TColor)RGB(rr,gg,bb);;
		 Image1->Canvas->Ellipse(TRect(i-radius, j-radius, i+radius, j+radius))  ;
		}
	  }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image1MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{

int x_cord;
int y_cord;

int radius=5;
 float factor_x  = 0.0264 ;// Коэфициенты перевода пикселей в см
	   float factor_y  = 0.0264 ;
float Phi= Test->PhiMain(X,Y) ;
         Image1->Canvas->Brush->Color=clGreen;
		 Image1->Canvas->Ellipse(TRect(X-radius, Y-radius, X+radius, Y+radius))  ;

         TListItem *ListItem;  // Переменная указатель типа одной строчки ListView

		x_cord=X;
        y_cord=Y;
		X=((X * factor_x) * 100) / 100  ;
		Y=(((Y * factor_y - 685.3149606299 * factor_y) * 100) / 100) * (-1);

        Test->Add(X,Y,x_cord,y_cord);

		ListItem = ListView1->Items->Add(); // Создаем новую строчку
		ListItem->Caption = X; //номер строки
		ListItem->SubItems->Add(Y);
		ListItem->SubItems->Add(Phi); // Заполняем ListItem
	 }
//---------------------------------------------------------------------------


void __fastcall TForm1::Button7Click(TObject *Sender)
{
Test->WriteToFile();
}
//---------------------------------------------------------------------------

void  TForm1::WriteToTable(TListView *LV)
{

	TListItem *ListItem;  // Переменная указатель типа одной строчки ListView

	for (int i = 0; i < Test->nlines; i++)
	{
		ListItem = LV->Items->Add(); // Создаем новую строчку
		ListItem->Caption =Test->get_X(i); //номер строки
		ListItem->SubItems->Add(Test->get_Y(i));
		ListItem->SubItems->Add(Test->get_Phi(i)); // Заполняем ListItem

	}
}

void __fastcall TForm1::Button6Click(TObject *Sender)
{
 Test->nlines=0;
 ListView1->Clear();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button5Click(TObject *Sender)
{
  Test->ReadFile();
  WriteToTable(ListView1);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button8Click(TObject *Sender)
{
Close();
}
//---------------------------------------------------------------------------

