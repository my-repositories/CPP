# Play Music Sounds (From Memory)

+ LPSTR getResource (int resourceId); <br />
SND_MONEY <br /> <br />

+ sndPlaySound (sound, SND_MEMORY | SND_ASYNC | SND_NODEFAULT); <br />
LPSTR sound = getResource (SND_MONEY); <br /> <br />

+ void mciSendString (LPCTSTR lpszCommand, NULL, NULL, NULL); <br />
open MUSIC.mp3 alias SND_MUSIC <br />
play SND_MUSIC repeat <br />
