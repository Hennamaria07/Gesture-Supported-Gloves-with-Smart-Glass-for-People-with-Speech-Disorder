from gtts import gTTS
from io import BytesIO
from pygame import mixer
import time

def MP3Maker(_StringToTalk):
    mp3_fp = BytesIO()
    tts = gTTS(_StringToTalk, lang='en')
    tts.write_to_fp(mp3_fp)
    return mp3_fp

def speak(_StringToTalk):
    if(_StringToTalk==""):
        return
    mixer.init()
    sound = MP3Maker(_StringToTalk)
    sound.seek(0)
    mixer.music.load(sound, "mp3")
    mixer.music.play()
    while mixer.music.get_busy():
        time.sleep(0.1)

    # time.sleep(1)

# speak(" hai i am sreejith")