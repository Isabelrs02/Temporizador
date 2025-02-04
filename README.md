README - Temporizador de LEDs com Raspberry Pi Pico W
Desenvolvedora: Isabel Rosa de Santana.

Descrição do Projeto

Este projeto implementa um temporizador para controlar o estado de três LEDs (azul, vermelho e verde) utilizando a placa Raspberry Pi Pico W. O sistema é acionado por um botão (pushbutton) e faz uso da função add_alarm_in_ms() do Pico SDK para criar atrasos temporizados entre as mudanças de estado dos LEDs.

O programa foi projetado para garantir que o botão só possa iniciar uma nova sequência após o término do ciclo atual, prevenindo múltiplos disparos enquanto o sistema está em execução.

Funcionamento

1. Inicialização:

Todos os LEDs começam a ser apagados.

Mensagem inicial exibida no monitor serial: Sistema iniciado! Pressione o botão para ativar os LEDs.

2. Ciclo de Operação:

Ao pressionar o botão:

1. Todos os LEDs acendem simultaneamente.

2. Após 3 segundos, o LED azul desliga e o LED vermelho permanece aceso.

3. Após mais 3 segundos, o LED vermelho desliga e o LED verde acende.

4. Após mais 3 segundos, o LED verde desliga e o ciclo é finalizado.

Durante o ciclo, novos pressionamentos do botão são ignorados.

3. Mensagens no Monitor Serial:

Durante o ciclo, mensagens indicativas informam o estado do sistema:

Iniciando sequência!

LED Vermelho ligado!

LED Verde ligado!

Sequência finalizada! Pronto para nova ativação.

Componentes Necessários

1. Hardware:

Raspberry Pi Pico W.

3 LEDs (azul, vermelho e verde).

3 resistores de 330 Ω.

1 botão (pushbutton).

2. Software:

Pico SDK configurado no ambiente de desenvolvimento.

Editor de código (recomendado: VS Code).

Simulador Wokwi (opcional para testes virtuais).

Esquema de Conexões

LED Azul: GPIO 11 com resistor de 330 Ω conectado ao GND.

LED Vermelho: GPIO 12 com resistor de 330 Ω conectado ao GND.

LED Verde: GPIO 13 com resistor de 330 Ω conectado ao GND.

Botão: GPIO 5 com resistor pull-up (interno).

Como Usar

1. Configure o ambiente de desenvolvimento para o Raspberry Pi Pico W com o Pico SDK.


2. Conecte os componentes seguindo o esquema descrito acima.


3. Compile e carregue o código no Raspberry Pi Pico W.


4. Abra o monitor serial para visualizar as mensagens do sistema.


5. Pressione o botão para iniciar o ciclo de ativação dos LEDs.


Requisitos e Considerações
O botão possui um debounce simples implementado por software.

O temporizador utiliza a função add_alarm_in_ms() para controlar os atrasos.

Apenas um ciclo pode ser executado por vez. Novos acionamentos do botão durante o ciclo são ignorados.

