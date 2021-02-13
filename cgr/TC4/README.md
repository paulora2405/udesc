# Trabalho complementar 4 de CGR
  *Paulo roberto Albuquerque*

## Simulação de Steering Behaviours

Para executar faça:
```sh
python3 boids-simulation.py
```

A classe `Boid` tem algumas variáveis estáticas importantes:
- `max_velocity`
- `min_distance`
- `close_distance`
- `border`

Estas variáveis representam, respectivamente:
- A velocidade máxima que uma entidade pode alcançar
- A distância mínina que uma entidade tenta manter das outras
- A distância máxima para se considerar uma outra entidade como estando "próxima"
- A distância máxima que uma entidade pode chegar da borda da janela

### Dependências

O arquivo `requirements.txt` contém as dependências necessárias, e basta fazer:

```sh
$ sudo apt install freeglut3-dev
$ pip3 install -r requirements.txt
```
para intala-las automaticamente.
