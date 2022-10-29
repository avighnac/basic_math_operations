#pragma once

#include <string>

std::string color(std::string text, std::string color) {
#define Black "\u001b[30m"
#define _Red "\u001b[31m"
#define _Green "\u001b[32m"
#define Yellow "\u001b[33m"
#define _Blue "\u001b[34m"
#define Magenta "\u001b[35m"
#define Cyan "\u001b[36m"
#define White "\u001b[37m"
#define Reset "\u001b[0m"

  if (color == "Black")
    return Black + text + Reset;
  else if (color == "Red")
    return _Red + text + Reset;
  else if (color == "Green")
    return _Green + text + Reset;
  else if (color == "Yellow")
    return Yellow + text + Reset;
  else if (color == "Blue")
    return _Blue + text + Reset;
  else if (color == "Magenta")
    return Magenta + text + Reset;
  else if (color == "Cyan")
    return Cyan + text + Reset;
  else if (color == "White")
    return White + text + Reset;

  return "no not a color";
}