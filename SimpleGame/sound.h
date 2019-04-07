#include"alut.h"
#include<string>
#include<vector>
#include"al.h"
#include"alc.h"
#include<vorbis/vorbisfile.h>
using namespace std;
#ifndef SOUND_H
#define SOUND_H
#define BUFFER_SIZE 32768
#define SNUMBER 200//max Sound number
class Sound
{
private:
	string sliptFile2Ext(const char* fileName)
	{
		string fin="123";
		for(int i=2;fileName[i]!='\0';i++)
		{
			fin[0]=fileName[i-2];
			fin[1]=fileName[i-1];
			fin[2]=fileName[i];
		}
		return fin;
	}
	bool LoadOgg(char *name, vector<char> &buffer, ALenum &format, ALsizei &freq)  
{  
    int endian = 0;                         // 0 for Little-Endian, 1 for Big-Endian  
    int bitStream;  
    long bytes;  
    char array[BUFFER_SIZE];                // Local fixed size array  
    FILE *f;  
    f = fopen(name, "rb");  
    if (f == NULL)  
        return false;   
    vorbis_info *pInfo;  
    OggVorbis_File oggFile;  
    // Try opening the given file  
    if (ov_open(f, &oggFile, NULL, 0) != 0)  
        return false;   
    pInfo = ov_info(&oggFile, -1);  
    if (pInfo->channels == 1) 
        format = AL_FORMAT_MONO16;  
    else  
        format = AL_FORMAT_STEREO16;  
    freq = pInfo->rate;  
    do  
    {   
        bytes = ov_read(&oggFile, array, BUFFER_SIZE, endian, 2, 1, &bitStream);  
        if (bytes < 0)  
            {  
            ov_clear(&oggFile);   
            exit(-1);  
            }  
        buffer.insert(buffer.end(), array, array + bytes);  
    }  
    while (bytes > 0);  
    ov_clear(&oggFile);  
    return true;   
}
	ALuint source;
	ALuint buffer;

