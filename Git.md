## Git
***Git*** — открытая распределенная система контроля версий.  
***Repository*** — место, где хранятся и поддерживаются какие-либо данные.  
***Version Control System*** — программное обеспречение для облегчения работы с изменяющийся информацией.  
***Commit*** — объект, в котором содержится описание изменений, которые были внеены в код.  

<br/>

Возможности:
- работа с локальными и удаленными репозиториями
- создание и слияние веток
- откат к предыдущим версиям

<br/>

***Клонирование*** — перенос информации из удаленного репозитория в локальный (скачивание репозитория на локальную машину).  
***Ветка*** — подвижний указатель на один из коммитов. Обычно ветка указывает на последний коммит в цепочке коммитов.  
***Ветка master*** — основная ветка проекта.  
Новая ветка нужна чтобы не ломать исходный код и обеспечить переключения между новым кодом и исходным кодом.

<br/>

***Push*** — отправка на сервер, в удаленный репозиторий.  
- для работы в команде, чтобы делиться своим кодом с коллегами  
- чтобы иметь резервную копию на случай потери данных на своей машине  

---

**Клонирование:**  
$ git clone [repo url]  

**Добавление:**  
$ git init  
$ git status  
$ git add .  
$ git commit -m "[commit text]"  
$ git remote add origin [repo url]  
$ git push https://[username]:[token][repo url]


