# Лабораторна робота 6. Мінімальний кістяк графа

Метою лабораторної роботи No6. «Мінімальний кістяк графа» є вивчення
методів розв'язання задачі знаходження мінімального кістяка графа.

Лабораторна робота розроблена для ОС **Windows**.

## Встановлення та компіляція
Ви повинні мати встановлений компілятор **GCC**. Для спочатку склонуйте репозиторій локально:

`git clone https://github.com/basarabst/asd2-lab6.git`

Перейдіть у папку склонованого репозиторію та, якщо ви маєте **Bush GNU**, виконайте скрипти:

`bash compile.sh`

`bash compile-output.sh`

А якщо ж ні, то скомпілюйте безпосередньо:

`gcc src/app.c src/utils/coords.c  src/utils/properties.c src/utils/dataStructures.c src/drawing/graphs.c src/drawing/edges.c -mwindows -o app.exe`

`gcc src/output.c src/utils/properties.c src/utils/dataStructures.c -o output.exe`

>Зауваження: app.exe - вікно з графічним представленням, output.exe - консольний вивід матриць (варто запускати з консолі)

## Основні параметри

При виконанні лабораторної роботи була використана умова з Лаб. роботи 3, **а також**:

- Коефіцієнт для графа: **0.94**
- Алгоритм: **Краскала**

## Матриця суміжності та матриця ваг
![adj matrix and weight matrix](https://github.com/basarabst/asd2-lab6/assets/114052215/dbc707cf-83b5-426d-9100-ced8e134529f)

## Графічне представлення
Виконання алгоритму відбувається поступово, крок за кроком натисканнями на кнопку **"Next"**

![Kruskal MST](https://github.com/basarabst/asd2-lab6/assets/114052215/daa45618-ea9c-4416-adae-48f5048c877e)
![Kruskal MST](https://github.com/basarabst/asd2-lab6/assets/114052215/aa443ff0-1ca2-46ae-bdbd-562d2b61d595)
![Kruskal MST](https://github.com/basarabst/asd2-lab6/assets/114052215/52f45687-54d1-4131-8829-e99d6e1a94b7)