	bool allow;
public:
	Sound(char* fileName, ALint loop)
	{
		//ogg------------------------------------------------------------
		allow=true;
		string ext = sliptFile2Ext(fileName);
		if(ext == "ogg") 
		{
			ALenum	format=NULL;
			vector<char> vData;
			ALsizei freq=NULL;
			//buffer---------------------------------------------------------
			alGenBuffers(1, &buffer );
			alGenSources(1, &source );	
			alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f);  
		    alSource3f(source, AL_POSITION, 0.0f, 0.0f, 0.0f); 
			    alSourcef (source, AL_GAIN, 1.0 );  
			LoadOgg(fileName, vData, format, freq);//alGetEnumValue依赖于设备，放在device之后
			alBufferData(buffer, format, &vData[0], static_cast<ALsizei>(vData.size()), freq);
			//source----------------------------------------------------------
			alSourcei(source, AL_BUFFER, buffer);
			alSourcei(source, AL_LOOPING, loop);//loop
			float pos[]={0,0,0};
			alSourcefv(source,AL_POSITION,pos);
		}
		else if(ext == "wav") 
		{
			ALenum	format;
			ALsizei	size;
			ALsizei freq;
			ALvoid* data;
			ALboolean loop;
			//buffer---------------------------------------------------------
			alGenBuffers(1,&buffer);
			alutLoadWAVFile((ALbyte*)fileName,&format,&data,&size,&freq,&loop);
			alBufferData(buffer, format, data, size, freq);
			alutUnloadWAV(format,data,size,freq);
			//source----------------------------------------------------------
			alGenSources( 1, &source );
			alSourcei (source, AL_BUFFER,buffer);
			alSourcei(source, AL_LOOPING, loop);//loop
			float pos[]={0,0,0};
			alSourcefv(source,AL_POSITION,pos);
		}
	}
	~Sound()
	{
		alSourceStop(source);
		alDeleteSources(1, &source);
		alDeleteBuffers(1, &buffer);
	}

	void Play()
	{
		if(allow){alSourcePlay(source);}
	}
	void Stop()
	{
		alSourceStop(source);
	}	
	void Pause()
	{
		alSourceStop(source);allow=false;
	}	

	bool IsPlaying()
	{
		ALint state;
		alGetSourcei( source, AL_SOURCE_STATE, &state);
		return (state == AL_PLAYING);
	}

	void SetLoop(bool loop)//循环
	{
		alSourcei(source, AL_LOOPING, loop);//loop
	}	
	void SetVolume(float v)//音量
	{
		alSourcef(source, AL_GAIN, v); 
	}
	void SetPitch(float v)//播放速度 只能是正数
	{
		alSourcef(source,AL_PITCH, v);  //openal
	}	
	void SetPos(float a,float b,float c)//音源位置
	{
		float d[]={a,b,c};
		alSourcefv(source,AL_POSITION,d );  
	}
	void SetVel(float a,float b,float c)//音源速度
	{
				float d[]={a,b,c};
		alSourcefv(source, AL_VELOCITY, d);  
	}
	void ListenerPos(float a,float b,float c)//pos
	{
		float d[]={a,b,c};
		alListenerfv(AL_POSITION,d);  
	}
	void ListenerVel(float a,float b,float c)//speed
	{
		float d[]={a,b,c};
		alListenerfv(AL_VELOCITY, d);  
	}
	void ListenerOri(float a,float b,float c, float e,float f,float g)//由"at"和"up"向量描述的方向
	{
		ALfloat listenerOri[]={a,b,c,e,f,g}; 
		alListenerfv(AL_ORIENTATION,listenerOri);
	}
	void SetRolloff(float v)//音源衰减率,默认1
	{
		alSourcef(source, AL_ROLLOFF_FACTOR, v);
	}

	float GetPitch()//播放速度 只能是正数
	{
		float v;	
		alGetSourcef(source,AL_PITCH, &v);
		return v;
	}	
	float GetSecOffset()//播放的位置，秒
	{
		float v;		
		alGetSourcef(source,AL_SEC_OFFSET, &v);  
		return v;
	}
	float GetTimeSize()
	{
		int fre, bits, channel, size;
		alGetBufferi(buffer, AL_FREQUENCY, &fre);//bit/秒
		alGetBufferi(buffer, AL_BITS, &bits);//bit
		alGetBufferi(buffer, AL_CHANNELS, &channel);//int
		alGetBufferi(buffer, AL_SIZE, &size);//byte

		float time = 8*size / fre / bits/ channel ;
		return time;
	}

	void DopplerFacor(float v)//多普勒系数，默认1
	{
		alDopplerFactor(v);
	}
};
class SodEdit
{
private:
	static SodEdit *instance;

	ALCdevice_struct *device;
	ALCcontext_struct *context;
public:
	static SodEdit* GetInstance() { return instance; }

	int AllNum;
	bool allow;
	Sound *Sod[SNUMBER];
	Sound *Now;
	SodEdit()
	{
		device = alcOpenDevice(0);
		context = alcCreateContext(device,0);
		ALboolean initStatus = alcMakeContextCurrent(context);
		AllNum=0;allow=true;
		float pos[]={1,1,1};
		alListenerfv(AL_POSITION,pos);
	}
	~SodEdit()
	{
		alcDestroyContext(context);
		alcCloseDevice(device);
	}
	bool IsPlaying(int ID)
	{
		return (Sod[ID]->IsPlaying());
	}
	void Load(char* name,int ID)
	{
		Sod[ID]= new Sound(name,0);
		AllNum++;
	}
	void Stop(int ID)
	{	Sod[ID]->Stop();}
	void Pause(int ID)
	{	Sod[ID]->Pause();}
	void Play(int ID,bool ifloop)
	{
		if(!allow){return;}
		Sod[ID]->Play();
		Sod[ID]->SetLoop(ifloop);
	}
	void Delete(int ID)
	{delete Sod[ID];AllNum--;}
	void Change(int ID)
	{Now=Sod[ID];}
	int GetAll()
	{return AllNum;}
};
SodEdit* SodEdit::instance = new SodEdit();
#endif