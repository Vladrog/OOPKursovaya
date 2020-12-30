//---------------------------------------------------------------------------

#pragma hdrstop

#include "Unit2.h"
#include "math.h"
#include "fstream"
//---------------------------------------------------------------------------
#pragma package(smart_init)

using namespace std;


int Potensial::get_X(int n){
	return  arr[n].X_point;
}

int Potensial::get_Y(int n){
	  return  arr[n].Y_point;
}

double Potensial::get_Phi(int n){
	   return  arr[n].Phi_point;
}

void Potensial::Add(int X_point,int Y_point,int X_cord,int Y_cord){

  arr[nlines].X_point=X_point;
  arr[nlines].Y_point=X_point;
  arr[nlines].Phi_point=PhiMain(X_cord,Y_cord);

  nlines++;

}
void Potensial::ReadFile()
{

	ifstream file("protokol.txt");     // Открытие файла
	if(!file)    // Проверка на открытие(если не открылся)
	{
		ShowMessage( "Файл не не найден !");
	}
	else
	{
		for (nlines=0; !file.eof(); nlines++)//Непосредственно запись
		{   //
			file >> arr[nlines].X_point >>arr[nlines].Y_point>> arr[nlines].Phi_point;
		}

	}
	file.close(); // Закрываем файл
}

void Potensial::WriteToFile()
{
	ofstream  file("protokol.txt");     // Открытие файла
	for(int i = 0; i < nlines; i++)
	{
		file << arr[i].X_point << " " << arr[i].Y_point << " " << arr[i].Phi_point;
		if(i < nlines-1)
			file << endl;
	}
	file.close(); // Закрываем файл
}



float Potensial::TauCount(float minusX[81] , float minusY[81] ,float plusX[81] ,float plusY[81] ,int elAmount ,float k,float dphi ,float r ) {

	float minusSum=0;
	float plusSum=0;
	float sums = 0;
	float tau ;

	for (int i = 0; i < elAmount/2; i++) {
		minusSum += (log((Sqrt(pow(plusX[elAmount/4]-r-minusX[i], 2) + pow(plusY[elAmount/4]-minusY[i], 2))) / (Sqrt(pow(minusX[i], 2) + pow(minusY[i], 2)))))   ;
		plusSum += (log((Sqrt(pow(plusX[elAmount/4]-r-plusX[i], 2) + pow(plusY[elAmount/4]-plusY[i], 2))) / (Sqrt(pow(plusX[i], 2) + pow(plusY[i], 2)))))   ;
	}
	sums = sums + minusSum - plusSum  ;
	minusSum = 0                       ;
	plusSum = 0                         ;

	for (int i = 0; i < elAmount/2; i++) {
		minusSum = minusSum + (log((Sqrt(pow(plusX[elAmount/4]+r-minusX[i], 2) + pow(plusY[elAmount/4]-minusY[i], 2))) / (Sqrt(pow(minusX[i], 2) + pow(minusY[i], 2)))))  ;
		plusSum = plusSum + (log((Sqrt(pow(plusX[elAmount/4]+r-plusX[i], 2) + pow(plusY[elAmount/4]-plusY[i], 2))) / (Sqrt(pow(plusX[i], 2) + pow(plusY[i], 2)))))   ;
	}
	sums = sums + minusSum - plusSum   ;
	minusSum = 0                      ;
	plusSum = 0                        ;

	for (int i = 0; i < elAmount/2; i++) {
		minusSum += log((Sqrt(pow(minusX[elAmount/4]-r-minusX[i], 2) + pow(minusY[elAmount/4]-minusY[i], 2))) / (Sqrt(pow(minusX[i], 2) + pow(minusY[i], 2))))  ;
		plusSum += log((Sqrt(pow(minusX[elAmount/4]-r-plusX[i], 2) + pow(minusY[elAmount/4]-plusY[i], 2))) / (Sqrt(pow(plusX[i], 2) + pow(plusY[i], 2))))       ;
	}
	sums = sums - minusSum + plusSum  ;
	minusSum = 0                       ;
	plusSum = 0                         ;

	for (int i = 0; i < elAmount/2; i++) {
		minusSum += log((Sqrt(pow(minusX[elAmount/4]+r-minusX[i], 2) + pow(minusY[elAmount/4]-minusY[i], 2))) / (Sqrt(pow(minusX[i], 2) + pow(minusY[i], 2))));
		plusSum += log((Sqrt(pow(minusX[elAmount/4]+r-plusX[i], 2) + pow(minusY[elAmount/4]-plusY[i], 2))) / (Sqrt(pow(plusX[i], 2) + pow(plusY[i], 2))))      ;
	}
	sums = sums - minusSum + plusSum  ;
	sums = sums * k                    ;

	tau = dphi / sums                   ;

	return tau   ;
}

