#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/timer.h"

// Definição dos pinos dos LEDs e do botão
#define LED_AZUL     11
#define LED_VERMELHO 12
#define LED_VERDE    13
#define BOTAO        5

// Estado para bloquear novos cliques até o ciclo ser concluído
volatile bool ciclo_em_execucao = false;

// Callback para desligar o LED Verde (Fim do ciclo)
int desligar_led_verde_callback(alarm_id_t id, void *user_data) {
    gpio_put(LED_VERDE, 0);
    ciclo_em_execucao = false; // Libera o botão para novo ciclo
    printf(" Sequência finalizada! Pronto para nova ativação.\n");
    return 0;
}

// Callback para desligar o LED Vermelho e ligar o Verde
int desligar_led_vermelho_callback(alarm_id_t id, void *user_data) {
    gpio_put(LED_VERMELHO, 0);
    gpio_put(LED_VERDE, 1);
    printf(" LED Verde ligado!\n");

    // Agenda o desligamento do Verde após 3s
    add_alarm_in_ms(3000, (alarm_callback_t)desligar_led_verde_callback, NULL, false);
    return 0;
}

// Callback para desligar o LED Azul e ligar o Vermelho
int desligar_led_azul_callback(alarm_id_t id, void *user_data) {
    gpio_put(LED_AZUL, 0);
    gpio_put(LED_VERMELHO, 1);
    printf("LED Vermelho ligado!\n");

    // Agenda o desligamento do Vermelho após 3s
    add_alarm_in_ms(3000, (alarm_callback_t)desligar_led_vermelho_callback, NULL, false);
    return 0;
}

// Callback para tratar o pressionamento do botão
void botao_callback(uint gpio, uint32_t events) {
    if (!ciclo_em_execucao) { 
        ciclo_em_execucao = true; // Bloqueia novos cliques

        // Liga todos os LEDs inicialmente
        gpio_put(LED_AZUL, 1);
        gpio_put(LED_VERMELHO, 1);
        gpio_put(LED_VERDE, 1);
        printf(" Iniciando sequência!\n");

        // Agenda o desligamento do Azul após 3s
        add_alarm_in_ms(3000, (alarm_callback_t)desligar_led_azul_callback, NULL, false);
    }
}

int main() {
    stdio_init_all(); // Inicializa comunicação serial

    // Configuração dos LEDs como saída
    gpio_init(LED_AZUL);
    gpio_set_dir(LED_AZUL, GPIO_OUT);
    gpio_init(LED_VERMELHO);
    gpio_set_dir(LED_VERMELHO, GPIO_OUT);
    gpio_init(LED_VERDE);
    gpio_set_dir(LED_VERDE, GPIO_OUT);

    // Inicializa os LEDs desligados
    gpio_put(LED_AZUL, 0);
    gpio_put(LED_VERMELHO, 0);
    gpio_put(LED_VERDE, 0);

    // Configuração do botão como entrada com pull-up
    gpio_init(BOTAO);
    gpio_set_dir(BOTAO, GPIO_IN);
    gpio_pull_up(BOTAO);

    // Configuração da interrupção no botão (com debounce simples)
    gpio_set_irq_enabled_with_callback(BOTAO, GPIO_IRQ_EDGE_FALL, true, &botao_callback);

    printf("Sistema iniciado! Pressione o botão para ativar os LEDs.\n");

    // Loop infinito para manter o programa rodando
    while (1) {
        tight_loop_contents();
    }

    return 0;
}
