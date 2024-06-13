#pragma once

#include <string>

using std::string;

namespace Utils {
    class String {
        public:
        static string centering(const string &str, const int& width) {
            int len = str.length();
            if(width < len) { return str; }

            int diff = width - len;
            int pad1 = diff/2;
            int pad2 = diff - pad1;
            return string(pad1, ' ') + str + string(pad2, ' ');
        }

        static char* cstring(const string& str) {
            char* result = new char[str.size()];
            for (int i = 0; i < str.size(); i++) {
                result[i] = str[i];
            }
            return result;
        }

        static string ctostr(char* str, const int& size) {
            string result;
            result.resize(size);
            for (int i = 0; i < size; i++) {
                result[i] = str[i];
            }
            return result;
        }
    };
}