float Potensial::PhiCount(float x,float y,float minusX[81] ,float minusY[81],float plusX[81] ,float plusY[81] ,int elAmount ,float k,float tau) {
	float minusSum=0;
	float plusSum=0;
	float phi= 0;

	for (int i = 0; i < elAmount/2; i++) {
		minusSum = minusSum + (log((Sqrt(pow(x-minusX[i], 2) + pow(y-minusY[i], 2))) / (Sqrt(pow(minusX[i], 2) + pow(minusY[i], 2)))));
		plusSum = plusSum + (log((Sqrt(pow(x-plusX[i], 2) + pow(y-plusY[i], 2))) / (Sqrt(pow(plusX[i], 2) + pow(plusY[i], 2)))))  ;
	}
	phi = (2 * k * tau * minusSum) - (2 * k * tau * plusSum) ;
	return phi   ;
}



float Potensial::PhiMain(float x,float y) {
	float otrAmount= 4; // Кол-во отражений
	int elAmount=0;          // Кол- элементов
	int stolb=0;
	int  strok=0;      // Кол-во строк столбцов
	float s=12;
	float c=9;
	float b=10;
	float rr = 1.5;

	float d = s - Sqrt(pow(s, 2)-pow(rr, 2))  ;
	d = d * 3.95                   ;

	s -= d   ;
	b += d    ;

	float tau=0;
	float phi=0;
	float dphi = 13.73; // dhi- Максимальное пфи
	float k=0 ;
	k = 1.0 / (4.0 * 3.14 * 8.85 * pow(10, -12)) ;
	float phiShift=0;
	int otrAmountint = 4;
	for (int i = 1; i <= otrAmountint; i++) { // Вычисление кол-во элементов
		elAmount = elAmount + i ;

	}
	elAmount = elAmount * 16     ;
	elAmount = elAmount + 2       ;
	strok = (2 * otrAmountint) + 1 ;// ВЫчисление строк

	stolb = elAmount / strok ;// вычисление столбцов


   float minusX[81] ; // создание массивов координат
	float minusY[81]  ;
	float plusX[81]   ;
	float plusY[81]    ;


	float jFloat=0;// Счетчики
	float j1Float=0;

	float floati = 1; // для 148, 149 строчки

	if (otrAmountint%2 == 0) { // Если количество отражений кратно 2, подсчёт координат первой строки
		minusX[0] = -s - 2*b*otrAmount - 2*s*(otrAmount-1)  ;
		plusX[0] = -s - 2*b*otrAmount - 2*s*otrAmount        ;
		minusY[0] = 2 * c * otrAmount                         ;
		plusY[0] = 2 * c * otrAmount                           ;

		for (int j = 1; j < stolb/2; j++) {
			if (j%2 == 0) {
				jFloat = 0;
			} else {
				jFloat = 1;
			}
			if ((j+1)%2 == 0) {
				j1Float = 0;
			} else {
				j1Float = 1 ;
			}
			minusX[j] = minusX[j-1] + 2*b + s*4*j1Float; //(j%2)
			plusX[j] = plusX[j-1] + 2*b + s*4*jFloat    ;//((j+1)%2)
			minusY[j] = minusY[0]                        ;
			plusY[j] = plusY[0]                           ;

		}

	}

	if (otrAmountint%2 == 1) {
		minusX[0] = -s - 2*b*otrAmount - 2*s*otrAmount     ;
		plusX[0] = -s - 2*b*otrAmount - 2*s*(otrAmount-1)  ;
		minusY[0] = 2 * c * otrAmount                       ;
		plusY[0] = 2 * c * otrAmount                         ;
		for (int j = 1; j < stolb/2; j++) {
			if (j%2 == 0) {
				jFloat = 0;
			} else {
				jFloat = 1 ;
			}
			if ((j+1)%2 == 0) {
				j1Float = 0 ;
			} else {
				j1Float = 1;
			}
			minusX[j] = minusX[j-1] + 2*b + s*4*jFloat; //(j%2)
			plusX[j] = plusX[j-1] + 2*b + s*4*j1Float  ;//((j+1)%2)
			minusY[j] = minusY[0]  ;
			plusY[j] = plusY[0]     ;
		}
	}

	floati = 0   ;

	for (int i = 1; i < strok; i++) {
		floati = floati + 1        ;
		for (int j = 0; j < stolb/2; j++) {
			minusX[j+i*stolb/2] = minusX[j] ;
			plusX[j+i*stolb/2] = plusX[j]    ;
			minusY[j+i*stolb/2] = minusY[0] - (2 * c * floati);
			plusY[j+i*stolb/2] = plusY[0] - (2 * c * floati)   ;
		}
	}

	tau = TauCount(minusX, minusY, plusX, plusY, elAmount, k, dphi, rr) ;

	phiShift = PhiCount((minusX[elAmount/4]+d)+rr, minusY[elAmount/4], minusX, minusY, plusX, plusY, elAmount, k, tau)  ;

	//phiShift = (PhiCount(minusX[elAmount/4]-rr, minusY[elAmount/4], minusX, minusY, plusX, plusY, elAmount, k, tau) + PhiCount(minusX[elAmount/4]+rr, minusY[elAmount/4], minusX, minusY, plusX, plusY, elAmount, k, tau)) / 2 // подсчёт сдвига потенциала
	for (int i = 1; i < 2; i++) {

		phi = 0   ;
		float factor_x  = 0.0264 ;// Коэфициенты перевода пикселей в см
		float factor_y  = 0.0264  ;
		float bias_x  = 600.9448818898; // Формула расчитывает что начало координат в середине поля
		float bias_y  = 336.3779527559 ;// bias -  смещение чтобы начало было в левом нижнем углу

		x = round(x*factor_x-bias_x*factor_x);//, 0.05)  ;
		y = round(y*factor_y-bias_y*factor_y);//, 0.05)   ;

		if (((pow(x-(plusX[elAmount/4]-d), 2) + pow(y-plusY[elAmount/4], 2)) <= pow(rr, 2)) || ((pow(x-(minusX[elAmount/4]+d), 2) + pow(y-minusY[elAmount/4], 2)) <= pow(rr, 2))) {
			if ((pow(x-(plusX[elAmount/4]-d), 2) + pow(y-plusY[elAmount/4], 2)) <= pow(rr, 2)) {
				phi = PhiCount((plusX[elAmount/4]-d)-rr, plusY[elAmount/4], minusX, minusY, plusX, plusY, elAmount, k, tau)      ;
			}
			if ((pow(x-(minusX[elAmount/4]+d), 2) + pow(y-minusY[elAmount/4], 2)) <= pow(rr, 2) ){
				phi = PhiCount((minusX[elAmount/4]+d)+rr, minusY[elAmount/4], minusX, minusY, plusX, plusY, elAmount, k, tau)  ;
			}
			phi -= phiShift        ;

		} else {
			phi = PhiCount(x, y, minusX, minusY, plusX, plusY, elAmount, k, tau)  ;
			phi = phi - phiShift                                                 ;

		}
	}

	////////Конец функции вычисления потенциала//////////////////////////////////////////////
   //	phi = //round(phi);// 0.01);
	return phi             ;

}