#ifndef _MIXER_H_
#define _MIXER_H_

// Store data of a single wave file read into memory.
// Space is dynamically allocated; must be freed correctly!
typedef struct {
	int numSamples;
	short *pData;
} wavedata_t;

#define MIXER_MAX_VOLUME 100



// init() must be called before any other functions,
// cleanup() must be called last to stop playback threads and free memory.
void Mixer_init(void);
void Mixer_cleanup(void);

// Read the contents of a wave file into the pSound structure. Note that
// the pData pointer in this structure will be dynamically allocated in
// readWaveFileIntoMemory(), and is freed by calling freeWaveFileData().
void Mixer_readWaveFileIntoMemory(char *fileName, wavedata_t *pSound);
void Mixer_freeWaveFileData(wavedata_t *pSound);

// Queue up another sound bite to play as soon as possible.
void Mixer_queueSound(wavedata_t *pSound);

// Get/set the volume.
// setVolume() function posted by StackOverflow user "trenki" at:
// http://stackoverflow.com/questions/6787318/set-alsa-master-volume-from-c-code
int  Mixer_getVolume();
void Mixer_setVolume(int newVolume);


#endif //_MIXER_H