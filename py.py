from yt_dlp import YoutubeDL
import argparse
import os

size = os.listdir('src')
sizeof_folder = len(size)

print(sizeof_folder)
parser = argparse.ArgumentParser()
parser.add_argument("url", help="NULL")
## parser.add_argument("song_name", help="NULL")

args = parser.parse_args()

ydl_opt = {
    'format': 'mp3/bestaudio/best',
    'outtmpl': f"src/{sizeof_folder + 10}.%(ext)s",

    'postprocessors': [{  # Extract audio using ffmpeg
        'key': 'FFmpegExtractAudio',
        'preferredcodec': 'mp3',
    }]
}

print(args.url)

try:
    with YoutubeDL(ydl_opt) as ydl:
        ydl.download(args.url)
except:
    print("not found")
