#include <zephyr.h>             // Funções básicas do Zephyr (ex: k_msleep)
#include <device.h>             // API  para obter e usar dispositivos
#include <drivers/gpio.h>       // API para controle de GPIO

#define LED_PORT       "GPIO_1" // Nome do controlador GPIO (label no .pio\build\frdm_kl25z\zephyr\zephyr.dts)
#define LED_PIN_R        18       // Pino PTB18 onde está o LED vermelho
#define LED_PIN_G        19		// // Pino PTB19 onde está o LED verde
#define SLEEP_TIME_MS  5000    // Intervalo de piscar (milissegundos)

void main(void)
{
    const struct device *port = device_get_binding(LED_PORT);
    // Obtém ponteiro para o controlador GPIO “GPIO_1”
    // (não é feito a cada iteração para economizar chamadas)

    gpio_pin_configure(port, LED_PIN_R, GPIO_OUTPUT_ACTIVE);
    // Configura o pino "Red" como saída ativa (LED apagado ou aceso depende de pull)
	gpio_pin_configure(port, LED_PIN_G, GPIO_OUTPUT_ACTIVE);
    // Configura o pino "Green" como saída ativa (LED apagado ou aceso depende de pull)

	int state = 0;

    while (1) {
		switch (state)
		{
		case 1: // estado 1: vermelho
			gpio_pin_set(port, LED_PIN_G, 1);
			gpio_pin_set(port, LED_PIN_R, 0);
        	//Impoe o nivel do pino verde em 0 e do vermelho em 1

        	k_msleep(SLEEP_TIME_MS);
        	// Suspende a tarefa por SLEEP_TIME_MS milissegundos

			state = 2;
			break;
		case 2: // estado 2: verde
			gpio_pin_set(port, LED_PIN_R, 1);
			gpio_pin_set(port, LED_PIN_G, 0);
			// Impoe o nivel do pino verde em 1 e do vermelho em 0

			k_msleep(SLEEP_TIME_MS);
        	// Suspende a tarefa por SLEEP_TIME_MS milissegundos

			state = 3;
			break;
		case 3: // estado 3: amarelo 
			gpio_pin_set(port, LED_PIN_R, 0);
			gpio_pin_set(port, LED_PIN_G, 0);
			// Impoe o nivel do pino verde em 1 e do vermelho em 1, formando luz amarela

			k_msleep(SLEEP_TIME_MS/2);
        	// Suspende a tarefa por SLEEP_TIME_MS milissegundos

			state = 1;
			break;
		default: // estado default: amarelo piscante
		
			gpio_pin_toggle(port, LED_PIN_R);
			gpio_pin_toggle(port, LED_PIN_G);
			// Alterna o nivel do pino verde e vermelho 

			k_msleep(SLEEP_TIME_MS/2);
        	// Suspende a tarefa por SLEEP_TIME_MS milissegundos

			gpio_pin_toggle(port, LED_PIN_R);
			gpio_pin_toggle(port, LED_PIN_G);
			// Impoe o nivel do pino verde em  e do vermelho em 0

			k_msleep(SLEEP_TIME_MS/2);
        	// Suspende a tarefa por SLEEP_TIME_MS milissegundos

			state = 1;
				
			break;
		}
        
    }
}