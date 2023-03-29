![C++](https://img.shields.io/badge/-C++-090909?style=for-the-badge&logo=C%2b%2b&logoColor=6296CC) ![MFC](https://img.shields.io/badge/-MFC-090909?style=for-the-badge) ![MFC](https://img.shields.io/badge/-Window_App-090909?style=for-the-badge)

<h3 align="center">Endulum</h3>
<p align="center">
Анимация движения маятника с учетом трения о воздух и в подшипнике
</p>


## О проекте
Вычисления проводятся в отдельном классе RungeKutta_method, с помощью Метода Рунге — Кутты.
В отдельном потоки вызывается отрисовка, за код потока отвечает файл AnimationFlow
За отрисовку отвечает Drawer.h

Программа  имеет 2 режима
1) Анимация движения маятника и фазовая траектория
2) Исследовательский, отрисовки нескольких фазовых траекторий с разными параметрами - фазовый портрет.


## Демонстрация
Программа также позволяет варьировать параметры. 
Ниже представлен пример работы в режиме отображения траектории, с разным параметром трения о воздух.

<div align="center">

![DEMO1](https://github.com/SkorEgor/picturesgifs-for-readme/blob/RobotControl/Endulum/phase_trajectory_1.gif)
</div>


<div align="center">

![DEMO2](https://github.com/SkorEgor/picturesgifs-for-readme/blob/RobotControl/Endulum/phase_trajectory_2.gif)
</div>

Пример с фазовым портретом.

<div align="center">

![DEMO3](https://github.com/SkorEgor/picturesgifs-for-readme/blob/RobotControl/Endulum/phase_portrait.gif)
</div>
