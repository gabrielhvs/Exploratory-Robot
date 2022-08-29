# Exploratory-Robot

<!---Esses são exemplos. Veja https://shields.io para outras pessoas ou para personalizar este conjunto de escudos. Você pode querer incluir dependências, status do projeto e informações de licença aqui--->

![GitHub repo size](https://img.shields.io/github/repo-size/iuricode/README-template?style=for-the-badge)
![GitHub language count](https://img.shields.io/github/languages/count/iuricode/README-template?style=for-the-badge)
![GitHub forks](https://img.shields.io/github/forks/iuricode/README-template?style=for-the-badge)
![Bitbucket open issues](https://img.shields.io/bitbucket/issues/iuricode/README-template?style=for-the-badge)
![Bitbucket open pull requests](https://img.shields.io/bitbucket/pr-raw/iuricode/README-template?style=for-the-badge)

<img src="imgs\3dModel.png" alt="exemplo imagem">

### Adjustments and improvements 

This project is still in development and the next updates will be the tasks below:

| #        | Etapas         | _Status_ |
|:--|:----------------------------|:------------------|
| 1 | Control of Engines     | <img alt="Finalizado" src="https://img.shields.io/badge/-Finalizado-brightgreen">| 
| 2 | Charge batteries on robot       | <img alt="Finalizado" src="https://img.shields.io/badge/-Finalizado-brightgreen"> |  
| 3 | Include sensors    | <img alt="Finalizado" src="https://img.shields.io/badge/-Em%20andamento-orange"> | 
| 4 | Communication with a control      | <img alt="Finalizado" src="https://img.shields.io/badge/-Não%20iniciado-red"> | 

## 💻 Before installing 

Before starting, looking if you have the following requirements:
<!---Estes são apenas requisitos de exemplo. Adicionar, duplicar ou remover conforme necessário--->
* You installed the version more recent of `Visual Studio v1.65.0` 
* * You installed the version more recent of `PlatformIO IDE v2.4.2`

## 🚀 Installing Exploratory-Robot

To install you shold follow the steps:

Linux, macOS e Windows:
```
git clone https://github.com/gabrielhvs/Exploratory-Robot.git
```

## ☕ Using libraries:

To use Sensor's libraries you should add in your code this commands:

```
#include "Sensors.hpp"
Sensor "Objet_name"(Quant., pinSensorDist, Qant., pinEnco, Qant., pinTemp);
"Object_name".begin"Sensor"(); //Start your sensor
"Object_name".read"Sensor"(); //Use your Sensor


```

To use Actuador's libraries you should add in your code this commands:

```
#include "Actuators.hpp"
Sensor "Objet_name"(pin_Left_1, pin_Left_2, pin_Right_1, pin_Right_2);
"Object_name".begin(); //Start your sensor
"Object_name"."comand"(pwm_Left, pwm_Right); //Use your Engines


```



[⬆ Voltar ao topo](#nome-do-projeto)<br>
