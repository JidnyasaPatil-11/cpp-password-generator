# C++ Password Generator

A console-based C++ application that generates random and personalized passwords and checks password strength.

## Features

- Generate random passwords
- Create personalized passwords
- Use user requirements such as a name, favorite word, date, or number
- Automatically include uppercase letters, lowercase letters, numbers, and symbols
- Check password strength
- Generate another password if the user does not like the result
- Simple and user-friendly console interface

## How It Works

The application provides three options:

1. **Generate Random Password**  
   Creates a random password based on the length entered by the user.

2. **Create Personalized Password**  
   The user can enter requirements such as a name, favorite word, date, or number. The program uses the provided information while generating the password.

3. **Check My Own Password**  
   The user can enter an existing password and check its strength.

## Technologies Used

- C++
- Standard C++ Libraries

## Password Strength

The application checks for:

- Uppercase letters
- Lowercase letters
- Numbers
- Symbols
- Password length

Based on these factors, the password is classified as:

- **STRONG**
- **MEDIUM**
- **WEAK**

## Example

### Personalized Password

```text
What are your requirements? Jid 11
Enter password length: 10

Generated Password : Jid11@Aa7
Password Strength  : STRONG
