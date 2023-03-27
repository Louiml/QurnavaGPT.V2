#include <iostream>
#include <string>
#include <random>
#include <ctime>
#include <fstream>
#include <map>
#include <windows.h>
#include <limits>

std::map<std::string, std::string> users;
const std::string configFile = "users.cfg";

void registerUser(std::string username, std::string password) {
  users[username] = password;
  std::ofstream file(configFile, std::ios::app);
  file << username << " " << password << std::endl;
  file.close();
  std::cout << "User registered successfully!" << std::endl;
}

void loadUsersFromConfig() {
  std::ifstream file(configFile);
  std::string line;
  while (std::getline(file, line)) {
    int spaceIndex = line.find(" ");
    std::string username = line.substr(0, spaceIndex);
    std::string password = line.substr(spaceIndex + 1);
    users[username] = password;
  }
  file.close();
}

bool login(std::string username, std::string password) {
  if (users.count(username) == 0) {
    std::cout << "Error: username not found." << std::endl;
    return false;
  }
  if (users[username] != password) {
    std::cout << "Error: incorrect password." << std::endl;
    return false;
  }
  return true;
}

void askgpt() {
  std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "Ask GPT: " << "\033[4m";
    std::string input;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, input);
    std::srand(unsigned(std::time(0)));
    std::string response;
    if (input.find("hello") != std::string::npos) {
      response = "Hi there!";
    }
    else if (input.find("thanks") != std::string::npos) {
      response = "You're welcome! If you need any more help, don't hesitate to ask.";
    } else if (input.find("what is your name") != std::string::npos) {
      response = "I'm QurnavaGPT, nice to meet you!";
    } else if (input.find("how are you") != std::string::npos) {
      std::string options[] = { "I'm good, thanks!", "I'm doing great!", "I'm feeling fantastic!", "Just surviving, thanks for asking." };
      int randomIndex = std::rand() % 4;
      response = "As an AI language model, I do not have feelings or emotions.\nI am programmed to respond to text inputs and generate text outputs based on my training data.\nBut here's a generate to \"" + input + "\":\n" + options[randomIndex];
    } else if (input.find("sup") != std::string::npos) {
      std::string options[] = { "I'm good, thanks!", "I'm doing great!", "I'm feeling fantastic!", "Just surviving, thanks for asking.", "Just hacking, How are you?" };
      int randomIndex = std::rand() % 4;
      response = options[randomIndex];
    } else if (input.find("need help") != std::string::npos) {
      std::string options[] = { "How can I assist you?", "Of course! I'd be happy to help you. What do you need help with?", "Sure! Can you please specify what you need help with? I'd be happy to assist you in any way I can.", "What happend?", "Don't care" };
      int randomIndex = std::rand() % 3;
      response = options[randomIndex];
    } else {
      response = "Sorry, I don't understand what you're saying.";
    }
    for (char c : response) {
      std::cout << "\033[0m" << "\033[1m" << c << "\033[0m" << std::flush;
      Sleep(160);
    }
    askgpt();
    std::cout << std::endl;
}

void runAfterLogin(std::string username) {
    std::cout << std::endl;
    std::cout << "Welcome " << "\033[4m" << username << "\033[0m"<< " to our weird GPT! We are grateful that you have chosen to join us and we hope that we can be of assistance to you.\n Our team is dedicated to providing the best experience possible, and we are here to help with any questions or concerns you may have.\nThank you for being a part of our community, and we look forward to serving you." << std::endl;
    askgpt();
}

int main() {
  loadUsersFromConfig();

  int choice;
  std::string username, password;

  while (true) {
    std::cout << "1. Register" << std::endl;
    std::cout << "2. Login" << std::endl;
    std::cout << "3. Quit" << std::endl;
    std::cout << "Enter your choice: ";
    std::cin >> choice;
    std::cout << std::endl;

    switch (choice) {
      case 1:
        std::cout << "Enter username: ";
        std::cin >> username;
        std::cout << "Enter password: ";
        std::cin >> password;
        registerUser(username, password);
        break;
      case 2:
        std::cout << "Enter username: ";
        std::cin >> username;
        std::cout << "Enter password: ";
        std::cin >> password;
        if (login(username, password)) {
          runAfterLogin(username);
        }
      case 3:
        return 0;
      default:
        std::cout << "Invalid choice. Try again." << std::endl;
    }
    std::cout << std::endl;
  }
  return 0;
}
