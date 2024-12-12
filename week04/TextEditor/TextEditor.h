#include <bits/stdc++.h>
#include <string>

class TextEditor {
   public:
    TextEditor();

    void addText(const std::string& text);
    void deleteText(int length);
    void moveCursor(int steps);
    void copy(int length);
    void paste();
    void print();

   private:
    std::list<char> text;
    std::list<char>::iterator cursor;
    std::string copiedText;
};
