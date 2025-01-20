# Differential Equations Project \[EN\]
A differential equation elasticity solution using the <a href="https://en.wikipedia.org/wiki/Finite_element_method">finite element method (FEM)</a> @AGH UST.

## General Information

Derivation of mathematical formulas and implementation details can be found in the `/derivation` directory. Currently, only the Polish version is available. An English version will be added soon.

To run the project, a GCC compiler and `cmake` must be installed on your system.  
- **Windows:** Requires MinGW.  
- **Linux:** GCC and `cmake` are typically pre-installed.  

For visualization, ensure Python is installed on your system.

## Running the project 

### Windows 

Open batch command line, navigate to the project directory and write
```batch
    :: Alternatively cd scripts && start run.bat
    start .\run.bat
```
### Linux 

Open your CLI, navigate to the project directory and write
```bash
    # Alternatively cd scripts && chmod +x ./run.sh &&  ./run.sh
    chmod +x ./scripts/run.sh
    ./scripts/run.sh
```

---

# Projekt Równań Różniczkowych \[PL\]
Rozwiązanie równań różniczkowych dla elastyczności przy użyciu <a href="https://pl.wikipedia.org/wiki/Metoda_element%C3%B3w_sko%C5%84czonych">metody elementów skończonych (MES)</a> @AGH UST.

## Informacje Ogólne

Wyprowadzenie wzorów matematycznych i szczegóły implementacji można znaleźć w katalogu `/derivation`.  
Obecnie dostępna jest wersja w języku polskim. Wersja angielska zostanie dodana wkrótce.

Do uruchomienia projektu wymagane jest zainstalowanie kompilatora GCC oraz `cmake`.  
- **Windows:** Wymagany MinGW.  
- **Linux:** GCC i `cmake` zazwyczaj są wstępnie zainstalowane.  

Do wizualizacji wyników należy upewnić się, że Python jest zainstalowany w systemie.

## Uruchamianie Projektu

### Windows 

1. Otwórz wiersz poleceń.  
2. Przejdź do katalogu projektu.  
3. Uruchom:  
```batch
    :: Alternatywnie cd scripts && start run.bat
    start .\run.bat
```
### Linux

1. Otwórz terminal.
2. Przejdź do katalogu projektu.
3. Uruchom
```bash
# Alternatywnie cd scripts && chmod +x ./run.sh && ./run.sh
chmod +x ./scripts/run.sh
./scripts/run.sh
```
## Lista zadań

- ✅ Napisać wyprowadzenie w języku polskim
- ⬜ Napisać wyprowadzenie w języku angielskim
- ✅ Napisać kod
- ✅ Napisać skrypty uruchamiające projekt
- ✅ Zwizualizować wyniki
- ⬜ Rozwiązać inne równania (wymaga reorganizacji projektu)