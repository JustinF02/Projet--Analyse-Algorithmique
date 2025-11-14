# 💶 Number to French Words Converter (Algorithm Analysis)

![Status](https://img.shields.io/badge/Status-Completed-success)
![Grade](https://img.shields.io/badge/Grade-18.20%2F20-success?style=for-the-badge)
![Language](https://img.shields.io/badge/Language-C%2B%2B-blue?style=for-the-badge)
![Course](https://img.shields.io/badge/Course-Advanced_Algorithm-orange?style=for-the-badge)

A rigorous algorithmic project designed to transcribe any monetary value (between 0.01€ and 1 Billion €) into full French text, strictly adhering to French grammatical rules.

> **Context:** DUT Informatique - IUT d'Amiens 
> **Project:** Advanced Algorithm Analysis

## 👥 The Team (Group 4)

| Member |
| :--- |
| [**Justin FERDINAND**](https://github.com/JustinF02)|
| [**Maël RHUIN**](https://github.com/LIncorruptible) |
| [**Baptiste RISSE**](https://github.com/Baptiste17) |

## 🎯 Objective

The goal was to create a robust algorithm capable of converting a floating-point number (e.g., `123456789.12`) into a grammatically correct French sentence:
> *"Cent vingt-trois millions quatre cent cinquante-six mille sept cent quatre-vingt-neuf euros et douze centimes."* 

### Key Constraints Handled
The analysis focuses on specific French linguistic rules:
* **Plurals:** Handling the "s" for "cents" and "vingts" only when they end the number (e.g., *quatre-vingts* vs *quatre-vingt-trois*).
* **Invariance:** "Mille" never takes an "s".
* **The "Et" rule:** Handling specific cases like 21 (*vingt-et-un*), 31, 41, etc..
* **Complex numbers:** Managing the 70-79 (*soixante-dix*) and 90-99 (*quatre-vingt-dix*) logic.

## 🧠 Functional Analysis (FAST)

The project was built using a **Top-Down Analysis** approach, breaking the complex problem into hierarchical functions (FP, FS, FT).

### Functional Hierarchy Tree

The algorithm is structured into 4 Main Functions (FP):

* **FP 3: Input Verification** (`saisie_verification_nombre`)
    * Ensures the input is a float between 0.01 and 999,999,999.99.
* **FP 1: Decomposition** (`decomposeNombreInitial`)
    * Splits the number into a manageable array of 4 integers: `[Millions, Thousands, Hundreds, Cents]` to avoid overflow errors and simplify processing.
* **FP 2: Processing** (`traite_Nombre_Decompose`)
    * **FS 2.1:** Re-decomposes chunks into Hundreds/Tens/Units.
    * **FS 2.2:** Manages Tens/Units logic (calls sub-functions for "Et" cases and "Dix" cases).
    * **FS 2.3:** Manages Hundreds logic.
    * **FS 2.4:** Concatenates the digits into words.
* **FP 4: Display** (`affiche_Nombre`)
    * Constructs the final sentence, adding units ("Million", "Mille", "Euro") and managing final capitalizations.

## 📝 Algorithm Logic Flow

The execution follows this specific order:

1.  **User Input:** User enters a float (e.g., `123456789.12`).
2.  **Decomposition (FP1):**
    * `Partie 1 (Millions/Thousands): 123456`
    * `Partie 2 (Hundreds/Decimals): 789.12`
    * *Resulting Array:* `[123, 456, 789, 12]`
3.  **Translation (FP2):** Each cell of the array is sent to the translation engine.
    * `123` -> "cent vingt-trois"
    * `456` -> "quatre cent cinquante-six"
    * `789` -> "sept cent quatre-vingt-neuf"
    * `12` -> "douze"
4.  **Assembly (FP4):** The strings are joined with the correct units (Millions, Mille, Euros, Centimes).
    * *Result:* "Cent vingt-trois **millions** quatre cent cinquante-six **mille** sept cent quatre-vingt-neuf **euros** et douze **centimes**."

## 🛠️ Technical Stack

* **Language:** C++ (Standard I/O libraries: `cin`, `cout`).
* **Methodology:** Functional Analysis (SADT/FAST).

## 📂 Repository Structure

* `/Analysis`: Contains the functional decomposition diagrams and logic charts.
* `/Src`: Source code implementing the logic described above.

---