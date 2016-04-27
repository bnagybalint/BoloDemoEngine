

#include "Assist/Common.h"
#include "Assist/Color.h"
#include "Assist/Timer.h"
#include "Assist/Vector2.h"
#include "Assist/MathCommon.h"

#include "System/WindowManager.h"

#include "Render/RenderManager.h"

#include "Audio/AudioManager.h"
#include "Audio/AudioOscillator.h"
#include "Audio/AudioBiquadFilter.h"
#include "Audio/AudioOutput.h"
#include "Audio/AudioTrack.h"
#include "Audio/AudioAdsrEnvelope.h"

#include "Graphics/GraphicsManager.h"
#include "Graphics/GraphicsCanvas.h"

struct AudioEnv {
	AudioOscillator*    osc;
	AudioBiquadFilter*  biq;
	AudioAdsrEnvelope*  adsr;
	AudioOutput*        sink;
};
AudioEnv synth;

namespace {
	uint32 float2int(float x)  { return *reinterpret_cast<uint32*>(&x); }
	float  int2float(uint32 x) { return *reinterpret_cast<float*>(&x); }
}

AudioTrack* gTrack = NULL;

void initSceneAudio()
{
	// ----- INITIALIZE SCENE -----

	synth.osc = new AudioOscillator();
	synth.biq = new AudioBiquadFilter();
	synth.adsr = new AudioAdsrEnvelope();
	synth.sink = new AudioOutput();

	synth.osc->control(0, 3);
	synth.osc->control(1, float2int(110.25f));
	synth.osc->control(3, float2int(1.0f));
	synth.osc->control(4, float2int(0.0f));
	synth.osc->control(5, float2int(0.5f));

	float biqcoeff[5];
	AudioBiquadFilter::calcCoeffs_LPF(80, 0.707f, biqcoeff);
	for (int i = 0; i < 5; i++)
		synth.biq->control(i, float2int(biqcoeff[i]));

	synth.adsr->control(1, float2int(20 / float(AUDIO_SAMPLE_FREQ)));
	synth.adsr->control(2, float2int(20 / float(AUDIO_SAMPLE_FREQ)));
	synth.adsr->control(3, float2int(0.7f));
	synth.adsr->control(4, float2int(0.8f));

#define SYNTH_CONFIG 1
#if SYNTH_CONFIG == 1
	synth.sink->addInput(synth.osc);
#elif SYNTH_CONFIG == 2
	synth.biq->addInput(synth.osc);
	synth.sink->addInput(synth.biq);
#elif SYNTH_CONFIG == 3
	synth.adsr->addInput(synth.osc);
	synth.sink->addInput(synth.adsr);
#else
#error UNKNOWN CONFIG
#endif 

	int trackStart = 0;
	int trackEnd = 10 * AUDIO_SAMPLE_FREQ;

	const int BPM = 10;
	const int seq_beats = 8;
	const int seq_layout[seq_beats] = { 1, 0, 0, 0, 0, 0, 0, 0 };
	const int seq_notes[seq_beats] = { 440, 0, 0, 0, 0, 0, 0, 0 };

	float* trackData = new float[trackEnd];
	int cur_beat = 0;
	int cur_note_rem = 0;
	int note_sustain_time = 150;
	for (int i = 0; i < trackEnd; i++)
	{
		if (i % (AUDIO_SAMPLE_FREQ / BPM) == 0)
		{
			// new beat
			synth.osc->control(1, float2int((float)seq_notes[cur_beat]));
			synth.adsr->control(0, float2int((float)seq_layout[cur_beat]));
			cur_beat = (cur_beat + 1) % seq_beats;
			cur_note_rem = note_sustain_time;
		}
		if (cur_note_rem > 0)
			cur_note_rem--;
		else
			synth.adsr->control(0, 0);

		trackData[i] = synth.sink->nextSample();
	}

	gTrack = new AudioTrack();
	gTrack->setAudioData(trackData, trackEnd);

	AudioManager::getInstance()->prepareTrack(gTrack);
	AudioManager::getInstance()->playTrack(gTrack);
}

int main()
{
	// ----- INITIALIZE ENVIRONMENT -----

	WindowManager  ::createSingletonInstance();
	RenderManager  ::createSingletonInstance();
	AudioManager   ::createSingletonInstance();
	GraphicsManager::createSingletonInstance();

	WindowManager*   windowMgr   = WindowManager::getInstance();
	RenderManager*   renderMgr   = RenderManager::getInstance();
	AudioManager*    audioMgr    = AudioManager::getInstance();
	GraphicsManager* graphicsMgr = GraphicsManager::getInstance();

	const int windowWidth = 800;
	const int windowHeight = 600;
	windowMgr->initWindow(windowWidth, windowHeight);
	//renderMgr->initDx(windowMgr->getMainWindowHandle());
	//audioMgr->init(windowMgr->getMainWindowHandle());

	graphicsMgr->init();

	// ----- PLAYGROUND -----


// 	initSceneAudio();

	// ----- ENTER MAIN LOOP -----
#if BDE_GLOBAL_FRAME_LIMITER_FPS > 0
	Timer frameTimer;
#endif
	while (true)
	{
// #if BDE_GLOBAL_FRAME_LIMITER_FPS > 0
// 		frameTimer.start();
// #endif

#if BDE_GLOBAL_ENABLE_EDITOR_FUNCTIONALITY
		// ----- PROCESS INPUT -----
		if(!windowMgr->processMessages())
			break;
#endif

		// ----- FRAME START -----

		// TODO scene

		// ----- FRAME END -----

// #if BDE_GLOBAL_FRAME_LIMITER_FPS > 0
// 		frameTimer.stop();
// 		float frameTimeMs = (float)frameTimer.getTimeMilliseconds();
// 		int sleepTimeMs = int((1000.0f / BDE_GLOBAL_FRAME_LIMITER_FPS) - frameTimeMs);
// 		if (sleepTimeMs >= 5)
// 			// sleep no less than 5ms
// 			Sleep(sleepTimeMs);
// #endif
	}

#if BDE_GLOBAL_ENABLE_NICE_DESTROY
	// SHUTDOWN

	if (gTrack)
	{
		audioMgr->stopTrack(gTrack);
		delete gTrack; gTrack = NULL;
	}

	audioMgr->shutdown();
	renderMgr->shutdownDx();
	windowMgr->shutdownWindow();

	AudioManager::destroySingletonInstance();
	RenderManager::destroySingletonInstance();
	WindowManager::destroySingletonInstance();
#endif

	return 0;
}
