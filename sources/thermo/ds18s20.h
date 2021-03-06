#ifndef __DS18S20_H__
#define __DS18S20_H__

#include <thermo/thermo-interface.h>
#include <1-wire/1-wire-interface.h>
#include <timer/timer.h>

// ВСЕ ТЕМПЕРАТУРЫ В ПАРАМЕТРАХ ФУНКЦИЙ ЗАДАЮТСЯ И ВОЗВРАЩАЮТСЯ В ФОРМАТЕ (ЗНАЧЕНИЕ * 1000)!

// Драйвер имеет 1 настроечный макрос, который может быть задан во флагах компилятора:
// DS18S20_DIRECT_POLLING
// По умолчанию (флаг не задан) драйвер создаёт задачу, опрашивающую датчик с заданной периодичностью
// и приоритетом (в параметры poll_period_ms и poll_prio функции инициализации). Температура 
// выдаётся пользовательскому коду с помощью интерфейсной функции thermo_read без задержек,
// поскольку ему отдаётся закэшированное последнее значение температуры (или код ошибки).
// Нужно иметь в виду, что период опроса не должен задаваться меньше 760 миллисекунд (датчик медленный).
// Если флаг задан, то при вызове интерфейсной функции вызывающий код будет заблокирован
// на время poll_period_ms - до завершения полного цикла чтения с датчика. В этом случае
// параметр poll_prio игнорируется.

typedef struct _ds18s20_t
{
    thermoif_t      thermoif;
    
    owif_t          *ow;
    timer_t         *timer;
    int             poll_period;
    int             cur_temp;
} ds18s20_t;


// Функция инициализации драйвера DS18S20.
// ow               - указатель на драйвер шины 1-wire.
// timer            - указатель на системный таймер для реализации ожидания.
// poll_period_ms   - период ожидания информации с датчика (период опроса).
// poll_prio        - приоритет задачи опроса (игнорируется, если задан макрос DS18S20_DIRECT_POLLING).
void ds18s20_init(ds18s20_t *ds18s20, owif_t *ow, timer_t *timer, int poll_period_ms, int poll_prio);


#endif // __DS18S20_H__
