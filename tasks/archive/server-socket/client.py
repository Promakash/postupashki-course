import sys
import random
import requests

def start_client(port):
    random_string = ''.join(random.choices('abcdefghijklmnopqrstuvwxyz', k=4096))

    url = f'http://localhost:{port}'

    response = requests.get(url, data=random_string)

    if response.text != random_string:
        print(f'{response.text} != {random_string}', file=sys.stderr)

    return response.text == random_string
    

if __name__ == "__main__":
    port = int(sys.argv[1])

    exit(int(not start_client(port)))