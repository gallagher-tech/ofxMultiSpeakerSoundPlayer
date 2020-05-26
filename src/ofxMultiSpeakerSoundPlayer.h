#pragma once
#include "ofConstants.h"
#include "ofSoundPlayer.h"
#include "ofMain.h"

extern "C" {
#include "fmod.h"
#include "fmod_errors.h"
}

typedef enum {
	SPEAKER_ONE,
	SPEAKER_TWO,
	SPEAKER_THREE,
	SPEAKER_FOUR,
	SPEAKER_FIVE,
	SPEAKER_SIX,
	SPEAKER_SEVEN,
	SPEAKER_EIGHT,
	SPEAKER_NINE,
	SPEAKER_TEN,
	SPEAKER_ELEVEN,
	SPEAKER_TWELVE,
	SPEAKER_THIRTEEN,
	SPEAKER_FOURTEEN,
	SPEAKER_FIFTEEN,
	SPEAKER_SIXTEEN,
	SPEAKER_NULL = -1
} ASIO_SPEAKERS;

class ofxMultiSpeakerSoundPlayer : public ofBaseSoundPlayer
{
public:

	ofxMultiSpeakerSoundPlayer();

	//bool load(string fileName, bool stream = false)
	virtual bool load(const std::filesystem::path& fileName, bool stream = false);
	void unload();
	void play();
	// !Use this for 7.1 setup. Should be working with WDM
	void playTo(int speaker);
	// !ASIO implementation to make use of all availble audio out
	void playTo(ASIO_SPEAKERS leftSpeaker = (ASIO_SPEAKERS)-1, ASIO_SPEAKERS rightSpeaker = (ASIO_SPEAKERS)-1, float* inputLevel = nullptr);
	void stop();

	void setVolume(float vol);
	void setPan(float vol);
	void setSpeed(float spd);
	void setPaused(bool bP);
	void setLoop(bool bLp);
	void setMultiPlay(bool bMp);
	void setPosition(float pct); // 0 = start, 1 = end;
	void setPositionMS(int ms);

	float getPosition() const;
	int getPositionMS() const;
	bool isPlaying() const;
	float getSpeed() const;
	float getPan() const;
	float getVolume() const;
	bool isLoaded() const;

	static void initializeFmod();
	static void closeFmod();

private:
	bool isStreaming;
	bool bMultiPlay;
	bool bLoop;
	bool bLoadedOk;
	bool bPaused;
	float pan; // -1 to 1
	float volume; // 0 - 1
	float internalFreq; // 44100 ?
	float speed; // -n to n, 1 = normal, -1 backwards
	unsigned int length; // in samples;

	FMOD_RESULT result;
	FMOD_CHANNEL* channel;
	FMOD_SOUND* sound;

	string currentLoaded;
};
