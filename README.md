# FITMATE

> A simple console-based Gym Finder & Management tool written in C.
> Find gyms, view details (fees, rating, trainer, area), apply filters, search gyms by name with fuzzy suggestions, and add new gym entries.
> Designed as a lightweight local utility that reads/writes plain text data files (`gym_details.txt`, `users.txt`) for persistent storage.
> Ideal for learning C file I/O, sorting, searching algorithms and basic console UI.

---

## Table of Contents

* [Features](#features)
* [Quick Start](#quick-start)
* [Files & Data Format](#files--data-format)
* [Usage](#usage)
* [Functions (brief)](#functions--descriptions)
---

## Features

* Load gym records from `gym_details.txt`.
* User login & account creation stored in `users.txt` (plain text).
* List all gyms with details: name, rating, monthly/quarterly/annual fees, premiumity level, area, address, trainer, contact.
* Sort and filter gyms by rating, price (monthly/quarterly/annual) and premium level (Gold/Platinum/Diamond).
* Search gyms by name with fuzzy matching (suggestions when exact match not found).
* Add new gym entry (appends to `gym_details.txt`).
* Console-based UI with simple menu flow.

---

## Quick Start

1. Place the source file and data files in the same folder:

   * `FITMATE.c` (source)
   * `gym_details.txt` (data)
   * `users.txt` (user credentials)
2. Compile with `gcc` or your preferred C compiler.
3. Run the program from the terminal/command prompt.

*Source file used for this README and review: FITMATE.txt.* 

---

## Files & Data Format

**Required data files (plain text):**

* `gym_details.txt` — each gym is one line with fields separated by whitespace:

```
<name> <rating> <monthlyFee> <quaterlyFee> <annualFee> <premiumity> <area> <address> <trainerName> <contactNumber>
```

Example:

```
FitForce 4.5 1200 3300 12000 Gold Downtown "12,MainStreet" Rohit 9876543210
```

> Note: current code uses `scanf("%s", ...)` so whitespace in fields (e.g., address) will break parsing. See **Improvements** section.

* `users.txt` — each line:

```
<username> <password>
```

Example:

```
alice pass123
bob qwerty
```

## Usage

1. On startup you'll see the ASCII banner and menu.
2. Choose `LOGIN` or `CREATE NEW ACCOUNT`.
3. After login:

   * `LIST ALL GYMS` — show all entries
   * `APPLY FILTERS` — sort by rating/price/premiumity
   * `SEARCH GYM` — search by gym name (fuzzy suggestions)
   * `ADD YOUR GYM` — append a gym to data file
   * `LOGOUT`

---

## Functions — Descriptions


* `loadfile(Gym G[], int *count)`: Reads `gym_details.txt` line-by-line, parses fields, and populates the in-memory `G[]` array up to `MAX_GYMS`. Increments `count` for each loaded gym. Exits gracefully if the file is not found.

* `printfdetails(Gym G[], int count)`: Prints all gym records in human-readable form to the console.

* `loginUser(char username[], char password[])`: Opens `users.txt` and performs a plain-text username/password match; returns boolean success.

* `createUser()`: Prompts for a username/password; ensures username does not already exist (case-insensitive check), and appends new credentials to `users.txt`.

* `mergesort` and `merge`: A mergesort implementation used to sort gyms by monthly/quarterly/annual fees. Internally uses VLA arrays for temporary halves.

* `filters(int count)`: Console UI for sorting/filtering by rating, price, and premiumity. Uses insertion sort for rating and mergesort for price fields.

* `checklist` & `badchartable`: Implements a Boyer-Moore-like fuzzy substring search to suggest close gym names when exact match isn’t found.

* `serachGym(int count)`: Asks user for gym name; uses `checklist` suggestions and prints full details on found match.

* `addGym()`: Prompts user for all fields and appends a new line to `gym_details.txt`.

---


