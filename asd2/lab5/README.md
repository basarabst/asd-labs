# Лабораторна робота 5. Обхід графа

Метою лабораторної роботи No5. «Обхід графа» є вивчення методу
дослідження графа за допомогою обходу його вершин в глибину або в ширину.

Лабораторна робота розроблена для ОС **Windows**.

## Встановлення та компіляція
Ви повинні мати встановлений компілятор **GCC**. Для спочатку склонуйте репозиторій локально:

`git clone https://github.com/basarabst/asd2-lab5.git`

Перейдіть у папку склонованого репозиторію та, якщо ви маєте **Bush GNU**, виконайте скрипти:

`bash compile.sh`

`bash compile-output.sh`

А якщо ж ні, то скомпілюйте безпосередньо:

`gcc src/app.c src/utils/coords.c  src/utils/properties.c src/utils/dataStructures.c src/drawing/graphs.c src/drawing/edges.c -mwindows -o app.exe`

`gcc src/output.c src/utils/properties.c src/utils/dataStructures.c -o output.exe`

>Зауваження: app.exe - вікно з обходами графа, output.exe - консольний вивід матриць (варто запускати з консолі)

## Основні параметри

При виконанні лабораторної роботи була використана умова з Лаб. роботи 3, **а також**:

- Коефіцієнт для графа: **0.84**

## Матриці

### Матриця суміжності графа
![adj matrix](https://i.imgur.com/x4yAvfK.png)

### Матриця BFS-дерева обходу та матриця відповідності вершин і одержаної нумерації
![BFS matrices](https://i.imgur.com/djb5sa0.png)

### Матриця DFS-дерева обходу та матриця відповідності вершин і одержаної нумерації
![DFS matrices](https://i.imgur.com/UM0Fr1w.png)

## Графічне представлення
У **головному меню** програми оберіть конкретний обхід, який бажаєте здійснити.
Обхід відбувається поступово, крок за кроком натисканнями на кнопку **"Next"**

### Breadth-first search
![BFS-1](https://i.imgur.com/aq7x172.png)
![BFS-2](https://i.imgur.com/CfXspuk.png)
![BFS-3](https://i.imgur.com/Hcuncr6.png)

### Depth-first search
![DFS-1](https://i.imgur.com/d4YroCA.png)
![DFS-2](https://i.imgur.com/u2vxVc4.png)
![DFS-3](https://i.imgur.com/Ua7fKTa.png)
