#include "Keyboard.h"
#include <regex>
#include <iostream>

using namespace std;
typedef pair<Color, Color> ColorPair;

regex rgbColor("[0-9a-fA-F]{6}");
regex hueColor("h(0|[1-2]\\d{0,2}|3[0-5]\\d?|3[6-9]|[4-9]\\d?)");
regex colorPair("([^-]+)-([^-]+)");

static bool isColor(const string &str) {
    return regex_match(str, rgbColor) || regex_match(str, hueColor);
}

static bool isColorPair(const string &str) {
    smatch sm;
    if (regex_match(str, sm, colorPair)) {
        return isColor(sm[1]) && isColor(sm[2]);
    } else {
        return isColor(str);
    }
}

static Color parseColor(const string &str) {
    if (regex_match(str, rgbColor)) {
        int rgb = stoi(str, nullptr, 16);
        return Color::rgb(rgb);
    }

    smatch sm;
    if (regex_match(str, sm, hueColor)) {
        int hue = stoi(sm[1]);
        return Color::hue(hue);
    }

    return Color(0, 0, 0);
}

static ColorPair parseColorPair(const string &str) {
    if (isColor(str)) {
        return make_pair(parseColor(str), Color(0, 0, 0));
    }

    smatch sm;
    if (regex_match(str, sm, colorPair)) {
        return make_pair(parseColor(sm[1]), parseColor(sm[2]));
    }
    
    return make_pair(Color(0, 0, 0), Color(0, 0, 0));
}

static void printUsage(const string &self) {
    cerr << self << " normal <left> <middle> <right>" << endl;
    cerr << self << " gaming <left>" << endl;
    cerr << self << " breathing <left> <middle> <right>" << endl;
    cerr << self << " wave <left> <middle> <right>" << endl;
    cerr << endl;
    cerr << "All colors can be specified either in HEX form (rrggbb) or as hue (hXXX)" << endl;
    cerr << "Breathing and wave mode also accepts color pairs (first-second) as argument" << endl;
}

int main(int argc, char **argv) {
    Keyboard kbd;

    if (argc == 5 && strcmp(argv[1], "normal") == 0 && isColor(argv[2]) && isColor(argv[3]) && isColor(argv[4])) {
        kbd.normal(parseColor(argv[2]), parseColor(argv[3]), parseColor(argv[4]));
    } else if (argc == 3 && strcmp(argv[1], "gaming") == 0 && isColor(argv[2])) {
        kbd.gaming(parseColor(argv[2]));
    } else if (argc == 5 && strcmp(argv[1], "breathing") == 0 && isColorPair(argv[2]) && isColorPair(argv[3]) && isColorPair(argv[4])) {
        kbd.breathing(parseColorPair(argv[2]), parseColorPair(argv[3]), parseColorPair(argv[4]));
    } else if (argc == 5 && strcmp(argv[1], "wave") == 0 && isColorPair(argv[2]) && isColorPair(argv[3]) && isColorPair(argv[4])) {
        kbd.wave(parseColorPair(argv[2]), parseColorPair(argv[3]), parseColorPair(argv[4]));
    } else {
        printUsage(argv[0]);
        return 1;
    }
    
    return 0;
}
