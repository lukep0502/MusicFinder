# Music Link Finder — C++

This project is a simple C++ console application designed to help search for music links by querying a list of people stored in a JSON file. The program allows searching by either a person's full name or their unique ID, returning associated music links and user details.

## Motivation

This project was created to help my girlfriend quickly find music links by searching a JSON database of people using their name or ID. The code is written in Portuguese because it was made specifically for her. It was also a fun way to practice C++ and JSON handling.

## Features

- Search users by full name (case-insensitive and trimming whitespace).  
- Search users by unique integer ID.  
- Display user details including full name, email, and music link.  
- Handle JSON data using [nlohmann/json](https://github.com/nlohmann/json) library.  
- Supports UTF-8 encoding for accented characters.  
- Simple console interface for input and output.

## How it works

1. The program loads a JSON file containing an array of user records.  
2. Each user record contains fields such as `ID`, `Nome completo` (full name), `Email`, and `Link da música:` (music link).  
3. The user chooses whether to search by name or ID via the console menu.  
4. After inputting the search term, the program displays the matching user information or a "not found" message.  
5. The program asks if the user wants to perform another search.

## Dependencies

- C++17 compatible compiler.  
- [nlohmann/json](https://github.com/nlohmann/json) header-only JSON library.  

## Usage

- Compile the program with your favorite C++ compiler.  
- Place the JSON data file (`exemplo_aleatorio.json`) in the same directory as the executable.  
- Run the program and follow the on-screen prompts to search for music links.

## Example JSON structure

```json
[
  {
    "ID": 1,
    "Nome completo": "Lucas Almeida",
    "Email": "lucas.almeida@example.com",
    "Link da música:": "https://music.example.com/track1"
  },
]
```

Mini dictionary:

Nome = Name

Link da musica = Music link

Sim = Yes

Nao = No

Deseja continuar procurando? = Do you want to continue searching?
