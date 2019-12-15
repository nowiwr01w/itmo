### [Презентации курса](https://drive.google.com/drive/folders/17RYSmrfn_8EDJguNyN-i00T5eQgeIZwB)
### Код с лекций [тут](https://github.com/gerra/ITMO-Android-19) и [тут](https://github.com/sandwwraith/AndroidDemo-ITMO2019), а результаты курса [тут](https://docs.google.com/spreadsheets/d/176sxNf1vuFRjJK4WfWvCXKv2r7JIjDeqw0VVClP2yoM/edit#gid=0)
### Кураторы и преподаватели курса:
 * [Леонид Старцев](https://vk.com/sandwwraith) (JetBrains)
 * [Герман Бережко](https://vk.com/gerra23) (Команда ВКонтакте)
 * [Веда Воронина](https://vk.com/veda345) (Команда ВКонтакте)
 * [Валерий Маевский](https://vk.com/id52033806) (Одноклассники)

# [Weather](https://github.com/nowiwr01/itmo/tree/master/android/Weather)
Хочу добавить ещё Room, но пока что пусть будет вот так. Краткое описание:
### Что было использовано в проекте?
* ConsraintLayout
* RecyclerView + CardView
* Retrofit2
* RxJava2
### Screenshots
<div style="display:flex" >
 <img src="https://github.com/nowiwr01/itmo/blob/master/android/Weather/screenshots/1n.jpg" width="200px" style="margin: 30px;" /> 
 <img src="https://github.com/nowiwr01/itmo/blob/master/android/Weather/screenshots/1d.jpg" width="200px" style="margin: 30px;" /> 
 <img src="https://github.com/nowiwr01/itmo/blob/master/android/Weather/screenshots/2n.jpg" width="200px" style="margin: 30px;" /> 
 <img src="https://github.com/nowiwr01/itmo/blob/master/android/Weather/screenshots/2d.jpg" width="200px" style="margin: 30px;" /> 
</div>

# [Contacts](https://github.com/nowiwr01/itmo/tree/master/android/Contacts)

<img src="https://github.com/nowiwr01/itmo/blob/master/android/Contacts/Contacts.gif" width="200px" /> 

### Что нужно сделать?
  * Поиграться с разрешениями. Например, по клику на очередной item открывать звонилку, но не начинать вызов.
  * Использовать `plurals`: выводить информацию о количестве контактов.
  * Реализовать возможность поиска по имени + по номеру телефона. Показать красивый экран, если результатов нет.
  * Написать `Unit` и `Integration` тесты: проверить фильтрацию, работу кнопок, отображение экранов-заглушек.
  * Бонус: использование `CardView`
  * Бонус: `UI тесты` для пермишенов + для отображения результатов.
### Что сделано? 
  * При клике на очередной контакт открывается звонилка с номером контакта. При клике на иконку отправки открывается поле для отправки SMS с заданным текстом.
  * Работа с `plurals`: 
    * Если пользователь дал разрешение на доступ к контактам и смс, при загрузке их в `RecyclerView` высвечивается `SnakeBar` с количеством импортированных контактов.
    * Если пользователь отклонил разрешение, высвечивается `SnakeBar` с таймером на перезапрос разрешения.
    * Если пользователь нажал "Больше не спрашивать", высвечивается `SnakeBar`, который предлагает пользователю перейти в настройки и поставить разрешение вручную.
  * Работа с `SearchView`:
    * Реализован поиск по имени и номеру телефона внутри адаптера. Если совпадений при поиске нет, высвечивается красивый экран "Not Found"
    * Данные об экране "Not Found" из адаптера передаются в `MainActivity` с помощью `LocalBroadcastManager`
  * Тестирование:
    * Unit-тестирование с помощью `Robolectric`: проверка существование отдельных компонентов на экране + отображение `SearchView` при клике на иконку поиска.
    * UI-тестирование с помощью `Espresso`: проверка отображения экрана-заглушки при существовании/не существовании контактов
    * Проверка того, что пользователь дал разрешение на доступ к контактам и смс.
### Что было использовано в проекте?
  * ConsraintLayout + SearchView
  * RecyclerView + CardView + элементы Material Design (SnakeBar + отступы)
  * Robolectric и Espresso

# [Networking](https://github.com/nowiwr01/itmo/tree/master/android/Networking)
### Что нужно сделать?
  * Немного пострадать. В этой домашке ходим в сеть только через `HttpURLConnection`.
  * Взять любое API и сделать список с превьюшками. В данном проекте используется [The Open Movie Database](https://www.omdbapi.com/)
  * По клику загрузить превьюшку в новой активити в высоком качестве.
  * Приложение должно переживать перевороты.
### Что сделано? 
  * Страдаем. Получаем информацию о фильмах, используя `AsyncTask`. На одной странице по дефолту располагаются 10 фильмов по запросу. Всего страниц по умолчанию 10, если, внезапно, количество найденных фильмов по запросу меньше, чем 100, прерываем поиск.
  * Даём пользователю знать, если у него выключен интернет, показывая `Toast`.
  * Чтобы `AsyncTask` не держал ссылку на убитую активити, используем `WeakReference`. Garbage Collector соберет такие объекты, когда на них не будет жестких ссылок.
  * Кэшируем результат путём запоминания последнего запроса. Из-за предыдущего пункта при поворотах приходится делать запрос заново. 
  * Кидаемся `Broadcasts` с помощью `LocalBroadcastManager`, чтобы взаимодействовать с `Service`, в котором открываем информацию о выбранном фильме. Используем `IntentService` для выполнения задачи в другом потоке.
  * Устанавливаем `setIntentRedelivery(true)`, чтобы если система убила сервис, то перезапустила его с восстановленным значением `intent`.
### Что было использовано в проекте?
  * ConsraintLayout + SearchView + Picasso
  * RecyclerView + GridLayoutManager (разный, в зависимости от ориентации) + CardView
  * AsyncTask
  * IntentService

# [Navigation](https://github.com/nowiwr01/itmo/tree/master/android/Navigation)
### Что нужно сделать?
  * Создать 3 таба. В каждом - свой бэкстэк. 
  * Всё должно быть на фрагментах (с одной активити).
  * Кнопка “Назад” в тулбаре и системная “Назад” ведут себя одинаково: если в стеке текущего таба есть фрагменты, то выкидываем один. Иначе – или выход из приложения, или возврат на предыдущий таб с непустым стеком.
  * Стейт при повороте не должен теряться.
  * Бонус: Анимации (желательно что-то посложнее fade in и fade out).
### Что сделано? 
  * Создано 3 таба, в каждом из которых свой бэкстэк.
    * Есть контейнер `RootFragment`, в который будем складывать `ChildFragment` в зависимости от текущего таба.
    * Идентификация фрагментов производится по тегам. 
  * Системная кнопка "Назад" работает так же, как и кнопка "Назад" на `Toolbar`
    * Приложение не закрывается по клику на "Назад", пока есть хотя бы один таб с непустым стеком.
  * Анимации.
    * Для каждого таба своя [анимация](https://developer.android.com/reference/android/transition/Slide) появления и исчезновения фрагмента.
### Что было использовано в проекте?
  * ConstraintLayout
  * Fragments + Animations
