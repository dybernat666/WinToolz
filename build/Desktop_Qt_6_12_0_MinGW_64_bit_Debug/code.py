import os
from pathlib import Path
 
username = os.environ['USERNAME']  # берем имя юзера из переменных окружения, норм и без ошибок крч
 
# собираем путь до папки автозагрузки, raw-строка (та самая r) чтобы бэкслеши не сходили с ума
path = Path(rf"C:\Users\{username}\AppData\Roaming\Microsoft\Windows\Start Menu\Programs\Startup")
 
files = path.iterdir()  # перебираем все файлы в папке, через pathlib короче
 
for f in files:
    print(f.name)  # печатаем только имя файла, без всего пути и тд, это потом Qt заберет к себе
 
