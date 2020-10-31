#pragma once
#define gTimeManager TimeManager::GetInstance()
#define gDeltaTime TimeManager::GetInstance()->GetDeltaTime()

using namespace std;
using namespace chrono;

class TimeManager
{
	private :
		TimeManager(void) ;
		~TimeManager(void);
	
	public : 
		static TimeManager* GetInstance() 
		{
		/*
			todo > GetInstance 인자로 enum 받아서 케이스처리
			todo > 게임 시간처리 / 애니메이션용 시간 처리
			todo > -시간 처리 : 최초는 스킵
		*/
			static TimeManager instance; 
			return &instance ; 
		}

	private:
		system_clock::time_point	lastTime;
		system_clock::time_point	newTime;
		duration<float>				deltaTime;
	
	public:
		void SetGameLoopStratTime();
		void SetGameLoopEndTime();
		float GetDeltaTime();
		system_clock::time_point GetCurTime();
};

