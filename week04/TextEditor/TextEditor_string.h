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
    int cur_pos;
    std::string text_buffer;
    std::string copy_text;
};
