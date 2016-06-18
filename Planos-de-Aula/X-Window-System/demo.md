# Demonstração X11

Demonstrações utilizando Ubuntu Server.

## Introdução

### Instalação

```sh
$ sudo apt-get install xorg x11-apps
```

### Execução

Para iniciar o ambiente X11 padrão, utilize o programa `startx`:

```sh
$ sudo startx
```

Caso queira customizar a inicialização do ambiente, quais aplicações abrir e onde posicionar as janelas, crie um arquivo `~/.xinitrc` e utilize o programa `xinit`:

```
xclock -d -update 1 -geometry +15+15 &
xcalc -geometry +15+50 &
xterm -geometry +300+50
```

Iniciando o ambiente customizado:

```sh
$ sudo xinit
```

### Gerenciadores de janelas

Embora seja possível utilizar o X11 sem um gerenciador de janelas, nem sempre é a maneira mais prática e flexível para o dia-a-dia. Existem [centenas de gerenciadores disponíveis](https://en.wikibooks.org/wiki/Guide_to_X11/Window_Managers). Para a demonstração, optamos por utilizar o [Tab Window Manager](https://wiki.archlinux.org/index.php/twm) (Twm) e o [Openbox](http://openbox.org/wiki/Main_Page).

```sh
$ sudo apt-get install twm
```

ou

```sh
$ sudo apt-get install openbox
```

Para gerar o menu de aplicações disponíveis (aka menu iniciar), instale o pacote `menu`:

```sh
$ sudo apt-get install menu
```

Para atualizar a listagem, utilize o comando `update-menus`:

```sh
$ sudo update-menus
```

Inicie seu ambiente gráfico:

```sh
$ sudo startx
```

## Abrir aplicações gráficas remotamente via SSH


1. Instale o pacote xauth

    ```sh
    $ sudo apt-get install xauth
    ```

2. Configure o servidor SSH para aceitar conexões que exportem saídas gráficas

    ```sh
    $ sudo vim /etc/ssh/sshd_config
    ```

    Procure o parâmetro `X11Forwarding` e altere seu valor para `yes`.

    Reinicie o servidor SSH:

    ```sh
    $ sudo service sshd restart
    ```

3. No computar remoto (de preferência Linux, uma vez que é necessário ter o X11 também instalado), realize a conexão SSH passando o parâmetro `-X`

    ```sh
    $ ssh -X usuario@host
    ```

4. Abra aplicações gráficas normalmente via linha de comando

    ```sh
    $ xedit arquivo.txt
    ```
