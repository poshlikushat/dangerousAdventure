# dangerousAdventure
# Спецификация игры
## Описание концепции
Игра представляет собой экшн с элементами стелса, где игрок управляет одним
персонажем, исследующим уровни, наполненные противниками. Игровой
процесс разделен на две фазы: начальная фаза предполагает скрытное
прохождение, где игрок должен избегать обнаружения, после чего действие
переходит в динамичные сражения с множеством противников.
## Техническая реализация
Игра использует 2.5D перспективу - двухмерные спрайты персонажей и
объектов размещаются на псевдотрёхмерных уровнях с имитацией глубины
пространства. Стены и другие вертикальные поверхности отрисовываются с
учётом перспективы. Для реализации используются библиотеки SDL2 и
SDL2_Image.
## Функционал
### Обязательные механики
- Передвижение персонажа по уровню
- Подбор оружия с уровня
- Туман войны для ограничения видимости
- Реализация pathfinding на основе алгоритма A*
### Механики, требующие проработки
- Система выпадения оружия с противников
- Детальное описание стелс-механик и условий их работы
- Условия и механика переключения между стелс и боевыми фазами
- Типы доступного оружия и их характеристики
Для дальнейшей разработки необходимо:
1. Определить приоритетность механик для первой версии игры
2. Детализировать каждую из обязательных механик
3. Придумать название, отражающее суть игрового процесса
