# Práctica 4

## Instalando Haskell en la máquina local

Entrar a la pagina oficial del [instalador de Haskell](https://www.haskell.org/ghcup/).

Abrir una ventana de _PowerShell_ y ejecutar el comando de instalación que nos

```sh
Set-ExecutionPolicy Bypass -Scope Process -Force;[System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072; try { & ([ScriptBlock]::Create((Invoke-WebRequest https://www.haskell.org/ghcup/sh/bootstrap-haskell.ps1 -UseBasicParsing))) -Interactive -DisableCurl } catch { Write-Error $_ }
```

> Nota: El comando mostrado arriba podría estar desactualizado, siempre usa el que provea la página oficial.

Al ejecutar el comando se mostraran una serie de preguntas en la interfaz de linea de comandos, seleccionar como se muestra:

- Directorio de instalación de _msys64_ dejar por defecto, solo precionar `ENTER`
- Directorio de instalación de _ghc_ dejar por defecto, solo precionar `ENTER`
- Cuando pregunte sobre si instalar algun módulo darle `Y` y `ENTER`
- Cuando pregunte sobre crear accesos directos en el escritorio es a tu consideración, yo le doy `N` y `ENTER`

> Nota: El antivirus y la conexión a internet podría interferir con la instalación, considerarlo y de ser necesario ejecutar el comando de instalación multiples veces.

En el proceso se abrirá una nueva ventana de _MSYS64_ para continuar, solo dejar que continue y darle `Y` o `ENTER` donde sea necesario. Al final deberia de decirte que preciones una tecla para terminar.

### Verificando la instalación

Una formad e verificar que la instalación fue exitosa es abrir una ventana de *git_bash* y ejecutar `ghc --version`, `ghc` es el comando que ejecuta el compilador de Haskell.

Si el comando regresa algo como el mensaje de abajo quiere decir que podemos comenzar, si no es así vuelve a ejecutar el comando.

```sh
$ ghc --version
The Glorious Glasgow Haskell Compilation System, version 9.6.7
```

## Instalando Haskell con Docker

Primero debemos de descargar Docker Desktop en Windows (para Linux buscar más información en linea, seguro es un solo comando a ejecutar).

Durante la instalación de Docker puede que se requiera reiniciar el equipo varias veces y además actualizar o instalar WSL, el cual es el subsistema de Linux en Windows el cual nos permite tener un kernel de Linux funcional en Windows, esto es necesario ay que la mayoria de _containers_ que se ejecutan en Docker funcionan con y en Linux.

Una vez tenemos WSL y Docker Desktop funcionando en nuestra máquina podemos seguir con montar todo para desarrollar ennuestra máquina y compilar en el _container_.

Descargar o copiar la images llamada _relaxed_buck.tar_ esta imagen contiene todo lo necesario para trabajar con Haskell, esta imagen la pueden crear ustedes desde cero y mas adelante les menciono como hacerlo, pero es tardado y necesita multiples recursos.

Para montar la imagen en Docker podemos ejecutar `docker load -i relaxed_buck.tar`

> Nota: Recuerda estar dentro del directorio de la imagen en la terminal

> Nota2: La imagen ya para funcionar tiene un tamaño de ~20GB acegurate de tener el espacio

Una vez montada la imagen necesitamos la extención de `Dev Containers` en VSCode.

Copiar el folder `.devcontainer` del repositorio de la clase en tu folder del proyecto y VSCode deberia de detectarlo.

### Verificando la instalación

## Primeros pasos en Haskell

Ya que tenemos algún modo de trabajar y compilar en Haskell vamos a hacer nuestro primer programa.

Crea un nuevo folder en tu _portafolio_ donde vmaos a estar trabajando con Haskell, algunos ejemplos de nombres son _practica3_, _p3_, _haskell_, _hsworkshop_.

Entra al folder de trabajo para esta práctica y crear un nuevo archivo llamado `helloworld.hs` abrir el archivo con VSCode `code .` y poner dentro el siguiente código.

```hs
main :: IO ()
main = putStrLn "Hello, World!"
```

Esta pequeña aplicación es nuestra bienvenida a Haskell, para poder compilarlo podemos abrir la terminal (dentro del mismo VSCode `` ctrl + ` ``) y ejecutar `ghc helloworld.hs`.

Esto nos va crear multiples archivos de compilación y lo más importante un ejecutable, este último en _Git Bash_ lo identificaremos con un tono verde en su nombre (al ejecutar `ls`). Para poder ejecutar ese `.exe` vamos a instroducir el comando `./helloworld.exe`.

Felicidades, tu primer programa en Haskell deberia de haberse ejecutado.

Sigue las instrucciones de los [primeros pasos con Haskell](https://www.haskell.org/ghcup/steps/) para más información sobre como iniciar con este lenguaje.

## Aplicación en Haskell
