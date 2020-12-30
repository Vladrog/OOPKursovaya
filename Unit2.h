//---------------------------------------------------------------------------

#ifndef Unit2H
#define Unit2H
//---------------------------------------------------------------------------

class Potensial{
	protected:
		struct Point
		{
			int X_cord;
            int Y_cord;
			int X_point;
			int Y_point;
			float Phi_point;
		};
		Point arr[100];

	public:

	 Potensial(){};
	~Potensial(){};

		 int nlines = 0; //количество строк

         	void ReadFile();	//Чтение файла
		void WriteToFile();    //Запись в файл
		void Add(int X_point,int Y_point,int X_cord,int Y_cord);

		float PhiCount(float x,float y,float minusX[81] ,float minusY[81],float plusX[81] ,float plusY[81] ,int elAmount ,float k,float tau) ;
		float TauCount(float minusX[81] , float minusY[81] ,float plusX[81] ,float plusY[81] ,int elAmount ,float k,float dphi ,float r );
		float PhiMain(float x,float y);

		int get_X(int n);
		int get_Y(int n);
		double get_Phi(int n);

};
#endif
