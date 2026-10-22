# Planejamento de testes – Atividade Threads

Ferramentas: placa FRDM-KL25Z, cronômetro do celular (ou vídeo em câmera lenta).
Observação: "piscar a cada X" foi implementado como troca de estado (acende/apaga) a cada X ms.
Cada LED é controlado por uma thread própria (`K_THREAD_DEFINE`).
Os dois LEDs são cores do mesmo LED RGB: com ambos acesos, a cor vista é ciano (verde + azul).

| # | Teste | Procedimento | Resultado esperado |
|---|-------|--------------|--------------------|
| 1 | Compilação | Build no PlatformIO | Compila sem erros |
| 2 | Gravação | Upload com a placa no USB | Gravação concluída, LEDs começam a piscar |
| 3 | LED verde (1 s) | Contar trocas de estado em 10 s | 10 trocas (acende 5 vezes) |
| 4 | LED azul (0,5 s) | Contar trocas de estado em 10 s | 20 trocas (acende 10 vezes) |
| 5 | Sincronia (1 s / 0,5 s) | Observar o LED verde trocar | Toda troca do verde coincide com uma troca do azul |
| 6 | Desafio – LED azul (350 ms) | Contar trocas em 10 s (vídeo ajuda) | Cerca de 28 trocas |
| 7 | Desafio – LED verde | Contar trocas em 10 s | 10 trocas, sem alteração |
| 8 | Independência das threads | Mudar só `LED2_INTERVALO_MS`, gravar e observar | Apenas o LED azul muda de ritmo; o verde continua igual |
| 9 | Reset | Apertar o botão RESET da placa | LEDs reiniciam apagados e voltam a piscar |
| 10 | Estabilidade | Deixar rodando 5 min | Ritmo constante, sem travar |
