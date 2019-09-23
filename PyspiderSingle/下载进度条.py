import sys
import requests
import os


def download(url, file_path):
    r = requests.get(url, stream=True, verify=False)
    total_size = int(r.headers['Content-Length'])
    temp_size = 0
    with open(file_path, "w") as f:
        for chunk in r.iter_content(chunk_size=1024):
            if chunk:
                temp_size += len(chunk)
                f.write(chunk)
                f.flush()
                done = int(50 * temp_size / total_size)
                sys.stdout.write(f"\r[{'█' * done}{' ' * (50 - done)}] {100 * temp_size / total_size}%%")
                sys.stdout.flush()
                print()
