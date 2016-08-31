# vitaAudio
###### *v0.5b* 

### Easy audio intergration for Vita-Homebrew projects.

Includes example

![Alt text](http://www.playlight.com.au/vita/vitaAudio/info/vitaAudio.png "")



## Prerequisites



## Building

To build the example, navigate to the directory containing `Makefile` and use the `make` command to build.

## Running

To run the example:
- send the generated `.vpk` to your vita:
	- start an FTP server on your vita.
	- upload the vpk to the vita using a FTP client.
- install the .vpk on your vita using a vpk installer (eg. VitaShell)
- a new folder will be created under `ux0:/app/` named `/VITAUDIO/`.


Original code by Marcin DrakonPL & Ogg support by Andrew Church.

## Functions
```
// initialize a vitaAudio pointer
vaudio snd_mysound;
```

```
// play WAV sound
vaudio_play_sound_wav( snd_mysound, "ux0:/data/vitaAudio/files/mysound.wav" );
```

```
// play OGG sound
vaudio_play_sound_ogg( snd_mysound, "ux0:/data/vitaAudio/files/mysound.ogg" );
```

```
// play wave background music
vaudio_play_music_wav( snd_mysound, "ux0:/data/vitaAudio/files/mysound.wav" );
```

```
// play OGG background music
vaudio_play_music_ogg( snd_mysound, "ux0:/data/vitaAudio/files/mysound.ogg" );
```




```
// stop sound or music playback
vaudio_stop( snd_mysound );
```

```
// check audio playback
vaudio_is_playing( snd_mysound );
```

```
// free resources from memory
vaudio_free( snd_mysound );
```
