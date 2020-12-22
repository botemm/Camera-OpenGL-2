//===================================================================================
//===================================================================================
//Автор: Писанка Юрій Валентинович
//Рік 2017
//Правка 2020
//Вироблено Християнином
//Опис: Класс камера, призначений для створення віртуальних камер для спрошення роботи з відображенням сцени і переміщень по ній
//
//Camera()  //Викликається для застосування камери викликається після фушкцій glViewport i  gluPerspective. Фунція застосовує параметри зміщення і повороту
//CameraR() //Окремо застосовує тільки повороти каери без зміщень
//CameraR(float X,float Y,float Z) //Теж саме що CameraR() тальки як аргументи задаються свої повороти Дані збервгаються як основні
//CameraT() //Окремо застосовує тільки зміщення каери без поворотів
//CameraT(float X,float Y,float Z) //Теж саме що CameraT() Тільки як аргументи задаються свої координати Дані збервгаються як основні
//CameraUP_Down(float ZN) //Рух камери вперед і назад залежно від того чи аргумент + чи - Сам аргумент задає швидкість Камера прекріплена до землі Вісі (x, z)
//CameraM::CameraUP_Down_VILNA  //Теж саме що CameraUP_Down(float ZN) але камера не прикріплена до чогось вільна. (Камера рухається туди куди дивиться)
//CameraRXN(float X_ZM) //Поворот по вісі X
//CameraRYN(float Y_ZM) //Поворот по вісі Y
//CameraRZN(float Z_ZM) //Поворот по вісі Z
//void CameraM::CameraLeft_Right(float ZN) //Вправо або вліво

//Прямий доступ до змінних
//	float RX,RY,RZ;  //Повороти камери
//	float TX,TY,TZ;  //Позиція камери

#pragma once
#include<GL\GL.H>
//*#include<AL\al.h>
#include<math.h>
class CameraM
{

public:

	float RX,RY,RZ;
	float TX,TY,TZ;
	float Speed;


	CameraM() //Конструктор
	{
		RX = 0;
		RY = 0;
		RZ = 0;
		TX = 0;
		TY = 1;
		TZ = 0;
	}

	void Camera()
	{
		CameraR();
		CameraT();
		Speed = 0;
	} //Примінити камкру Все

	
	void CameraR()
	{
		glRotatef(RX,1,0,0);
		glRotatef(RZ,0,0,1);
		glRotatef(RY,0,1,0);

	} //задіяти кути
	
	void CameraT(float X,float Y,float Z)
	{
		TX = X;
		TY = Y;
		TZ = Z;
		CameraT();	
	} //Задати і примінити Зміщенння


	void CameraM::CameraR(float X,float Y,float Z)
	{
		RX = X;
		RY = Y;
		RZ = Z;
		CameraR();
	} //Примінити кути вказавши їх


	void CameraT()
	{
		//*ALfloat ListenerPos[] = {TX,TY,TZ};
		//*alListenerfv(AL_POSITION,    ListenerPos);
		glTranslatef(-TX,-TY,-TZ);



	//*  ALfloat ListenerOri[] = { TX, TY, TZ,  TX - sin(6.28273/360*RY)*5, TY + sin(6.28273/360*RX)*5, TZ + cos(6.28273/360*RY)*5 };
      //*alListenerfv(AL_ORIENTATION, ListenerOri);

	} //Примінити Зміщенння
	
	void CameraM::CameraUP_Down(float ZN) //–ух вперед назад залежно в≥д значенн¤
	{
		ZN*=-1;
		TX -= (sin(6.28273/360*RY) * ZN) * Speed; 
		TZ += (cos(6.28273/360*RY) * ZN) * Speed;
		//TY += sin(6.28273/360*RX) * ZN;
	} //Рух вперед назад залежно від значення



	void CameraM::CameraLeft_Right(float ZN) //Вправо або вліво
	{
		ZN*=-1;
		TX -= (sin(6.28273/360*(RY+90)) * ZN) * Speed; 
		TZ += (cos(6.28273/360*(RY+90)) * ZN) * Speed;

	} //Вправо або вліво

	void CameraM::CameraUP_Down_VILNA(float ZN) //–ух вперед назад вверх залежно в≥д значенн¤
	{
		ZN*=-1;
		TX -= (sin(6.28273/360*RY) * ZN) * Speed; 
		TZ += (cos(6.28273/360*RY) * ZN) * Speed;
		TY += (sin(6.28273/360*RX) * ZN) * Speed;
	} //Рух вперед назад вверх залежно від значення
	

	//Повертають змінене значення
	 float CameraM::CameraRYN(float Y_ZM) //ѕовертанн¤ камери по Y
	{
		RY+=Y_ZM * Speed;
		return RY;
	}//Повертання камери по Y

	float CameraM::CameraRXN(float X_ZM) //ѕовертанн¤ камери по X
	{
		RX+=X_ZM * Speed;
		return RX;
	} //Повертання камери по X

	float CameraM::CameraRZN(float Z_ZM) //ѕовертанн¤ камери по Z
	{
		RZ+=Z_ZM * Speed;
		return RZ;
	} //Повертання камери по Z


	~CameraM() //Деструктор
	{
	}
};







class fps_us
{
private:
	//Час попереднього циклу
	double previousTime;
	//Змінна яка Яка сумує дельта тайми поки не набереться сикунда або менше залежно від коефіцієнту
	double ReadoutSum;
	//Доки дельта тайми сумуються тут рахується фпс як фоновоий буфер 
	int tempFps;
	//


public:
	//Різнця між попережнім і теперішнім часом, або скільки пройшло від менулого запуску функції
	float deltaTime; 
	//Тут буде зберігатись вже розраховане ФПС
	double fps;
	//Скільки раз в секунду оновлювати фпс рекомендоване згачення 4 а ще краще 1;
	double Cof;
	
	fps_us()
	{
		tempFps = 0;
		fps = 0;
		Cof = 4;
	}


	double fps_v(double RealTime)
	{
		
	

		deltaTime = RealTime-previousTime;

		previousTime = RealTime;

		

		if(ReadoutSum<=(1.0f/Cof))
		{
			ReadoutSum+=deltaTime;
			tempFps++;
		}
		else
		{
			fps = tempFps;
			tempFps=0;
			ReadoutSum = 0;
			fps*=Cof;
		}

		return fps;
		/*	deltaTime = (T-Temps_fps);
		Temps_fps = T;

		if(fps_t>=1000/4)
		{
			fps = fps_tt*4;
			fps_t = 0;
			fps_tt = 0;

			
		}
		else
		{
			fps_t+=deltaTime;
			fps_tt++;
		}

		return fps;*/

	}

};

