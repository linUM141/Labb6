# Labb6 [![Build Status](https://travis-ci.org/linUM141/Labb6.svg?branch=master)](https://travis-ci.org/linUM141/Labb6)
Diskussioner sker under:
https://gitter.im/linUM141/Lobby

# Kom igång
Det finns tre alternativ tillgängliga för att komma igång, de listas nedan.

## Bygg bara biblioteken
Om du vill få fram en version av biblioteken så kör du:
```bash
make lib
```
Det kommer att skapa tre filer:
- libresistance.so
- libpower.so
- libcomponent.so

under mappen lib/.

### Teknisk beskrivning
Respektive komponent byggs som vanligt fast med positions oberoende kod som är ett krav för att kunna agera som ett länkningsbart bibliotek.
Växeln som används för detta är -fPIC.

Nedan är exemplet för libresistance.c: 
```bash
.
libresistance.o: lib/libresistance/libresistance.c lib/libresistance/libresistance.h
	gcc -c -fPIC lib/libresistance/libresistance.c lib/libresistance/libresistance.h
.
.
```
För att kunna skapa en *.so fil, alltså en bibliotek som länkas in dynamiskt, så måste man skapa det från objektsfilen som skapades i förra steget. Det sker genom flaggan -shared och -fPIC.

Se nedan för exempel:
```bash
.
gcc -shared -fPIC -o lib/libresistance.so libresistance.o
.
.
```

## Köra i lib och program "utvecklingsläge"
Om du vill köra i "utvecklingsläge" med lib och program kör du:
```bash
make
#samma som "make all"
```
Det som händer när ovan kommando körs är att:
- Bibloteken byggs, se ovan beskrivning(make lib).
- En version av programmet skapas och länkas hårt mot versionen av biblioteket under lib/

Kör programmet med kommandot nedan i root mappen för projektet:
```bash
./electrotest
```

### Teknisk beskrivning
Här länkas biblioteken in hårt från lib/, detta görs med flaggorna:
- -L som säger vart länkaren ska leta efter biblioteken
- -Wl,-rpath= som pekar ut vart programmet ska titta efter biblioteket vid exekvering

Se nedan för exempel:
```bash
gcc -L./lib -Wall -o electrotest main.c -lresistance -lpower -lcomponent -Wl,-rpath=./lib
```

## Installera program
Här installeras programmet och biblioteken i de publika mapparna på datorn.

Programmet installeras under:/usr/local/bin/

Biblioteket installeras under:/usr/lib/

För att installera:
```bash
make install
```

För att köra programmet:
```bash
electrotest
```
### Teknisk beskrivninga
Här utförs i princip samma sak som när utvecklings versionen av programmet och biblioteken skapas. Den stora skillnaden är:
- lib filerna kopieras in i de publika mapparna
- programmet länkas mot de publika mapparna på datorn
- programmet kopieras till de publika mapparna på datorn

Då default beteendet vid länkning och vart man ska titta efter *.so filer i gcc är att titta i de publika mapparna så tar vi mer eller mindre bort de specificerande flaggorna som vi hade när vi länkade utvecklingsprogrammet.

Se nedan för exempel:
```bash
gcc -Wall -o electrotest main.c -lresistance -lpower -lcomponent
```

## Avinstallera program
Här avinstalleras programmet och biblioteken ifrån de publika mapparna på datorn.

Programmet tas bort från: /usr/local/bin/

Biblioteket tas bort från: /usr/lib/

För att avinstallera:
```bash
make uninstall
```