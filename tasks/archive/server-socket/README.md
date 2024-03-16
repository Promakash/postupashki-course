# EchoServer

Напишите эхо-сервер!

Сервер ждёт TCP подключения от клиента далее от него получает HTTP GET запрос.
В теле HTTP запроса содержится сообщение - вы должны отправить клиенту его же сообщение.

Не трогайте переменную stop :)

Рекомендуется написать отдельный класс - HttpParser для парсинга http.

# Доп. Литература

1) man accept, man bind, man socket
2) https://en.wikipedia.org/wiki/List_of_HTTP_header_fields
3) https://developer.mozilla.org/en-US/docs/Web/HTTP/Messages